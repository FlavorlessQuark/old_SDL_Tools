#include "SDL_Master.h"

SpriteSheet *init_spritesheet(SDL_Texture *sheet, int count, int w, int h)
{

}

Input *init_input()
{

}

ScreenDiv *init_grid()
{

}

Display *init_display()
{
	Display *display;

	display = malloc(sizeof(Display));
	display->spritesheet = malloc(sizeof(SDL_Rect) * ((VAL * VAL) * VAL));

	display->window = SDL_CreateWindow(WIN_NAME, WIN_X, WIN_Y, WIN_W, WIN_H, WIN_FLAGS);
	display->renderer = SDL_CreateRenderer(display->window, -1, render_flags);

	return display;
}

Master *init_master()
{
	Master *master;

	SDL_Init(SDL_INIT_EVERYTHING);
	Uint32 render_flags = SDL_RENDERER_SOFTWARE;

	return master;
}
