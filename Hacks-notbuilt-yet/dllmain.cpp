#include <windows.h>
#include <stdio.h>
#include <math.h>

struct Vector3 { float x, y, z; };

void CalcAngle(Vector3 src, Vector3 dst, float* angles) {
    double rel[3] = { dst.x - src.x, dst.y - src.y, dst.z - src.z + 18.0f };
    double dist = sqrt(rel[0] * rel[0] + rel[1] * rel[1]);
    angles[0] = (float)(-atan2(rel[2], dist) * 180.0 / 3.14159); // Pitch
    angles[1] = (float)(atan2(rel[1], rel[0]) * 180.0 / 3.14159); // Yaw
}

DWORD WINAPI AimbotThread(LPVOID hModule) {
    AllocConsole();
    freopen("CONOUT$", "w", stdout);
    printf(" CS 1.6 FINAL AIMBOT ACTIVE \n");
    printf("Hold [CAPSLOCK] to Snap-to-Target.\n");

    uintptr_t scanStart = 0x17000000;
    uintptr_t scanEnd   = 0x18000000;

    while (!(GetAsyncKeyState(VK_END) & 0x8000)) {
        if (GetAsyncKeyState(VK_CAPITAL) & 0x8000) {
            Vector3 players[2];
            int found = 0;

            for (uintptr_t addr = scanStart; addr < scanEnd; addr += 4) {
                if (IsBadReadPtr((void*)addr, 12)) continue;
                float* c = (float*)addr;
                if (c[2] < -230.0f && c[2] > -240.0f && c[0] != 0) {
                    players[found++] = { c[0], c[1], c[2] };
                }
                if (found >= 2) break;
            }

            if (found >= 2) {
                float angles[2];
                CalcAngle(players[0], players[1], angles);

                // MOUSE MOVE COMMAND
                // We move the mouse slightly towards the calculated Yaw
                int moveX = (int)(angles[1] * 2); 
                int moveY = (int)(angles[0] * 2);
                
                mouse_event(MOUSEEVENTF_MOVE, moveX, moveY, 0, 0);
                printf("SNAPPING... Yaw: %.2f          \r", angles[1]);
            }
        }
        Sleep(1);
    }

    FreeConsole();
    FreeLibraryAndExitThread((HMODULE)hModule, 0);
    return 0;
}

BOOL WINAPI DllMain(HINSTANCE h, DWORD r, LPVOID p) {
    if (r == DLL_PROCESS_ATTACH) CreateThread(0, 0, AimbotThread, h, 0, 0);
    return TRUE;
}
