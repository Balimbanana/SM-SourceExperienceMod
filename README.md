# SM-SourceExperienceMod
You can see the original mod here:
https://forums.alliedmods.net/showthread.php?t=123926
The SXPM mod was originally created and abandoned by lilEzek in 2010.

The Source Experience Mod is a mod that allows players to level up by various means. There are 9 skills with one that is toggleable and currently one active skill to summon a manhack.

SXPM has setups to allow for running it on Synergy, HL2:DM, ~Obsidian~, Insurgency, and Dino D-Day.

Here are the skills:

**1 Strength** (max level 400): Start health + Strength-Level + (Strength * Awareness / 100)

**2 Superior Armor** (max level 450): Start armor + Armor-Level + (Armor * Awareness / 100)

**3 Health Regeneration** (max level 300): A chance to get 1-3 HP every second where 300 is every second

**4 Nano Armor** (max level 300): A chance to get 1-3 Armor every second where 300 is every second

**5 Ammunition Regeneration** (max level 30): Gives random ammo every 33-Ammolevel seconds

**6 Anti Gravity Device** (max level 40): Lowers your gravity while jumping by: 1 - (0.8 * AntiGravLevel/40)

**7 Speed Increase** (max level 80): If 1 is real speed: 1 + 1 * SpeedLevel/80
Toggleable via `sxpm_awareness 0`

**7 Awareness** (max level 80): Increases other skills in a small way, replaces speed if set
Toggleable via `sxpm_awareness 1`

**8 TeamPower** (max level 60): Increases health and armor for you and your teammates

**9 Block Attack** (max level 140): Every time you are hit, there is a chance between BlockLevel and 300 to be invincible.


**Commands Chat/Console**

`!sxpm` or `!sxpminfo` Displays chat commands and a menu which does most of what the other commands do.

`!selectskills` Displays level up menu, to spend skill points.
This option is also in the `!sxpm` menu.

`!spendpoints # #` Where the first number is the skill number, and the second is the amount to spend. A faster way to spend a lot of points.

`!removepoints # #` Same as spendpoints, just for removing skill points for re-allocation. If you have points in Strength, you will lose health equal to how much you take out of this skill.

`!resetskills` Takes out all skill points from all skills allowing you to re-allocate. Similar to do a removepoints on all skills.

`!playerlevels` Shows all players levels and how much TeamPower they have.

`!showexp` Shows how much XP you have gained since the start.

`!hudmsg` Allows you to set the SXPM HUD color. Accepts color names such as `red` or RGB numbers such as `255 0 0`
This option is also in the `!sxpm` menu.

`!sxpmhud` Changes the way the SXPM HUD is shown, default is `0` or `off`. This is shown by either `0` ShowHudText or `1` CreateDialog
This option is also in the `!sxpm` menu.

`drophealth` or `eyeposchk` Allows clients to heal each other and refill health/suit chargers which gives XP.

`!skills` or `!skillsinfo` Opens console and shows all skills with their descriptions.

`!mhk` or `7` on keyboard will summon a manhack if your level is high enough (or it is unlocked by QModule). Pressing 7 twice will unsummon.

`!mhkk` Unsummons manhack.

`mhkg` or `C` Will tell your manhack to go to where you are looking, or attack what you are looking at.

`!givelevel <ClientName> <Amount>` Gives your levels to another player, this is done by what XP it took to get to your current level.
So if you are level 21 and did `!givelevel Bob 1` It would give Bob the XP it took to get from level 20 to level 21.

**Server CMD's**

`setlvl <CL ID> <Amount>` Sets level by Client ID, this function is blocked while connected to an external DB.

`setlvlid <SteamID2> <Amount>` Sets level by Steam ID 2 (STEAM_0:#:#####) allows for setting offline players levels. Disabled while connected to external DB.

`sxpm_con` Checks SQL connection status and whether or not it is using the standard/failover/fallback DB's.

`reloadxpclients` This is done automatically, but if for some reason it doesn't, this will reload all clients skills.

`transferstore` Transfers currently connected clients levels/stats local server DB to an external DB.

**Databases** In the databases.cfg SXPM searches for "SXPM" and "SXPMFailover" for available databases. These setting are not required. If they are not present, SXPM will default to the local store.
When SXPM starts up, it will check these configs, then attempt to connect up to 4 times for "SXPM" then another 4 times to "SXPMFailover" then it will use the local database and attempt to reconnect every 10 minutes starting with "SXPM" again.


**CVar's**

`sv_propjump_enable` Enable propjump/surf, default is 0.

`sk_suitcharger_citadel_maxarmor` Sets max armor from citadel suit chargers, default is 200 This is the base max, Superior Armor will allow for more.

`sxpm_xpgain` Base EXP to scale enemies EXP value, default is 18. This does not include the XP gained on hit.

`sxpm_awareness` Enable Awareness to replace Speed, default is 1

`sxpm_hl1armor` Enable HL1 armor system to make damage to health only occur after your armor reaches 0, default is 0

`sxpm_aoexp` Enable Area of Effect experience on kill, default is 1. What this means is that players in your vicinity will gain a little XP whenever you get a kill.
The number of players in your vicinity is denoted by the number on the bottom left of your hud.

`sxpm_xpgainpermap` Sets maximum xp per map so grinding one spot is slightly harder, default is 1000. Synergy donators get 1.25* this number.

`sxpm_xpgainmaxenforce` Enforces max XP per map so reconnecting clients will still be at max, it will instead reset on map change with this active, default is 1

`sxpm_weapbon` Enable weapon bonuses, default is 1. This is for a small chance every 10 seconds that clients with certain maxed skills will get a certain weapon.

`sxpm_healsound` Change the sound played when healing other players or recharging health chargers. Default is "items/medshot4.wav"

`sxpm_storelocal` Enable local database store while connected to an external database for fallback, default is 0

`skill` In most mods, this will set the enemy difficulty. This will also scale XP gain per kill by: 1 = 1.0, 2 = 1.25, 3 = 1.5
Where 1 is easy, 2 is normal, 3 is hard. Insurgency will use `ins_bot_difficulty` instead.

**Map Makers**
You can place a blank file in modname\maps\sxpmgrav\mapname to block Anti Gravity on your maps if you prefer to not have it.
