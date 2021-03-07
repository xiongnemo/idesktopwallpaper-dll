// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <string>
#include "Shobjidl.h"

extern "C" {
    __declspec(dllexport)
        void SetWallpaper(int id, const wchar_t* s)
    {
        HRESULT  ad;
        UINT count;
        WCHAR* mid = new WCHAR[200];
        WCHAR* temp = mid;
        memset(mid, 0, 200 * 2);
        CoInitialize(NULL);

        IDesktopWallpaper* p;
        if (SUCCEEDED(CoCreateInstance(__uuidof(DesktopWallpaper), 0, CLSCTX_LOCAL_SERVER, __uuidof(IDesktopWallpaper), (void**)&p))) {
            p->GetMonitorDevicePathCount(&count); //count: the numbers of monitor
            p->GetMonitorDevicePathAt(id, &mid);  //0: the first monitor  1: the second monitor
            ad = p->SetWallpaper(mid, s);
            p->Release();
        }
        delete[] temp;
        CoUninitialize();
    }
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}