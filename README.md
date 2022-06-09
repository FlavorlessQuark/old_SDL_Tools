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
git clone git@github.com:FlavorlessQuark/old_SDL_Tools.git
cd old_SDL_Tools
make dynamic
make static
```

## Code example

**The assets used in this example were made by me. If you wish to use them, ask for permission first :)**

In this example, you will learn how to use the rendering, animator, input mapping and GUI components of SDLX

The end product will be a small scene with an animated sprite that can be moved around and a button that can be hovered and clicked

https://github.com/FlavorlessQuark/old_SDL_Tools/blob/9894a814b08cf6b160081bffccd6b409b79ce1ed/Ressources/example.c#L1-L99

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

```c
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

```c
void	SDLX_ColliderCreate(int layerMask, int type, void *collisionBox, SDLX_Collider *dst,
							SDLX_CollisionFn collisionFn, SDLX_ReactionFn reactionFn, void *data);
```

Initializes the collider dst. A collider can only collider with objects within the same layermask. Type is 0 for rectangle and 1 for circle. collisionbox may be any structure that will be used to determine the hitbox of the collision and will be passed to collisionFn (which is the function used to check for collision) ReactionFn is the function that determines what happens after a collision has been detected.

