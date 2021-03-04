#include "SDLX/SDLX.h"

static SDLX_Display display;
void SDLX_Init(void);

void	SDLX_Close(void)
{
	SDL_DestroyWindow(SDLX_DisplayGet()->window);
	SDL_Quit();
}

void	SDLX_Start()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDLX_Init();
	atexit(SDLX_Close);
}

SDLX_Display	*SDLX_DisplayGet(void) {return &display;}

void 			SDLX_BackgroundSet(SDL_Texture *bg) {display.background = bg;}

void			SDLX_DisplaySet(void)
{
	display.window = SDL_CreateWindow(
				WIN_TITLE,
				WIN_X, WIN_Y,
				WIN_W, WIN_H,
				SDL_WINDOW_SHOWN
	);
	display.renderer = SDL_CreateRenderer(display.window, -1, 0);
}