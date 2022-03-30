#pragma once
#include "stdafx.h"

//void __usercall Tails_Act1(CharObj2 *data2@<eax>, EntityData2 *data2_pp@<ecx>, EntityData1 *data1)
extern const void* Tails_Act1_Ptr = (void*)0x45E5D0;
void _cdecl Tails_Act1_r(CharObj2* data2, EntityData2* data2_pp, EntityData1* data1);
static void __declspec(naked) Tails_Act1()
{
    __asm
    {
        push[esp + 04h] // data1
        push ecx // data2_pp
        push eax // data2

        // Call your __cdecl function here:
        call Tails_Act1_r

        pop eax // data2
        pop ecx // data2_pp
        add esp, 4 // data1
        retn
    }
}