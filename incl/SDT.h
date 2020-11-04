#ifndef SDL_MASTER_H
# define SDL_MASTER_H

# include <SDL2/SDL.h>
# include "SDT_def.h"
# include <stdbool.h>

typedef struct s_master Master;

typedef struct
{
	SDL_Scancode		key;
	SDL_MouseButtonEvent mouse;
}				SDT_Input;

typedef struct s_SDT_Point
{
	int x;
	int y;
}				SDT_Point;

typedef struct s_SDT_Object
{
	int			ID:
	void		*data;

	SDT_Point 	coordinates;

	bool		(*func)(void *);
}				SDT_Object;

typedef struct SDT_EventNode
{
	int			ID;
	bool		remove;

	SDT_EventNode *next;
}				SDT_EventNode;

typedef struct 	SDT_Dict
{
	int 		size;
	int			*keys;

	SDT_Object	**values;
}				SDT_Dict;

typedef union	SDT_rgba
{
	Uint32		color;
	struct {
		Uint8 	r;
		Uint8 	g;
		Uint8 	b;
		Uint8 	a;
	}			bit_data;
}				SDT_rgba;

typedef struct
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
}					SDT_Display;

typedef struct 	SDT_Screenspace
{
	int			div_x;
	int			div_y;

	/* This might need to be a linked list... */
	SDT_Object	**screen_objs;
}				SDT_Screenspace;


typedef struct
{
	SDT_Display		display;
	SDT_Dict		*objects;
	SDT_Input		*input;

	SDT_Screenspace	*screenspace;
}					SDT_Scene;



/* Functions */

/* File : SDT.c */

SDT_Scene		*SDT_SceneGet();

void			SDT_ScreenAdd(SDT_Object *object);
void			SDT_ScreenRemove(int ID);
void			SDT_ScreenEmpty();

/* File : SDT_dict.c */

SDT_Dict	*SDT_DictRetrieve(int ID, SDT_Dict dict);
SDT_Dict	*SDT_DictInit(int size);
void		 SDT_DictRemove(int ID, SDT_Dict dict);
void		 SDT_DictEmpty(SDT_Dict dict);
void		 SDT_DictDelete(SDT_Dict dict);
void		 SDT_DictAdd(SDT_Object *object, SDT_Dict *dict);

/* File : SDT_events.c */

SDT_EventNode	SDT_EventInit();
SDT_EventNode	SDT_EventGet(int ID);
void			SDT_EventAdd(int ID);
void			SDT_EventRemove(int ID);
void			SDT_EventEmpty();


/* File : reference_texture.c */
void	ref_texture(SDL_Rect *ref, int width, int length);

/*File SDT_update.c */
void	SDT_Update();
void	SDT_Render();
void	SDT_Events();
void	SDT_Inputs();

#endif
