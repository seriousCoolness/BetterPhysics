#include "stdafx.h"
#include "IniFile.hpp"
#include <math.h>
#include "EnemyBounceThing.h"
#include "WaterRun.h"
#include "ClassicJump.h"
#include "ClassicRoll.h"
#include "FixGomban.h"
#include "Turning.h"
// or #include "stdafx.h" for previous Visual Studio versions

PointerInfo jumps[] = {
	// this didn't work somehow
	ptrdecl(loc_4496E1, WaterRun_asm),
	ptrdecl(EnemyBounceThing_ptr, EnemyBounceThing_r),
	ptrdecl(DoJumpThing, DoJumpThing_r),
	ptrdecl(sub_446ED0, FixGomban_r),
	ptrdecl(sub_4491E0, GraduallyTurn_r)
};

static const int jump_cancel = Buttons_B;

namespace CollisionList
{
	enum _enum
	{
		Players,
		Unknown_1,
		Targetable,
		Hazard,
		Unknown_4,
		Unknown_5,
		Minimal,
		Rings,
		Unknown_8,
		Chao,
		COUNT
	};
}

#pragma pack(push, 1)
struct _CollisionData
{
	__int16 field_0;
	__int16 field_2;
	int field_4;
	NJS_VECTOR v;
	float anonymous_1;
	float anonymous_2;
	float anonymous_3;
	int field_20;
	int field_24;
	int field_28;
	int field_2C;
};
struct _CollisionInfo
{
	__int16 List;
	__int16 field_2;
	__int16 Flags;
	__int16 Count;
	float f8;
	_CollisionData* CollisionArray;
	Uint8 field_10[140];
	ObjectMaster* Object;
	__int16 field_A0;
	__int16 field_A2;
	_CollisionInfo* CollidingObject;
};
#pragma pack(pop)

enum CollisionMode : Sint16
{
	Unknown00,
	Unknown01,
	Unknown02,
	Solid,
	Unknown04,
	Unknown05,
	Unknown06,
	Unknown07,
	Unknown08,
	Unknown09,
	CanTarget = 0x40
};

#if 0
static void __cdecl InitCollision_(ObjectMaster* obj, _CollisionData* collisionArray, int count, Uint8 list);
static Trampoline hax(0x0041CAF0, 0x0041CAF5, InitCollision_);
static void __cdecl InitCollision_(ObjectMaster* obj, _CollisionData* collisionArray, int count, Uint8 list)
{
	FunctionPointer(void, original, (ObjectMaster*, _CollisionData*, int, Uint8), hax.Target());
	original(obj, collisionArray, count, list);

	//if (list != 6)
		//return;

	if (collisionArray == nullptr)
		return;

	//auto info = reinterpret_cast<_CollisionInfo*>(obj->Data1->CollisionInfo);
	//if (info != nullptr)
		//info->Flags = 0;

	for (auto i = 0; i < count; i++)
	{
		//collisionArray[i].field_0 = 0;
		collisionArray[i].field_2 = 0;
	}
}
#endif

extern "C"
{
	bool ShowDebugInfo = false;
	int PhysicsType = 0;
	bool ChangeRunCap = true;
	bool SA2JumpDash = true;
	float JumpHeavyness = 0.01f;
	float AirDeceleration = -0.019f;
	float AirControl = -0.028f;
	bool DeleteLoops = false;
	bool DeleteDashPanels = true;
	bool TweakCameras = false;

	bool ApplyPhysicsFor[8] = { 1 };

	bool LevelTweaks[11] = { 1 };
	
	//Velocity-based
	float RollingSlopeInfluenceMax[8] = { 0.32f };
	float RollingSlopeInfluenceMin[8] = { 0.04f };
	float RunningSlopeInfluenceMax[8] = { 0.16f };
	float RunningSlopeInfluenceMin[8] = { 0.04f };
	float RollingDecel[8] = { -0.08f };
	float SlopeOffsetDivisor[8] = { 32.0f };
	float RunningSlopeOffset[8] = { 0.10f };
	float RollingSlopeOffset[8] = { 0.12f };
	//Rotation-based
	float SlopeFactor[8] = { 0.100f };
	float SlopeRollUp[8] = { 0.058125f };
	float SlopeRollDown[8] = { 0.3125f };


	float InitialJumpSpeed[8] = { 1.66f };
	float InitialAirAccel[8] = { 0.031 };
	float InitialAirDecel[8] = { -0.028 };
	float InitialAirBrake[8] = { -0.17 };

	int InitialLoopInstruction;
	int InitialPanelInstruction;

	int DebugSelect = 0;

	bool PrevOnGround = false;

	__declspec(dllexport) PointerList Jumps[] = { { arrayptrandlengthT(jumps, int) } };

	__declspec(dllexport) void __cdecl Init(const char* path, const HelperFunctions& helperFunctions)
	{
		// Executed at startup, contains helperFunctions and the path to your mod (useful for getting the config file.)
		// This is where we override functions, replace static data, etc.
		
		const IniFile* config = new IniFile(std::string(path) + "\\config.ini");
		ShowDebugInfo = config->getBool("General", "Show Debug Info", false);
		PhysicsType = config->getInt("General", "PhysicsType", 0);
		ChangeRunCap = config->getBool("General", "Increase Speed Cap", true);
		SA2JumpDash = config->getBool("General", "SA2JumpDash", true);
		JumpHeavyness = config->getFloat("General", "JumpHeavyness", 0.02f);
		AirDeceleration = config->getFloat("General", "AirDeceleration", -0.019f);
		AirControl = config->getFloat("General", "AirControl", -0.028f);
		DeleteLoops = config->getBool("General", "DeleteLoops", false);
		DeleteDashPanels = config->getBool("General", "DeleteDashPanels", true);
		TweakCameras = config->getBool("General", "TweakCameras", false);

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
		
		RollingDecel[0] = config->getFloat("Advanced", "Sonic Rolling Deceleration", -0.004f);
		RollingSlopeInfluenceMax[0] = config->getFloat("Advanced", "Sonic Max Roll Slope Influence", 0.32f);
		RollingSlopeInfluenceMin[0] = config->getFloat("Advanced", "Sonic Min Roll Slope Influence", 0.04f);
		RollingSlopeOffset[0] = config->getFloat("Advanced", "Sonic Roll Slope Influence Offset", 0.14f);
		RunningSlopeInfluenceMax[0] = config->getFloat("Advanced", "Sonic Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[0] = config->getFloat("Advanced", "Sonic Min Run Slope Influence", 0.04f);
		RunningSlopeOffset[0] = config->getFloat("Advanced", "Sonic Run Slope Influence Offset", 0.10f);
		SlopeOffsetDivisor[0] = config->getFloat("Advanced", "Sonic Slope Influence Offset Divisor", 32.00f);
		SlopeFactor[0] = config->getFloat("Advanced", "SonicSF", 0.080f);
		SlopeRollUp[0] = config->getFloat("Advanced", "SonicSRU", 0.058125f);
		SlopeRollDown[0] = config->getFloat("Advanced", "SonicSRD", 0.3125f);

		RollingDecel[2] = config->getFloat("Advanced", "Tails Rolling Deceleration", -0.004f);
		RollingSlopeInfluenceMax[2] = config->getFloat("Advanced", "Tails Max Roll Slope Influence", 0.16f);
		RollingSlopeInfluenceMin[2] = config->getFloat("Advanced", "Tails Min Roll Slope Influence", 0.04f);
		RollingSlopeOffset[2] = config->getFloat("Advanced", "Tails Roll Slope Influence Offset", 0.14f);
		RunningSlopeInfluenceMax[2] = config->getFloat("Advanced", "Tails Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[2] = config->getFloat("Advanced", "Tails Min Run Slope Influence", 0.00f);
		RunningSlopeOffset[2] = config->getFloat("Advanced", "Tails Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[2] = config->getFloat("Advanced", "Tails Slope Influence Offset Divisor", 30.00f);
		SlopeFactor[2] = config->getFloat("Advanced", "TailsSF", 0.080f);
		SlopeRollUp[2] = config->getFloat("Advanced", "TailsSRU", 0.058125f);
		SlopeRollDown[2] = config->getFloat("Advanced", "TailsSRD", 0.3125f);
		
		RollingDecel[3] = config->getFloat("Advanced", "Knuckles Rolling Deceleration", -0.008f);
		RollingSlopeInfluenceMax[3] = config->getFloat("Advanced", "Knuckles Max Roll Slope Influence", 0.16f);
		RollingSlopeInfluenceMin[3] = config->getFloat("Advanced", "Knuckles Min Roll Slope Influence", 0.04f);
		RollingSlopeOffset[3] = config->getFloat("Advanced", "Knuckles Roll Slope Influence Offset", 0.14f);
		RunningSlopeInfluenceMax[3] = config->getFloat("Advanced", "Knuckles Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[3] = config->getFloat("Advanced", "Knuckles Min Run Slope Influence", 0.04f);
		RunningSlopeOffset[3] = config->getFloat("Advanced", "Knuckles Run Slope Influence Offset", 0.10f);
		SlopeOffsetDivisor[3] = config->getFloat("Advanced", "Knuckles Slope Influence Offset Divisor", 30.00f);
		SlopeFactor[3] = config->getFloat("Advanced", "KnucklesSF", 0.080f);
		SlopeRollUp[3] = config->getFloat("Advanced", "KnucklesSRU", 0.058125f);
		SlopeRollDown[3] = config->getFloat("Advanced", "KnucklesSRD", 0.3125f);
		
		RollingDecel[5] = config->getFloat("Advanced", "Amy Rolling Deceleration (Unused)", -0.008f);
		RollingSlopeInfluenceMax[5] = config->getFloat("Advanced", "Amy Max Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeInfluenceMin[5] = config->getFloat("Advanced", "Amy Min Roll Slope Influence (Unused)", 0.04f);
		RollingSlopeOffset[5] = config->getFloat("Advanced", "Amy Roll Slope Influence Offset", 0.16f);
		RunningSlopeInfluenceMax[5] = config->getFloat("Advanced", "Amy Max Run Slope Influence", 0.16f);
		RunningSlopeInfluenceMin[5] = config->getFloat("Advanced", "Amy Min Run Slope Influence", 0.02f);
		RunningSlopeOffset[5] = config->getFloat("Advanced", "Amy Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[5] = config->getFloat("Advanced", "Amy Slope Influence Offset Divisor", 25.00f);
		SlopeFactor[5] = config->getFloat("Advanced", "AmySF", 0.038125f);
		SlopeRollUp[5] = config->getFloat("Advanced", "AmySRU", 0.058125f);
		SlopeRollDown[5] = config->getFloat("Advanced", "AmySRD", 0.3125f);

		RollingDecel[6] = config->getFloat("Advanced", "Gamma Rolling Deceleration (Unused)", -0.008f);
		RollingSlopeInfluenceMax[6] = config->getFloat("Advanced", "Gamma Max Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeInfluenceMin[6] = config->getFloat("Advanced", "Gamma Min Roll Slope Influence (Unused)", 0.04f);
		RollingSlopeOffset[6] = config->getFloat("Advanced", "Gamma Roll Slope Influence Offset", 0.16f);
		RunningSlopeInfluenceMax[6] = config->getFloat("Advanced", "Gamma Max Run Slope Influence", 0.08f);
		RunningSlopeInfluenceMin[6] = config->getFloat("Advanced", "Gamma Min Run Slope Influence", 0.00f);
		RunningSlopeOffset[6] = config->getFloat("Advanced", "Gamma Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[6] = config->getFloat("Advanced", "Gamma Slope Influence Offset Divisor", 25.00f);
		SlopeFactor[6] = config->getFloat("Advanced", "GammaSF", 0.038125f);
		SlopeRollUp[6] = config->getFloat("Advanced", "GammaSRU", 0.058125f);
		SlopeRollDown[6] = config->getFloat("Advanced", "GammaSRD", 0.3125f);

		RollingDecel[7] = config->getFloat("Advanced", "Big Rolling Deceleration (Unused)", -0.008f);
		RollingSlopeInfluenceMax[7] = config->getFloat("Advanced", "Big Max Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeInfluenceMin[7] = config->getFloat("Advanced", "Big Min Roll Slope Influence (Unused)", 0.32f);
		RollingSlopeOffset[7] = config->getFloat("Advanced", "Big Roll Slope Influence Offset", 0.16f);
		RunningSlopeInfluenceMax[7] = config->getFloat("Advanced", "Big Max Run Slope Influence", 0.08f);
		RunningSlopeInfluenceMin[7] = config->getFloat("Advanced", "Big Min Run Slope Influence", 0.00f);
		RunningSlopeOffset[7] = config->getFloat("Advanced", "Big Run Slope Influence Offset", 0.08f);
		SlopeOffsetDivisor[7] = config->getFloat("Advanced", "Big Slope Influence Offset Divisor", 25.00f);
		SlopeFactor[7] = config->getFloat("Advanced", "BigSF", 0.038125f);
		SlopeRollUp[7] = config->getFloat("Advanced", "BigSRU", 0.058125f);
		SlopeRollDown[7] = config->getFloat("Advanced", "BigSRD", 0.3125f);


		if (ApplyPhysicsFor[0])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Sonic].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Sonic].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Sonic].MaxAccel = 3.0f;
			}

			PhysicsArray[Characters_Sonic].RollDecel = RollingDecel[0];
			PhysicsArray[Characters_Sonic].RollEnd = 0.90f;
			PhysicsArray[Characters_Sonic].GroundDecel = -0.028;
		}
		if (ApplyPhysicsFor[2])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Tails].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Tails].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Tails].MaxAccel = 2.0f;
			}
			PhysicsArray[Characters_Tails].FloorGrip = 2;
			PhysicsArray[Characters_Tails].RollDecel = RollingDecel[2];
			PhysicsArray[Characters_Tails].RollEnd = 0.90f;
		}
		if (ApplyPhysicsFor[3])
		{
			if (ChangeRunCap) {
				PhysicsArray[Characters_Knuckles].HSpeedCap = 24.0f;
				PhysicsArray[Characters_Knuckles].VSpeedCap = 24.0f;
				PhysicsArray[Characters_Knuckles].MaxAccel = 3.0f;
			}
			PhysicsArray[Characters_Knuckles].RollDecel = RollingDecel[3];
			PhysicsArray[Characters_Knuckles].RollEnd = 0.90f;
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
			PhysicsArray[Characters_Amy].RollEnd = 0.90f;
		}

		//WriteData<5>((void*)0x449364, 0x90);
		//WriteData<5>((void*)0x44934B, 0x90);

		WriteData((const int**)0x00492F56, &jump_cancel);
		WriteData((short*)0x00497476, (short)0xE990);

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

		Init_Levels(LevelTweaks, helperFunctions);

		if (DeleteLoops) 
		{
			InitialLoopInstruction = *(char*)0x4BB1F0;
			InitialPanelInstruction = *(char*)0x007A4450;
		}

		if (TweakCameras)
		{
			Init_Cameras(LevelTweaks, helperFunctions);
		}

		SlopeFactor[0] = SlopeFactor[0] * 0.92f;
		SlopeRollUp[0] = SlopeRollUp[0] * 0.92f;
		SlopeRollDown[0] = SlopeRollDown[0] * 0.92f;
		SlopeFactor[2] = SlopeFactor[2] * 0.92f;
		SlopeRollUp[2] = SlopeRollUp[2] * 0.92f;
		SlopeRollDown[2] = SlopeRollDown[2] * 0.92f;
		SlopeFactor[3] = SlopeFactor[3] * 0.92f;
		SlopeRollUp[3] = SlopeRollUp[3] * 0.92f;
		SlopeRollDown[3] = SlopeRollDown[3] * 0.92f;
		SlopeFactor[5] = SlopeFactor[5] * 0.92f;
		SlopeRollUp[5] = SlopeRollUp[5] * 0.92f;
		SlopeRollDown[5] = SlopeRollDown[5] * 0.92f;
		SlopeFactor[6] = SlopeFactor[6] * 0.92f;
		SlopeRollUp[6] = SlopeRollUp[6] * 0.92f;
		SlopeRollDown[6] = SlopeRollDown[6] * 0.92f;
		SlopeFactor[7] = SlopeFactor[7] * 0.92f;
		SlopeRollUp[7] = SlopeRollUp[7] * 0.92f;
		SlopeRollDown[7] = SlopeRollDown[7] * 0.92f;
		
	}

	__declspec(dllexport) void __cdecl OnFrame()
	{
		// Executed before the game processes input
		// Executed every running frame of SADX
		if (DeleteLoops) {
			WriteData<1>((char*)0x4BB1F0, InitialLoopInstruction);
			Delete_Splines(LevelTweaks);
		}
		if (DeleteDashPanels) {
			WriteData<1>((char*)0x007A4450, InitialPanelInstruction);
			Delete_Panels(LevelTweaks);
		}

		EntityData1* data1 = EntityData1Ptrs[0];
		EntityData2* data2 = EntityData2Ptrs[0];

		if (data1 == nullptr) {
			DisplayDebugString(NJM_LOCATION(2, 2), "As of version 1.9, the Mechanics Tweaks mod has been merged with Better Physics.");
			DisplayDebugString(NJM_LOCATION(2, 3), "If you still have it installed, please quit the game and disable it now.");
		}

		if (data1 != nullptr && ApplyPhysicsFor[data1->CharID] && data1->Status != StatusBits_DisableControl)
		{

			NJS_VECTOR ForwardDirection = { 1, 0, 0 };
			NJS_VECTOR SideDirection = { 0, 0, 1 };

			PlayerDirectionTransform(data1, &ForwardDirection);
			PlayerDirectionTransform(data1, &SideDirection);

			bool on_ground = (data1->Action >= 1 && data1->Action <= 5);
			bool apply_air_tweaks = !((data1->Action >= 10 && data1->Action <= 12) || (data1->CharID == Characters_Tails && data1->Action == 15) || data1->Status == 16385);

			// && abs(Controllers[0].LeftStickX) < 20 && abs(Controllers[0].LeftStickY) < 20
			if (on_ground && !PrevOnGround) {
				if (data2->VelocityDirection.y < 0 && data2->CharacterData->SurfaceNormal.y <= 0.925f) {
					//GravityAngle_X = 0;
					//GravityAngle_Z = 0;

					NJS_VECTOR NormalVelDotProduct = { 0,0,0 };
					NJS_VECTOR NormalSquared = { 0,0,0 };
					DotProduct(&data2->CharacterData->SurfaceNormal, &data2->VelocityDirection, &NormalVelDotProduct);
					DotProduct(&data2->CharacterData->SurfaceNormal, &data2->CharacterData->SurfaceNormal, &NormalSquared);
					NJS_VECTOR Reflected_Normal = { 0,0,0 };
					
					if (data2->CharacterData->SurfaceNormal.x != 0.0f && data2->CharacterData->SurfaceNormal.x != -0.0f)
						Reflected_Normal.x = 2 * ((NormalVelDotProduct.x / NormalSquared.x) * data2->CharacterData->SurfaceNormal.x) - data2->VelocityDirection.x;
					if (data2->CharacterData->SurfaceNormal.z != 0.0f && data2->CharacterData->SurfaceNormal.z != -0.0f)
						Reflected_Normal.z = 2 * ((NormalVelDotProduct.z / NormalSquared.z) * data2->CharacterData->SurfaceNormal.z) - data2->VelocityDirection.z;

					
					float SurfaceAngleY = atan2(Reflected_Normal.z, Reflected_Normal.x);
					data1->Rotation.y = (SurfaceAngleY) * (65536.0f / (2.0f * 3.141592f));
					data2->Forward.y = data1->Rotation.y;
					
					PlayerDirectionTransform(data1, &ForwardDirection);

					data2->CharacterData->Speed.x = abs(data2->CharacterData->Speed.x) - (ForwardDirection.y * SlopeFactor[data1->CharID]);
					
				}

			}
			PrevOnGround = on_ground;



			if (ShowDebugInfo)
			{
				DisplayDebugString(NJM_LOCATION(20, 4), "Status:");
				PrintDebugNumber(NJM_LOCATION(30, 4), data1->Status, 2);

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
				PhysicsArray[data1->CharID].AirAccel = 0.028;
			}
			else
			{
				PhysicsArray[data1->CharID].Gravity = 0.08f;
				PhysicsArray[data1->CharID].JumpSpeed = InitialJumpSpeed[data1->CharID];
				PhysicsArray[data1->CharID].AirDecel = InitialAirDecel[data1->CharID];
				PhysicsArray[data1->CharID].AirBrake = InitialAirBrake[data1->CharID];
				PhysicsArray[data1->CharID].AirAccel = InitialAirAccel[data1->CharID];
			}


			if (on_ground) {

				if (ShowDebugInfo) {

					DisplayDebugString(NJM_LOCATION(2, 2), "On_ground: true");

				}
				if (data1->Action == 4 || data1->Action == 5) {
					if (PhysicsType == 1) {
						if (data2->VelocityDirection.y > 0)
							PhysicsArray[data1->CharID].Gravity = (RollingSlopeOffset[data1->CharID] - 0.02f) - (data2->VelocityDirection.y / SlopeOffsetDivisor[data1->CharID]);
						if (data2->VelocityDirection.y <= 0)
							PhysicsArray[data1->CharID].Gravity = RollingSlopeOffset[data1->CharID] - (data2->VelocityDirection.y / SlopeOffsetDivisor[data1->CharID]);

						if (PhysicsArray[data1->CharID].Gravity > RollingSlopeInfluenceMax[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RollingSlopeInfluenceMax[data1->CharID];
						}
						if (PhysicsArray[data1->CharID].Gravity < RollingSlopeInfluenceMin[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RollingSlopeInfluenceMin[data1->CharID];
						}
					}
					if (PhysicsType == 0) {
						PhysicsArray[data1->CharID].Gravity = 0.0f;
						data2->CharacterData->Speed.y -= 0.001f;

						if (data2->VelocityDirection.y > 0.0f)
						{
							data2->CharacterData->Speed.x -= ForwardDirection.y * SlopeRollUp[data1->CharID];
						}
						else
						{
							data2->CharacterData->Speed.x -= ForwardDirection.y * SlopeRollDown[data1->CharID];
						}

						/*
						Float len = 1.0f / squareroot(ForwardDirection.z * ForwardDirection.z + ForwardDirection.x * ForwardDirection.x + ForwardDirection.y * ForwardDirection.y);
						Angle x = static_cast<Angle>((acos(len * 3.3499999f) * 65536.0f * 0.1591549762031479f) - (acos(-(len * ForwardDirection.y)) * 65536.0f * 0.1591549762031479f));
						if (sgn(data2->VelocityDirection.x) == sgn(njSin(x)))
							data2->CharacterData->Speed.x -= SlopeRollUp * njSin(x);
						else
							data2->CharacterData->Speed.x -= SlopeRollDown * njSin(x);
						*/
					}

				}
				else {
					if (PhysicsType == 1)
					{
						PhysicsArray[data1->CharID].Gravity = RunningSlopeOffset[data1->CharID] - (data2->VelocityDirection.y / SlopeOffsetDivisor[data1->CharID]);

						if (PhysicsArray[data1->CharID].Gravity > RunningSlopeInfluenceMax[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RunningSlopeInfluenceMax[data1->CharID];
						}
						if (PhysicsArray[data1->CharID].Gravity < RunningSlopeInfluenceMin[data1->CharID]) {
							PhysicsArray[data1->CharID].Gravity = RunningSlopeInfluenceMin[data1->CharID];
						}

					}

					if (PhysicsType == 0) {
						PhysicsArray[data1->CharID].Gravity = 0.0f;
						data2->CharacterData->Speed.y -= 0.001f;
						data2->CharacterData->Speed.x -= ForwardDirection.y * SlopeFactor[data1->CharID];

					}
				}
			}
			if (!on_ground) {

				if (ShowDebugInfo)
					DisplayDebugString(NJM_LOCATION(2, 2), "On_ground: false");

				if (!apply_air_tweaks)
					PhysicsArray[data1->CharID].Gravity = 0.08f;
				else
					PhysicsArray[data1->CharID].Gravity = 0.08f + JumpHeavyness;

			}



			if (ShowDebugInfo) {
				DisplayDebugString(NJM_LOCATION(2, 6), "Gravity: ");
				char array2[10];
				sprintf_s(array2, "%f", PhysicsArray[data1->CharID].Gravity);
				DisplayDebugString(NJM_LOCATION(12, 6), array2);

				NJS_VECTOR ForwardDirection = { 1, 0, 0 };
				NJS_VECTOR SideDirection = { 0, 0, -1 };
				PlayerDirectionTransform(data1, &ForwardDirection);
				PlayerDirectionTransform(data1, &SideDirection);

				DisplayDebugString(NJM_LOCATION(2, 10), "roll down div: ");
				char arrayX[16];
				sprintf_s(arrayX, "%f", (45.0f - abs(SideDirection.y * 45) * SlopeRollDown[data1->CharID]));
				DisplayDebugString(NJM_LOCATION(20, 10), arrayX);

				DisplayDebugString(NJM_LOCATION(2, 11), "roll up div: ");
				char arrayY[16];
				sprintf_s(arrayY, "%f", (45.0f - abs(SideDirection.y * 45) * SlopeRollUp[data1->CharID]));
				DisplayDebugString(NJM_LOCATION(20, 11), arrayY);

				DisplayDebugString(NJM_LOCATION(2, 12), "run div: ");
				char arrayZ[16];
				sprintf_s(arrayZ, "%f", (45.0f - abs(SideDirection.y * 45) * SlopeFactor[data1->CharID]));
				DisplayDebugString(NJM_LOCATION(20, 12), arrayZ);


				if (data2->CharacterData != nullptr) {
					DisplayDebugString(NJM_LOCATION(2, 14), "Surface x: ");
					char arraySX[16];
					sprintf_s(arraySX, "%f", data2->CharacterData->SurfaceNormal.x);
					DisplayDebugString(NJM_LOCATION(20, 14), arraySX);
					DisplayDebugString(NJM_LOCATION(2, 15), "Surface y: ");
					char arraySY[16];
					sprintf_s(arraySY, "%f", data2->CharacterData->SurfaceNormal.y);
					DisplayDebugString(NJM_LOCATION(20, 15), arraySY);
					DisplayDebugString(NJM_LOCATION(2, 16), "Surface z: ");
					char arraySZ[16];
					sprintf_s(arraySZ, "%f", data2->CharacterData->SurfaceNormal.z);
					DisplayDebugString(NJM_LOCATION(20, 16), arraySZ);
				}

				if (Controllers[0].PressedButtons & Buttons_L) {
					if (PhysicsType == 0)
						PhysicsType = 1;
					else
						PhysicsType = 0;
				}
				if (PhysicsType == 0)
					DisplayDebugString(NJM_LOCATION(30, 19), "Physics Type: Rotation");
				else
					DisplayDebugString(NJM_LOCATION(30, 19), "Physics Type: Velocity");


				if ((Controllers[0].PressedButtons & Buttons_Up) && DebugSelect < 14) {
					DebugSelect += 1;
				}
				if ((Controllers[0].PressedButtons & Buttons_Down) && DebugSelect > 0) {
					DebugSelect -= 1;
				}

				if (Controllers[0].HeldButtons & Buttons_Right) {
					if (DebugSelect == 0)
						SlopeOffsetDivisor[data1->CharID] += 0.01f;
					if (DebugSelect == 1)
						SlopeFactor[data1->CharID] += 0.001f;
					if (DebugSelect == 2)
						SlopeRollUp[data1->CharID] += 0.001f;
					if (DebugSelect == 3)
						SlopeRollDown[data1->CharID] += 0.001f;
					if (DebugSelect == 4)
						PhysicsArray[data1->CharID].GravityAdd += 0.001f;
					if (DebugSelect == 5)
						PhysicsArray[data1->CharID].Gravity += 0.001f;
					if (DebugSelect == 6)
						PhysicsArray[data1->CharID].FloorGrip += 0.01f;
					if (DebugSelect == 7)
						PhysicsArray[data1->CharID].MaxAccel += 0.01f;
					if (DebugSelect == 8)
						PhysicsArray[data1->CharID].GroundAccel += 0.01f;
					if (DebugSelect == 9)
						data2->CharacterData->Speed.y += 0.1f;
					if (DebugSelect == 10)
						data2->CharacterData->Speed.x += 0.1f;
					if (DebugSelect == 11)
						data2->CharacterData->Speed.z += 0.1f;
					if (DebugSelect == 12)
						data1->Position.y += 0.1f;
					if (DebugSelect == 13)
						data1->Position.x += 0.1f;
					if (DebugSelect == 14)
						data1->Position.z += 0.1f;
				}
				if (Controllers[0].HeldButtons & Buttons_Left) {
					if (DebugSelect == 0)
						SlopeOffsetDivisor[data1->CharID] -= 0.01f;
					if (DebugSelect == 1)
						SlopeFactor[data1->CharID] -= 0.001f;
					if (DebugSelect == 2)
						SlopeRollUp[data1->CharID] -= 0.001f;
					if (DebugSelect == 3)
						SlopeRollDown[data1->CharID] -= 0.001f;
					if (DebugSelect == 4)
						PhysicsArray[data1->CharID].GravityAdd -= 0.001f;
					if (DebugSelect == 5)
						PhysicsArray[data1->CharID].Gravity -= 0.001f;
					if (DebugSelect == 6)
						PhysicsArray[data1->CharID].FloorGrip -= 0.01f;
					if (DebugSelect == 7)
						PhysicsArray[data1->CharID].MaxAccel -= 0.01f;
					if (DebugSelect == 8)
						PhysicsArray[data1->CharID].GroundAccel -= 0.01f;
					if (DebugSelect == 9)
						data2->CharacterData->Speed.y -= 0.1f;
					if (DebugSelect == 10)
						data2->CharacterData->Speed.x -= 0.1f;
					if (DebugSelect == 11)
						data2->CharacterData->Speed.z -= 0.1f;
					if (DebugSelect == 12)
						data1->Position.y -= 0.1f;
					if (DebugSelect == 13)
						data1->Position.x -= 0.1f;
					if (DebugSelect == 14)
						data1->Position.z -= 0.1f;
				}

				char arrayDEBUG[16];

				if (DebugSelect == 0) {
					DisplayDebugString(NJM_LOCATION(30, 14), "SlopeOffsetDivisor:");

					sprintf_s(arrayDEBUG, "%f", SlopeOffsetDivisor[data1->CharID]);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 1) {
					DisplayDebugString(NJM_LOCATION(30, 14), "SlopeFactor:");

					sprintf_s(arrayDEBUG, "%f", SlopeFactor[data1->CharID]);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 2) {
					DisplayDebugString(NJM_LOCATION(30, 14), "SlopeRollUp:");

					sprintf_s(arrayDEBUG, "%f", SlopeRollUp[data1->CharID]);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 3) {
					DisplayDebugString(NJM_LOCATION(30, 14), "SlopeRollDown:");

					sprintf_s(arrayDEBUG, "%f", SlopeRollDown[data1->CharID]);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 4) {
					DisplayDebugString(NJM_LOCATION(30, 14), "GravityAdd:");

					sprintf_s(arrayDEBUG, "%f", PhysicsArray[data1->CharID].GravityAdd);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 5) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Gravity:");

					sprintf_s(arrayDEBUG, "%f", PhysicsArray[data1->CharID].Gravity);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 6) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Floor Grip:");

					sprintf_s(arrayDEBUG, "%f", PhysicsArray[data1->CharID].FloorGrip);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 7) {
					DisplayDebugString(NJM_LOCATION(30, 14), "MaxAccel:");

					sprintf_s(arrayDEBUG, "%f", PhysicsArray[data1->CharID].MaxAccel);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 8) {
					DisplayDebugString(NJM_LOCATION(30, 14), "GroundAccel:");

					sprintf_s(arrayDEBUG, "%f", PhysicsArray[data1->CharID].GroundAccel);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 9) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Speed.y:");

					sprintf_s(arrayDEBUG, "%f", data2->CharacterData->Speed.y);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 10) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Speed.x:");

					sprintf_s(arrayDEBUG, "%f", data2->CharacterData->Speed.x);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 11) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Speed.z:");

					sprintf_s(arrayDEBUG, "%f", data2->CharacterData->Speed.z);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 12) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Position.y:");

					sprintf_s(arrayDEBUG, "%f", data1->Position.y);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 13) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Position.x:");

					sprintf_s(arrayDEBUG, "%f", data1->Position.x);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
				if (DebugSelect == 14) {
					DisplayDebugString(NJM_LOCATION(30, 14), "Position.z:");

					sprintf_s(arrayDEBUG, "%f", data1->Position.z);
					DisplayDebugString(NJM_LOCATION(45, 14), arrayDEBUG);
				}
			}
		}
		ClassicRoll_OnFrame();
	}

	__declspec(dllexport) void __cdecl OnInput()
	{
		
	}

	__declspec(dllexport) void __cdecl OnControl()
	{
		// Executed when the game processes input

		
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