#ifndef SDLX_UTILS_H
# define SDLX_UTILS_H

# include "SDLX/SDLX_structs.h"
/*
* Caps FPS to FRAMERATE and ensure app ticks are consitent
 */
void		SDLX_FPSAdjust(void);
int			SDLX_MouseInRect(int x, int y, SDL_Rect rect);
SDL_Texture *SDLX_LoadTexture(char *path, SDLX_Display *display);
void		SDLX_SpriteCreate(SDLX_Sprite *spriteDst, SDL_Texture *tex, SDL_Rect *src, SDL_Rect *dst);
int			SDLX_DefaultCollision(SDLX_Collider *self, SDLX_Collider *other);

static int	SDLX_NullGUIFunc(SDLX_GUIElem *elem){return 0;};
int			SDLX_PointInCircle(SDL_Point point, SDLX_Circle circle);


#endif
