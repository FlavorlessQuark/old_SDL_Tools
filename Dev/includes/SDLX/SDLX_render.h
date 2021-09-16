#ifndef SDLX_RENDER_H
# define SDLX_RENDER_H

#include "SDLX/SDLX_structs.h"

void			SDLX_RenderQueueAdd(int queue, SDLX_Sprite sprite);


SDLX_RenderQueue**SDLX_RenderQueue_FetchAll(int *amount);

void			SDLX_RenderMessage(TTF_Font *font, char *msg, const SDL_Rect *src, const SDL_Rect *dst);
void			SDLX_RenderQueueDisplay(SDLX_RenderQueue *queue, SDLX_Display *display);
void			SDLX_ResetWindow(void);
void 			SDLX_Render_DisplayAll(SDLX_Display *display);

#endif
