#include "SDLX/SDLX_input.h"


// These variables to be only visible within this file
// Input can bet fetched via SDLX_InputGet();
// Keymap to contain all keymappings. User shouldn't be able to
// access this
typedef struct	SDLX_KeyMap
{
	int key;
	int type;
	int	*dest;
	int value;
	int controller_no;

	struct SDLX_KeyMap *next;
}	SDLX_KeyMap;

static SDLX_Input input;
static SDLX_KeyMap *keymap;
static int input_buffer[INPUT_AMOUNT];

SDLX_Input	SDLX_InputGet(void) {return input;}

void 		SDLX_InputReset(int key) {input.input[key] = 0;}

void 		SDLX_InputResetBuffer(void)
{
	SDL_memcpy4(input_buffer, input.input, INPUT_AMOUNT);
	SDL_memset4(input.input, 0, INPUT_AMOUNT);
	input.mouse_click = SDLX_FALSE;
	input.key_down = SDLX_NONE;
}

int			SDLX_DirReverse(int dir)
{
	if (dir == SDLX_LEFT )	return SDLX_RIGHT;
	if (dir == SDLX_RIGHT)	return SDLX_LEFT;
	if (dir == SDLX_UP   )	return SDLX_DOWN;
	if (dir == SDLX_DOWN )	return SDLX_UP;
	return SDLX_NONE;
}
//sdl_code as sdl macro defining what key

void SDLX_InputMap(int sdl_code, int type, int sdlx_code, int value, int controller_no)
{
	SDLX_KeyMap *new_mapping;

	// This could be a static array of MAX_MAPPING size, however it is unlikely that things will get
	// new mappins in the middle of a game, and I feel like a few small allocations as the game starts
	// won't be much of a drawback. This allows to have an arbitrary number of mappings
	// Though one can argue that it is unlikely that something will get mapped more than a certain amount
	// However linked lists also allow for easier unmapping since nodes can dynamically be removed
	// wheras arrays have a fixed number of indices and it would be troublesome to null them
	// But unmaping keys should also be fairly rare. All in all the pros and cons still have to be weighted
	// so I am going with what I find easiest at the moment.
	new_mapping = calloc(1, sizeof(SDLX_KeyMap));
	new_mapping->next = keymap;
	new_mapping->type = type;
	new_mapping->value = value;
	new_mapping->key = sdl_code;
	new_mapping->dest = &input.input[sdlx_code];
	new_mapping->controller_no = controller_no;
	keymap = new_mapping;
}


int SDLX_InputRemap(int sdl_code, int type, int sdlx_code, int value,  int controller_no)
{
	SDLX_KeyMap *map;

	map = keymap;
	while (map)
	{
		if (map->type == type && map->key == sdl_code)
		{
			map->dest = &input.input[sdlx_code];
			map->controller_no = controller_no;
			return (0);
		}
		map = map->next;
	}
	return (1);
}


//SPECIFIC KEY LIKE W A S D ETC
// int SDLX_GetKeyState(int key)
// {

// }

// KEYMAP KEY LIKE SLDX_UP, DOWN ETC
int SDLX_GetKeyMapState(int key)
{
	int state;
	int pstate;

	state = input.input[key];
	pstate = input_buffer[key];

	if (state > 0 && pstate > 0)
		return SDLX_KEYHELD;
	else if (state == 0 && pstate > 0)
		return SDLX_KEYUP;
	else if (state > 0 && pstate == 0)
		return SDLX_KEYDOWN;
	else
		return SDLX_NONE;
}


void _GetInputState(SDLX_KeyMap 	*map_node)
{
	const Uint8		*keyboard;
	int input_val;

	keyboard = SDL_GetKeyboardState(NULL);

	if (map_node->type == SDLX_KEYBOARD)
		input_val = (keyboard[map_node->key] * map_node->value);
	// else if (map_node->type == SDLX_CONTROLLER)
	// {
	// 	input_val = SDL_GameControllerGetButton(
	// 						SDL_GameControllerFromPlayerIndex(map_node->controller_no),// Getting undefined reference here, not sure why
	// 						map_node->key);
	// }
	*(map_node->dest) |= (input_val * map_node->value);
}

// This might need more input "types" but these would require that the events be saved
// Events can't be saved if they are left for the user to poll
// Lies and deception. They CAN be saved AHA! PEEKEVENTS~

void SDLX_InputUpdate()
{
	SDLX_KeyMap 	*map_node;
	SDL_Event		e[1];
	int				controller_button;
	int 			eNum;

	map_node = keymap;

	SDL_GetMouseState(&input.mouse.x, &input.mouse.y);
	SDL_GetRelativeMouseState(&input.mouse_delta.x, &input.mouse_delta.y);
	SDL_PumpEvents();

	SDLX_InputResetBuffer();
	eNum = SDL_PeepEvents(e, 1, SDL_PEEKEVENT, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP);

	if (e[0].button.type == SDL_MOUSEBUTTONUP || e[0].button.type == SDL_MOUSEBUTTONDOWN)
			input.mouse_click = e[0].button.type;
	map_node = keymap;
;
	while (map_node)
	{
		_GetInputState(map_node);
		map_node = map_node->next;
	}
}


// The below function only as placeholder else SDL doesn't render window
void SDLX_InputLoop(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
	}
}
