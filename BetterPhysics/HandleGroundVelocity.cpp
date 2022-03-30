#include "stdafx.h"
#include "HandleGroundVelocity.h"
#include "Turning.h"
#include "UsercallFunctionHandler.h"

const void* sub_44BB60_ptr = reinterpret_cast<void*>(0x0044BB60);

//0x44B0E0
void (*sub_44B0E0)(EntityData1* a1, CharObj2* eax0, EntityData2* arg_0) = GenerateUsercallWrapper<void (*)(EntityData1* a1, CharObj2* eax0, EntityData2* arg_0)>(noret, 0x44B0E0, rECX, rEAX, stack4);

//0x449380
void (*sub_449380)(EntityData1* a1, EntityData2* a2, CharObj2* a3) = GenerateUsercallWrapper<void (*)(EntityData1* a1, EntityData2* a2, CharObj2* a3)>(noret, 0x449380, rEAX, rESI, stack4);

//0x443E60
void (*sub_443E60)(EntityData1* a1, CharObj2* a2, EntityData2* a3, unsigned __int16 a4) = GenerateUsercallWrapper<void (*)(EntityData1* a1, CharObj2* a2, EntityData2* a3, unsigned __int16 a4)>(noret, 0x443E60, rEBX, rESI, stack4, stack2);

//0x443DF0
void (*sub_443DF0)(CharObj2* a1, EntityData1* entity, EntityData2* a3, __int16 bams) = GenerateUsercallWrapper<void (*)(CharObj2* a1, EntityData1* entity, EntityData2* a3, __int16 bams)>(noret, 0x443DF0, rEAX, rEDI, stack4, stack4);

void __cdecl sub_44BB60_r(EntityData1* data1, EntityData2* a2, CharObj2* a3)
{
    EntityData1* data1_; // ebp
    CharObj2* v4; // esi
    Angle v5; // edx
    EntityData1* v6; // eax
    Angle v7; // ecx
    Angle v8; // ebx
    int v9; // eax
    int v10; // edx
    long double v11; // st7
    Angle v12; // ecx
    EntityData2* v13; // [esp-28h] [ebp-50h]
    unsigned __int16 v14; // [esp-24h] [ebp-4Ch]
    NJS_VECTOR vs; // [esp+4h] [ebp-24h] BYREF
    NJS_VECTOR a3a; // [esp+10h] [ebp-18h] BYREF
    NJS_VECTOR vd; // [esp+1Ch] [ebp-Ch] BYREF

    data1_ = data1;
    if ((data1->Status & Status_DisableControl) == 0)
    {
        v4 = a3;
        if ((data1->Status & Status_OnPath) != 0)
        {
            FollowSpline(a3, a2, data1);
        }
        else
        {
            v5 = a2->Forward.y;
            if (GetAnalog(data1, (Angle*)&data1, 0))
            {
                if ((v4->SurfaceFlags & 0x20000) != 0)
                {
                    v9 = data1_->CharIndex;
                    v10 = Controllers[v9].LeftStickY;
                    data1 = (EntityData1*)(Controllers[v9].LeftStickX << 8);
                    v11 = (double)(int)data1;
                    data1 = (EntityData1*)(v10 << 8);
                    v8 = (unsigned __int64)(atan2(v11, (double)(v10 << 8)) * 65536.0 * 0.1591549762031479);
                    vs.x = 0.0;
                    vs.y = 0.0;
                    vs.z = -1.0;
                    njPushMatrixEx();
                    njUnitMatrix(0);
                    v6 = Camera_Data1;
                    v7 = Camera_Data1->Rotation.y;
                    if (v7)
                    {
                        njRotateY(0, (unsigned __int16)v7);
                        v6 = Camera_Data1;
                    }
                    v12 = v6->Rotation.x;
                    if (v12)
                    {
                        njRotateX(0, (unsigned __int16)v12);
                    }
                    njCalcVector(0, &vs, &a3a);
                    njPopMatrix(1u);
                    njPushMatrixEx();
                    njUnitMatrix(0);
                    njRotate(0, &v4->SurfaceNormal, v8);
                    njCalcVector(0, &a3a, &vd);
                    njPopMatrix(1u);
                    vs.x = 1.0;
                    vs.y = 0.0;
                    vs.z = 0.0;
                    ProjectVectorZXY(data1_, &vs);
                    v14 = sub_438410(&vs, &vd, &v4->SurfaceNormal) + data1_->Rotation.y;
                    v13 = a2;
                    a2->Forward.y = v14;
                    sub_443E60(data1_, v4, v13, v14);
                    goto LABEL_16;
                }
                v5 = (Angle)data1;
                if ((data1_->Status & (Status_Ground | Status_Unknown1)) != 0)
                {
                    sub_4491E0(data1_, a2, a3);
                    v5 = BAMS_SubWrap(data1_->Rotation.y, (Angle)data1, (-400 * abs(a2->CharacterData->Speed.x))+5200);
                    a2->Forward.y = v5;
                    goto LABEL_16;
                }
            }
            else
            {
                if ((data1_->Status & (Status_Unknown1 | Status_Ground)) != 0)
                {
                    sub_4491E0(data1_, a2, a3);
                    return;
                }
                
            }
            a2->Forward.y = v5;
        }
    LABEL_16:
        RotateTowards(v4, data1_, a2, a2->Forward.y);
    }
}

/*void __cdecl HandleGroundVelocity_r(EntityData1* entity, EntityData2* a2, CharObj2* charobj)
{
    EntityData1* localEntity1; // edi
    int v4; // eax
    EntityData2* v5; // ebx
    int have_analog; // esi
    double v7; // st7
    float v8; // ecx
    float v9; // edx
    double v10; // st7
    NJS_VECTOR* v11; // ecx
    double v12; // st7
    double v13; // st7
    double v14; // st6
    float v15; // et1
    double v16; // st6
    float v17; // et1
    unsigned __int8 v19 = 0; // c0
    unsigned __int8 v20 = 0; // c3
    double v21; // st6
    Angle analogAngleModified; // esi
    float v23; // et1
    double v24; // st7
    float v25; // et1
    unsigned __int8 v27 = 0; // c0
    unsigned __int8 v28 = 0; // c2
    double v29; // st7
    double v30; // st7
    float v31; // et1
    double v32; // st7
    float v33; // et1
    unsigned __int8 v35 = 0; // c0
    unsigned __int8 v36 = 0; // c2
    unsigned __int8 v38 = 0; // c0
    unsigned __int8 v39 = 0; // c3
    int v40; // ecx
    EntityData2* v41; // eax
    float v42; // ecx
    double v43; // st7
    double v44; // st7
    double v45; // st7
    double v46; // st7
    double v47; // st7
    double v48; // st7
    double v49; // st7
    float v50; // edx
    float analog_magnitude; // [esp+4h] [ebp-30h] BYREF
    Angle angle; // [esp+8h] [ebp-2Ch] BYREF
    int have_analog_; // [esp+Ch] [ebp-28h]
    NJS_VECTOR new_speed; // [esp+10h] [ebp-24h] BYREF
    NJS_VECTOR v55; // [esp+1Ch] [ebp-18h]
    NJS_VECTOR a3; // [esp+28h] [ebp-Ch] BYREF
    float a1a; // [esp+38h] [ebp+4h]
    float a1b; // [esp+38h] [ebp+4h]
    float a1c; // [esp+38h] [ebp+4h]

    localEntity1 = entity;
    if ((entity->Status & Status_DisableControl) != 0)
    {
        sub_447510(entity, a2, charobj);
        return;
    }
    v4 = charobj->SurfaceFlags;
    if ((v4 & 0x20000) != 0)
    {
        sub_44B0E0(entity, charobj, a2);
        return;
    }
    if ((v4 & 0x4000) != 0)
    {
        sub_447010(entity, a2, charobj);
        return;
    }
    v7 = Gravity.x * charobj->PhysicsData.Gravity;
    v5 = a2;
    v8 = a2->SomeCollisionVector.y;
    v9 = a2->SomeCollisionVector.z;
    new_speed.x = a2->SomeCollisionVector.x;
    new_speed.y = v8;
    new_speed.z = v9;
    new_speed.x = v7 + new_speed.x;
    v10 = Gravity.y * charobj->PhysicsData.Gravity;
    v55.z = 0.0;
    v55.y = 0.0;
    v55.x = 0.0;
    new_speed.y = v10 + v8;
    new_speed.z = Gravity.z * charobj->PhysicsData.Gravity + v9;
    WorldToPlayer(entity, &new_speed);
    have_analog = GetAnalog(entity, &angle, &analog_magnitude);
    v11 = (NJS_VECTOR*)&charobj->array_1x132 + 0x1C;
    have_analog_ = have_analog;
    njOuterProduct(v11, &a2->VelocityDirection, &a3);
    if (charobj->Up < 0.1 && fabs(a3.y) > 0.60000002 && charobj->Speed.x > 1.16)
    {
        v12 = 0.0;
        new_speed.x = 0.0;
        new_speed.y = -charobj->PhysicsData.Gravity;
        goto LABEL_16;
    }
    if (charobj->Up < -0.40000001 && charobj->Speed.x > 1.16)
    {
        v13 = charobj->PhysicsData.Gravity * 5.0;
    what:
        new_speed.y = new_speed.y - v13;
    LABEL_15:
        v12 = new_speed.z;
        goto LABEL_16;
    }
    if (charobj->Up < -0.30000001 && charobj->Speed.x > 1.16)
    {
        v13 = charobj->PhysicsData.Gravity * 0.80000001;
        goto what;
    }
    if (charobj->Up < -0.1 && charobj->Speed.x > 1.16)
    {
        v13 = charobj->PhysicsData.Gravity * 0.40000001;
        goto what;
    }
    if (charobj->Up >= 0.5
        || charobj->Speed.x >= (double)charobj->PhysicsData.RollEnd
        || -charobj->PhysicsData.RollEnd >= charobj->Speed.x)
    {
        if (charobj->Up >= 0.69999999
            || charobj->Speed.x >= (double)charobj->PhysicsData.RollEnd
            || -charobj->PhysicsData.RollEnd >= charobj->Speed.x)
        {
            if (charobj->Up >= 0.87
                || charobj->Speed.x >= (double)charobj->PhysicsData.RollCancel
                || -charobj->PhysicsData.RollEnd >= charobj->Speed.x)
            {
                goto LABEL_15;
            }
            v12 = new_speed.z * 1.4;
        }
        else
        {
            v12 = new_speed.z + new_speed.z;
        }
    }
    else
    {
        new_speed.x = new_speed.x * 4.2249999;
        v12 = new_speed.z * 4.2249999;
    }
LABEL_16:
    v14 = charobj->Speed.x;
    if (have_analog)
    {
        if (v14 > charobj->PhysicsData.MaxAccel && charobj->Up > 0.95999998)
        {
            v21 = (charobj->Speed.x - charobj->PhysicsData.MaxAccel) * charobj->PhysicsData.RollDecel * 1.7;
            goto LABEL_43;
        }
    }
    else if (v14 > charobj->PhysicsData.RollEnd)
    {
    LABEL_42:
        v21 = charobj->PhysicsData.RollDecel * charobj->Speed.x;
        goto LABEL_43;
    }
    v15 = charobj->Speed.x;
    v17 = charobj->PhysicsData.MaxAccel;
    v16 = charobj->Speed.x;
    if (v19 | v20)
    {
        if (v16 >= 0.0)
        {
            goto LABEL_44;
        }
        goto LABEL_42;
    }
    v21 = (v16 - charobj->PhysicsData.MaxAccel) * charobj->PhysicsData.RollDecel;
LABEL_43:
    new_speed.x = v21 + new_speed.x;
LABEL_44:
    new_speed.y = charobj->PhysicsData.GravityAdd * charobj->Speed.y + new_speed.y;
    new_speed.z = charobj->PhysicsData.HitSpeed * charobj->Speed.z + v12;
    if (have_analog)
    {
        if ((entity->Status & Status_OnPath) != 0)
        {
            FollowSpline(charobj, a2, entity);
            analogAngleModified = a2->Forward.y;
            v55.y = -0.80000001;
        }
        else
        {
            if (charobj->Up < 0.94 && (charobj->SurfaceFlags & 0x800000) != 0)
            {
                //sub_449380(entity, a2, charobj);
                localEntity1 = entity;
                v5 = a2;
            }
            analogAngleModified = angle;
            if (entity->Status & Status_Ball)
                //analogAngleModified = BAMS_SubWrap(a2->Forward.y, (int)angle, 4096) / 3;
                analogAngleModified = 0;
        }
        v23 = charobj->Speed.x;
        v25 = charobj->PhysicsData.MaxAccel;
        v24 = charobj->Speed.x;
        if (v27 | v28)
        {
            if (v24 < charobj->PhysicsData.RollCancel)
            {
                if (analog_magnitude > 0.5)
                {
                LABEL_67:
                    v30 = analog_magnitude * charobj->PhysicsData.GroundAccel;
                    goto LABEL_77;
                }
                v29 = charobj->PhysicsData.RollCancel * 0.40000001;
            LABEL_66:
                if (v29 <= charobj->Speed.x)
                {
                    analog_magnitude = 0.0;
                LABEL_78:
                    v40 = BAMS_Subtract(localEntity1->Rotation.y, analogAngleModified);
                    if (charobj->Speed.x == 0.0 && v40 > 4096)
                    {
                        v5->Forward.y = analogAngleModified;
                        analog_magnitude = 0.0;
                        //sub_443DF0(charobj, localEntity1, v5, analogAngleModified);
                    LABEL_95:
                        have_analog = have_analog_;
                        v42 = analog_magnitude;
                        a2->field_34 = analog_magnitude;
                        v55.x = v42;
                        v5 = a2;
                        goto LABEL_96;
                    }
                    if ((charobj->PhysicsData.RollEnd + charobj->PhysicsData.RollCancel) * 0.5 > charobj->Speed.x
                        || v40 <= 4096)
                    {
                        if (charobj->Speed.x >= (double)charobj->PhysicsData.RollCancel && v40 < 4096
                            || charobj->Speed.x >= (double)charobj->PhysicsData.Run2
                            && (charobj->SurfaceFlags & 0x800000) != 0)
                        {
                            a2->Forward.y = analogAngleModified;
                            //sub_443E60(entity, charobj, a2, analogAngleModified);
                            goto LABEL_95;
                        }
                        if (charobj->Speed.x >= (double)charobj->PhysicsData.RollCancel
                            && charobj->Speed.x <= (double)charobj->PhysicsData.Run1
                            && v40 > 0x2000)
                        {
                            analog_magnitude = analog_magnitude * 0.80000001;
                        }
                        v41 = a2;
                        a2->Forward.y = analogAngleModified;
                    }
                    else
                    {
                        v41 = a2;
                        a2->Forward.y = analogAngleModified;
                        analog_magnitude = charobj->PhysicsData.GroundDecel;
                    }
                    RotateTowards(charobj, entity, v41, analogAngleModified);
                    goto LABEL_95;
                }
                goto LABEL_67;
            }
            if (charobj->Speed.x < (double)charobj->PhysicsData.RollEnd)
            {
                if (analog_magnitude > 0.69999999)
                {
                    v30 = analog_magnitude * charobj->PhysicsData.GroundAccel;
                LABEL_77:
                    analog_magnitude = v30;
                    goto LABEL_78;
                }
                v29 = (charobj->PhysicsData.RollEnd + charobj->PhysicsData.RollEnd) * 0.5;
                goto LABEL_66;
            }
            v31 = charobj->Speed.x;
            v33 = charobj->PhysicsData.Run1;
            v32 = analog_magnitude;
            if (v35 | v36)
            {
                v30 = analog_magnitude * charobj->PhysicsData.GroundAccel;
                if (v38 | v39)
                {
                    v30 = v30 * 0.30000001;
                }
                goto LABEL_77;
            }
        }
        else
        {
            if (v24 < charobj->PhysicsData.MaxAccel || charobj->Up >= 0.0)
            {
                v30 = analog_magnitude * charobj->PhysicsData.GroundAccel * 0.40000001;
                goto LABEL_77;
            }
            v32 = analog_magnitude;
        }
        v30 = v32 * charobj->PhysicsData.GroundAccel;
        goto LABEL_77;
    }
    if (charobj->Up >= 0.70999998)
    {
        if (charobj->Speed.x <= 0.0)
        {
            if (charobj->Speed.x < 0.0)
            {
                v55.x = -charobj->PhysicsData.GroundDecel;
            }
            a2->field_34 = 0.0;
        }
        else
        {
            v55.x = charobj->PhysicsData.GroundDecel;
            a2->field_34 = 0.0;
        }
    }
    else
    {
        sub_4491E0(entity, a2, charobj);
        a2->field_34 = 0.0;
    }
LABEL_96:
    if (charobj->Up < 0.70999998
        && charobj->Speed.x < (double)charobj->PhysicsData.RollCancel
        && -charobj->PhysicsData.RollCancel < charobj->Speed.x
        && !have_analog)
    {
        new_speed.x = new_speed.x * 10.0;
        new_speed.z = new_speed.z * 10.0;
        goto LABEL_144;
    }
    if (charobj->Speed.x == 0.0)
    {
        a1a = charobj->PhysicsData.field_68 * v5->SomeMultiplier * new_speed.y;
        new_speed.x = new_speed.x + v55.x;
        if (!have_analog
            && (new_speed.x < (double)a1a && -a1a < new_speed.x || new_speed.x < 0.050999999 && new_speed.x > -0.050999999))
        {
            new_speed.x = 0.0;
        }
        goto LABEL_144;
    }
    if (v55.x < 0.0)
    {
        if ((charobj->SurfaceFlags & 4) == 0)
        {
            if (charobj->Speed.x <= 0.0)
            {
                if (!have_analog
                    && charobj->Speed.x <= (double)charobj->PhysicsData.RollCancel
                    && new_speed.x < 0.050999999
                    && new_speed.x > -0.050999999
                    || (v44 = charobj->PhysicsData.field_68 * v5->SomeMultiplier * new_speed.y + v55.x, v44 >= 0.0))
                {
                    v44 = 0.0;
                }
            }
            else
            {
                v44 = new_speed.x + v55.x;
                if (v55.x * v44 < 0.0)
                {
                    v44 = 0.0;
                }
            }
            goto LABEL_143;
        }
        if (new_speed.y < 0.0)
        {
            v43 = charobj->PhysicsData.MinSpeed * v5->SomeMultiplier * new_speed.y;
            a1b = v43;
            if (v43 > 0.0 && -v55.x > a1b)
            {
                v44 = new_speed.x + v55.x;
                if (v44 < 0.0)
                {
                    *(float*)&angle = -a1b;
                    if (v44 < *(float*)&angle)
                    {
                        v5->field_38 = v44 - a1b;
                        v44 = *(float*)&angle;
                    LABEL_143:
                        new_speed.x = v44;
                        goto LABEL_144;
                    }
                }
                if (v44 <= 0.0)
                {
                    goto LABEL_143;
                }
            LABEL_135:
                if (v44 > a1b)
                {
                    v5->field_38 = v44 - a1b;
                    v44 = a1b;
                }
                goto LABEL_143;
            }
        }
        goto LABEL_137;
    }
    a1b = charobj->PhysicsData.field_68 * v5->SomeMultiplier * new_speed.y;
    if (charobj->Speed.x >= 0.0 || new_speed.x >= 0.050999999 || new_speed.x <= -0.050999999)
    {
        if (a1b > 0.0 && a1b < (double)v55.x)
        {
            v44 = new_speed.x + v55.x;
            goto LABEL_135;
        }
    LABEL_137:
        if (!have_analog
            && charobj->Speed.x <= (double)charobj->PhysicsData.RollCancel
            && new_speed.x < 0.050999999
            && new_speed.x > -0.050999999)
        {
            new_speed.x = 0.0;
            goto LABEL_144;
        }
        v44 = new_speed.x + v55.x;
        goto LABEL_143;
    }
    v45 = new_speed.x + v55.x;
    new_speed.x = v45;
    if (v45 * v55.x < 0.0)
    {
        new_speed.x = 0.0;
    }
LABEL_144:
    if (charobj->Speed.z == 0.0)
    {
        v46 = charobj->PhysicsData.field_68 * v5->SomeMultiplier * new_speed.y;
        if (new_speed.z < v46 && -v46 < new_speed.z)
        {
            new_speed.z = 0.0;
        }
        goto LABEL_168;
    }
    if (new_speed.y >= 0.0)
    {
        a1c = 0.0;
    }
    else
    {
        a1c = charobj->PhysicsData.field_64 * v5->SomeMultiplier * new_speed.y;
    }
    v47 = new_speed.z;
    if ((charobj->SurfaceFlags & 4) == 0)
    {
        if (v47 <= 0.0)
        {
            if (new_speed.z < 0.0)
            {
                v55.z = a1c;
            }
        }
        else
        {
            v55.z = -a1c;
        }
        v48 = new_speed.z + v55.z;
        if (new_speed.z != 0.0 && v55.z != 0.0 && new_speed.z * v48 < 0.0)
        {
            v48 = 0.0;
        }
        new_speed.z = v48;
        goto LABEL_168;
    }
    if (v47 <= 0.0)
    {
        if (v47 < 0.0)
        {
            v47 = v47 + a1c;
            if (v47 > 0.0)
            {
                v47 = 0.0;
            }
        }
        goto LABEL_158;
    }
    v47 = v47 - a1c;
    if (v47 >= 0.0)
    {
    LABEL_158:
        new_speed.z = v47;
        goto LABEL_168;
    }
    new_speed.z = 0.0;
LABEL_168:
    v49 = new_speed.y + v55.y;
    v50 = new_speed.z;
    charobj->field_2C.x = new_speed.x;
    new_speed.y = v49;
    charobj->field_2C.y = new_speed.y;
    charobj->field_2C.z = v50;
}*/