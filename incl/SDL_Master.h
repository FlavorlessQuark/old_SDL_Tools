#ifndef SDL_MASTER_H
# define SDL_MASTER_H
# include <SDL2/SDL.h>
# include <stdbool.h>

/* Defines */

# define WIN_NAME "default"
# define WIN_H 0
# define WIN_W 0
# define WIN_X 0
# define WIN_Y 0
# define WIN_FLAGS 0

# define MOUSE_IN 0
# define KEY_IN 0

# define BUTTON_MAX 1
# define SCREEN_DIVX 5 /* It is best to have divisions per w and h in case the screen is not square, though it may not matter*/
# define SCREEN_DIVY 5

# define FRAME_DELAY 0
# define ENDGAME 0
# define VAL 0

/* Structs */

struct s_master;
typedef struct s_master Master;

typedef void * (*func)(Master *);

typedef struct
{
	SDL_Scancode	key;
	SDL_MouseButtonEvent mouse;
}				Input;

typedef union	u_color_rgba
{
	Uint32		color;
	struct{
		Uint8 	r;
		Uint8 	g;
		Uint8 	b;
		Uint8 	a;
	}			bit_data;
}				color_rgba;

typedef struct	s_button
{
	SDL_Rect	hitbox;
	SDL_Texture *tex;

	color_rgba	color_clicked;
	color_rgba	color_default;

	bool		is_click;

	func		button_click;
	func		button_release;
}				Button;

typedef struct
{
	Button 		*buttons;
	int 		max;
	int 		current;
}				ScreenDiv;

typedef struct
{
	SDL_Rect	*sprites;
	SDL_Texture	*sheets;

	int			count;
}				SpriteSheet;

typedef struct
{
	SDL_Renderer *renderer;
	SDL_Window	*window;

	SpriteSheet	**SpriteSheets;
}				Display;

typedef struct
{
	Display		*display;
	Input		*input;
	ScreenDiv	*grid;
}				Master;

/* Functions */

/* File : SDLTools_init.c */
Input		*init_input();
Master		*init_master();
Display		*init_display();
ScreenDiv	*init_grid();
SpriteSheet *init_spritesheet(SDL_Texture *sheet, int count, int w, int h);

/* File : SDLTools_destroy.c */
void	annhilate(Display *display);


/* File : reference_texture.c */
void	ref_texture(SDL_Rect *ref, int width, int length);

/*File update.c */
void	update(Display *display);

#endif
