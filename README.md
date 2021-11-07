# DITTO MAZE Midterm Game
 
How to play:
 
Move with the keys WASD you move your ditto. With the keys UP,DOWN,LEFT,RIGHT, you change the direction of where you're looking at. Move the player towards the trainers(AGUMON) on the map and press the UP key, this will start the battle. TRAINER 1(PINK) = turn based mini game, TRAINER 2(BLUE) = quiz mini game. Once the trainer loses, it disapears. There are 4 pick ups on the map, Green box = health, player gains health. Red box = bigger radius, smaller radius so the trainer cant see you. Blue pick up= speed boast. Yellow pickup = Legendary move, stronger move against trainers(use the RIGHT key).

# gf3d
a collection of utlitity functions designed to facilitate creating 3D games with ~~OpenGL~~ Vulkan and SDL2
This project is specifically intended to function as an educational tool for my students taking 3D Game Programming.

Currently the project is in a WIP state.
It represents my first stab at getting vulkan rendering pipeline setup.
It is not stable and I intend to do a complete rewrite of the vulkan system as soon as I can find some time


# Build Process

Before you can build the example code we are providing for you, you will need to obtain the libraries required
by the source code. Some of these libraries are easy to obtain and others are provided by the vendors of hardware
that is installed in your computer. After the libraries are obtained the following sequence of steps should be
performable from the following steps from the root of the cloned git repository within a terminal. 

1. Obtain the code: `git clone <repo name>`
2. Checkout seed branch: `git checkout <branch name>`
3. Make sure ou fetch submodules: `git submodule update --init --recursive`
4. Build libraries: `pushd gfc/src; make; popd`
5. Build game: `pushd src; make; popd`

You should now have a `gf3d` binary within the root of your git repository. Executing this will start your game.
