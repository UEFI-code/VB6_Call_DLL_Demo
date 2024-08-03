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

