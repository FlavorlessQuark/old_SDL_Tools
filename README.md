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

```c
#include "SDLX/SDLX.h"
#include "SDL2/SDL_image.h"

typedef struct t_example
{
	SDLX_Sprite  dragon;
	SDLX_Sprite  buttonSprite;

	SDLX_GUIElem button;

	SDLX_Animator dragonAnimator;
	SDLX_Animator buttonAnimator;
}				t_example;

t_example example;

int buttonHover(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(&example.buttonAnimator, 1, SDLX_NONE);
}

int buttonClick(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(&example.buttonAnimator, 2, SDLX_NONE);
	SDL_Log("CLICK %s\n", elem->name);
}

void init()
{
	SDLX_Display *display;
	SDLX_Input 	input;
	SDLX_Anim	**dragonanim;
	SDLX_Anim	**buttonanim;
	SDL_Texture *dragontex;
	SDL_Texture *buttontex;
	
	SDLX_Start("DEFAULT", WIN_X, WIN_Y, WIN_H, WIN_W, SDL_WINDOW_SHOWN);
	
	dragonanim = calloc(1, sizeof(SDLX_Anim *));
	buttonanim = calloc(2, sizeof(SDLX_Anim *));
	display = SDLX_DisplayGet();

	SDLX_InputMap(SDL_SCANCODE_W, 1, SDLX_UP, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_A, 1, SDLX_LEFT, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_S, 1, SDLX_DOWN, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_D, 1, SDLX_RIGHT,1, -1);

	SDLX_InputMap(SDL_SCANCODE_UP, 1, SDLX_UP, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT, 1, SDLX_LEFT, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_DOWN, 1, SDLX_DOWN, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT, 1, SDLX_RIGHT,1, -1);

	dragontex = SDL_CreateTextureFromSurface(display->renderer, IMG_Load("Assets/test.png"));
	buttontex = SDL_CreateTextureFromSurface(display->renderer, IMG_Load("Assets/button.png"));
	
	dragonanim[0] = SDLX_AnimLoadHorizontal(dragontex, 8, 32, 32, SDLX_TRUE, 0, 0);

	buttonanim[0] = SDLX_AnimLoadHorizontal(buttontex, 1, 64, 64, SDLX_FALSE, 0, 0);
	buttonanim[1] = SDLX_AnimLoadHorizontal(buttontex, 9, 64, 64, SDLX_FALSE, 0, 0);
	buttonanim[2] = SDLX_AnimLoadHorizontal(buttontex, 2, 64, 64, SDLX_FALSE, 64 * 8, 0);

	SDLX_SpriteCreate(&example.dragon, dragontex, NULL, &(SDL_Rect){(WIN_W / 2) - 128, (WIN_H / 2) - 256, 256, 256});
	SDLX_SpriteCreate(&example.buttonSprite, buttontex, NULL, &(SDL_Rect){(WIN_W / 2) - 128, (WIN_H / 2), 256, 256});
	
	SDLX_GUIElem_Create(&example.button, &example.buttonSprite, "button", SDLX_DefaultGUISelect, buttonHover, SDLX_NullGUIFunc, SDLX_NullGUIFunc, buttonClick);

	SDLX_AnimatorCreate(&example.dragonAnimator, dragonanim, 1, &example.dragon);
	SDLX_AnimatorCreate(&example.buttonAnimator, buttonanim, 3, &example.buttonSprite);

	SDLX_GUIElem_SetDefaultTarget(&example.button);

	example.button.active = SDLX_TRUE;
}

int main()
{
	SDLX_Display *display;
	SDLX_Input input;

	init();
	display = SDLX_DisplayGet();
	while (1)
	{
		SDLX_ResetWindow(display);
		SDLX_InputLoop();
		SDLX_InputUpdate();
		{
			input = SDLX_InputGet();
			example.dragon.dst->y += (input.input[SDLX_UP] * -5) + (input.input[SDLX_DOWN] * 5); 
			example.dragon.dst->x += (input.input[SDLX_RIGHT] * 5) + (input.input[SDLX_LEFT] * -5); 
		}
		SDLX_GUIUpdate();
		SDLX_AnimationUpdate();
		SDLX_RenderQueueAdd(0, example.dragon);
		SDLX_Render_DisplayAll(display);
		SDL_RenderPresent(display->renderer); 
		SDLX_FPSAdjust();
	}
}
```

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

