#include "stdafx.h"

#include "Tails.h"

/*const void* Tails_Act1_Ptr = reinterpret_cast<void*>(0x0045E5D0);

void _cdecl Tails_Act1_r(CharObj2* data2, EntityData2* data2_pp, EntityData1* data1)
{
    EntityData1* _data1; // ebp
    int v6; // eax
    __int16 v7; // ax
    __int16 v8; // ax
    signed int v9; // eax
    CollisionInfo* v10; // eax
    __int16 v11; // cx
    __int16 v12; // cx
    __int16 v13; // ax
    Sint8 v14; // cl
    _BOOL1 v15; // zf
    __int16 v16; // ax
    __int16 v17; // cx
    Sint8 v18; // al
    _BOOL1 v19; // zf
    CollisionInfo* v20; // eax
    __int16 v21; // dx
    int v22; // eax
    __int16 v23; // ax
    __int16 v24; // ax
    Sint8 v25; // al
    Sint8 v26; // al
    int v27; // eax
    signed int v28; // eax
    ObjectMaster* v29; // eax
    ObjectMaster* v30; // eax
    signed int v31; // eax
    __int16 v32; // ax
    ObjectMaster* v33; // eax
    ObjectMaster* v34; // eax
    CollisionInfo* v35; // eax
    __int16 v36; // dx
    int v37; // eax
    signed int v38; // eax
    signed int v39; // eax
    double v40; // st7
    _BOOL1 v41; // c0
    _BOOL1 v42; // c3
    __int16 v43; // ax
    ObjectMaster* v44; // eax
    DataPtr1 v45; // eax
    int v46; // eax
    ObjectMaster* v47; // eax
    DataPtr1 v48; // eax
    int v49; // ecx
    _BOOL1 v50; // c0
    void* v51; // eax
    float* v52; // eax
    _DWORD* v53; // esi
    int v54; // eax
    int v55; // eax
    int v56; // eax
    _BOOL1 v57; // c0
    void* v58; // eax
    float* v59; // eax
    double v60; // st7
    double v61; // st7
    __int16 v62; // ax
    EntityData2* v63; // [esp-4h] [ebp-38h]
    Vector3 a2a; // [esp+10h] [ebp-24h] BYREF
    Vector3 a3a; // [esp+1Ch] [ebp-18h] BYREF
    Vector3 vd; // [esp+28h] [ebp-Ch] BYREF

    _data1 = data1;
    if (IsLevelChaoGarden())
    {
        v6 = sub_459B50(_data1);
        sub_442720(_data1->CharIndex.UByte[0], v6);
    }
    if (data2 && data2->Powerups < 0)
    {
        _data1->Status |= 32768u;
        _data1->InvulnerableTime = 0;
    }
    else
    {
        v7 = _data1->InvulnerableTime;
        if (v7)
        {
            LOBYTE(_data1->Status) &= ~4u;
            _data1->InvulnerableTime = v7 - 1;
        }
        else if (Tails_Hurt(data2, _data1, data2_pp))
        {
            _data1->Status |= Status_Unknown7;
            if ((_data1->Status & Status_HoldObject) != 0)
            {
                sub_45AA80(data2, _data1);
            }
            HIBYTE(_data1->Status) &= 0xC6u;
            v8 = data2->Powerups;
            if ((v8 & 3) != 0)
            {
                data2->Powerups = v8 & 0xFFFC;
            }
            else
            {
                HurtCharacter(_data1->CharIndex.SByte[0]);
            }
        }
        else
        {
            HIBYTE(_data1->Status) &= 0x7Fu;
        }
    }
    switch (_data1->Action)
    {
    case 1:
        if (sub_45C100(data2, _data1, data2_pp)
            || sub_45CE30(data2, _data1)
            || sub_45BFE0(data2, _data1)
            || sub_45A9C0(data2, _data1)
            || sub_45D6D0(data2, _data1))
        {
            return;
        }
        if (sub_442680(_data1))
        {
            _data1->Action = 63;
            data2->AnimationThing.Index = 132;
        }
        else
        {
            data1 = (EntityData1*)("\aStop!  Come back here!" + 17);
            if (sub_442570(_data1, data2_pp, data2, 8864257) == 1)
            {
                return;
            }
        }
        if (GetAnalog(_data1, 0, 0))
        {
            goto LABEL_282;
        }
        if (data2->array_1x132->njs_vector1C.y < 0.76999998
            && njScalor(&data2->Speed) >(double)data2->PhysicsData.slide_speed)
        {
            _data1->Action = 17;
            data2->AnimationThing.Index = 23;
        }
        return;
    case 2:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if (sub_45CE30(data2, _data1) || sub_45BFE0(data2, _data1))
            {
                goto LABEL_52;
            }
            if (data2->Speed.x <= 2.0)
            {
                v9 = sub_45D6D0(data2, _data1);
            }
            else
            {
                v9 = sub_473C10((int)_data1, (int)data2);
            }
            if (!v9 && !sub_45A9C0(data2, _data1))
            {
                if (sub_45D6D0(data2, _data1) || sub_45CEB0((int)data2, (int)_data1))
                {
                    goto LABEL_52;
                }
                v10 = _data1->CollisionInfo;
                v11 = v10->Flags;
                if ((v11 & 0x10) != 0
                    && (_data1->Status & 4) == 0
                    && (v10->CollidingObject->CollisionArray[v10->field_A2].flags & 0x2000) == 0
                    && (v11 & 4) != 0
                    && sub_43C060(_data1) == 4)
                {
                    _data1->Action = 12;
                    data2->AnimationThing.Index = 24;
                    _data1->Status &= 0xDFFFu;
                }
                if (sub_4429C0(_data1) && data2->Speed.x >= (double)data2->PhysicsData.jog_speed)
                {
                    _data1->Action = 11;
                    data2->AnimationThing.Index = 21;
                    sub_45BDF0(_data1, 18);
                    _data1->Status &= 0xDFFFu;
                }
            }
        }
        return;
    case 3:
        HIBYTE(_data1->Status) &= 0xFAu;
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if (sub_45CE30(data2, _data1) || sub_45BFE0(data2, _data1))
            {
                goto LABEL_52;
            }
            if (data2->Speed.x < (double)data2->PhysicsData.jog_speed)
            {
                _data1->Action = 2;
                data2->AnimationThing.Index = 9;
                goto LABEL_52;
            }
            if (sub_45CEB0((int)data2, (int)_data1))
            {
                HIBYTE(_data1->Status) &= 0xDFu;
            }
        }
        return;
    case 4:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            goto LABEL_62;
        }
        if (sub_45CE30(data2, _data1) || sub_45BFE0(data2, _data1))
        {
            data2->AnimationThing.Index = 14;
            data2->SpindashSpeed = 2.0;
            HIBYTE(_data1->Status) |= 5u;
            _data1->Rotation.z = 0;
            _data1->Rotation.x = 0;
            return;
        }
        if (sub_45A970((int)data2, (int)_data1))
        {
            goto LABEL_62;
        }
        if ((AttackButtons & Controllers[_data1->CharIndex.UByte[0]].PressedButtons) != 0)
        {
            _data1->Action = 2;
            data2->AnimationThing.Index = 36;
        LABEL_62:
            HIBYTE(_data1->Status) &= 0xFAu;
        }
        return;
    case 5:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if (sub_45CE30(data2, _data1))
            {
                data2->AnimationThing.Index = 14;
                data2->SpindashSpeed = 5.0;
                _data1->Rotation.z = 0;
                _data1->Rotation.x = 0;
                _data1->Status = _data1->Status & ~0x2000 | 0x500;
            }
            else if (data2->Speed.x < 1.85)
            {
                data2->AnimationThing.Index = 14;
                data2->SpindashSpeed = 5.0;
                v12 = _data1->Status;
                _data1->Rotation.z = 0;
                _data1->Rotation.x = 0;
                _data1->Status = v12 & ~0x2000 | 0x500;
            }
        }
        return;
    case 6:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if ((_data1->Status & 3) != 0)
            {
                sub_45BDF0(_data1, 33);
                if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
                {
                    _data1->Action = 11;
                    data2->AnimationThing.Index = 21;
                    HIBYTE(_data1->Status) &= 0xFAu;
                }
                else
                {
                    if (!sub_45CEB0((int)data2, (int)_data1))
                    {
                        _data1->Rotation.x = data2_pp->Forward.x;
                        _data1->Rotation.z = data2_pp->Forward.z;
                        _data1->Action = 2;
                        goto LABEL_79;
                    }
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    if (data2_pp->VelocityDirection.y <= -5.0)
                    {
                        data2->AnimationThing.Index = 20;
                    }
                    else
                    {
                        data2->AnimationThing.Index = 2;
                    }
                    HIBYTE(_data1->Status) &= 0xFAu;
                }
            }
            else
            {
                if (JumpAllowed(_data1))
                {
                    HIBYTE(_data1->Status) &= 0xFAu;
                    _data1->Action = 15;
                    data2->AnimationThing.Index = 37;
                    data2->TailsFlightTime = 0.0;
                    v13 = _data1->Status;
                    v14 = _data1->Object.SByte[3] & 0xFE;
                    _data1->Object.SByte[2] |= 1u;
                    _data1->Object.SByte[3] = v14;
                    _data1->Status = v13 & 0xFEFF | 0x400;
                    if (!_data1->CharIndex.SByte[0] && sub_4BD3F0())
                    {
                        v15 = (((unsigned __int16)CurrentAct | (unsigned __int16)(CurrentLevel << 8)) & 0xFF00) == 2304;
                        goto LABEL_116;
                    }
                    goto LABEL_118;
                }
                if (!sub_45A830((int)data2, (int)_data1))
                {
                    if (DoJumpThing(_data1, data2))
                    {
                        data2->Speed.y = data2->PhysicsData.jmp_addit * 0.80000001 + data2->Speed.y;
                    }
                }
            }
        }
        return;
    case 7:
        if (!sub_45C100(data2, _data1, data2_pp) && data2_pp->VelocityDirection.y <= 0.0)
        {
            _data1->Action = 10;
            v16 = data2->AnimationThing.Index;
            if (v16 == 64)
            {
                data2->AnimationThing.Index = 65;
            }
            else
            {
                data2->AnimationThing.Index = v16 != 66 ? 18 : 67;
            }
        }
        return;
    case 8:
        if (!sub_45C100(data2, _data1, data2_pp) && data2_pp->VelocityDirection.y <= 0.0)
        {
            _data1->Action = 10;
            data2->AnimationThing.Index = 18;
        }
        return;
    case 9:
        if (!sub_45C100(data2, _data1, data2_pp) && (_data1->Status & 3) != 0)
        {
            sub_45BDF0(_data1, 33);
            if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
            {
                goto LABEL_125;
            }
            if (!sub_45CEB0((int)data2, (int)_data1))
            {
                goto LABEL_162;
            }
            _data1->Rotation.x = data2_pp->Forward.x;
            _data1->Rotation.z = data2_pp->Forward.z;
            if (data2_pp->VelocityDirection.y <= -5.0)
            {
                goto LABEL_376;
            }
            data2->AnimationThing.Index = 2;
        }
        return;
    case 0xA:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if ((_data1->Status & 3) != 0)
            {
                if ((_data1->Object.SByte[3] & 2) != 0)
                {
                    sub_436140();
                }
                _data1->Object.SByte[2] &= 0xFEu;
                sub_45BDF0(_data1, 33);
                if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
                {
                    goto LABEL_125;
                }
                if (!sub_45CEB0((int)data2, (int)_data1))
                {
                    goto LABEL_162;
                }
                _data1->Rotation.x = data2_pp->Forward.x;
                _data1->Rotation.z = data2_pp->Forward.z;
                if (data2_pp->VelocityDirection.y <= -5.0)
                {
                    goto LABEL_376;
                }
                data2->AnimationThing.Index = 1;
            }
            else if (JumpAllowed(_data1))
            {
                HIBYTE(_data1->Status) &= 0xFAu;
                _data1->Action = 15;
                data2->AnimationThing.Index = 37;
                data2->TailsFlightTime = 0.0;
                v17 = _data1->Status;
                v18 = _data1->CharIndex.SByte[0];
                _data1->Object.SByte[2] |= 1u;
                _data1->Status = v17 & 0xFEFF | 0x400;
                _data1->Object.SByte[3] &= 0xFEu;
                if (!v18 && sub_4BD3F0())
                {
                    v15 = (((unsigned __int16)CurrentAct | (unsigned __int16)(CurrentLevel << 8)) & 0xFF00) == 2304;
                LABEL_116:
                    if (!v15)
                    {
                        _data1->Object.SByte[3] |= 2u;
                        sub_437D20((int)sub_469590, 20, 2);
                    }
                }
            LABEL_118:
                sub_45BDF0(_data1, 1243);
            }
        }
        return;
    case 0xB:
        if (!sub_45C100(data2, _data1, data2_pp) && !sub_45CE30(data2, _data1) && !sub_45BFE0(data2, _data1))
        {
            if (data2->Speed.x > 0.0 || !sub_4429C0(_data1))
            {
                v19 = data2->AnimationThing.Index == 21;
                goto LABEL_523;
            }
            _data1->Action = 2;
            data2->AnimationThing.Index = 22;
            sub_44BB60(_data1, data2_pp, data2);
            _data1->Rotation.y = data2_pp->Forward.y;
        }
        return;
    case 0xC:
        if (sub_45C100(data2, _data1, data2_pp)
            || sub_45BFE0(data2, _data1)
            || sub_45CE30(data2, _data1)
            || sub_45CEB0((int)data2, (int)_data1))
        {
            goto LABEL_356;
        }
        v20 = _data1->CollisionInfo;
        v21 = v20->Flags;
        if ((v21 & 0x10) == 0
            || (_data1->Status & 4) != 0
            || (v20->CollidingObject->CollisionArray[v20->field_A2].flags & 0x2000) != 0
            || (v21 & 4) == 0)
        {
            goto LABEL_360;
        }
        v22 = sub_43C060(_data1) - 3;
        if (v22)
        {
            if (v22 != 1)
            {
                goto LABEL_146;
            }
        }
        else if ((_data1->Status & 0x800) == 0)
        {
            _data1->Action = 2;
            data2->AnimationThing.Index = 9;
            goto LABEL_356;
        }
        return;
    case 0xD:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            v23 = data2->AnimationThing.Index;
            if (v23 != 26 && v23 != 27)
            {
                if (sub_45CEB0((int)data2, (int)_data1))
                {
                    goto LABEL_524;
                }
                goto LABEL_154;
            }
            v24 = _data1->InvulnerableTime;
            if (!v24)
            {
                if ((_data1->Status & 3) == 0)
                {
                    goto LABEL_313;
                }
                goto LABEL_162;
            }
            if ((unsigned __int16)v24 <= 0x3Cu && GetAnalog(_data1, 0, 0))
            {
                if (!sub_45BFE0(data2, _data1) && (_data1->Status & 3) != 0)
                {
                    goto LABEL_162;
                }
            }
            else if (_data1->InvulnerableTime != 120 && (_data1->Status & 3) != 0)
            {
                _data1->Rotation.x = data2_pp->Forward.x;
                _data1->Rotation.z = data2_pp->Forward.z;
                data2->AnimationThing.Index = 27;
            }
        }
        return;
    case 0xE:
        if (!sub_45C100(data2, _data1, data2_pp)
            && !sub_45CE30(data2, _data1)
            && !sub_45BFE0(data2, _data1)
            && !sub_45CEB0((int)data2, (int)_data1)
            && data2->Speed.x >= 0.0)
        {
        LABEL_154:
            _data1->Action = 2;
            sub_459DA0(data2, data2_pp, _data1);
        }
        return;
    case 0xF:
        v15 = sub_45C100(data2, _data1, data2_pp) == 0;
        v25 = _data1->Object.SByte[3];
        if (v15)
        {
            if ((v25 & 1) != 0)
            {
                _data1->Action = 10;
                NullifyVelocity(0, data2);
                data2->AnimationThing.Index = 19;
                v26 = _data1->Object.SByte[2];
                _data1->Status &= 0xFBFFu;
                _data1->Object.SByte[2] = v26 & 0xFE;
            }
            if ((_data1->Status & 3) != 0)
            {
                if ((_data1->Object.SByte[3] & 2) != 0)
                {
                    sub_436140();
                }
                _data1->Object.SByte[2] &= 0xFEu;
                sub_45BDF0(_data1, 33);
                if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
                {
                    _data1->Action = 11;
                    data2->AnimationThing.Index = 21;
                }
                else if (sub_45CEB0((int)data2, (int)_data1))
                {
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    data2->AnimationThing.Index = 1;
                }
                else
                {
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    _data1->Action = 2;
                    sub_459DA0(data2, data2_pp, _data1);
                }
                data2->SomeFrameNumberThing = 0.80000001;
                _data1->Status &= 0xFBFFu;
            }
            v27 = (unsigned __int16)data2->AnimationThing.Index;
            if (v27 == 37)
            {
                if (fabs(data2->Speed.y) > 2.0)
                {
                    data2->AnimationThing.Index = 40;
                }
            }
            else if (v27 == 40 && fabs(data2->Speed.y) < 1.5)
            {
                data2->AnimationThing.Index = 37;
            }
        }
        else
        {
            if ((v25 & 2) != 0)
            {
                sub_436140();
            }
            _data1->Object.SByte[2] &= 0xFEu;
        }
        return;
    case 0x10:
        if (data2->AnimationThing.Index != 34 && !sub_45CE30(data2, _data1))
        {
            v19 = data2->AnimationThing.Index == 35;
            goto LABEL_523;
        }
        return;
    case 0x11:
        if (!sub_45C100(data2, _data1, data2_pp)
            && !sub_45CE30(data2, _data1)
            && !sub_45BFE0(data2, _data1)
            && !sub_45D6D0(data2, _data1))
        {
            if (GetAnalog(_data1, 0, 0))
            {
                goto LABEL_282;
            }
            if (njScalor(&data2_pp->VelocityDirection) < (double)data2->PhysicsData.slide_speed
                || data2->array_1x132->njs_vector1C.y > 0.98000002)
            {
                goto LABEL_184;
            }
        }
        return;
    case 0x12:
        v63 = data2_pp;
        if ((_data1->Status & 0x800) != 0)
        {
            goto LABEL_502;
        }
        goto LABEL_173;
    case 0x13:
        if (sub_45C100(data2, _data1, data2_pp) || (_data1->Status & 3) == 0)
        {
            return;
        }
        if ((_data1->Object.SByte[3] & 2) != 0)
        {
            sub_436140();
        }
        _data1->Object.SByte[2] &= 0xFEu;
        sub_45BDF0(_data1, 33);
        if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
        {
        LABEL_125:
            _data1->Action = 11;
            data2->AnimationThing.Index = 21;
            return;
        }
        if (sub_45CEB0((int)data2, (int)_data1))
        {
            _data1->Rotation.x = data2_pp->Forward.x;
            _data1->Rotation.z = data2_pp->Forward.z;
            if (data2_pp->VelocityDirection.y <= -5.0)
            {
                goto LABEL_376;
            }
            data2->AnimationThing.Index = 1;
        }
        else
        {
        LABEL_162:
            _data1->Rotation.x = data2_pp->Forward.x;
            _data1->Rotation.z = data2_pp->Forward.z;
            _data1->Action = 2;
            sub_459DA0(data2, data2_pp, _data1);
        }
        return;
    case 0x14:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            goto LABEL_253;
        }
        if (data2->AnimationThing.Index)
        {
            sub_45E280(data2, _data1);
            Tails_LoadAttackEffect(data2_pp, data2, _data1);
        }
        else
        {
            _data1->Action = 1;
            data2->AnimationThing.Index = 0;
        LABEL_253:
            _data1->Object.SByte[2] &= 0xFDu;
        }
        return;
    case 0x15:
        if ((_data1->Status & 0x800) != 0)
        {
            v28 = sub_45C850((int)data2, (int)_data1, (int)data2_pp);
        }
        else
        {
            v28 = sub_45C100(data2, _data1, data2_pp);
        }
        if (!v28 && !sub_45CE30(data2, _data1))
        {
            sub_45CF40((int)data2, (int)_data1);
        }
        return;
    case 0x16:
    case 0x1A:
        if ((_data1->Status & 0x800) != 0)
        {
            v31 = sub_45C850((int)data2, (int)_data1, (int)data2_pp);
        }
        else
        {
            v31 = sub_45C100(data2, _data1, data2_pp);
        }
        if (v31)
        {
            return;
        }
        if (sub_45D0F0(_data1, data2))
        {
            return;
        }
        v32 = data2->AnimationThing.Index;
        if (v32 == 84 || v32 == 85)
        {
            return;
        }
        v19 = v32 == 88;
        goto LABEL_523;
    case 0x17:
        if (!sub_45C850((int)data2, (int)_data1, (int)data2_pp) && !sub_45CE30(data2, _data1))
        {
            v29 = data2->ObjectHeld;
            if (!v29 || v29->Data1.Unknown && v29->Data2.Entity)
            {
                if ((GrabButtons & Controllers[_data1->CharIndex.UByte[0]].HeldButtons) != 0
                    && GetAnalog(_data1, 0, 0)
                    && *((_BYTE*)data2->ObjectHeld->Data1.Unknown + 2) == 4)
                {
                    _data1->Action = 35;
                    data2->AnimationThing.Index = 75;
                }
                else if (!sub_45D000(data2, _data1, data2_pp)
                    && !sub_45BFE0(data2, _data1)
                    && GetAnalog(_data1, 0, 0))
                {
                    _data1->Action = 25;
                    data2->AnimationThing.Index = 63;
                }
            }
            else
            {
                HIBYTE(_data1->Status) &= 0xF7u;
                data2->ObjectHeld = 0;
                _data1->Action = 1;
                data2->IdleTime = 0;
                data2->AnimationThing.Index = 2;
            }
        }
        return;
    case 0x18:
        if (!sub_45D350((int)data2, (CharObj1*)_data1))
        {
            sub_45BFE0(data2, _data1);
        }
        return;
    case 0x19:
        if (sub_45C850((int)data2, (int)_data1, (int)data2_pp))
        {
            return;
        }
        v30 = data2->ObjectHeld;
        if (!v30 || v30->Data1.Unknown && v30->Data2.Entity)
        {
            if (sub_45CE30(data2, _data1)
                || sub_45BFE0(data2, _data1)
                || sub_45D000(data2, _data1, data2_pp)
                || sub_45CEB0((int)data2, (int)_data1))
            {
            LABEL_52:
                HIBYTE(_data1->Status) &= 0xDFu;
            }
            else if (!sub_45D000(data2, _data1, data2_pp)
                && sub_4429C0(_data1)
                && data2->Speed.x >= (double)data2->PhysicsData.jog_speed)
            {
                _data1->Action = 27;
                data2->AnimationThing.Index = 60;
                sub_45BDF0(_data1, 18);
                HIBYTE(_data1->Status) &= 0xDFu;
            }
        }
        else
        {
            HIBYTE(_data1->Status) &= 0xF7u;
            data2->ObjectHeld = 0;
        LABEL_282:
            _data1->Action = 2;
            data2->AnimationThing.Index = 9;
        }
        return;
    case 0x1B:
        if (sub_45C850((int)data2, (int)_data1, (int)data2_pp)
            || sub_45CE30(data2, _data1)
            || sub_45BFE0(data2, _data1))
        {
            return;
        }
        if (data2->Speed.x <= 0.0 && sub_4429C0(_data1))
        {
            _data1->Action = 25;
            data2->AnimationThing.Index = 61;
            sub_44BB60(_data1, data2_pp, data2);
            _data1->Rotation.y = data2_pp->Forward.y;
            return;
        }
        if (data2->AnimationThing.Index == 60)
        {
            return;
        }
        _data1->Action = 23;
        goto LABEL_307;
    case 0x1C:
        if (sub_45C850((int)data2, (int)_data1, (int)data2_pp))
        {
            return;
        }
        v33 = data2->ObjectHeld;
        if (!v33 || v33->Data1.Unknown && v33->Data2.Entity)
        {
            if ((_data1->Status & 3) != 0)
            {
                sub_45BDF0(_data1, 33);
                if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
                {
                    goto LABEL_369;
                }
                if (sub_45CEB0((int)data2, (int)_data1))
                {
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    if (data2_pp->VelocityDirection.y <= -5.0)
                    {
                        goto LABEL_373;
                    }
                    data2->AnimationThing.Index = 62;
                }
                else
                {
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    _data1->Action = 25;
                    sub_459DA0(data2, data2_pp, _data1);
                }
            }
            else if (sub_45D000(data2, _data1, data2_pp))
            {
                HIBYTE(_data1->Status) &= 0xDFu;
            }
        }
        else
        {
            HIBYTE(_data1->Status) &= 0xF7u;
            data2->ObjectHeld = 0;
        LABEL_313:
            _data1->Action = 10;
            data2->AnimationThing.Index = 19;
        }
        return;
    case 0x1D:
        if (sub_45C850((int)data2, (int)_data1, (int)data2_pp))
        {
            return;
        }
        v34 = data2->ObjectHeld;
        if (!v34 || v34->Data1.Unknown && v34->Data2.Entity)
        {
            if ((_data1->Status & 3) != 0)
            {
                sub_45BDF0(_data1, 33);
                if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
                {
                    _data1->Action = 27;
                    data2->AnimationThing.Index = 60;
                    HIBYTE(_data1->Status) &= 0xFAu;
                }
                else if (sub_45CEB0((int)data2, (int)_data1))
                {
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    if (data2_pp->VelocityDirection.y <= -5.0)
                    {
                        data2->AnimationThing.Index = 83;
                    }
                    else
                    {
                        data2->AnimationThing.Index = 62;
                    }
                    HIBYTE(_data1->Status) &= 0xFAu;
                }
                else
                {
                    _data1->Rotation.x = data2_pp->Forward.x;
                    _data1->Rotation.z = data2_pp->Forward.z;
                    _data1->Action = 25;
                LABEL_79:
                    sub_459DA0(data2, data2_pp, _data1);
                    HIBYTE(_data1->Status) &= 0xFAu;
                }
            }
            else
            {
                if (DoJumpThing(_data1, data2))
                {
                    data2->Speed.y = data2->PhysicsData.jmp_addit * 0.40000001 + data2->Speed.y;
                }
                if (!sub_45D000(data2, _data1, data2_pp))
                {
                LABEL_341:
                    if (data2_pp->VelocityDirection.y <= 0.0)
                    {
                        _data1->Action = 28;
                        data2->AnimationThing.Index = 81;
                    }
                }
            }
        }
        else
        {
            HIBYTE(_data1->Status) &= 0xF7u;
            data2->ObjectHeld = 0;
            _data1->Action = 6;
            data2->AnimationThing.Index = 14;
        }
        return;
    case 0x1E:
    case 0x1F:
        goto LABEL_341;
    case 0x20:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45BFE0(data2, _data1) || sub_45CE30(data2, _data1))
        {
            goto LABEL_356;
        }
        if ((GrabButtons & Controllers[_data1->CharIndex.UByte[0]].HeldButtons) == 0)
        {
            sub_45BE80(data2, _data1);
            sub_45AA80(data2, _data1);
            if (_data1->CharIndex.SByte[0] != 1)
            {
                DoSoundQueueThing(15);
            }
        }
        v35 = _data1->CollisionInfo;
        v36 = v35->Flags;
        if ((v36 & 0x10) == 0
            || (_data1->Status & 4) != 0
            || (v35->CollidingObject->CollisionArray[v35->field_A2].flags & 0x2000) != 0
            || (v36 & 4) == 0)
        {
        LABEL_360:
            sub_45AA80(data2, _data1);
        LABEL_361:
            _data1->Action = 2;
            data2->AnimationThing.Index = 9;
            goto LABEL_356;
        }
        v37 = sub_43C060(_data1);
        if (v37)
        {
            if (v37 == 4)
            {
                _data1->Action = 12;
                data2->AnimationThing.Index = 24;
                goto LABEL_356;
            }
        LABEL_146:
            if ((_data1->Status & 0x800) != 0)
            {
                _data1->Action = 32;
                data2->AnimationThing.Index = 73;
                goto LABEL_356;
            }
            goto LABEL_361;
        }
        if ((_data1->Status & 0x800) == 0)
        {
            return;
        }
        _data1->Action = 24;
        data2->AnimationThing.Index = 79;
    LABEL_356:
        if (_data1->CharIndex.SByte[0] != 1)
        {
            DoSoundQueueThing(15);
        }
        return;
    case 0x21:
        if ((_data1->Status & 0x800) != 0)
        {
            v38 = sub_45C850((int)data2, (int)_data1, (int)data2_pp);
        }
        else
        {
            v38 = sub_45C100(data2, _data1, data2_pp);
        }
        if (v38)
        {
            return;
        }
        if ((_data1->Status & 3) != 0)
        {
            sub_45BDF0(_data1, 33);
            if (sub_4429C0(_data1) && data2->Speed.x > 0.0)
            {
            LABEL_369:
                _data1->Action = 27;
                data2->AnimationThing.Index = 60;
            }
            else
            {
                v39 = sub_45CEB0((int)data2, (int)_data1);
                _data1->Rotation.x = data2_pp->Forward.x;
                _data1->Rotation.z = data2_pp->Forward.z;
                if (v39)
                {
                    v40 = data2_pp->VelocityDirection.y;
                    v41 = v40 < -5.0;
                    v42 = v40 == -5.0;
                    if ((_data1->Status & 0x800) != 0)
                    {
                        if (v41 || v42)
                        {
                        LABEL_373:
                            data2->AnimationThing.Index = 83;
                        }
                        else
                        {
                        LABEL_307:
                            data2->AnimationThing.Index = 62;
                        }
                    }
                    else if (v41 || v42)
                    {
                    LABEL_376:
                        data2->AnimationThing.Index = 20;
                    }
                    else
                    {
                        sub_459BF0(_data1, data2);
                    }
                }
                else
                {
                    _data1->Action = (_data1->Status & 0x800) != 0 ? 25 : 2;
                    sub_459DA0(data2, data2_pp, _data1);
                }
            }
        }
        else if (!sub_45D0F0(_data1, data2))
        {
            v43 = data2->AnimationThing.Index;
            if (v43 != 86 && v43 != 87)
            {
                _data1->Action = 10;
                data2->AnimationThing.Index = 19;
            }
        }
        return;
    case 0x22:
        if (sub_45C850((int)data2, (int)_data1, (int)data2_pp)
            || sub_45CE30(data2, _data1)
            || sub_45BFE0(data2, _data1))
        {
            return;
        }
        if (!sub_43BB30((int)_data1))
        {
            goto LABEL_386;
        }
        if (!GetAnalog(_data1, 0, 0))
        {
            _data1->Action = 24;
            data2->AnimationThing.Index = 79;
        }
        return;
    case 0x23:
        if (sub_45C850((int)data2, (int)_data1, (int)data2_pp)
            || sub_45CE30(data2, _data1)
            || sub_45BFE0(data2, _data1))
        {
            return;
        }
        v44 = data2->ObjectHeld;
        if (v44 && (v45.Unknown = (void*)v44->Data1) != 0 && *((_BYTE*)v45.Unknown + 2) == 4)
        {
            if (!GetAnalog(_data1, 0, 0))
            {
                _data1->Action = 23;
                data2->AnimationThing.Index = 77;
            }
        }
        else
        {
        LABEL_386:
            sub_45BE80(data2, _data1);
            sub_45AA80(data2, _data1);
        }
        return;
    case 0x24:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        if (sub_45BFE0(data2, _data1))
        {
            goto LABEL_52;
        }
        if ((_data1->Status & 0x2000) == 0)
        {
            goto LABEL_200;
        }
        if (GetAnalog(_data1, (Angle*)&data1, 0))
        {
            if (BAMS_Subtract(_data1->Rotation.y, (int)data1) >= 0x4000)
            {
                data2->Speed.x = -0.375;
            }
            else
            {
                data2->Speed.x = 0.375;
            }
            if (data2->AnimationThing.Index == 92)
            {
                data2->AnimationThing.dword14 = 0;
            }
            else
            {
                data2->AnimationThing.dword14 = 1107296256;
            }
            _data1->Action = 37;
            data2->AnimationThing.Index = 90;
        }
        else
        {
        LABEL_199:
            if ((AttackButtons & Controllers[_data1->CharIndex.UByte[0]].PressedButtons) != 0)
            {
            LABEL_200:
                _data1->Action = 10;
                data2->AnimationThing.Index = 19;
                HIBYTE(_data1->Status) &= ~0x20u;
            }
        }
        return;
    case 0x25:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        if (sub_45BFE0(data2, _data1))
        {
            goto LABEL_52;
        }
        if ((_data1->Status & 0x2000) != 0)
        {
            goto LABEL_199;
        }
        goto LABEL_200;
    case 0x26:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        if (sub_45BFE0(data2, _data1))
        {
            goto LABEL_52;
        }
        if ((_data1->Status & 0x2000) == 0)
        {
            goto LABEL_211;
        }
        if (GetAnalog(_data1, (Angle*)&data1, 0))
        {
            if (BAMS_Subtract(49152 - Camera_Data1->Rotation.y, (int)data1) >= 0x4000)
            {
                data2->Speed.x = -0.375;
            }
            else
            {
                data2->Speed.x = 0.375;
            }
        }
        return;
    case 0x27:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        if (sub_45BFE0(data2, _data1))
        {
            goto LABEL_52;
        }
        if ((_data1->Status & 0x2000) == 0)
        {
        LABEL_211:
            _data1->Action = 10;
            data2->AnimationThing.Index = 19;
            NullifyVelocity(data2_pp, data2);
            HIBYTE(_data1->Status) &= 0xDFu;
        }
        return;
    case 0x28:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        if (sub_4B83C0(_data1))
        {
            sub_45BDF0(_data1, 33);
            NullifyVelocity(data2_pp, data2);
            _data1->Action = 41;
            data2->AnimationThing.Index = 96;
        }
        else if ((_data1->Status & 3) != 0)
        {
            sub_45BDF0(_data1, 33);
            NullifyVelocity(data2_pp, data2);
        LABEL_184:
            _data1->Action = 1;
            data2->IdleTime = 0;
            data2->AnimationThing.Index = 2;
        }
        return;
    case 0x29:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        if (sub_4B83F0(_data1) <= 0)
        {
            goto LABEL_184;
        }
        if (JumpAllowed(_data1) == 2)
        {
            sub_4B8470(_data1);
            _data1->Action = 40;
            data2->AnimationThing.Index = 95;
        }
        return;
    case 0x2A:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if ((HeldButtons[_data1->CharIndex.UByte[0] + 9] & 0x306FE) != 0)
            {
                _data1->CharIndex.SShort[1] -= 20;
            }
            if (!_data1->CharIndex.SShort[1])
            {
                goto LABEL_524;
            }
        }
        return;
    case 0x2B:
        if ((_data1->Status & 0x1000) != 0 && _data1->NextAction == 28)
        {
            _data1->Action = 7;
            data2->AnimationThing.Index = 17;
            HIBYTE(_data1->Status) &= 0xDAu;
        }
        return;
    case 0x2C:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45BFE0(data2, _data1))
        {
            goto LABEL_408;
        }
        v46 = Controllers[_data1->CharIndex.UByte[0]].LeftStickX << 8;
        if (v46 < -3072)
        {
            _data1->Action = 46;
            data2->AnimationThing.Index = 103;
            return;
        }
        if (v46 <= 3072)
        {
            goto LABEL_406;
        }
        _data1->Action = 47;
        data2->AnimationThing.Index = 104;
        return;
    case 0x2D:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45BFE0(data2, _data1))
        {
            goto LABEL_408;
        }
        v47 = data2->ObjectHeld;
        if (!v47)
        {
            goto LABEL_524;
        }
        v48.Unknown = (void*)v47->Data1;
        if (v48.Unknown && (v49 = *((_DWORD*)v48.Unknown + 14)) != 0)
        {
            if (*(float*)(*(_DWORD*)(v49 + 12) + 12)
                + *((float*)v48.Unknown + 9)
                - *(float*)(*(_DWORD*)(v49 + 12) + 24) < _data1->Position.y)
            {
            LABEL_406:
                if (_data1->Action < 44 || _data1->Action > 47)
                {
                LABEL_408:
                    data2->ObjectHeld = 0;
                }
            }
            else
            {
                _data1->Action = 44;
                data2->AnimationThing.Index = 106;
            }
        }
        else
        {
            _data1->Action = 1;
        }
        return;
    case 0x2E:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45BFE0(data2, _data1))
        {
            goto LABEL_408;
        }
        if (Controllers[_data1->CharIndex.UByte[0]].LeftStickX << 8 <= -3072)
        {
            goto LABEL_406;
        }
        _data1->Action = 44;
        data2->AnimationThing.Index = 102;
        return;
    case 0x2F:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45BFE0(data2, _data1))
        {
            goto LABEL_408;
        }
        if (Controllers[_data1->CharIndex.UByte[0]].LeftStickX << 8 >= 3072)
        {
            goto LABEL_406;
        }
        _data1->Action = 44;
        data2->AnimationThing.Index = 102;
        return;
    case 0x30:
        if (sub_45A8E0((int)data2_pp, (int)data2, (int)_data1))
        {
            return;
        }
        if (sub_45CE30(data2, _data1))
        {
            goto LABEL_427;
        }
        if ((JumpButtons & Controllers[_data1->CharIndex.UByte[0]].PressedButtons) != 0)
        {
            _data1->Action = 52;
            v50 = data2->Speed.x < (double)data2->PhysicsData.rush_speed;
            data2->Speed.y = data2->PhysicsData.jmp_y_spd;
            data2->AnimationThing.Index = 111;
            if (v50)
            {
                data2->Speed.x = data2->PhysicsData.jog_speed + data2->Speed.x;
            }
            v51 = data2->field_6C;
            if (v51)
            {
                v52 = (float*)*((_DWORD*)v51 + 10);
                if (v52)
                {
                    EntityData2_SetSomeCollisionVector(_data1->CharIndex.UByte[0], v52[4], v52[5], v52[6]);
                }
                if (*(_BYTE*)(*((_DWORD*)data2->field_6C + 8) + 2) == 9)
                {
                    _data1->Action = 53;
                    sub_45BDF0(_data1, 230);
                    v53 = (_DWORD*)*((_DWORD*)data2->field_6C + 8);
                    a2a.x = 0.0;
                    a2a.y = 1.4;
                    a2a.z = 3.0;
                    njPushMatrix(nj_unit_matrix_);
                    v54 = v53[7];
                    if (v54)
                    {
                        njRotateZ(0, (unsigned __int16)v54);
                    }
                    v55 = v53[6];
                    if (v55)
                    {
                        njRotateY(0, (unsigned __int16)v55);
                    }
                    v56 = v53[5];
                    if (v56)
                    {
                        njRotateX(0, (unsigned __int16)v56);
                    }
                    njRotateY(0, 0x8000);
                    njCalcVector(0, &a2a, &a3a);
                    a2a.z = 0.0;
                    a2a.x = 0.0;
                    a2a.y = 1.0;
                    njCalcVector(0, &a2a, &vd);
                    sub_4415F0(
                        _data1->CharIndex.UByte[0],
                        (unsigned __int64)(asin(vd.z) * 65536.0 * 0.1591549762031479),
                        (unsigned __int64)(atan2(a3a.x, a3a.z) * 65536.0 * 0.1591549762031479),
                        (unsigned __int64)(asin(vd.x) * 65536.0 * -0.1591549762031479));
                    njPopMatrix(1u);
                    EntityData2_SetSomeCollisionVector(_data1->CharIndex.UByte[0], a3a.x, a3a.y, a3a.z);
                    if (data2->Speed.x <= 4.1399999)
                    {
                        if (data2->Speed.x <= 2.76)
                        {
                            if (data2->Speed.x <= 1.84)
                            {
                                _data1->Action = 52;
                                data2->AnimationThing.Index = 111;
                                sub_459B20(10);
                            }
                            else
                            {
                                data2->AnimationThing.Index = 126;
                                sub_45BDF0(_data1, 1471);
                                sub_459B20(30);
                            }
                        }
                        else
                        {
                            data2->AnimationThing.Index = 123;
                            sub_45BDF0(_data1, 1470);
                            sub_459B20(50);
                        }
                    }
                    else
                    {
                        data1 = (EntityData1*)rand();
                        if ((double)(int)data1 * 0.000030517578 <= 0.66000003)
                        {
                            data2->AnimationThing.Index = 122;
                            sub_45BDF0(_data1, 1457);
                        }
                        else
                        {
                            data2->AnimationThing.Index = 121;
                            sub_45BDF0(_data1, 1456);
                        }
                        data1 = (EntityData1*)rand();
                        if ((double)(int)data1 * 0.000030517578 < 0.5)
                        {
                            sub_437D20((int)sub_469080, 0, 2);
                        }
                        else
                        {
                            sub_437D20((int)sub_468EC0, 0, 2);
                        }
                        *((_DWORD*)&stru_3B2C660 + 18) = 0;
                        sub_459B20(100);
                    }
                }
            }
            LOBYTE(_data1->Status) &= 0xFDu;
            data2->JumpTime = 0;
            sub_440C40(231, _data1->CharIndex.SByte[0], _data1->Action);
        }
        else if (sub_4429C0(_data1) && data2->Speed.x >= (double)data2->PhysicsData.jog_speed)
        {
            _data1->Action = 50;
            goto LABEL_458;
        }
        return;
    case 0x32:
        if (sub_45A8E0((int)data2_pp, (int)data2, (int)_data1))
        {
            return;
        }
        if (sub_45CE30(data2, _data1))
        {
        LABEL_427:
            _data1->Action = 51;
            data2->AnimationThing.Index = 116;
        }
        else if ((JumpButtons & Controllers[_data1->CharIndex.UByte[0]].ReleasedButtons) != 0)
        {
            _data1->Action = 52;
            v57 = data2->Speed.x < (double)data2->PhysicsData.rush_speed;
            data2->Speed.y = data2->PhysicsData.jmp_y_spd;
            if (v57)
            {
                data2->Speed.x = data2->PhysicsData.jog_speed + data2->Speed.x;
            }
            v58 = data2->field_6C;
            if (v58)
            {
                v59 = (float*)*((_DWORD*)v58 + 10);
                if (v59)
                {
                    EntityData2_SetSomeCollisionVector(_data1->CharIndex.UByte[0], v59[4], v59[5], v59[6]);
                }
            }
            data2->AnimationThing.Index = 111;
            LOBYTE(_data1->Status) &= 0xFDu;
            data2->JumpTime = 0;
            sub_45BDF0(_data1, 17);
        }
        else if (sub_4429C0(_data1) && data2->Speed.x >= (double)data2->PhysicsData.jog_speed)
        {
        LABEL_458:
            GetAnalog(_data1, (Angle*)&data1, 0);
            data2->AnimationThing.Index = (sub_4383A0(_data1->Rotation.y, (__int16)data1) <= 0) + 108;
        }
        else
        {
        LABEL_494:
            _data1->Action = 48;
            data2->AnimationThing.Index = 107;
            sub_45A790((int)data2, (int)_data1);
        }
        return;
    case 0x33:
        if (sub_45A8E0((int)data2_pp, (int)data2, (int)_data1) || (_data1->Status & 3) == 0)
        {
            return;
        }
        sub_45BDF0(_data1, 33);
        _data1->Action = 48;
        if (data2->Speed.y > -3.0)
        {
            v60 = data2->Speed.x;
            data2->AnimationThing.Index = 107;
            if (v60 <= 0.30000001)
            {
                data2->Speed.x = 1.0;
            }
        }
        else
        {
            data2->AnimationThing.Index = 118;
        }
        goto LABEL_490;
    case 0x34:
        if (sub_45A8E0((int)data2_pp, (int)data2, (int)_data1) || (_data1->Status & 3) == 0)
        {
            return;
        }
        _data1->Action = 48;
        if (data2->Speed.y > -3.0)
        {
            v61 = data2->Speed.x;
            data2->AnimationThing.Index = 107;
            if (v61 <= 0.30000001)
            {
                data2->Speed.x = 1.0;
            }
        }
        else
        {
            data2->AnimationThing.Index = 118;
        }
        goto LABEL_490;
    case 0x35:
        if (sub_45A8E0((int)data2_pp, (int)data2, (int)_data1) || (_data1->Status & 3) == 0)
        {
            return;
        }
        _data1->Action = 48;
        if (data2->Speed.y > -3.0)
        {
            data2->AnimationThing.Index = 107;
        }
        else
        {
            data2->AnimationThing.Index = 118;
        }
    LABEL_490:
        _data1->Rotation.x = data2_pp->Forward.x;
        _data1->Rotation.z = data2_pp->Forward.z;
        sub_45A790((int)data2, (int)_data1);
        return;
    case 0x36:
        if (!sub_45A8E0((int)data2_pp, (int)data2, (int)_data1))
        {
            v62 = data2->AnimationThing.Index;
            if (v62 != 114 && v62 != 115)
            {
                goto LABEL_494;
            }
        }
        return;
    case 0x37:
        if (!sub_45C100(data2, _data1, data2_pp))
        {
            if (sub_45CE30(data2, _data1))
            {
                _data1->Action = 56;
            }
        }
        return;
    case 0x38:
        if (!sub_45C100(data2, _data1, data2_pp) && (_data1->Status & 3) != 0)
        {
            sub_45BDF0(_data1, 33);
            _data1->Action = 55;
            _data1->Rotation.x = data2_pp->Forward.x;
            _data1->Rotation.z = data2_pp->Forward.z;
        }
        return;
    case 0x39:
        if (sub_45C100(data2, _data1, data2_pp))
        {
            return;
        }
        v19 = (data2->AnimationThing.field_E & 1) == 0;
        goto LABEL_523;
    case 0x3A:
        if (!*((_DWORD*)_data1->field_3C + 19))
        {
            _data1->Rotation.x = data2_pp->Forward.x;
            _data1->Rotation.z = data2_pp->Forward.z;
            sub_45BE80(data2, _data1);
        }
        return;
    case 0x3D:
        v63 = data2_pp;
        if ((_data1->Status & 0x800) != 0)
        {
        LABEL_502:
            sub_45C850((int)data2, (int)_data1, (int)v63);
        }
        else
        {
        LABEL_173:
            sub_45C100(data2, _data1, v63);
        }
        return;
    case 0x3F:
        if (!sub_45C100(data2, _data1, data2_pp)
            && !sub_45CE30(data2, _data1)
            && !sub_45BFE0(data2, _data1)
            && data2->AnimationThing.Index != 132)
        {
            _data1->Action = 64;
        }
        return;
    case 0x40:
        if (!sub_45C100(data2, _data1, data2_pp)
            && !sub_45CE30(data2, _data1)
            && !sub_45BFE0(data2, _data1)
            && (!sub_442680(_data1) || GetAnalog(_data1, 0, 0)))
        {
            _data1->Action = 65;
        }
        return;
    case 0x41:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45CE30(data2, _data1) || sub_45BFE0(data2, _data1))
        {
            return;
        }
        v19 = data2->AnimationThing.Index == 134;
        goto LABEL_523;
    case 0x42:
        if (sub_45C100(data2, _data1, data2_pp) || sub_45CE30(data2, _data1))
        {
            return;
        }
        v19 = data2->AnimationThing.Index == 135;
    LABEL_523:
        if (!v19)
        {
        LABEL_524:
            sub_45BE80(data2, _data1);
        }
        return;
    default:
        return;
    }
}
*/