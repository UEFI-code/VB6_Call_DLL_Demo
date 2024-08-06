// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

#include "mytypes.h"

#include "my_opcode_x64.h"

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
    __declspec(dllexport) void hello(void)
    {
        MessageBox(NULL, L"Hello World from TheDLL C Function", L"Hi", SW_NORMAL);
        cppFunc();
    }

    void Load_x64_Sys_Dll(void);

    __declspec(dllexport) void runx64(void)
    {
        __asm
        {
            // Backup Useful Pointer, for below x64 function use
            lea eax, [krnlbaseDllName];
            push eax;
            lea eax, [KrnlBase_BaseAddr];
            push eax;

            // Now prepare enter x64!
            push 033h;
            push x64code;
            retf
                x64code :
            nop;
            nop;
            call Load_x64_Sys_Dll;
            nop;
            nop;
            //Now Back to x86 Mode;
            push x86BackPosition; // Here will push 8 bytes
            mov [esp + 4], 023h;
            retf
                x86BackPosition :
            add esp, 8 // manully pop 8 bytes to restore stack
            // 233, below is C code
        }
        MessageBox(NULL, L"Backed to x86", L"233", SW_NORMAL);
    }

    __declspec(naked) void Load_x64_Sys_Dll(void)
    {
        __asm
        {
            x64_mov_rax_prefix;
            EMIT(0xF0) EMIT(0x46) EMIT(0xED) EMIT(0xEF) EMIT(0xFC) EMIT(0x7F) EMIT(0) EMIT(0); // Set RAX to LdrLoadDll

            x64_xor_rcx_rcx; // Set First Param to NULL

            x64_xor_rdx_rdx; // Set Sec Param to NULL

            x64_xor_rbx_rbx; // Clear RBX

            add esp, 8; // manully pop 8 bytes to skip the return addr for below purpose

            // lea ebx, [krnlbaseDllName]; Unfortunatly, this opcode is not same in x64
            mov ebx, [esp]; // ebx = KrnlBase_BaseAddr
            x64_mov_r9_rbx; // Set Forth Param to &KrnlBase_BaseAddr
            add esp, 4; // manully pop 4 bytes, cause x64 Not have pop ebx
            
            // lea ebx, [KrnlBase_BaseAddr]; Unfortunatly, this opcode is not same in x64
            mov ebx, [esp]; // ebx = krnlbaseDllName
            x64_mov_r8_rbx; // Set Third Param to &krnlbaseDllName

            sub esp, 12; // restore stack

            x64_call_rax;
            
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