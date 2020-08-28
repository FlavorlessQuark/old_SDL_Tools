#include "SDL_Master.h"

void destroy_display(Display *display)
{
	SDL_DestroyRenderer(display->renderer);
	SDL_DestroyWindow(display->window);
	SDL_Quit();
}
