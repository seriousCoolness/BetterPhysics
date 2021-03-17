#pragma once

#include "stdafx.h"
#include "MemAccess.h"

void ReplaceCAM(std::string src, const HelperFunctions& helperFunctions);
void ReplaceSET(std::string src, const HelperFunctions& helperFunctions);
int sgn(float val);
void LookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy);
void PlayerLookAt(NJS_VECTOR* from, NJS_VECTOR* to, Angle* outx, Angle* outy);
void DotProduct(NJS_VECTOR* v1, NJS_VECTOR* v2, NJS_VECTOR* vOut);
void RotateVectorY(NJS_VECTOR* vector, Angle angle);

FunctionPointer(void, PlayerDirectionTransform, (EntityData1 *playerData, NJS_VECTOR *direction), 0x43EC90);
FunctionPointer(void, WorldToPlayer, (EntityData1* data1, NJS_VECTOR* velocitydir), 0x43EC00);
FunctionPointer(void, RotateTowards, (CharObj2* obj, EntityData1* data1, EntityData2* data2, int target_angle), 0x443C50);