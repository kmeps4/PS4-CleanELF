# Playstation 5 Cleaned ELF [Port]
This is a source for building ELF files on the PS5<br>
This is not system version specific, so it will work on 3.00 to 4.51

# Includes
- C++ Compiler
- Detour Functions (Example of how to do a stub)
- Vector classes and functions
- Imports (Libc, Network, Threads, Notify)
- Socket Printf

# How to Use
- Make sure you have cc1plus installed (sudo apt-get install g++)
- Go to directory with the Makefile on Linux Shell
- type 'make'
- project.elf is your exectuable
- Load with jkpatch or api of your choice

# Known Issues:
- Because we do not use stdlib (-fnostdlib), there are some limitations like not having global variables with constructors. As an example, in my vector class there is a constructor and deconstructor. If you try make a global vec3_t or vec2_t variable, it will not link because the constructor for the variable is never being called. If anyone knows how to fix this without using the g++ standards let me know

# Credits
- Sabotage: how to do x64 detours
- 2much4u/xemio: makefile/building examples
- PS5 Port by SiSTR0: https://github.com/SiSTR0
