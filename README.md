# SDL_Tools

Wrapper for the SDL library
# Dependencies

This assumes that the SDL2 library header files are located in SDL2/ in your includes folder

This also uses SDL2_image, SDL2_ttf and SDL2_mixer

These are avalable on SDL2 websie, via brew or in this repository under Dev/includes/SDL2

# Contents

This library contains animations, input and display tools. - fro now-

- Documentation in the h files, write summary here at some point

# Known issues

None so far. This program only contains features >:)

# Upcoming features and fixes

- Fix input mapper only accepts 5 mappings. Input mapper is currently static . needs to be allocated /reallocated

- Fix SDLX_DisplaySet() not called. Somehow not causing issues but still needs t be fixed

- Change srcs and dest in animator to have pointers and not pointers, easier to change for user

- Add Input remap

# Usage

```
git clone https://github.com/FlavorlessQuark/SDL_Tools/Release
copy the contents of the includes folder into your project's include directory
compile your project  with -L -l libSDLX.a
```

