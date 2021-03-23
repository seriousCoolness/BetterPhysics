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
FunctionPointer(void, WorldToPlayer, (EntityData1* a1, NJS_VECTOR* vd), 0x43EC00);

#define FunctionPointer(RETURN_TYPE, NAME, ARGS, ADDRESS) static RETURN_TYPE (__cdecl *const NAME)ARGS = (RETURN_TYPE (__cdecl *)ARGS)ADDRESS
#define StdcallFunctionPointer(RETURN_TYPE, NAME, ARGS, ADDRESS) static RETURN_TYPE (__stdcall *const NAME)ARGS = (RETURN_TYPE (__stdcall *)ARGS)ADDRESS
#define FastcallFunctionPointer(RETURN_TYPE, NAME, ARGS, ADDRESS) static RETURN_TYPE (__fastcall *const NAME)ARGS = (RETURN_TYPE (__fastcall *)ARGS)ADDRESS
#define ThiscallFunctionPointer(RETURN_TYPE, NAME, ARGS, ADDRESS) static RETURN_TYPE (__thiscall *const NAME)ARGS = (RETURN_TYPE (__thiscall *)ARGS)ADDRESS
#define VoidFunc(NAME, ADDRESS) FunctionPointer(void,NAME,(void),ADDRESS)
#define ObjectFunc(NAME, ADDRESS) FunctionPointer(void,NAME,(ObjectMaster *obj),ADDRESS)


// void __usercall(CharObj2 *charobj2@<edi>, EntityData1 *data1@<esi>, EntityData2 *data2, int target_angle)
static const void* const RotateTowardsPtr = (void*)0x443C50;
static inline void RotateTowards(CharObj2* charobj2, EntityData1* data1, EntityData2* data2, int target_angle)
{
	__asm
	{
		push[target_angle]
		push[data2]
		mov esi, [data1]
		mov edi, [charobj2]
		call RotateTowardsPtr
		add esp, 8
	}
}