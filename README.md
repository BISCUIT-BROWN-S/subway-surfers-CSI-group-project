# Subway Surfers Group Project

**Table of Contents:**
1. [About](#about)
2. [Installation and Setup](#installation-and-setup)
3. [Game Rules & Info](#game-rules-and-info)

# About
Classic Subway Surfer remake that is top down. Players must avoid the trains and collect coins in order to level up. There are different power ups allong the way that will help the player. 
Avoid being caught by police officer chasing you and get a high score. The game was built with C++, SDL2, SDL Mixer, and SDL TTF for the libraries. 

# Installation and Setup
1. Clone the source code with git: ``git clone https://github.com/BISCUIT-BROWN-S/subway-surfers-CSI-group-project.git``
2. Install SDL2 and SDL2 Mixer
3. Installing SDL2_TTF
5. Build the source code and make sure to include all the SDL libraries and source code files
6. Execute it and play the Game!

**Installing SDL_TTF (Using Homebrew):**
1. brew install sdl2 sdl2_ttf
2. Open source code directory in xcode
3. Add framework search paths ``/opt/homebrew/lib`` and ``/opt/homebrew/include`` (If on intel mac then add ``/usr/local/lib`` and ``/usr/local/include`` too)
4. Add header search path ``/opt/homebrew/include/SDL2`` and enable recursive
5. Add a runpath: If using .dylib instead of frameworks, add ``@loader_path`` ``@executable_path`` and ``/opt/homebrew/lib`` to the Build Settings Runpath Search Path

**Installing on Windows with MinGW:**
1. Follow the installation instruction to install MSYS2 at www.msys2.org
2. Open MSYS2 UCRT64 env and run the following commands
3. Run ``pacman -Syu``
4. Run ``pacman -S mingw-w64-ucrt-x86_64-gcc``
5. Run ``pacman -S mingw-w64-x86_64-toolchain``
6. Run ``pacman -S mingw-w64-x86_64-SDL2``
7. Run ``pacman -S mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_ttf``
8. Optionally: Add msys2 MinGw to the windows path vars by ``C:\msys64\mingw64\bin`` into the Path vars for the local user
9. git clone the the repo to desired directory
10. Finally run this command to compile the source code: ``g++ main.cpp functions.cpp SDL_Plotter.cpp structs.cpp -IC:\msys64\mingw64\include\SDL2 -LC:\msys64\mingw64\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_ttf -o game.exe``
11. Execute game.exe

# Game Rules and Info
- Run from the police and get points
- Collect coins to get a better score
- Avoid trains as all costs as you will lose if they hit you
- Collect powerups to get boosts and get a better score. There is immunity and speed orbs.
- Avoid hitting red dots as they will cause guard to get closer till he catches you
