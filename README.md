# SM-SourceExperienceMod
You can see the original mod here:
https://forums.alliedmods.net/showthread.php?t=123926
The SXPM mod was originally created and abandoned by lilEzek in 2010.

The Source Experience Mod is a mod that allows players to level up by various means. There are 9 skills with one that is toggleable and currently one active skill to summon a manhack.

SXPM has setups to allow for running it on Synergy, HL2:DM, ~Obsidian~, Insurgency, Day of Infamy, Counter-Strike: Source, Golden Eye: Source, Dino D-Day, Left 4 Dead 2, Team Fortress 2.

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

**10 Reload Speed** (max level 100): Increases reload speed up to 2x at max level.

**11 Vampire** (max level 50): Gives health on kill based on a percentage of how much damage you did to the enemy.

**12 Summon Mastery** (max level 80): Increases summons health and damage.


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

`!givexp <ClientName> <Amount>` Gives XP to another player, a different variant of givelevel, you can specify exactly how much XP you want to give, levels will be reduced if you have less than enough in the current level.

**SXPMQModule Commands**

`sxpm_quests` or `quests` Shows your currently active quests and side quests.
`sxpm_getquest` or `quest` will show available quests to be selected. You may only select one campaign quest at a time.

`!showassists` Shows assisted kills information.

`!sxpmskill` opens additional active skills menu. These skills can also be directly bound by:
- `sxpm_use_skill fireblast`
- `sxpm_use_skill snipershot`
- `sxpm_use_skill auxrefill`
- `sxpm_use_skill areaheal`
- `sxpm_use_skill rapidfire`
- `sxpm_use_skill combinecannon`

See the full descriptions of the active skills at the bottom of this page.

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

`sxpm_losexpmode` Sets whether or not deaths or suicides will minus XP, 1 is just suicides, 2 is any player deaths, 3 is just team kills, 4 is team kills and suicides, 5 is team kills suicides and regular deaths (but not people who died from team kills), default is 0

`sxpm_gamename` Sets whether or not the game description will be overriden with the first three letters of the game/mod followed by SXPM VER, default is 1

`skill` In most mods, this will set the enemy difficulty. This will also scale XP gain per kill by: 1 = 1.0, 2 = 1.25, 3 = 1.5
Where 1 is easy, 2 is normal, 3 is hard. Insurgency will use `ins_bot_difficulty` instead. L4D2 will use `z_difficulty` instead.

`sxpm_difficulty` When set to 1, it will adjust certain stats of combine and zombies and give slight random increase of health. 2 will have a 10% chance of giving enemies abilities and will be colored.

**SXPMQModule Active Skills Descriptions:**
You use completed side quests, and campaign quests as currency to buy skills.
The costs are listed in the !sxpmskill menu, these costs are only once to unlock permanently.

**Fire Blast**
- Ignites NPCs in front of you.
- Costs 5 side quests completed.
- Cooldown 20 seconds.

**Fire Blast Level 2:**
- Increased duration of ignite.
- Increased range of fire.

**Sniper Shot**
- Movement speed reduced to 0.2 while active.
- Can zoom in 3 times with right click.
- Costs 5 campaign quests completed.
- Cooldown 40 seconds.

**AUX Refill**
- Refills AUX meter immediately.
- Costs 5 side quests completed.
- Cooldown 20 seconds.

**Area Heal**
- Heals everyone (including NPCs) around you.
- Pulses every second for 10 seconds, healing 5 health and gives 1 XP per heal.
- Costs 8 side quests completed.
- Cooldown 30 seconds.

**Heal level 2:**
- Increased amount healed per wave by 2.
- Increased range of heal by 1.25x

**Rapid Fire**
- Gives rapid fire for 5 seconds.
- Reduces damage dealt by half.
- Costs 5 campaign quests completed.
- Cooldown 30 seconds.

**Combine Cannon**
- Orbital cannon that charges up and explodes from the sky.
- Cannot be fired under roofs.
- Costs 10 campaign quests completed.
- Cooldown 60 seconds.

**Cannon Level 2:**
- Increased radius of explosion by 1.2x
- Increased damage by 1.25x

# Map Makers
You can place files in modname\maps\sxpmgrav\mapname to block Anti Gravity on your maps if you prefer to not have it. (Mostly for backwards compatibility)

You can now place in a modname\maps\sxpm\mapname.txt file a list of disabled skills, one per line allowing for more specific restrictions of skills on your map:
- strength
- armor
- healthregen
- armorregen
- ammoregen
- antigravity
- awareness
- speed
- teampower
- block
- reloadspeed
- vampire
- summonmastery
