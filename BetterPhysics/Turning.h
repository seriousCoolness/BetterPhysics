#pragma once
#include "stdafx.h"

extern bool ShowDebugInfo;
extern int PhysicsType;
extern bool ChangeRunCap;
extern bool SA2JumpDash;

extern float SlopeFactor[8];
extern float SlopeRollUp[8];
extern float SlopeRollDown[8];

FunctionPointer(void, sub_4491E0,(EntityData1* a1, EntityData2* a2, CharObj2* a3), 0x4491E0);
void __cdecl GraduallyTurn_r(EntityData1* a1, EntityData2* a2, CharObj2* a3);
