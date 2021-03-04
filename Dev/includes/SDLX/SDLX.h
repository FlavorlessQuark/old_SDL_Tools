#ifndef SDLX_H
#define SDLX_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_ttf.h"

# include "SDLX_config.h"
# include "SDLX_structs.h"
# include "SDLX_input.h"

# ifndef MAX
#  define MAX(a, b)\
	({ 	__typeof__ (a) _a = (a);\
		__typeof__ (b) _b = (b);\
		(_a > _b) ? (a) : (b);})\

# endif

# ifndef MIN
#  define MIN(a, b)			\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a < _b) ? (a) : (b);})\

# endif

void			SDLX_Start();
void			SDLX_DisplaySet(void);
void			SDLX_BackgroundSet(SDL_Texture *bg);
SDLX_Display	*SDLX_DisplayGet(void);

void			SDLX_screen_reset(SDL_Renderer *renderer, SDL_Color *bg_color);

void			SDLX_AnimationUpdate(void);
void			SDLX_RenderQueueAdd(int queue, SDLX_Sprite sprite);
SDLX_Animator	*SDLX_AnimatorInstantiate(SDLX_Animator *copy, SDLX_Anim **anims, int amount, SDL_Rect *dst);
SDLX_RenderQueue **SDLX_RenderQueueFetch(int *amount);

void			SDLX_RenderMessage(TTF_Font *font, char *msg, const SDL_Rect *src, const SDL_Rect *dst);
void			SDLX_RenderQueueDisplay(SDLX_RenderQueue *queue, SDLX_Display *display);
void			SDLX_ResetWindow(void);

void			SDLX_InputLoop(void);
void			SDLX_FPSAdjust(void);

SDLX_Anim		*SDLX_AnimLoad(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off);

#endif