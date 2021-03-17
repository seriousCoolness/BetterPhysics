#include "stdafx.h"

#include "FixGomban.h"

CharObj2* __cdecl FixGomban_r(Uint8 a1, float a2, float a3, float a4) {

    int v4; // eax
    CharObj2* v5; // ecx
    CharObj2* result; // eax
    double v7; // st7

    v4 = a1;
    v5 = CharObj2Ptrs[v4];
    result = (CharObj2*)EntityData2Ptrs[v4];
    if (v5->PhysicsData.Gravity == 0.0f)
        v7 = 1.0 / 0.08f;
    else
        v7 = 1.0 / v5->PhysicsData.Gravity;
    *((float*)result + 4) = v7 * a2;
    *((float*)result + 5) = v7 * a3;
    *((float*)result + 6) = v7 * a4;
    return result;
}