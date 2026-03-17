CS 1.6 Hack Tool Readme
This guide explains how to compile and use the tools developed for Counter-Strike 1.6. It covers both the Internal DLL (Aimbot) and the External Executable (No-Flash).

1. Compiling the Internal DLL (TOOL.dll)
To create the DLL file using Dev-C++, follow these specific steps to ensure all libraries link correctly:

Setup: Open your project and ensure dllmain.cpp contains the source code.

Linker Settings: Go to Project Options > Parameters and add the following to the Linker box:

-lopengl32

-lpsapi

-lgdi32

Compile: Press F9 (or Compile & Build). This generates TOOL.dll.

2. Injection Process (Using Cheat Engine)
Cheat Engine can be used as a powerful DLL injector. Follow these steps:

Launch the Game: Run hl.exe (CS 1.6) and join a match.

Open Cheat Engine: Run Cheat Engine as Administrator.

Select Process: Click the Computer Icon (Select Process) and choose hl.exe from the "Applications" or "Processes" tab. Click Open.

Open Memory Viewer: Click the Memory View button (located in the middle-right of the main window).

Inject DLL: * In the Memory Viewer window, click the Tools menu at the top.

Select Inject DLL.

Browse and select your compiled TOOL.dll (or cstool.dll).

When asked "Do you want to execute a function of the DLL?", you can usually click No unless your code requires a specific export call.

Activation: In-game, hold CAPS LOCK to engage the Aimbot logic.

Note: If the Aimbot is not responding, the memory offsets for your specific version of hl.exe may need updating.

3. Using the External No-Flash (noflash.exe)
The No-Flash tool is a standalone program that runs alongside the game.

Compilation: Open noflash.cpp in Dev-C++. Ensure the compiler is set to TDM-GCC 32-bit Release (CS 1.6 is a 32-bit game).

Execution: Run the compiled noflash.exe as Administrator.

The console will display [*] Waiting for hl.exe....

Once detected, it will show [*] No-Flash ACTIVE.

Test: Throw a flashbang at your feet; the tool will force the flash alpha to 0 to keep your vision clear.

4. Troubleshooting & Status
Internal DLL (Aimbot): If the DLL injects but the aimbot doesn't work, the "offsets" or "signatures" inside the code are likely outdated for your version of CS 1.6.

External No-Flash: If the console says "Active" but you still see white, the tool is writing to the wrong memory address. You must use Cheat Engine to find the correct m_flFlashHoldTime or fadealpha offset for your build.

Termination: Press F12 to close the external No-Flash tool safely.
