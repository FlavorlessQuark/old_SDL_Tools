#include "SDL_Master.h"

void annhilate(Display *display)
{
	SDL_DestroyRenderer(display->renderer);
	SDL_DestroyWindow(display->window);
	SDL_Quit();
}

Display *display_init()
{
	Display *display;

	SDL_Init(SDL_INIT_EVERYTHING);
	Uint32 render_flags = SDL_RENDERER_SOFTWARE;

	display = malloc(sizeof(Display));
	display->spritesheet = malloc(sizeof(SDL_Rect) * ((VAL * VAL) * VAL));

	display->window = SDL_CreateWindow(WIN_NAME, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);
	display->renderer = SDL_CreateRenderer(display->window, -1, render_flags);

	return display;
}
