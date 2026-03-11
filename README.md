# termChat

### A P2P chatting app for the terminal, sorta like a ripoff of IRC.
This is a project to teach me more about applied C++. My learning goals pushed me to go with a project inspired by IRC, in the terminal. The initial commit gets the basics up and running, no networking or anything yet.

## Learning goals for the project:
- Understanding networking in C++, with the help of a platform-independent wrapper like [TinyCSocket](https://tinycsocket.readthedocs.io/)
- Using simple TUI libraries, like ncurses, and building around their C limitations (yes there are bindings but booo)
- Applying modern C++ programing principles: MVC architecture, PIMPL, RAII, portability with STL utilites
- More thoroughly understanding version control


## Preset platforms
- MSYS2-UCRT64 on Windows w/ gcc
- Linux w/ gcc

## Preset dependencies
- gcc/g++
- CMake
- Ninja
- ncurses development libraries

## Build instructions

### Easiest (VS Code)
1. Install dependencies, clone repo
2. Install Visual Studio Code
    - Install the C++ extension
3. Edit ./.vscode/settings.json and comment in/out your PRESET configuration. I will refine this process later
4. Go to Run and Debug, run the config to configure, compile, and run termChat
5. The termChat executable will be in ./out/build/{configuration}/
    - I still need to figure out copying DLLs after building for Windows, so have their dir in $PATH or copy to the build dir manually

### Mediumest (terminal)
1. Install dependencies, clone repo
2. ```cmake --preset {platform}-{compiler}-{buildType}```
    - platform: msys-ucrt64, linux
    - compiler: gcc
    - buildType: release, debug
3. ```cmake --build ./out/build/{platform}-{compiler}-{buildType}```
4. Execute ```./out/build/termChat```