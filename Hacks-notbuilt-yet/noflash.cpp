#include <windows.h>
#include <TlHelp32.h>
#include <iostream>


const char* PROCESS_NAME = "hl.exe";
const char* MODULE_NAME = "hw.dll"; 

// Function to get the Process ID (PID)
DWORD GetProcessId(const char* processName) {
    DWORD processId = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(entry);
        if (Process32First(snapshot, &entry)) {
            do {
                if (stricmp(entry.szExeFile, processName) == 0) {
                    processId = entry.th32ProcessID;
                    break;
                }
            } while (Process32Next(snapshot, &entry));
        }
    }
    CloseHandle(snapshot);
    return processId;
}

// Function to get the base address of a module
uintptr_t GetModuleBaseAddress(DWORD processId, const char* moduleName) {
    uintptr_t moduleBaseAddress = 0;
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, processId);
    if (snapshot != INVALID_HANDLE_VALUE) {
        MODULEENTRY32 entry;
        entry.dwSize = sizeof(entry);
        if (Module32First(snapshot, &entry)) {
            do {
                if (stricmp(entry.szModule, moduleName) == 0) {
                    moduleBaseAddress = (uintptr_t)entry.modBaseAddr;
                    break;
                }
            } while (Module32Next(snapshot, &entry));
        }
    }
    CloseHandle(snapshot);
    return moduleBaseAddress;
}

int main() {
    SetConsoleTitleA("CS 1.6 No-Flash");

    std::cout << "[*] Waiting for hl.exe..." << std::endl;

    DWORD processId = 0;
    while (!(processId = GetProcessId(PROCESS_NAME))) {
        Sleep(500);
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, processId);
    if (!hProcess) {
        std::cerr << "[-] Error: Run as Administrator!" << std::endl;
        system("pause");
        return 1;
    }

    uintptr_t hwBase = GetModuleBaseAddress(processId, MODULE_NAME);
    if (!hwBase) {
        std::cerr << "[-] Error: Could not find " << MODULE_NAME << std::endl;
        CloseHandle(hProcess);
        system("pause");
        return 1;
    }

    std::cout << "[+] Found " << MODULE_NAME << " at 0x" << std::hex << hwBase << std::dec << std::endl;
    std::cout << "[*] No-Flash ACTIVE. Press F12 to close." << std::endl;

    float noFlash = 0.0f;

    while (true) {
        if (GetAsyncKeyState(VK_F12) & 1) break;

        // Offset 1: v43 Warzone
        uintptr_t addr1 = hwBase + 0x122250; 
        // Offset 2: Legacy Non-Steam
        uintptr_t addr2 = hwBase + 0x122244;
        // Offset 3: Alternate Build
        uintptr_t addr3 = hwBase + 0x11FA10;

        WriteProcessMemory(hProcess, (LPVOID)addr1, &noFlash, sizeof(noFlash), NULL);
        WriteProcessMemory(hProcess, (LPVOID)addr2, &noFlash, sizeof(noFlash), NULL);
        WriteProcessMemory(hProcess, (LPVOID)addr3, &noFlash, sizeof(noFlash), NULL);

        Sleep(10); 
    }

    std::cout << "[*] Closing..." << std::endl;
    CloseHandle(hProcess);
    return 0;
}
