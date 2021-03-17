#include "stdafx.h"

#include "Turning.h"

void __cdecl GraduallyTurn_r(EntityData1* a1, EntityData2* a2, CharObj2* a3) 
{
    float v3; // ecx
    float v4; // edx
    float v5; // eax
    double v6; // st7
    int v7; // ebp
    double v8; // st7
    double v9; // st7
    int v10; // eax
    Angle v11; // [esp-Ch] [ebp-28h]
    NJS_VECTOR a2a; // [esp+4h] [ebp-18h] BYREF
    NJS_VECTOR a1a; // [esp+10h] [ebp-Ch] BYREF

    if (!a3->field_A && (a3->SurfaceFlags & 0x4000) == 0)
    {
        a2a.x = Gravity.x;
        a2a.y = Gravity.y;
        v3 = a2->VelocityDirection.x;
        a2a.z = Gravity.z;
        v4 = a2->VelocityDirection.y;
        v5 = a2->VelocityDirection.z;
        a1a.x = v3;
        a1a.y = v4;
        a1a.z = v5;
        if (njScalor(&a1a) <= (double)a3->PhysicsData.Run1
            || (njUnitVector(&a1a), v6 = njInnerProduct(&Gravity, &a1a), !((v6 < -0.86))))
        {
            WorldToPlayer(a1, &a2a);
            if ((a2a.y < 0.0) && a2a.y > -0.87)
            {
                if ((a2a.x < 0.0))
                {
                    a2a.x = -a2a.x;
                }
                v7 = a1->Rotation.y - (atan2(a2a.z, a2a.x) * 65536.0 * -0.1591549762031479);
                if ((a2a.z < 0.0))
                {
                    a2a.z = -a2a.z;
                }
                v8 = a2a.z;
                if ((a1->Status & Status_Ball) != 0)
                {
                    v9 = v8 * 3072.0;
                }
                else
                {
                    v9 = v8 * 1536.0;
                }
                v10 = BAMS_SubWrap(a2->Forward.y, v7, v9);
                a2->Forward.y = v10;
                RotateTowards(a3, a1, a2, v10);
            }
            else
            {
                v11 = a1->Rotation.y;
                a2->Forward.y = v11;
                RotateTowards(a3, a1, a2, v11);
            }
        }
    }
}