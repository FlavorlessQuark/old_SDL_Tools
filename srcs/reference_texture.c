#include "SDL_Master.h"

void ref_texture(SDL_Rect *ref, int width, int length)
{
	int w, l;

	w = 0;
	while (w < width)
	{
		l = 0;
		while (l < length)
		{
			ref[ w * VAL + l].w = TILE_H;
			ref[ w * VAL + l].h = TILE_W;
			ref[ w * VAL + l].x = (w * TILE_W);
			ref[ w * VAL + l].y = (l * TILE_H);
			l++;
		}
		w++;
	}
}
