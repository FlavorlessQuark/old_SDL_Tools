#include "SDLX/SDLX_structs.h"
#include "SDLX/SDLX_utils.h"
#include "SDLX/SDLX_input.h"

// #define UISIZE sizeof(SDLX_GUIElem) + sizeof(int)

# define GUICT 15
# define U 0
# define D 1
# define L 2
# define R 3
# define STARTSELECT 0
# define STAY 1
# define ENDSELECT 2
# define CLICKED 3
# define SELECT 4
# define WASSELECT 4


// typedef struct SDLX_GUIMeta
// {
// 	int active;
// 	int selectStatus;

// 	SDLX_UIFunc		isSelectFn;
// 	SDLX_UIFunc		UIFuncs[4];
// 	SDLX_GUIElem	*neighbours[4];
// }				SDLX_GUIMeta;

// typedef struct SDLX_GUIInfo
// {
// 	SDLX_GUIElem elem;
// 	SDLX_GUIMeta meta;

// 	struct SDLX_GUIInfo *next;
// }				SDLX_GUIInfo;

typedef struct GUI_intern
{
	SDLX_GUIElem **elems;
	// SDLX_GUIInfo *tail;

	size_t GUICount;
	size_t GUICap;
}			GUI_intern;

static int keypress;
static int selector;
static int GUI_KEYS[5];
static int KEYSDATA[5];
static GUI_intern _intern;
static SDLX_GUIElem *defaultTarget;
static SDLX_GUIElem *currentTarget;


// Change names for greater undertandability
// Active -> Enabled
//
void SDLX_ResetInput(int key);

void SDLX_GUIInit(void)
{
	_intern.elems = calloc(GUICT, sizeof(SDLX_GUIElem *));
	_intern.GUICount = 0;
	_intern.GUICap = GUICT;
	defaultTarget = NULL;
	currentTarget = NULL;
	selector = SDLX_KEYBOARD;
}


//Return int for error catching

void SDLX_GUIElem_Create(SDLX_GUIElem *dest,
			SDLX_Sprite *sprite, const char *name,
			SDLX_UIFunc isSelectFn,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickFn)
{
	if (_intern.GUICount >= _intern.GUICap)
	{
		_intern.GUICap *= 2;
		_intern.elems = realloc(_intern.elems, _intern.GUICap * sizeof(SDLX_Animator *));
	}

	if (sprite)
	{
		dest->sprite = sprite;
 	}
	else
		return ;

	(dest->sprite->dst == NULL)
		? (dest->sprite->dst = &dest->sprite->_dst)
		: (NULL);
	dest->name = name;
	dest->autotrigger = 	SDLX_TRUE;

	// dest->cd			= 10;
	dest->active		= SDLX_FALSE;
	dest->selectStatus	= SDLX_FALSE;

	dest->isSelectFn 		= isSelectFn;

	dest->UIFuncs[STARTSELECT]	= OnSelectEnterFn;
	dest->UIFuncs[STAY] 		= OnSelectStayFn;
	dest->UIFuncs[ENDSELECT]	= OnSelectExitFn;
	dest->UIFuncs[CLICKED]		= OnClickFn;

	_intern.elems[_intern.GUICount] = dest;
	_intern.GUICount++;
}

void SDLX_GUI_KeyMap(int up, int down, int left, int right, int select)
{
	GUI_KEYS[U] = up;
	GUI_KEYS[D] = down;
	GUI_KEYS[L] = left;
	GUI_KEYS[R] = right;
	GUI_KEYS[SELECT] = select;
}

void	SDLX_GUIElem_SetDefaultTarget(SDLX_GUIElem *def) {
	defaultTarget = def;
	def->selectStatus = SDLX_NONE;
	currentTarget = def;
	def->triggered = SDLX_FALSE;
}

void	SDLX_GUIElem_SetKbTarget(SDL_UNUSED int Target,SDLX_GUIElem *target, SDLX_GUIElem *up, SDLX_GUIElem *down, SDLX_GUIElem *left, SDLX_GUIElem *right)
{
	target->neighbours[U] = up;
	target->neighbours[D] = down;
	target->neighbours[L] = left;
	target->neighbours[R] = right;
}

int count(int *c, int max)
{
	if (!(*c))
	{
		*c = max;
		return 0;
	}
	*c -= 1;
	return 1;
}

int _MouseUpdate(SDLX_GUIElem *elem)
{
	SDLX_Input input;
	int select;
	int mouseHover;

	input = SDLX_InputGet();
	elem->triggered = 0;
	select = elem->selectStatus;
	mouseHover = SDLX_MouseInRect(input.mouse.x, input.mouse.y, *elem->sprite->dst);

	if (!mouseHover && currentTarget == elem)
	{
		select = SDLX_FALSE;
	}
	else if (mouseHover && select == STARTSELECT)
		select = SDLX_TRUE;
	else if (mouseHover && select == SDLX_NONE)
	{
		select = SDLX_TRUE;
	}
	else if (!mouseHover && select != SDLX_NONE)
		select = SDL_FALSE;
	if (elem->autotrigger == SDLX_TRUE)
	{
		elem->triggered = (input.mouse_click == SDL_MOUSEBUTTONDOWN);
	}

	return select;
}


int _KBUpdate(SDLX_GUIElem *elem)
{
	int select;

	select = elem->selectStatus;
	if (elem == currentTarget)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((KEYSDATA[i] == SDLX_KEYDOWN || (KEYSDATA[i] == SDLX_KEYHELD && !count(&(elem->cd), 10)))
			&& elem->neighbours[i])
			{
				select = 0;
				currentTarget = elem->neighbours[i];
				currentTarget->selectStatus = 1;
				KEYSDATA[i] = SDLX_NONE;
				break ;
			}
		}
		if (elem->autotrigger)
		{
			elem->triggered = (KEYSDATA[4] == SDLX_KEYDOWN);
		}
	}

	return select;
}

int SDLX_DefaultGUISelect(SDLX_GUIElem *elem)
{
	int select;

	select = SDLX_FALSE;
	if (selector & 1 || ((selector >> 1) & 1))
		select = _MouseUpdate(elem);
	if (selector == 0)
		select = _KBUpdate(elem);
	return select;
}

int		_GetSelector(void)
{
	SDLX_Input	input;

	int			newselector;
	int			oldselector;

	size_t		i;

	input = SDLX_InputGet();
	oldselector = (selector << 1) & 2;
	newselector = 0;
	i = 0;
	while(i < _intern.GUICount)
	{
		if (SDL_PointInRect(&input.mouse, _intern.elems[i]->sprite->dst))
		{
			newselector = 1;
			break ;
		}
		i++;
	}

	for (int i = 0; i < 4; i++)
	{
		KEYSDATA[i] = SDLX_GetKeyMapState(GUI_KEYS[i]);
		if (KEYSDATA[i] == SDLX_KEYDOWN || KEYSDATA[i] == SDLX_KEYHELD)
		{
			newselector = 0;
			break ;
		}
	}
	KEYSDATA[4] = SDLX_GetKeyMapState(GUI_KEYS[4]);
	selector = oldselector + newselector;

	return 1;
}

void SDLX_GUIUpdate(void)
{
	SDLX_Input 	input;
	int mouseHover;
	int select;
	int oldSelect;
	size_t		i;

	_GetSelector();
	i = 0;
	while (i < _intern.GUICount)
	{
		if (_intern.elems[i]->active)
		{
			select =  _intern.elems[i]->isSelectFn(_intern.elems[i]);
			oldSelect = _intern.elems[i]->selectStatus;

			if (select == SDLX_TRUE && oldSelect == SDLX_FALSE)
			{
				_intern.elems[i]->UIFuncs[STARTSELECT](_intern.elems[i]);
			}
			else if (select == SDLX_TRUE && oldSelect == SDLX_TRUE)
			{
				_intern.elems[i]->UIFuncs[STAY](_intern.elems[i]);
			}
			else if (select == SDLX_FALSE && oldSelect == SDLX_TRUE)
			{
				_intern.elems[i]->UIFuncs[ENDSELECT](_intern.elems[i]);
			}
			// SDL_Log("FUNC");
			_intern.elems[i]->selectStatus = select;
			if (select != SDLX_FALSE && _intern.elems[i]->triggered)
			{
				_intern.elems[i]->UIFuncs[CLICKED](_intern.elems[i]);
			}
			// if (&node->>autotrigger) Maybe?
			_intern.elems[i]->triggered = SDLX_FALSE;
		}
		i++;
	}
}
