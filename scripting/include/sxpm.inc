#if defined _SXPM_included
	#endinput
#endif
#define _SXPM_included

/**
 * SXPM Query Stats enum
 */
enum SXPMStat
{
	SXPM_Strength = 1,				/**< Strength */
	SXPM_Armor = 2,					/**< Superior Armor */
	SXPM_HealthRegen = 3,			/**< Health Regen */
	SXPM_NanoArmor = 4,				/**< Nano Armor */
	SXPM_AmmoRegen = 5,				/**< Ammo Regen */
	SXPM_AntiGravity = 6,			/**< Anti-Gravity */
	SXPM_Speed = 7,					/**< Speed/Awareness */
	SXPM_Awareness = 7,				/**< Speed/Awareness */
	SXPM_TeamPower = 8,				/**< TeamPower */
	SXPM_Block = 9,					/**< Block */
	SXPM_Level = 10,					/**< Level */
	SXPM_EXP = 11,					/**< XP */
	SXPM_SkillPoints = 12,			/**< Skill Points */
	SXPM_ReloadSpeed = 13,			/**< Reload Speed */
	SXPM_Vampire = 14,				/**< Vampire */
	SXPM_SummonMastery = 15,			/**< Summon Mastery */
	/* --- */
};

/**
 * Add XP to CL
 *
 * @param client			client index
 * @param XP				amount of XP to give
 */
native void SXPM_AddXp(int client, int XP);

/**
 * Add XP above max XP per map to CL
 *
 * @param client			client index
 * @param XP				amount of XP to give
 */
native void SXPM_AddXpOverride(int client, int XP);

/**
 * Query CL stats
 *
 * @param client			client index
 * @param qstat				What to query, use SXPMStat enum
 */
native int SXPM_Stats(int client, SXPMStat qstat);


//------------------------------------------------------
// Progress bar rendering
//------------------------------------------------------
int g_SXPMBeamSprite = -1;
int g_pSXPMProgressBar[128] = {-1, ...};
stock void SXPM_Client_ProgressBar(int pPlayer, float flTime = 4.0, float flBarLength = 30.0, float flBarWidth = 0.3, int Color[4] = {0, 255, 0, 255}, float flDistFromPlayer = 20.0)
{
	// Always remove previous bar if there is one
	SXPM_Client_RemoveProgressBar(pPlayer);
	
	static float vecEyePosition[3];
	
	if (IsValidEntity(pPlayer))
	{
		GetClientEyePosition(pPlayer, vecEyePosition);
		
		int iBeam = SXPM_SetupBeamBar(flBarWidth, vecEyePosition, Color, 4);
		if (IsValidEntity(iBeam))
		{
			int iBarBox = SXPM_SetupBeamBar(flBarWidth*1.2, vecEyePosition, {55, 55, 55, 40}, 2);
			if (IsValidEntity(iBarBox))
			{
				SetEntPropEnt(iBeam, Prop_Data, "m_hEffectEntity", iBarBox);
				SetEntPropEnt(iBarBox, Prop_Data, "m_hEffectEntity", pPlayer);
				SDKHookEx(iBarBox, SDKHook_SetTransmit, SXPM_Transmit_ProgressBarBox);
			}
			
			g_pSXPMProgressBar[pPlayer] = iBeam;
			static float vecStats[3];
			vecStats[0] = flTime;
			vecStats[1] = flBarLength;
			vecStats[2] = flDistFromPlayer;
			SetEntPropVector(iBeam, Prop_Data, "m_vecMaxs", vecStats);
			SetEntPropFloat(iBeam, Prop_Data, "m_flLocalTime", GetGameTime() + flTime);
			
			SDKHookEx(iBeam, SDKHook_SetTransmit, SXPM_Transmit_ProgressBar);
		}
	}
	
	return;
}

stock int SXPM_SetupBeamBar(float flBarWidth, float vecInitOrigin[3], int Color[4], int iRenderMode)
{
	static int iBeam;
	iBeam = CreateEntityByName("beam");
	if (IsValidEntity(iBeam))
	{
		DispatchKeyValue(iBeam, "model", "sprites/laser.vmt");
		DispatchKeyValue(iBeam, "texture", "sprites/halo01.vmt");
		if (g_SXPMBeamSprite == -1)
		{
			g_SXPMBeamSprite = PrecacheModel("sprites/laserbeam.vmt");
			// sprites/laser.vmt
			
			if (g_SXPMBeamSprite == -1) g_SXPMBeamSprite = 0;
		}
		if (g_SXPMBeamSprite > 0) SetEntProp(iBeam, Prop_Data, "m_nModelIndex", g_SXPMBeamSprite);
		SetEntProp(iBeam, Prop_Data, "m_nHaloIndex", 0);
		TeleportEntity(iBeam, vecInitOrigin, NULL_VECTOR, NULL_VECTOR);
		DispatchSpawn(iBeam);
		ActivateEntity(iBeam);
		
		SetEntityRenderColor(iBeam, Color[0], Color[1], Color[2], Color[3]);
		SetEntProp(iBeam, Prop_Data, "m_nBeamType", 1);
		SetEntProp(iBeam, Prop_Data, "m_nBeamFlags", 0);
		SetEntProp(iBeam, Prop_Data, "m_nNumBeamEnts", 2);
		SetEntPropVector(iBeam, Prop_Data, "m_vecEndPos", vecInitOrigin);
		SetEntPropFloat(iBeam, Prop_Data, "m_fWidth", flBarWidth);
		SetEntPropFloat(iBeam, Prop_Data, "m_fEndWidth", flBarWidth);
		SetEntPropFloat(iBeam, Prop_Data, "m_fSpeed", 0.0);
		SetEntPropFloat(iBeam, Prop_Data,"m_flFrameRate", 0.0);
		SetEntPropFloat(iBeam, Prop_Data,"m_flHDRColorScale", 1.0);
		SetEntProp(iBeam, Prop_Data, "m_nDissolveType", -1);
		SetEntProp(iBeam, Prop_Data, "m_nRenderMode", iRenderMode);
		SetEntPropFloat(iBeam, Prop_Data, "m_fHaloScale", 0.0);
	}
	return iBeam;
}

stock void SXPM_Client_RemoveProgressBar(int iPlayer)
{
	int iEntity = -1;
	while ((iEntity = FindEntityByClassname(iEntity, "beam")) != -1)
	{
		if (IsValidEntity(iEntity))
		{
			if (HasEntProp(iEntity, Prop_Data, "m_hEffectEntity"))
			{
				if (GetEntPropEnt(iEntity, Prop_Data, "m_hEffectEntity") == iPlayer)
				{
					//PrintToServer("RemoveBar %i", iEntity);
					AcceptEntityInput(iEntity, "kill");
					if (g_pSXPMProgressBar[iPlayer] == iEntity)
						g_pSXPMProgressBar[iPlayer] = -1;
				}
			}
		}
	}
	
	if (IsValidEntity(g_pSXPMProgressBar[iPlayer]))
	{
		char szClassname[8] = "";
		if (HasEntProp(g_pSXPMProgressBar[iPlayer], Prop_Data, "m_iClassname"))
		{
			GetEntPropString(g_pSXPMProgressBar[iPlayer], Prop_Data, "m_iClassname", szClassname, sizeof(szClassname));
			if (StrEqual(szClassname, "beam", false))
				AcceptEntityInput(g_pSXPMProgressBar[iPlayer], "kill");
		}
	}
	g_pSXPMProgressBar[iPlayer] = -1;
	
	return;
}

public Action SXPM_Transmit_ProgressBarBox(int entity, int client)
{
	if (GetEntPropEnt(entity, Prop_Data, "m_hEffectEntity") == client)
	{
		return Plugin_Continue;
	}
	return Plugin_Handled;
}

public Action SXPM_Transmit_ProgressBar(int entity, int client)
{
	if (IsValidEntity(client))
	{
		if (g_pSXPMProgressBar[client] == entity)
		{
			static int iBarBox;
			static float vecStats[3];
			static float vecStart[3], vecEnd[3], vecBeamOrigin[3];
			static float vecEyeAngles[3], vecEyePosition[3];
			static float flAdjustPosition, angAdjust, flEndTime;
			
			if (IsValidEntity(entity))
			{
				flEndTime = GetEntPropFloat(entity, Prop_Data, "m_flLocalTime");
				if (GetGameTime() >= flEndTime) AcceptEntityInput(entity, "Kill");
				
				GetClientEyePosition(client, vecEyePosition);
				GetClientEyeAngles(client, vecEyeAngles);
				GetEntPropVector(entity, Prop_Data, "m_vecAbsOrigin", vecBeamOrigin);
				
				GetEntPropVector(entity, Prop_Data, "m_vecMaxs", vecStats);
				
				angAdjust = vecEyeAngles[0];
				if (angAdjust < 0.0) angAdjust = -1.0*angAdjust;
				if (angAdjust > 64.0) angAdjust = 64.0;
				vecStats[2] = (-1.0 * (vecStats[2] * angAdjust) / 90.0) + vecStats[2];
				vecStats[1] = (vecStats[1] * angAdjust) / 180.0 + vecStats[1];
				
				vecStart[0] = (vecEyePosition[0] + (vecStats[2] * Cosine(DegToRad(vecEyeAngles[1]+vecStats[1]))));
				vecStart[1] = (vecEyePosition[1] + (vecStats[2] * Sine(DegToRad(vecEyeAngles[1]+vecStats[1]))));
				// Clamp vertical position
				angAdjust = vecEyeAngles[0];
				if (angAdjust > 64.0) angAdjust = 64.0;
				else if (angAdjust < -64.0) angAdjust = -64.0;
				vecStart[2] = (vecEyePosition[2] - (vecStats[2] * Tangent(DegToRad(angAdjust))));
				
				vecEnd[0] = (vecEyePosition[0] + (vecStats[2] * Cosine(DegToRad(vecEyeAngles[1]-vecStats[1]))));
				vecEnd[1] = (vecEyePosition[1] + (vecStats[2] * Sine(DegToRad(vecEyeAngles[1]-vecStats[1]))));
				vecEnd[2] = vecStart[2];
				
				
				// Background box
				iBarBox = GetEntPropEnt(entity, Prop_Data, "m_hEffectEntity");
				if (IsValidEntity(iBarBox))
				{
					TeleportEntity(iBarBox, vecStart, NULL_VECTOR, NULL_VECTOR);
					SetEntPropVector(iBarBox, Prop_Data, "m_vecEndPos", vecEnd);
				}
				// End background box
				
				
				flAdjustPosition = GetVectorDistance(vecStart, vecEnd, false);
				angAdjust = (flAdjustPosition * (flEndTime - GetGameTime()) / vecStats[0]) - flAdjustPosition;
				
				vecEnd[0] = (vecStart[0] + (angAdjust * Cosine(DegToRad(vecEyeAngles[1]+90.0))));
				vecEnd[1] = (vecStart[1] + (angAdjust * Sine(DegToRad(vecEyeAngles[1]+90.0))));
				vecEnd[2] = vecStart[2];
				
				TeleportEntity(entity, vecStart, NULL_VECTOR, NULL_VECTOR);
				SetEntPropVector(entity, Prop_Data, "m_vecEndPos", vecEnd);
				
				return Plugin_Continue;
			}
			else AcceptEntityInput(entity, "Kill");
		}
	}
	return Plugin_Handled;
}