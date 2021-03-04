#include "SDLX/SDLX.h"
#include "SDL2/SDL_image.h"

SDLX_Anim	*SDLX_AnimLoad(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off)
{
	SDLX_Anim	*anim;
	SDLX_Display *display;
	int i;
	int x;
	int y;

	display = SDLX_DisplayGet();
	anim = calloc(1, sizeof(*anim));
	anim->cycle = cycle;
	anim->start = 0;
	anim->loop = loop;
	anim->queue = 0;
	anim->sprites = calloc(cycle, sizeof(SDLX_Sprite));
	
	i = 0;
	x = x_off;
	y = y_off;
	while (i < cycle)
	{
		anim->sprites[i].src.x = x;
		anim->sprites[i].src.y = y;
		anim->sprites[i].src.h = cell_h;
		anim->sprites[i].src.w = cell_w;
		anim->sprites[i].srcptr = &anim->sprites[i].src;
		
		anim->sprites[i].center.x = 0;
		anim->sprites[i].center.y = 0;
		anim->sprites[i].spriteSheet = tex;

		anim->sprites[i].angle = 0;
		x += cell_w;
		i++;
	}
	return anim;
}