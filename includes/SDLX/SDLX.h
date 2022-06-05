/**
 *  @file:
 *  @author: FlavorlessQuark
 *  Last Modified: 2021-03-09 22:59:10
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

# include "../SDL2/SDL.h"
# include "../SDL2/SDL_image.h"
# include "../SDL2/SDL_ttf.h"

# include "SDLX_config.h"
# include "SDLX_LevelManager.h"
# include "SDLX_anim.h"
# include "SDLX_input.h"
# include "SDLX_render.h"
# include "SDLX_UI.h"
# include "SDLX_utils.h"
# include "SDLX_collisions.h"

/**
 * @brief initializes SDLX and creates a display
 */
void	SDLX_Start(char *name, int x, int y, int h, int w, int flags);
/**
 * @brief reset or sets the display
 */
void			SDLX_DisplaySet(char *name, int x, int y, int h, int w, int flags);
void			SDLX_BackgroundSet(SDL_Texture *bg);
SDLX_Display	*SDLX_DisplayGet(void);


#endif
