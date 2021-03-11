/**
 *  @file:
 *  @author: FlavorlessQuark
 *  Last Modified: 2021-03-10 22:06:12
 *
 * 	IMPORTANT : This library relies on SDL2. It assumes SDL2 lives in the same includes/
 *  folder, in a directory named SDL2.
 *
 *  @brief: This is the main header file for the SDLX library and as such
 * 	it contains most of the functions used thorughout SDLX.
 *
 *  SDLX is a wrapper around SDL2. Its main purpose is to reduce development time by
 *  providing functions and tools such as automatic animations and rendering
 *
 */

#ifndef SDLX_H
#define SDLX_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"

# include "SDLX_config.h"
# include "SDLX_structs.h"
# include "SDLX_input.h"

# ifndef MAX
#  define MAX(a, b)\
	({ 	__typeof__ (a) _a = (a);\
		__typeof__ (b) _b = (b);\
		(_a > _b) ? (a) : (b);})\

# endif

# ifndef MIN
#  define MIN(a, b)			\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a < _b) ? (a) : (b);})\

# endif

/**
 * @brief initializes SDLX and creates a display. Should be called once at program start
 */
void			SDLX_Start();
/**
 * @brief reset or sets the display
 */
void			SDLX_DisplaySet(void);
void			SDLX_BackgroundSet(SDL_Texture *bg);
SDLX_Display	*SDLX_DisplayGet(void);

/**
* @brief Legacy function to clear screen, use SDLX_ResetWindow instead
 */
void			SDLX_screen_reset(SDL_Renderer *renderer, SDL_Color *bg_color);

void			SDLX_AnimationUpdate(void);
void			SDLX_RenderQueueAdd(int queue, SDLX_Sprite sprite);

/**
 * @brief Creates an animtor from scratch or as a copy of another
 * @param copy animator to copy. NULL if creating a new animator
 * @param anims the set of animtions to add to the animator
 * @param amount the number of animation to add.  This shiuld be the length of anims
 * @param dst	the destination rectangle to render the anim
 */
SDLX_Animator	*SDLX_AnimatorInstantiate(SDLX_Animator *copy, SDLX_Anim **anims, int amount, SDL_Rect *dst);
SDLX_RenderQueue**SDLX_RenderQueueFetch(int *amount);

void			SDLX_RenderMessage(TTF_Font *font, char *msg, const SDL_Rect *src, const SDL_Rect *dst);
void			SDLX_RenderQueueDisplay(SDLX_RenderQueue *queue, SDLX_Display *display);
void			SDLX_ResetWindow(void);

void			SDLX_InputLoop(void);

/*
* Caps FPS to FRAMERATE and ensure app ticks are consitent
 */
void			SDLX_FPSAdjust(void);

/**
 * @brief Loads an animation from a spritesheet.
 * User should make their own function as this assues all frames of an animation are within the same row
 * @param cycle the number of frames in the animation
 * @param cell_w the width in pixels of a single frame
 * @param ceell_h the height in pixels of a single frame
 * @param loop whether to make this  animation repeat or not
 * @param x_off offset in pixel of the leftmost frame from the border of te image
 * @param y_off offset in pixel of the topmost frame from the border of te image
 */
SDLX_Anim		*SDLX_AnimLoad(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off);

#endif

