# Ludum Dare #30 (Jam)
Check out http://www.ludumdare.com/compo/ludum-dare-30/?action=preview&uid=7989 for a full description of the game including the control scheme.

## Compiling the source

We're using the following libraries in the game:
- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer

### Linux
    mkdir src/build
    cd src/build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make

The compiled binary will be put in the bin directory. This should also be your working directory when starting the game.
