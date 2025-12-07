# Subway Surfers Group Project

**Table of Contents:**
1. [About](#about)
2. [Installation and Setup](#installation-and-setup)
3. [Game Rules](#game-rules-and-info)

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

# Game Rules and Info
- Run from the police and get points
- Collect coins to get a better score
- Avoid trains as all costs as you will lose if they hit you
- Collect powerups to get boosts and get a better score
- Avoid hitting red dots as they will cause guard to get closer till he catches you
