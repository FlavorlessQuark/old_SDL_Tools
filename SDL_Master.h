#ifndef SDL_MASTER_H
# define SDL_MASTER_H
# include <SDL2/SDL.h>

# define WIN_NAME "default"
# define WIN_H 0
# define WIN_W 0
# define WIN_X 0
# define WIN_Y 0

# define MOUSE_IN 0
# define KEY_IN 0

# define TILE_W 0
# define TILE_H 0

# define FRAME_DELAY 0
# define ENDGAME 0

typedef struct s_display
{
	SDL_Renderer *renderer;
	SDL_Window	*window;

	int state;

}				Display

#endif
