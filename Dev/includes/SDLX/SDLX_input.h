#include "SDLX.h"

#ifndef SDLX_INPUT_H
# define SDLX_INPUT_H

typedef struct	SDLX_KeyMap
{
	int key;
	int type;
	int	*dest;
	int controller_no;
	
	struct SDLX_KeyMap *next;
}	SDLX_KeyMap;

typedef struct	SDLX_Input
{
	int input[5];
	int mouse_x;
	int mouse_y;
}				SDLX_Input;


typedef enum SDLX_Keys
{
	SDLX_NONE = 0,
	SDLX_UP,
	SDLX_DOWN,
	SDLX_LEFT,
	SDLX_RIGHT,
	SDLX_PAUSE
}			SDLX_Keys;

typedef enum SDLX_InputType
{
	SDLX_UNDEFINED = 0,
	SDLX_KEYBOARD,
	SDLX_CONTROLLER,
	SDLX_AXIS,
	SDLX_GESTURE
}				SDLX_InputType;

SDLX_Input	SDLX_InputGet();
int			SDLX_DirReverse(int dir);
int			SDLX_InputRemap(int sdl_code, int type, int sdlx_code, int controller_no);
void		SDLX_InputMap  (int sdl_code, int type, int sdlx_code, int controller_no);
void		SDLX_InputUpdate(SDL_Event SDL_UNUSED event);

#endif