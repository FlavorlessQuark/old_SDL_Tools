#ifndef SDL_MASTER_H
# define SDL_MASTER_H
# include <SDL2/SDL.h>

# define WIN_NAME "default"
# define WIN_H 0
# define WIN_W 0
# define WIN_X 0
# define WIN_Y 0
# define WIN_FLAGS 0

# define MOUSE_IN 0
# define KEY_IN 0

# define TILE_W 0
# define TILE_H 0

# define FRAME_DELAY 0
# define ENDGAME 0
# define VAL 0

typedef struct	s_input
{
	SDL_Scancode key;

	int 		mouse_x;
	int 		mouse_y;
}				Input;

typedef struct s_display
{
	SDL_Renderer *renderer;
	SDL_Window	*window;
	SDL_Rect	*spritesheet;

	Input		input;
	int			state;
}				Display;

/* File : display_init.c */
Display	*display_init();
void	annhilate(Display *display);

/* File : reference_texture.c */
void	ref_texture(SDL_Rect *ref, int width, int length);

/*File update.c */
void	update(Display *display);

#endif
