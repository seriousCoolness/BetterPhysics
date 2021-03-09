#include "stdafx.h"
#include "IniFile.hpp"
#include <math.h>
// or #include "stdafx.h" for previous Visual Studio versions

extern "C"
{
	bool ShowDebugInfo = false;
	bool ChangeRunCap = false;
	bool SA2JumpDash = true;
	float JumpHeavyness = 0.01f;
	float AirDeceleration = -0.019f;
	float AirControl = -0.028f;
	bool DeleteLoops = true;
	bool TweakCameras = true;

	bool ApplyPhysicsFor[8] = { 1 };
	
	bool LevelTweaks[11] = { 1 };

	float RollingSlopeInfluenceMax[8] = { 0.32f };
	float RollingSlopeInfluenceMin[8] = { 0.04f };
	float RunningSlopeInfluenceMax[8] = { 0.16f };
	float RunningSlopeInfluenceMin[8] = { 0.04f };
	float RollingDecel[8] = { -0.08f };
	float SlopeOffsetDivisor[8] = { 32.0f };
	float RunningSlopeOffset[8] = { 0.10f };
	float RollingSlopeOffset[8] = { 0.12f };

	float InitialJumpSpeed[8] = { 1.66f };

	int InitialLoopInstruction;

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
		
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		ShowDebugInfo = config->getBool("General", "Show Debug Info", false);
		ChangeRunCap = config->getBool("General", "Increase Speed Cap", false);
		SA2JumpDash = config->getBool("General", "SA2JumpDash", true);
		JumpHeavyness = config->getFloat("General", "JumpHeavyness", 0.02f);
		AirDeceleration = config->getFloat("General", "AirDeceleration", -0.019f);
		AirControl = config->getFloat("General", "AirControl", -0.028f);
		DeleteLoops = config->getBool("General", "DeleteLoops", true);
		TweakCameras = config->getBool("General", "TweakCameras", true);

		ApplyPhysicsFor[0] = config->getBool("Physics", "Sonic", true);
		ApplyPhysicsFor[2] = config->getBool("Physics", "Tails", true);
		ApplyPhysicsFor[3] = config->getBool("Physics", "Knuckles", true);
		ApplyPhysicsFor[5] = config->getBool("Physics", "Amy", true);
		ApplyPhysicsFor[7] = config->getBool("Physics", "Big", true);
		ApplyPhysicsFor[6] = config->getBool("Physics", "Gamma", true);
		
		LevelTweaks[0] = config->getBool("Levels", "Emerald Coast", true);
		LevelTweaks[1] = config->getBool("Levels", "Windy Valley", true);
		LevelTweaks[2] = config->getBool("Levels", "Twinkle Park", true);
		LevelTweaks[3] = config->getBool("Levels", "Speed Highway", true);
		LevelTweaks[4] = config->getBool("Levels", "Red Mountain", true);
		LevelTweaks[5] = config->getBool("Levels", "Sky Deck", true);
		LevelTweaks[6] = config->getBool("Levels", "Lost World", true);
		LevelTweaks[7] = config->getBool("Levels", "Ice Cap", true);
		LevelTweaks[8] = config->getBool("Levels", "Casinopolis", true);
		LevelTweaks[9] = config->getBool("Levels", "Final Egg", true);
		LevelTweaks[10] = config->getBool("Levels", "Hot Shelter", true);
		
		RollingDecel[0] = config->getFloat("Advanced", "Sonic Rolling Deceleration", -0.008f);
		RollingSlopeInfluenceMax[0] = config->getFloat("Advanced", "Sonic Max Roll Slope Influence", 0.32f);
		RollingSlopeInfluenceMin[0] = config->getFloat("Advanced", "Sonic Min Roll Slope Influence", 0.04f);
		RollingSlopeOffset[0] = config->getFloat("Advanced", "Sonic Roll Slope Influence Offset", 0.14f);
		RunningSlopeInfluenceMax[0] = config->getFloat("Advanced", "Sonic Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[0] = config->getFloat("Advanced", "Sonic Min Run Slope Influence", 0.04f);
		RunningSlopeOffset[0] = config->getFloat("Advanced", "Sonic Run Slope Influence Offset", 0.10f);
		SlopeOffsetDivisor[0] = config->getFloat("Advanced", "Sonic Slope Influence Offset Divisor", 32.00f);
		
		RollingDecel[2] = config->getFloat("Advanced", "Tails Rolling Deceleration", -0.004f);
		RollingSlopeInfluenceMax[2] = config->getFloat("Advanced", "Tails Max Roll Slope Influence", 0.16f);
		RollingSlopeInfluenceMin[2] = config->getFloat("Advanced", "Tails Min Roll Slope Influence", 0.04f);
		RollingSlopeOffset[2] = config->getFloat("Advanced", "Tails Roll Slope Influence Offset", 0.14f);
		RunningSlopeInfluenceMax[2] = config->getFloat("Advanced", "Tails Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[2] = config->getFloat("Advanced", "Tails Min Run Slope Influence", 0.00f);
		RunningSlopeOffset[2] = config->getFloat("Advanced", "Tails Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[2] = config->getFloat("Advanced", "Tails Slope Influence Offset Divisor", 30.00f);
		
		RollingDecel[3] = config->getFloat("Advanced", "Knuckles Rolling Deceleration", -0.008f);
		RollingSlopeInfluenceMax[3] = config->getFloat("Advanced", "Knuckles Max Roll Slope Influence", 0.16f);
		RollingSlopeInfluenceMin[3] = config->getFloat("Advanced", "Knuckles Min Roll Slope Influence", 0.04f);
		RollingSlopeOffset[3] = config->getFloat("Advanced", "Knuckles Roll Slope Influence Offset", 0.14f);
		RunningSlopeInfluenceMax[3] = config->getFloat("Advanced", "Knuckles Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[3] = config->getFloat("Advanced", "Knuckles Min Run Slope Influence", 0.04f);
		RunningSlopeOffset[3] = config->getFloat("Advanced", "Knuckles Run Slope Influence Offset", 0.10f);
		SlopeOffsetDivisor[3] = config->getFloat("Advanced", "Knuckles Slope Influence Offset Divisor", 30.00f);
		
		RollingDecel[5] = config->getFloat("Advanced", "Amy Rolling Deceleration (Unused)", -0.008f);
		RollingSlopeInfluenceMax[5] = config->getFloat("Advanced", "Amy Max Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeInfluenceMin[5] = config->getFloat("Advanced", "Amy Min Roll Slope Influence (Unused)", 0.04f);
		RollingSlopeOffset[5] = config->getFloat("Advanced", "Amy Roll Slope Influence Offset", 0.16f);
		RunningSlopeInfluenceMax[5] = config->getFloat("Advanced", "Amy Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[5] = config->getFloat("Advanced", "Amy Min Run Slope Influence", 0.02f);
		RunningSlopeOffset[5] = config->getFloat("Advanced", "Amy Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[5] = config->getFloat("Advanced", "Amy Slope Influence Offset Divisor", 25.00f);
		
		RollingDecel[6] = config->getFloat("Advanced", "Gamma Rolling Deceleration (Unused)", -0.008f);
		RollingSlopeInfluenceMax[6] = config->getFloat("Advanced", "Gamma Max Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeInfluenceMin[6] = config->getFloat("Advanced", "Gamma Min Roll Slope Influence (Unused)", 0.04f);
		RollingSlopeOffset[6] = config->getFloat("Advanced", "Gamma Roll Slope Influence Offset", 0.16f);
		RunningSlopeInfluenceMax[6] = config->getFloat("Advanced", "Gamma Max Run Slope Influence", 0.08f);
		RunningSlopeInfluenceMin[6] = config->getFloat("Advanced", "Gamma Min Run Slope Influence", 0.00f);
		RunningSlopeOffset[6] = config->getFloat("Advanced", "Gamma Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[6] = config->getFloat("Advanced", "Gamma Slope Influence Offset Divisor", 25.00f);
		
		RollingDecel[7] = config->getFloat("Advanced", "Big Rolling Deceleration (Unused)", -0.008f);
		RollingSlopeInfluenceMax[7] = config->getFloat("Advanced", "Big Max Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeInfluenceMin[7] = config->getFloat("Advanced", "Big Min Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeOffset[7] = config->getFloat("Advanced", "Big Roll Slope Influence Offset", 0.16f);
		RunningSlopeInfluenceMax[7] = config->getFloat("Advanced", "Big Max Run Slope Influence", 0.08f);
		RunningSlopeInfluenceMin[7] = config->getFloat("Advanced", "Big Min Run Slope Influence", 0.00f);
		RunningSlopeOffset[7] = config->getFloat("Advanced", "Big Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[7] = config->getFloat("Advanced", "Big Slope Influence Offset Divisor", 25.00f);

		delete config;

		Init_Levels(LevelTweaks, helperFunctions);

		if (ApplyPhysicsFor[0])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Sonic].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Sonic].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Sonic].MaxAccel = 3.0f;
			}

			PhysicsArray[Characters_Sonic].RollDecel = RollingDecel[0];
			PhysicsArray[Characters_Sonic].RollEnd = 1.69f;
		}
		if (ApplyPhysicsFor[2])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Tails].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Tails].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Tails].MaxAccel = 3.0f;
			}
			PhysicsArray[Characters_Tails].FloorGrip = 2;
			PhysicsArray[Characters_Tails].RollDecel = RollingDecel[2];
			PhysicsArray[Characters_Tails].RollEnd = 1.69f;
		}
		if (ApplyPhysicsFor[3])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Knuckles].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Knuckles].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Knuckles].MaxAccel = 3.0f;
			}
			PhysicsArray[Characters_Knuckles].RollDecel = RollingDecel[3];
			PhysicsArray[Characters_Knuckles].RollEnd = 1.69f;
		}
		if (ApplyPhysicsFor[5])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Amy].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Amy].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Amy].MaxAccel = 3.0f;
			}
			PhysicsArray[Characters_Amy].FloorGrip = 2;
			PhysicsArray[Characters_Amy].RollDecel = RollingDecel[5];
			PhysicsArray[Characters_Amy].RollEnd = 1.69f;
		}
		
		for (int i = 0; i < 8; i++)
		{
			InitialJumpSpeed[i] = PhysicsArray[i].JumpSpeed;
		}

		if (SA2JumpDash) 
		{
			static float dash_force = 0.98f;
			static float dash_timer = 15.0f;
			WriteData((float**)0x0049233F, &dash_force);
			WriteData((float**)0x00497BCA, &dash_timer);
		}

		if (DeleteLoops) 
		{
			InitialLoopInstruction = *(char*)0x4BB1F0;
		}

	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		// Executed every running frame of SADX
	}

	__declspec(dllexport) void __cdecl OnInput()
	{
		// Executed before the game processes input
	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		// Executed when the game processes input

		if (DeleteLoops) {
			WriteData<1>((char*)0x4BB1F0, InitialLoopInstruction);
			Delete_Splines(LevelTweaks);
		}
		
		EntityData1* data1 = EntityData1Ptrs[0];
		EntityData2* data2 = EntityData2Ptrs[0];

			if (data1 != nullptr && ApplyPhysicsFor[data1->CharID])
			{

				bool on_ground = (data1->Action >= 1 && data1->Action <= 5);
				bool apply_air_tweaks = !((data1->Action >= 10 && data1->Action <= 12) || (data1->CharID == Characters_Tails && data1->Action == 15));

				if (ShowDebugInfo)
				{
					DisplayDebugString(NJM_LOCATION(20, 4), "Level:");
					PrintDebugNumber(NJM_LOCATION(30, 4), GetLevelAndAct(), 2);

					if (apply_air_tweaks)
						DisplayDebugString(NJM_LOCATION(20, 2), "Apply_air_tweaks: true");
					else
						DisplayDebugString(NJM_LOCATION(20, 2), "Apply_air_tweaks: false");
					DisplayDebugString(NJM_LOCATION(20, 3), "CharID: ");
					PrintDebugNumber(NJM_LOCATION(28, 3), data1->CharID, 2);
				}

				if (apply_air_tweaks)
				{
					PhysicsArray[data1->CharID].JumpSpeed = InitialJumpSpeed[data1->CharID] + (JumpHeavyness * 20.75f);
					PhysicsArray[data1->CharID].AirDecel = AirDeceleration;
					PhysicsArray[data1->CharID].AirBrake = AirControl;
				}
				
				if (on_ground) {

					if (ShowDebugInfo)
						DisplayDebugString(NJM_LOCATION(2, 2), "On_ground: true");

					if (data1->Action == 4 || data1->Action == 5) {

						if (data2->VelocityDirection.y > 0)
							PhysicsArray[data1->CharID].Gravity = (RollingSlopeOffset[data1->CharID] - 0.02f) - (data2->VelocityDirection.y / SlopeOffsetDivisor[data1->CharID]);
						if (data2->VelocityDirection.y < 0)
							PhysicsArray[data1->CharID].Gravity = RollingSlopeOffset[data1->CharID] - (data2->VelocityDirection.y / SlopeOffsetDivisor[data1->CharID]);

						if (PhysicsArray[data1->CharID].Gravity > RollingSlopeInfluenceMax[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RollingSlopeInfluenceMax[data1->CharID];
						}
						if (PhysicsArray[data1->CharID].Gravity < RollingSlopeInfluenceMin[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RollingSlopeInfluenceMin[data1->CharID];
						}

					}
					else {
						PhysicsArray[data1->CharID].Gravity = RunningSlopeOffset[data1->CharID] - (data2->VelocityDirection.y / SlopeOffsetDivisor[data1->CharID]);

						if (PhysicsArray[data1->CharID].Gravity > RunningSlopeInfluenceMax[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RunningSlopeInfluenceMax[data1->CharID];
						}
						if (PhysicsArray[data1->CharID].Gravity < RunningSlopeInfluenceMin[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RunningSlopeInfluenceMin[data1->CharID];
						}

					}
				}
				else {

					if (ShowDebugInfo)
						DisplayDebugString(NJM_LOCATION(2, 2), "On_ground: false");
					
					if(!apply_air_tweaks)
						PhysicsArray[data1->CharID].Gravity = 0.08f;
					else
						PhysicsArray[data1->CharID].Gravity = 0.08f + JumpHeavyness;
					
				}
				

				if (ShowDebugInfo) {
					DisplayDebugString(NJM_LOCATION(2, 6), "Gravity: ");
					char array2[10];
					sprintf_s(array2, "%f", PhysicsArray[data1->CharID].Gravity);
					DisplayDebugString(NJM_LOCATION(12, 6), array2);

					DisplayDebugString(NJM_LOCATION(2, 10), "Rotation x: ");
					PrintDebugNumber(NJM_LOCATION(12, 10), data1->Rotation.x, 7);

					DisplayDebugString(NJM_LOCATION(2, 11), "Rotation y: ");
					PrintDebugNumber(NJM_LOCATION(12, 11), data1->Rotation.y, 7);

					DisplayDebugString(NJM_LOCATION(2, 12), "Rotation z: ");
					PrintDebugNumber(NJM_LOCATION(12, 12), data1->Rotation.z, 7);

					//One full rotation = 65480
					float converted_x_rotation = (data1->Rotation.x / 65480.0f) * 3.141592f;
					float converted_y_rotation = (data1->Rotation.y / 65480.0f) * 3.141592f;
					float converted_z_rotation = (data1->Rotation.z / 65480.0f) * 3.141592f;

					DisplayDebugString(NJM_LOCATION(2, 13), "Rotation y radians: ");
					char array3[16];
					sprintf_s(array3, "%f", converted_y_rotation);
					DisplayDebugString(NJM_LOCATION(20, 13), array3);

					DisplayDebugString(NJM_LOCATION(2, 14), "Velocity direction x: ");
					PrintDebugNumber(NJM_LOCATION(20, 14), data2->VelocityDirection.x, 10);
					DisplayDebugString(NJM_LOCATION(2, 15), "Velocity direction y: ");
					PrintDebugNumber(NJM_LOCATION(20, 15), data2->VelocityDirection.y, 10);
					DisplayDebugString(NJM_LOCATION(2, 16), "Velocity direction z: ");
					PrintDebugNumber(NJM_LOCATION(20, 16), data2->VelocityDirection.z, 10);

					DisplayDebugString(NJM_LOCATION(2, 18), "Grav Offset: ");
					char array4[16];
					sprintf_s(array4, "%f", (data2->VelocityDirection.y / (SlopeOffsetDivisor[data1->CharID] * 1.25)));
					DisplayDebugString(NJM_LOCATION(20, 18), array4);

					if (Controllers[0].HeldButtons & Buttons_Left) {
						SlopeOffsetDivisor[data1->CharID] += 0.01f;
					}
					if (Controllers[0].HeldButtons & Buttons_Right) {
						SlopeOffsetDivisor[data1->CharID] -= 0.01f;
					}

					DisplayDebugString(NJM_LOCATION(2, 19), "Grav Offset Divisor: ");
					char array5[16];
					sprintf_s(array5, "%f", SlopeOffsetDivisor[data1->CharID]);
					DisplayDebugString(NJM_LOCATION(24, 19), array5);
				}
			}
	}

	__declspec(dllexport) void __cdecl OnRenderDeviceReset()
	{
		// Executed when the window size changes
	}

	__declspec(dllexport) void __cdecl OnRenderDeviceLost()
	{
		// Executed when the game fails to render the scene
	}

	__declspec(dllexport) void __cdecl OnRenderSceneStart()
	{
		// Executed before the game starts rendering the scene
	}

	__declspec(dllexport) void __cdecl OnRenderSceneEnd()
	{
		// Executed when the game finishes rendering the scene
	}

	__declspec(dllexport) void __cdecl OnExit()
	{
		// Executed when the game is about to terminate
	}

	__declspec(dllexport) ModInfo SADXModInfo = { ModLoaderVer }; // This is needed for the Mod Loader to recognize the DLL.
}