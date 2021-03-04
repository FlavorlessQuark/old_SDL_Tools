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

void	SDLX_RenderQueueDisplay(SDLX_RenderQueue *queue, SDLX_Display *display)
{
	size_t i;

	i = 0;
	SDL_Log("Queue has %zu\n", queue->amount);
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