#include "stdafx.h"

#include "Turning.h"

void __cdecl GraduallyTurn_r(EntityData1* data1, EntityData2* data2, CharObj2* a3)
{
    float vX; // ecx
    float vY; // edx
    float vZ; // eax
    int v6; // ebp
    double v7; // st7
    double v8; // st7
    int v9; // eax
    Angle v10; // [esp-Ch] [ebp-28h]
    NJS_VECTOR a2a; // [esp+4h] [ebp-18h] BYREF
    NJS_VECTOR a1a; // [esp+10h] [ebp-Ch] BYREF

    if (!a3->field_A && (a3->SurfaceFlags & 0x4000) == 0)
    {
        a2a.x = Gravity.x;
        a2a.y = Gravity.y;
        a2a.z = Gravity.z;
        vX = data2->VelocityDirection.x;
        vY = data2->VelocityDirection.y;
        vZ = data2->VelocityDirection.z;
        a1a.x = vX;
        a1a.y = vY;
        a1a.z = vZ;
        
        WorldToPlayer(data1, &a2a);
            if (abs(data2->CharacterData->SurfaceNormal.y) <= 0.925 && data1->Action != 4) {
                NJS_VECTOR SideDirection = { 0, 0, 1 };
                NJS_VECTOR ForwardDirection = { 1, 0, 0 };
                PlayerDirectionTransform(data1, &SideDirection);
                PlayerDirectionTransform(data1, &ForwardDirection);
                float SideAngleLimit = atan2(abs(SideDirection.y), data2->CharacterData->Speed.x) * (65536.0f / (2.0f * 3.141592f));
                float RotationDivisor;
                RotationDivisor = 45.0f - abs(SideDirection.y * 22.5f);
                float SurfaceAngleY = atan2(data2->CharacterData->SurfaceNormal.z, data2->CharacterData->SurfaceNormal.x) * (65536.0f / (2.0f * 3.141592f));
                //float AngleDifference = ((data1->Rotation.y - SurfaceAngleY) / 60.0);
                if (PhysicsType == 1)
                    v9 = BAMS_SubWrap(data1->Rotation.y, SurfaceAngleY, (65536.0f / RotationDivisor));
                else
                    v9 = BAMS_SubWrap(data1->Rotation.y, SurfaceAngleY, (SideAngleLimit * 2));
                data2->Forward.y = v9;
                RotateTowards(a3, data1, data2, v9);
            }
        //data1->Rotation.y = (SurfaceAngleY) * (65536.0f / (2.0f * 3.141592f));
    }
}