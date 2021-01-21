#include "../../incl/SDT.h"

void SDT_InputLoop(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
	}
}

void SDT_RenderLoop(void)
{	
	SDT_Scene *scene;

	scene = SDT_GetScene();
	SDL_RenderCopy(scene->renderer, scene->tex, NULL, NULL);
	SDL_RenderPresent(scene->renderer);
	SDL_SetRenderDrawColor(scene->renderer, 0, 0, 0, 255);
	// SDL_RenderClear(scene->renderer);
}

void SDT_Update(void)
{
	SDT_InputLoop();
	SDT_RenderLoop();
}