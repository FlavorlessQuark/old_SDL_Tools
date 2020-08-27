#include "SDL_Master.h"


int main()
{
	Display *display;

	display = display_init();
	update(display);
}
