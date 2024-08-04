// dllmain.cpp : DLL アプリケーションのエントリ ポイントを定義します。
#include "pch.h"

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

    __declspec(dllexport) void runx64(void)
    {
        __asm
        {
            push 033h;
            push x64code;
            retf
                x64code :
            nop;
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

