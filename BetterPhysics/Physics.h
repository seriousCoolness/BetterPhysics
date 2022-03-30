#pragma once
#include "stdafx.h"
extern bool ShowDebugInfo;
extern int PhysicsType;
extern bool ChangeRunCap;
extern bool SA2JumpDash;
extern bool MechanicsTweaks;

extern float SlopeFactor[8];
extern float SlopeRollUp[8];
extern float SlopeRollDown[8];

extern "C"
{
	bool GetAirTweaks(EntityData1* data1);
}