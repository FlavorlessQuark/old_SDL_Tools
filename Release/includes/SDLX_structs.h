#ifndef SDLX_structs_H
#define SDLX_structs_H

# include "SDL2/SDL.h"


typedef struct SDLX_Display
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*background;
}	SDLX_Display;

typedef struct SDLX_Sprite
{
	SDL_Rect			dst;
	SDL_Rect			src;
	SDL_Rect			*dstptr;
	SDL_Rect			*srcptr;

	SDL_RendererFlip	flip;
	SDL_Point			center;
	SDL_Texture			*spriteSheet;

	double				angle;
}	SDLX_Sprite;

typedef struct SDLX_Anim
{
	int			cycle;
	int			start;
	int			queue;

	SDL_bool	loop;
	SDLX_Sprite	*sprites;
}				SDLX_Anim;

typedef struct SDLX_Animator
{
	int			state;
	int			amount;
	int			frameNo;

	SDL_Rect	dst;
	SDL_Rect	*dstptr;
	SDLX_Anim	**anims;
}				SDLX_Animator;

typedef struct SDLX_RenderQueue
{
	size_t		amount;
	size_t		capacity;

	SDLX_Sprite *sprites;
}	SDLX_RenderQueue;




#endif