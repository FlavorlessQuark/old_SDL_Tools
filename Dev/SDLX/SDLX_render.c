#include "SDLX/SDLX.h"

void	SDLX_ResetWindow(void)
{
	SDLX_Display *display;

	display = SDLX_DisplayGet();

	SDL_RenderClear(display->renderer);
	SDL_SetRenderDrawColor(display->renderer, 0, 0, 0, 0);
	if (display->background)
		SDL_RenderCopy(display->renderer, display->background, NULL, NULL);
}

void SDLX_RenderMessage(TTF_Font *font, char *msg, const SDL_Rect *src, const SDL_Rect *dst)
{
	SDL_Surface *message;
	SDLX_Display *display;

	display = SDLX_DisplayGet();
	message = TTF_RenderText_Solid(font,
						msg,
						(SDL_Color){255, 255, 255, 255});
	SDL_RenderCopy(display->renderer,
					SDL_CreateTextureFromSurface(display->renderer, message),
					src, dst);
	SDL_FreeSurface(message);
}

// This as a template display. User is free to create their own renderQ displayer
// this one just puts everything on the screen starting from the lowest Queue (assumed to be the background queue)
void	SDLX_RenderQueueDisplay(SDLX_RenderQueue *queue, SDLX_Display *display)
{
	size_t i;

	i = 0;
	while (i < queue->amount)
	{
		SDL_RenderCopyEx(display->renderer,
						queue->sprites[i].spriteSheet,
						queue->sprites[i].srcptr,
						queue->sprites[i].dstptr,
						queue->sprites[i].angle,
						&queue->sprites[i].center,
						queue->sprites[i].flip);
		i++;
	}
	queue->amount = 0;
}
