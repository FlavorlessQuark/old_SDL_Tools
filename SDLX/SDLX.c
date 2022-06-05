#include "SDLX/SDLX.h"

/**
 * WIll need to change some ints to bools, but maybe not
 */

static SDLX_Display display;

void SDLX_RenderInit(void);
void SDLX_AnimInit(void);
void SDLX_GUIInit(void);

void	SDLX_Close(void)
{
	SDL_DestroyWindow(SDLX_DisplayGet()->window);
	SDL_Quit();
}

SDLX_Display	*SDLX_DisplayGet(void) {return &display;}

void 			SDLX_BackgroundSet(SDL_Texture *bg) {display.background = bg;}

void			SDLX_DisplaySet(char *name, int x, int y, int h, int w, int flags)
{
	display.window = SDL_CreateWindow(
				name,
				x, y,
				w, h,
				flags
	);
	display.renderer = SDL_CreateRenderer(display.window, -1, 0);
}

//ADD SDLX FLAGS
void			SDLX_Start(char *name, int x, int y, int h, int w, int flags)
{
	if (!SDL_WasInit(0))
		SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDLX_DisplaySet(name, x, y, h, w, flags);
	SDLX_CollisionsInit();
	SDLX_RenderInit();
	SDLX_AnimInit();
	SDLX_GUIInit();
	atexit(SDLX_Close);
}
