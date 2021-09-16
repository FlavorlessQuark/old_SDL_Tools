#include "SDLX/SDLX_structs.h"
#include "SDLX/SDLX_config.h"
# include "SDL2/SDL_image.h"

void SDLX_FPSAdjust()
{
	static int start;
	int delay;

	// This if statement else first frame is delayed by > 1000 ms
	// Workaround is to pass start time but requires variable from outside func
	// Somehow set start to an appropriate starting value
	// This only slows game if it is rendering too fast - but it also halts loop
	// Need to :  if too fast render extra frames of non animated things
	// Render less if too slow
	if (start != 0)
	{
		delay = start - SDL_GetTicks();
		delay = MAX(FRAME_TIME - delay , 0);
		SDL_Delay(delay);
	}
	start = SDL_GetTicks();
}

SDL_Texture *SDLX_LoadTexture(char *path, SDLX_Display *display)
{
	return 	SDL_CreateTextureFromSurface(display->renderer, IMG_Load(path));
}

//?????????\
//How do??
void SDLX_SpriteCreate(SDLX_Sprite *spriteDst, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst)
{
	if (dst)
		spriteDst->dst = *dst;
	if (src)
		spriteDst->src = *src;
	spriteDst->dstptr = &spriteDst->dst;
	spriteDst->srcptr = &spriteDst->src;
	if (tex)
		spriteDst->sprite_sheet = tex;

}

int	SDLX_MouseInRect(int x, int y, SDL_Rect rect)
{
	if (rect.x <= x && x <= (rect.x + rect.w) &&
		rect.y <= y && y <= (rect.y + rect.h))
		return SDLX_TRUE;
	return SDLX_FALSE;
}

int SDLX_PointInCircle(SDL_Point point, SDLX_Circle circle)
{
	return (
			point.x <= circle.x + circle.radius
		&&	point.x >= circle.x - circle.radius
		&&	point.y <= circle.y + circle.radius
		&&	point.y >= circle.y - circle.radius
	);
}

int		SDLX_DefaultCollision(SDLX_Collider *self, SDLX_Collider *other)
{
	return SDL_HasIntersection(self->collisionBoxPtr, other->collisionBoxPtr);
}
