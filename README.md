## CS 1.6 Hack Tool Readme

This guide explains how to compile and use the tools developed for Counter-Strike 1.6. It covers both the **Internal DLL** (Aimbot) and the **External Executable** (No-Flash).

---

### 1. Compiling the Internal DLL (TOOL.dll)

To create the DLL file using **Dev-C++**, follow these specific steps to ensure all libraries link correctly:

* **Setup:** Open your project and ensure `dllmain.cpp` contains the source code.
* **Linker Settings:** Go to **Project Options** > **Parameters** and add the following to the **Linker** box to prevent "undefined reference" errors:
* `-lopengl32`
* `-lpsapi`
* `-lgdi32`


* **Compile:** Press **F9** (or Compile & Build). This generates `TOOL.dll`.

### 2. Injection Process (Using Process Hacker 2)

Once the DLL is compiled, it must be "injected" into the game memory:

1. **Launch the Game:** Run `hl.exe` (CS 1.6) and join a match or stay in the main menu.
2. **Open Process Hacker:** Run **Process Hacker 2** as Administrator.
3. **Locate Process:** Find `hl.exe` in the list of running processes.
4. **Inject:** * Right-click `hl.exe`.
* Navigate to **Miscellaneous** > **Inject DLL...**.
* Select your compiled `TOOL.dll` (or `cstool.dll`).


5. **Activation:** In-game, hold **CAPS LOCK** to engage the Aimbot logic.
* *Note:* If the Aimbot is not responding, the memory offsets for your specific version of `hl.exe` may need updating.



---

### 3. Using the External No-Flash (noflash.exe)

Unlike the DLL, the No-Flash tool is a standalone program that runs alongside the game.

* **Compilation:** Open the `noflash.cpp` file in Dev-C++. Ensure the compiler is set to **TDM-GCC 32-bit/64-bit Release**.
* **ISO C++11 Error:** If you see a standard error, go to **Compiler Options** and add `-std=c++11` to the compiler commands.
* **Execution:** 1.  Run the compiled `noflash.exe` as **Administrator**.
2.  The program will display `[*] Waiting for hl.exe...` in a console window.
3.  Once the game is detected and the module (`hw.dll` or `client.dll`) is found, it will display `[*] No-Flash ACTIVE`.
4.  **Test:** Throw a flashbang at your feet; the tool will continuously write `0.0f` to the flash memory address to keep your screen clear.

---

### 4. Troubleshooting & Status

* **Internal DLL (Aimbot):** Currently compiled successfully, but may not function if the hardcoded offsets do not match the specific build of your game.
* **External No-Flash:** Currently programmed to scan for common offsets. If the console says "Active" but you are still flashed, the specific memory offset for your game version must be found using a tool like Cheat Engine and updated in the code.
* **Termination:** For the external tool, press **F12** to safely close the program.
