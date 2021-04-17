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

void SDLX_RenderFillCircle(SDL_Renderer *ren, SDLX_Circle circle)
{
	double x;
	double y;
	double val;
	double valx;
	double valy;

	x = 0;
	valx = 0;
	y = circle.radius;
	val = 1 - circle.radius;
	valy = -2 * circle.radius;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawLine(ren,
						circle.x + circle.radius, circle.y,
						circle.x - circle.radius, circle.y);
	SDL_RenderDrawLine(ren,
						circle.x, circle.y + circle.radius,
						circle.x, circle.y - circle.radius);
	while(x < y)
	{
		if(val > 0)
		{
			y--;
			valy += 2;
			val += valy;
		}
		x++;
		valx += 2;
		val += valx + 1;
		SDL_RenderDrawLine(ren,
							circle.x + x, circle.y + y,
							circle.x - x, circle.y + y);
		SDL_RenderDrawLine(ren,
							circle.x + x, circle.y - y,
							circle.x - x, circle.y - y);
		SDL_RenderDrawLine(ren,
							circle.x - y, circle.y - x,
							circle.x + y, circle.y - x);
		SDL_RenderDrawLine(ren,
							circle.x - y, circle.y + x,
							circle.x + y, circle.y + x);
	}
}

void SDLX_RenderDrawCircle(SDL_Renderer *ren, SDLX_Circle circle)
{
	int i;
	double x;
	double y;
	double val;
	double valx;
	double valy;

	i= 0;
	x = 0;
	valx = 0;
	y = circle.radius;
	val = 1 - circle.radius;
	valy = -2 * circle.radius;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderDrawPoint(ren, circle.x + circle.radius, circle.y);
	SDL_RenderDrawPoint(ren, circle.x - circle.radius, circle.y);
	SDL_RenderDrawPoint(ren, circle.x, circle.y + circle.radius);
	SDL_RenderDrawPoint(ren, circle.x, circle.y - circle.radius);

	while(x < y)
	{
		if(val > 0)
		{
			y--;
			valy += 2;
			val += valy;
		}
		x++;
        valx += 2;
        val += valx + 1;
		SDL_RenderDrawPoint(ren, circle.x + x, circle.y + y);
		SDL_RenderDrawPoint(ren, circle.x - x, circle.y + y);
		SDL_RenderDrawPoint(ren, circle.x + x, circle.y - y);
		SDL_RenderDrawPoint(ren, circle.x - x, circle.y - y);
		SDL_RenderDrawPoint(ren, circle.x - y, circle.y - x);
		SDL_RenderDrawPoint(ren, circle.x + y, circle.y - x);
		SDL_RenderDrawPoint(ren, circle.x - y, circle.y + x);
		SDL_RenderDrawPoint(ren, circle.x + y, circle.y + x);
		i += 8;
	}
	// printf("Points %d circumfrence %d",i,(int)( 2 * M_PI * circle.radius ));
}
