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
	int input[INPUT_AMOUNT]; // This is just assuming no more than 5 keys will be mapped but that is a terrible asusmption. This should be allocated
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
/*
* This functions doesn't exist yet :>
 */
int			SDLX_InputRemap(int sdl_code, int type, int sdlx_code, int controller_no);

/**
 * @brief Maps an SDL input Keycode to and SDLX code for ease of access. Allows multiple mappins per SDLX code
 * @example SDLX_inputMap(SDL_KEYCODE_RIGH, 1, SDLX_RIGHT, 0);
 * @param sdl_code the SDL_Keycode or Controller_code to map from
 * @param type the type of input to be mapped 1: keyboard 2 :controller
 * @param sdlx_code the SDLX code to map to
 * @param controller_no controller index to pull input from, irrelevant if type is not 2
 *  */
void		SDLX_InputMap  (int sdl_code, int type, int sdlx_code, int SDL_UNUSED controller_no);
void		SDLX_InputUpdate(SDL_Event SDL_UNUSED event);

#endif
