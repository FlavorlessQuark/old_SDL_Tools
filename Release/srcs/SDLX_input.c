#include "SDLX/SDLX_input.h"


// These variables to be only visible within this file
// Input can bet fetched via SDLX_InputGet();
// Keymap to contain all keymappings. User shouldn't be able to
// access this

static SDLX_Input input;
static SDLX_KeyMap *keymap;

SDLX_Input	SDLX_InputGet(void) {return input;}

int			SDLX_DirReverse(int dir)
{
	if (dir == SDLX_LEFT )	return SDLX_RIGHT;
	if (dir == SDLX_RIGHT)	return SDLX_LEFT;
	if (dir == SDLX_UP   )	return SDLX_DOWN;
	if (dir == SDLX_DOWN )	return SDLX_UP;
	return SDLX_NONE;
}
//sdl_code as sdl macro defining what key
void SDLX_InputMap(int sdl_code, int type, int sdlx_code, int controller_no)
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
	new_mapping->key = sdl_code;
	new_mapping->dest = &input.input[sdlx_code];
	new_mapping->controller_no = controller_no;
	keymap = new_mapping;
}

// Unmapping input here, commented out for now as I'm not sure if I will keep this a list or change to an array
// see comments above

//int SDLX_InputUnmap(int sdl_code, int type)
//{
//	SDLX_KeyMap *map;
//}

int SDLX_InputRemap(int sdl_code, int type, int sdlx_code, int controller_no)
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

// This might need more input "types" but these would require that the events be saved
// Events can't be saved if they are left for the user to poll

void SDLX_InputUpdate(SDL_Event SDL_UNUSED event)
{
	SDLX_KeyMap 	*map_node;
	int				controller_button;
	int 			i;
	const Uint8		*keyboard;

	keyboard = SDL_GetKeyboardState(NULL);
	map_node = keymap;
	i = 0;
	//SDL_Log("Updating input \n");
	while (i < 5)
	{
		input.input[i] = 0;
		i++;
	}

	map_node = keymap;
	while (map_node)
	{
		if (map_node->type == SDLX_KEYBOARD)
			*(map_node->dest) = MAX(keyboard[map_node->key], *(map_node->dest));
		else if (map_node->type == SDLX_CONTROLLER)
		{
			controller_button = SDL_GameControllerGetButton(
								SDL_GameControllerFromPlayerIndex(map_node->controller_no),
								map_node->key);
			*(map_node->dest) = MAX(*(map_node->dest), controller_button);
		}
		map_node = map_node->next;
	}
}


// The below function might be best to be left to the user
// This is prevent user from accessing events
void SDLX_InputLoop(void)
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			exit(0);
	}
	SDLX_InputUpdate(event);
}
