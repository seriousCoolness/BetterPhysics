#pragma once
#include "stdafx.h"

extern const void* sub_44BB60_ptr;

FunctionPointer(void, HandleGroundVelocity, (EntityData1* entity, EntityData2* a2, CharObj2* charobj), 0x44C270);
FunctionPointer(void, sub_447510, (EntityData1* arg0, EntityData2* arg4, CharObj2* a3), 0x447510);
FunctionPointer(void, sub_447010, (EntityData1* arg0, EntityData2* arg4, CharObj2* a3), 0x447010);
FunctionPointer(signed int, sub_438410, (NJS_VECTOR* a1, NJS_VECTOR* a2, NJS_VECTOR* a3), 0x438410);
//void __cdecl HandleGroundVelocity_r(EntityData1* entity, EntityData2* a2, CharObj2* charobj);
void __cdecl sub_44BB60_r(EntityData1* data1, EntityData2* a2, CharObj2* a3);