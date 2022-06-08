# SDL_Tools

Wrapper for the SDL2 library

**This is the old version, the new version is located at https://github.com/FlavorlessQuark/SDL_Tools**


### Table of Contents
**[Dependencies](#dependncies)**<br>
**[Contents](#contents)**<br>
**[Known Issues](#known-issues)**<br>
**[Usage](#usage)**<br>
**[Code example](#code-examples)**<br>
**[Upcomming features and fixes](#upcoming-features-and-fixes)**<br>

## Overview

This library currently supports animations, buttons, input collisions and rendering.

## Dependencies

This assumes that the SDL2 library header files(along with SDL_image, SDL_ttf, and SDL_mixer) are located in SDL2/ in your includes folder

These are available on SDL2 website, via your package manager or in this repository under includes/SDL2

## Get started

To use this library you will need the SDL2 headers in your includes/ folder, and you will need to compile either with the libsdlx.a or libsdlx.so binary

Currently, only the .a and .so for Linux are available. If you are using another OS, you will need to compile those by hand or compile with the source code. To compile the .a and .so files, you must do the following: 

```
git git@github.com:FlavorlessQuark/old_SDL_Tools.git
cd old_SDL_Tools
make dynamic
make static
```

## Code example

**The assets used in this example were made by me. If you wish to use them, ask for permission first :)**

In this example, you will learn how to use the rendering, animator, input mapping and GUI components of SDLX

The end product will be a small scene with an animated sprite that can be moved around and a button that can be hovered and clicked

First we will need a struct to hold our data. We will need two sprite as well as two animatores to animate our sprites and one GUIElem to let our button be clieck and hovered

<br><img align="center" src="Ressources/struct.png"/><br>

Here we set some simple functions that we will use with the button. When hovered  we change the animator state so that it plays a different animation, and we do the same on click.

<br><img align="center" src="Ressources/functions.png"/><br>


Next we need to initialize SDLX and give our data some values;

We will need a Display, as most things concerning rendering use SDL_renderer which is stored in the display struct along with window and background texture;

We will also need animations and textures from which to parse thone animations

First we want to start SDLX(this also inits SDL and the tff and image subsystems). We pass it the name of the window as well as its position and dimensions and a flag that would be passed to SDL_Init

Next, we want to allocate some space for our animations; (1 for our character and 3 for our button - hovered, clicked and idle - 

Then we map our inputs. Mapping input takes and SDL scancode and maps it to an SDLX key (it can be mapped to anythign really). more info in [this section](#Input)

After this we want to load our textures and parse the animations. AnimLoadHorizontal parses sprite sheets layed out horizontally

Next we create the sprite for the button and the character  as well as the Animators and UI elements.

The UI element can be set using default functions (which do nothing)

It's mandatory to set the GUI default target and set the button to active. The former tells the engine which button should be defaulted to, and the second is needed to make buttons interactable and rendered automatically; There are more settings  that you can view [here](#GUI)

<br><img align="center" src="Ressources/Init.png"/><br>


In our mian function is where we will have our loop. 
We will need a display to render our sprites and an input struct to be able to get the input and use it.

First we want to callour init function and set our display.

In our loop, we clear the window and run the input loop (This loop is mandaotryorelse SDL will not render the window. This loop can and should be replaced with your own loop)

Then we call InputUpdate to update the SDLX input (this should be called before your own input loop and does not consume the input)
To set our input, we call InputGet. Now we can use our  input mappings to determine what we should do. Since we have mapped W and UP ARROW to SDLX_UP , if any of them is pressed, input.input[SDLX_UP] should be one.

Then we call, in this order, GUI_Update to update the state of buttons and Animation Update to update the state of animators. 

It is not necessary to add the sprites which have animators, as they render themselves but it is done here to show how to add a sprite to a render queue.

Once we have everything we want to render in a render queue, we call RenderDisplayAll, to copy everything to the renderer, and then RenderPresent to display it on the screen

SDLX_FPSAdjust will then wait the appropriate amoutn of time to maintain a constant framerate(in this casem 30FPS)

<br><img align="center" src="Ressources/main.png"/><br>

## Rendering

## Input

## GUI

## Collisions

