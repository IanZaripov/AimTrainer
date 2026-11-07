#define WIN32_LEAN_AND_MEAN
#define NOGDI
#define NOUSER
#include <windows.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <vector>

#include "SystemStats.h"

// Отменяем макросы Windows
#undef DrawText
#undef DrawTextEx
#undef CloseWindow
#undef ShowCursor

void SystemStats::Update(float deltaTime) {
    updateTimer += deltaTime;
    if (updateTimer >= 0.5f) {
        float newCPU = FetchCPULoad();
        float newGPU = FetchGPULoad();
        
        // Сглаживание (Lerp)
        cpu = cpu + (newCPU - cpu) * 0.3f;
        gpu = gpu + (newGPU - gpu) * 0.3f;
        
        updateTimer = 0.0f;
    }
}

float SystemStats::FetchCPULoad() {
    static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
    static int numProcessors;
    static HANDLE self;
    static bool init = false;

    if (!init) {
        SYSTEM_INFO sysInfo;
        FILETIME ftime, fsys, fuser;
        GetSystemInfo(&sysInfo);
        numProcessors = sysInfo.dwNumberOfProcessors;
        GetSystemTimeAsFileTime(&ftime);
        lastCPU.LowPart = ftime.dwLowDateTime;
        lastCPU.HighPart = ftime.dwHighDateTime;
        self = GetCurrentProcess();
        GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
        lastSysCPU.LowPart = fsys.dwLowDateTime;
        lastSysCPU.HighPart = fsys.dwHighDateTime;
        lastUserCPU.LowPart = fuser.dwLowDateTime;
        lastUserCPU.HighPart = fuser.dwHighDateTime;
        init = true;
        return 0.0f;
    }

    FILETIME ftime, fsys, fuser;
    ULARGE_INTEGER now, sys, user;
    GetSystemTimeAsFileTime(&ftime);
    now.LowPart = ftime.dwLowDateTime;
    now.HighPart = ftime.dwHighDateTime;

    GetProcessTimes(self, &ftime, &ftime, &fsys, &fuser);
    sys.LowPart = fsys.dwLowDateTime;
    sys.HighPart = fsys.dwHighDateTime;
    user.LowPart = fuser.dwLowDateTime;
    user.HighPart = fuser.dwHighDateTime;

    float percent = (float)((sys.QuadPart - lastSysCPU.QuadPart) + (user.QuadPart - lastUserCPU.QuadPart));
    float timeDiff = (float)(now.QuadPart - lastCPU.QuadPart);
    
    if (timeDiff > 0.0f) {
        percent /= timeDiff;
        percent /= numProcessors;
    } else {
        percent = 0.0f;
    }
    
    lastCPU = now;
    lastUserCPU = user;
    lastSysCPU = sys;

    return percent * 100.0f;
}

float SystemStats::FetchGPULoad() {
    static PDH_HQUERY query = nullptr;
    static PDH_HCOUNTER counter = nullptr;
    static bool init = false;

    if (!init) {
        PdhOpenQuery(nullptr, 0, &query);
        PdhAddEnglishCounterW(query, L"\\GPU Engine(*)\\Utilization Percentage", 0, &counter);
        PdhCollectQueryData(query);
        init = true;
    }

    PdhCollectQueryData(query);

    DWORD bufferSize = 0;
    DWORD itemCount = 0;
    PdhGetFormattedCounterArrayW(counter, PDH_FMT_DOUBLE, &bufferSize, &itemCount, nullptr);
    
    if (bufferSize > 0) {
        std::vector<BYTE> buffer(bufferSize);
        PPDH_FMT_COUNTERVALUE_ITEM_W items = reinterpret_cast<PPDH_FMT_COUNTERVALUE_ITEM_W>(buffer.data());
        
        if (PdhGetFormattedCounterArrayW(counter, PDH_FMT_DOUBLE, &bufferSize, &itemCount, items) == ERROR_SUCCESS) {
            double total = 0.0;
            for (DWORD i = 0; i < itemCount; i++) {
                if (items[i].FmtValue.CStatus == PDH_CSTATUS_VALID_DATA || items[i].FmtValue.CStatus == PDH_CSTATUS_NEW_DATA) {
                    total += items[i].FmtValue.doubleValue;
                }
            }
            return (float)(total > 100.0 ? 100.0 : total);
        }
    }
    return 0.0f;
}