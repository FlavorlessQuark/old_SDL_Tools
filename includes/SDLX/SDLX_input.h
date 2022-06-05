#ifndef SDLX_INPUT_H
# define SDLX_INPUT_H

# include "SDLX_structs.h"


SDLX_Input	SDLX_InputGet();
int			SDLX_DirReverse(int dir);


/**
 * @brief Maps an SDL input Keycode to and SDLX code for ease of access. Allows multiple mappins per SDLX code
 * 
 * @param sdl_code the SDL_Keycode or Controller_code to map from
 * @param type the type of input to be mapped 1: keyboard 2 :controller
 * @param sdlx_code the SDLX code to map to
 * @param value value returned when the key is pressed, if undure, set to 1
 * @param controller_no  controller index to pull input from, irrelevant if type is not 2
 * 
 */
void        SDLX_InputMap(int sdl_code, int type, int sdlx_code, int value, int controller_no);

void 		SDLX_InputResetBuffer(void);

void		SDLX_InputMap  (int sdl_code, int type, int sdlx_code, int value, int SDL_UNUSED controller_no);
void		SDLX_InputUpdate();
void		SDLX_InputLoop(void);

int 		SDLX_GetKeyMapState(int key);

#endif
