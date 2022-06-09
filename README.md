# SDL_Tools

Wrapper for the SDL2 library

**This is the old version, the new version is located at https://github.com/FlavorlessQuark/SDL_Tools**


### Table of Contents
**[Overview](#overview)**<br>
**[Dependencies](#dependencies)**<br>
**[Get started](#get-started)**<br>
**[Example](#code-example)**<br>
**[Init / Utils](#init-and-utils)**<br>
**[Rendering](#rendering)**<br>
**[Input](#input)**<br>
**[GUI](#gui)**<br>
**[Collisions](#collisions)**<br>

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

## Init and Utils

`void	SDLX_Start(char *name, int x, int y, int h, int w, int flags);`

Inits SDLX and SDL. Sets the SDLX_Display struct with a window and renderer created from the parameters passed (window name, positions, dimension)

`void			SDLX_BackgroundSet(SDL_Texture *bg);`

Sets the backrgound image

`SDLX_Display	*SDLX_DisplayGet(void);`

Gets the SDLX_Display struct;

`void		SDLX_FPSAdjust(void);`

Delays subsequent code to match the frame rate set in SDLX_config.h

`SDL_Texture *SDLX_LoadTexture(char *path, SDLX_Display *display);`

Loads a texture from a path

`void		SDLX_SpriteCreate(SDLX_Sprite *spriteDst, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst);`

Initializes the sprite spriteDst withtexture, src and dst. If src is null, sprite._src will be undefined. Else sprite.src will point to sprite._src
sprite.dst will point to sprite._dst;

`SDL_bool			SDLX_DefaultCollision(SDLX_Collider *self, SDLX_Collider *other);`

Default collision assumes the collider is a rectangle;

`static int	SDLX_NullGUIFunc(SDLX_GUIElem *elem){return 0;};`

Does nothing. Pass into GUIElem_create instead of NULL

`int			SDLX_PointInCircle(SDL_Point point, SDLX_Circle circle);`

Returns 1 if a point is in a circle, else 0



## Rendering

`void			SDLX_RenderQueueAdd(int queue, SDLX_Sprite sprite);`

Add a sprite to the specified queue; Does nothing if the queue doesnt exist;

`SDLX_RenderQueue**SDLX_RenderQueue_FetchAll(int *amount);`

Returns all the renderQueues and sets amount to the total count of returned queues;

`void			SDLX_RenderMessage(TTF_Font *font, char *msg, const SDL_Rect *src, const SDL_Rect *dst);`

Renders text to the screen. Src specifies what portion of the text to render (NULL if all) and dst specifies the position and dimensions;

`void			SDLX_RenderQueueDisplay(SDLX_RenderQueue *queue, SDLX_Display *display);`

Copies the content of a renderqueue to the renderer

`void			SDLX_ResetWindow(SDLX_Display *display);`

Clears the screen


`void 			SDLX_Render_DisplayAll(SDLX_Display *display);`

Copies the content of all queues to the renderer

## Input

`void        SDLX_InputMap(int sdl_code, int type, int sdlx_code, int value, int controller_no);`

Maps an SDL Keycode to an SDLX code (or any other interg). sdl_code **must** be and sdlkeycode, type should be 1 for keyboard and 2 for controller, value as the value to be set when the key has been pressed. controller no i irrelevant if setting a keyboard;

`void		SDLX_InputUpdate();`

Updates the input struct with the latest input. This does not consume the input

`SDLX_Input	SDLX_InputGet();`

returns the input struct


## GUI

```
void SDLX_GUIElem_Create(SDLX_GUIElem *dest,
			SDLX_Sprite *sprite, const char *name,
			SDLX_UIFunc isSelectFn,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickFn);
```

Initializes the GUIElem dest. If unnedeed, the functions may be set to SDLX_NullGUIFunc

`void	SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive);`

Sets a GUIElem to be interactable and rendered

`void	SDLX_GUIUpdate(void);`

Updates all active GUIElem

`void	SDLX_GUI_KeyMap(int up, int down, int left, int right, int select);`

Maps SDL_Keycodes for button selection with the keyboard

`void	SDLX_GUIElem_SetKbTarget(int isTarget,SDLX_GUIElem *target, SDLX_GUIElem *up, SDLX_GUIElem *down, SDLX_GUIElem *left, SDLX_GUIElem *right);`

Sets a GUIElem to be selectable with the keyboard. up, down, left and right should be the elements to be selected when the respective key is pressed.

`void	SDLX_GUIElem_SetDefaultTarget(SDLX_GUIElem *defaultTarget);`

Default GUIElem to be selected when using the keyboard. this MUST be set if using the kayboard to select GUIElem

## Collisions

`void	SDLX_PollCollisions(void);`

Updates the collision array 

`void	SDLX_ResolveCollisions(void);`

Resolves the collisions in the collison array

```
void	SDLX_ColliderCreate(int layerMask, int type, void *collisionBox, SDLX_Collider *dst,
							SDLX_CollisionFn collisionFn, SDLX_ReactionFn reactionFn, void *data);
```

Initializes the collider dst. A collider can only collider with objects within the same layermask. Type is 0 for rectangle and 1 for circle. collisionbox may be any structure that will be used to determine the hitbox of the collision and will be passed to collisionFn (which is the function used to check for collision) ReactionFn is the function that determines what happens after a collision has been detected.

