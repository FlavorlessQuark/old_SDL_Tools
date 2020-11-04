#include "SDT.h"

static void		 	SDT_Exit()
{
	SDT_ScreenEmpty();
	SDT_DictEmpty();
	SDT_EventEmpty();
	SDL_DestroyWindow(SDT_SceneGet()->display.window);
	SDL_Quit();
}

static void		SDT_Init(SDT_Scene *scene)
{
	SDL_Window	*window;

	SDL_Init(SDL_INIT_EVERYTHING);
	window = SDL_CreateWindow(WIN_NAME,WIN_X, WIN_Y,WIN_W, WIN_,SDL_WINDOW_SHOWN);

	scene->display.window = window;
	scene->display.renderer = SDL_CreateRenderer(window, -1, 0);

	atexit(SDT_Exit());
}


SDT_Scene		*SDT_SceneGet()
{
	static SDT_Scene scene;

	if (scene == NULL)
		SDT_Init(&scene)
	return &scene;
}
#pragam start SDT_SceneGet 1

void			SDT_ScreenAdd(SDT_Object *object)
{
/* Calculate grid coordinates from object , add to corresponding  */
}

void			SDT_ScreenRemove(int ID);
void			SDT_ScreenEmpty();
