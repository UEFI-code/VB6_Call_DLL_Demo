// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

#include "mytypes.h"

#include "my_opcode_x64.h"

#include <stdio.h>

UNICODE_STRING64 krnlbaseDllName = {28, 30, 0, (UINT64)L"kernelbase.dll"};
UNICODE_STRING64 krnl32DllName = { 24, 26, 0, (UINT64)L"kernel32.dll" };

UINT64 KrnlBase_BaseAddr = 0;
UINT64 Krnl32_BaseAddr = 0;

void cppFunc(void)
{
    MessageBox(NULL, L"Hello World from TheDLL C++ Function", L"Hi", SW_NORMAL);
}

extern "C"

{
    __declspec(dllexport) void Load_x64_Sys_Dll_Stage1(UNICODE_STRING64* DllName, UINT64* BaseAddr);
    void Load_x64_Sys_Dll_Stage2(void);

    __declspec(dllexport) void hello(void)
    {
        MessageBox(NULL, L"Hello World from TheDLL C Function", L"Hi", SW_NORMAL);
        cppFunc();
    }

    __declspec(dllexport) void runx64(void)
    {
        char msg[128] = { 0 };
        Load_x64_Sys_Dll_Stage1(&krnlbaseDllName, &KrnlBase_BaseAddr);
        sprintf_s(msg, "Successfully Load x64 kernelbase.dll -> 0x%llX", KrnlBase_BaseAddr);
        MessageBoxA(NULL, msg, "Notice", SW_NORMAL);
        Load_x64_Sys_Dll_Stage1(&krnl32DllName, &Krnl32_BaseAddr);
        sprintf_s(msg, "Successfully Load x64 kernel32.dll -> 0x%llX", Krnl32_BaseAddr);
        MessageBoxA(NULL, msg, "Notice", SW_NORMAL);
    }

    __declspec(dllexport) __declspec(naked) void Load_x64_Sys_Dll_Stage1(UNICODE_STRING64* DllName, UINT64* BaseAddr)
    {
        __asm
        {
            // Now prepare enter x64!
            push 033h;
            push x64code;
            retf
                x64code :
            nop;
            nop;
            call Load_x64_Sys_Dll_Stage2;
            nop;
            nop;
            //Now Back to x86 Mode;
            push x86BackPosition; // Here will push 8 bytes
            mov [esp + 4], 023h;
            retf
                x86BackPosition :
            // 233, below is C code
        }
        MessageBox(NULL, L"Backed to x86", L"233", SW_NORMAL);
        _asm ret;
    }

    __declspec(naked) void Load_x64_Sys_Dll_Stage2(void)
    {
        __asm
        {
            x64_mov_rax_prefix;
            EMIT(0xF0) EMIT(0x46) EMIT(0xED) EMIT(0xEF) EMIT(0xFC) EMIT(0x7F) EMIT(0) EMIT(0); // Set RAX to LdrLoadDll

            x64_xor_rcx_rcx; // Set 1st Param to NULL

            x64_xor_rdx_rdx; // Set 2st Param to NULL

            add esp, 8+4; // manully dive 8+4 bytes to skip the ret addrs for below purpose

            x64_xor_rbx_rbx; // Clear RBX

            // lea ebx, [krnlbaseDllName]; Unfortunatly, this opcode is not same in x64
            mov ebx, [esp]; // ebx = &krnlbaseDllName
            x64_mov_r8_rbx; // Set 3rd Param to &krnlbaseDllName

            add esp, 4; // manully dive 4 bytes, because x64 Not have pop ebx

            // lea ebx, [KrnlBase_BaseAddr]; Unfortunatly, this opcode is not same in x64
            mov ebx, [esp]; // ebx = &KrnlBase_BaseAddr
            x64_mov_r9_rbx; // Set 4th Param to &KrnlBase_BaseAddr
            
            sub esp, 4+4+8; // restore stack height

            sub esp, 16; // give ntdll func 16 bytes stack gap
            x64_call_rax;
            add esp, 16; // free the gap space
            
            nop;
            nop;
            nop;
            ret;
        }

    }
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, L"TheDLL Attached!", L"233", SW_NORMAL);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}