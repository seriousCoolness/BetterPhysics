#include "pch.h"
#include <math.h>
// or #include "stdafx.h" for previous Visual Studio versions

extern "C"
{
	bool ShowDebugInfo = false;
	bool ChangeRunCap = true;
	bool ApplyPhysicsFor[8] = { 1 };
	float RollingSlopeInfluenceMax[8] = { 0.16f };
	float RollingSlopeInfluenceMin[8] = { 0.04f };
	float RunningSlopeInfluenceMax[8] = { 0.12f };
	float RunningSlopeInfluenceMin[8] = { 0.04f };
	float RollingDecel[8] = { 0.08f };
	float GravOffsetDivisor[8] = { 32.0f };

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
		
		//const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		//IsChaoGardenBanned = config->getBool("Stage", "IsChaoGardenBanned", false);
		
		
		PhysicsData* p = &PhysicsArray[Characters_Sonic];

		p->HSpeedCap = 16.0f;
		p->VSpeedCap = 16.0f;
		p->RollDecel = 0.004f;
		PhysicsArray[Characters_Sonic] = *p;

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
		
		//DisplayDebugString(NJM_LOCATION(2, 2), "JumpAddSpeed: ");
		//char array[10];
		//sprintf_s(array, "%f", PhysicsArray[Characters_Sonic].JumpAddSpeed);
		//DisplayDebugString(NJM_LOCATION(12, 2), array);

		for (int i = 0; i < 8; i++)
		{
			EntityData1* data1 = EntityData1Ptrs[i];
			EntityData2* data2 = EntityData2Ptrs[i];

			if (data1 != nullptr && data1->CharID == Characters_Sonic)
			{
				bool on_ground = (data1->Action >= 1 && data1->Action <= 5);
					
				if (on_ground) {

					DisplayDebugString(NJM_LOCATION(2, 2), "On_ground: true");
					if (data1->Action == 4 || data1->Action == 5) {
						PhysicsArray[Characters_Sonic].Gravity = 0.08f - (data2->VelocityDirection.y / 30.0f);
						
						if (PhysicsArray[Characters_Sonic].Gravity > 0.16f) {
							PhysicsArray[Characters_Sonic].Gravity = 0.16f;
						}
						if (PhysicsArray[Characters_Sonic].Gravity < 0.04f) {
							PhysicsArray[Characters_Sonic].Gravity = 0.04f;
						}

					}
					else {
						PhysicsArray[Characters_Sonic].Gravity = 0.12f - (data2->VelocityDirection.y / 30.0f);
						
						if (PhysicsArray[Characters_Sonic].Gravity > 0.12f) {
							PhysicsArray[Characters_Sonic].Gravity = 0.12f;
						}
						if (PhysicsArray[Characters_Sonic].Gravity < 0.04f) {
							PhysicsArray[Characters_Sonic].Gravity = 0.04f;
						}

					}
				}
				else {

					DisplayDebugString(NJM_LOCATION(2, 2), "On_ground: false");
					PhysicsArray[Characters_Sonic].Gravity = 0.08f;
				}

				DisplayDebugString(NJM_LOCATION(2, 6), "Gravity: ");
				char array2[10];
				sprintf_s(array2, "%f", PhysicsArray[Characters_Sonic].Gravity);
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
				DisplayDebugString(NJM_LOCATION(19, 13), array3);
				
				DisplayDebugString(NJM_LOCATION(2, 14), "Velocity direction x: ");
				PrintDebugNumber(NJM_LOCATION(19, 14), data2->VelocityDirection.x, 10);
				DisplayDebugString(NJM_LOCATION(2, 15), "Velocity direction y: ");
				PrintDebugNumber(NJM_LOCATION(19, 15), data2->VelocityDirection.y, 10);
				DisplayDebugString(NJM_LOCATION(2, 16), "Velocity direction z: ");
				PrintDebugNumber(NJM_LOCATION(19, 16), data2->VelocityDirection.z, 10);

				DisplayDebugString(NJM_LOCATION(2, 18), "Grav Offset: ");
				char array4[16];
				sprintf_s(array4, "%f", (data2->VelocityDirection.y / GravOffsetDivisor[0]));
				DisplayDebugString(NJM_LOCATION(19, 18), array4);

				if (Controllers[0].HeldButtons & Buttons_Left) {
					GravOffsetDivisor[0] += 0.001f;
				}
				if (Controllers[0].HeldButtons & Buttons_Right) {
					GravOffsetDivisor[0] -= 0.001f;
				}
				
				DisplayDebugString(NJM_LOCATION(2, 19), "Grav Offset: ");
				char array5[16];
				sprintf_s(array5, "%f", GravOffsetDivisor[0]);
				DisplayDebugString(NJM_LOCATION(19, 19), array5);
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