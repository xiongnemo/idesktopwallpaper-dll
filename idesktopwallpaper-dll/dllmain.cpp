// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <string>
#include "Shobjidl.h"

extern "C" {
    __declspec(dllexport)
        void SetWallpaper(int desired_monitor_id, const wchar_t* path_to_img)
    {
        HRESULT  ad;
        UINT monitor_count;
        WCHAR* monitor_device_path = new WCHAR[200];
        WCHAR* temp = monitor_device_path;
        memset(monitor_device_path, 0, 200 * 2);
        CoInitialize(NULL);

        IDesktopWallpaper* p;
        if (SUCCEEDED(CoCreateInstance(__uuidof(DesktopWallpaper), 0, CLSCTX_LOCAL_SERVER, __uuidof(IDesktopWallpaper), (void**)&p))) {
            p->GetMonitorDevicePathCount(&monitor_count); // monitor_count: the numbers of monitor
            p->GetMonitorDevicePathAt(desired_monitor_id, &monitor_device_path);  // 0: the first monitor  1: the second monitor
            ad = p->SetWallpaper(monitor_device_path, path_to_img);
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