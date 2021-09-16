#include "SDLX_structs.h"
#include "SDLX_utils.h"
#include "SDLX_input.h"

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


typedef struct SDLX_GUIMeta
{
	int active;
	int selectStatus;

	SDLX_UIFunc		isSelectFn;
	SDLX_UIFunc		UIFuncs[4];
	SDLX_GUIElem	*neighbours[4];
}				SDLX_GUIMeta;

typedef struct SDLX_GUIInfo
{
	SDLX_GUIElem elem;
	SDLX_GUIMeta meta;

	struct SDLX_GUIInfo *next;
}				SDLX_GUIInfo;

typedef struct GUI_intern
{
	SDLX_GUIInfo *head;
	SDLX_GUIInfo *tail;

	size_t GUICount;
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
	_intern.head = calloc(GUICT, sizeof(SDLX_GUIInfo));
	_intern.tail = _intern.head;
	_intern.GUICount = 0;
	defaultTarget = NULL;
	currentTarget = NULL;
	selector = SDLX_KEYBOARD;
}


//Change this to linked list /array
void SDLX_GUIElem_Create(SDLX_GUIElem *dest,
			SDLX_Sprite *sprite, const char *name,
			SDLX_UIFunc isSelectFn,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickFn)
{
	SDLX_GUIInfo *node;

	node =  calloc(1, sizeof(SDLX_GUIInfo));

	if (sprite)
	{
		node->elem.sprite = sprite;
 	}
	else
		return NULL;

	(node->elem.sprite.dstptr == NULL)
		? (node->elem.sprite.dstptr = &node->elem.sprite.dst)
		: (NULL);
	node->elem.name = name;
	node->elem.metadata = &node->meta;
	node->elem.autotrigger = 	SDLX_TRUE;

	node->meta.cd				= 10;
	node->meta.active			= SDLX_FALSE;
	node->meta.selectStatus	= SDLX_FALSE;

	node->meta.isSelectFn 		= isSelectFn;

	node->meta.UIFuncs[STARTSELECT]= OnSelectEnterFn;
	node->meta.UIFuncs[STAY] 		= OnSelectStayFn;
	node->meta.UIFuncs[ENDSELECT]	= OnSelectExitFn;
	node->meta.UIFuncs[CLICKED]	= OnClickFn;

	_intern.tail->next = node;
	_intern.tail = node;
	_intern.GUICount++;
	return &(node->elem);
}

void	SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive)
{
	elem->metadata->active = isActive;
	if (elem->animator.anims)
		elem->animator.active = isActive;
		elem->animator.frameNo = 0;
		elem->animator.state = 0;
	}
}

void SDLX_GUI_KeyMap(int up, int down, int left, int right, int select)
{
	GUI_KEYS[U] = up;
	GUI_KEYS[D] = down;
	GUI_KEYS[L] = left;
	GUI_KEYS[R] = right;
	GUI_KEYS[SELECT] = select;
}

void	SDLX_GUIElem_SetDefaultTarget(SDLX_GUIElem *def) { defaultTarget = def; def->metadata->selectStatus = SDLX_NONE;
	currentTarget = def;
	def->triggered = SDLX_FALSE;
}

void	SDLX_GUIElem_SetKbTarget(SDL_UNUSED int Target,SDLX_GUIElem *target, SDLX_GUIElem *up, SDLX_GUIElem *down, SDLX_GUIElem *left, SDLX_GUIElem *right)
{
	target->metadata->neighbours[U] = up;
	target->metadata->neighbours[D] = down;
	target->metadata->neighbours[L] = left;
	target->metadata->neighbours[R] = right;
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
	select = elem->metadata->selectStatus;
	mouseHover = SDLX_MouseInRect(input.mouse.x, input.mouse.y, *elem->spriteptr->dstptr);

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
	SDLX_GUIMeta *meta;

	meta = elem->metadata;
	select = elem->metadata->selectStatus;
	if (elem == currentTarget)
	{
		for (int i = 0; i < 4; i++)
		{
			if ((KEYSDATA[i] == SDLX_KEYDOWN || (KEYSDATA[i] == SDLX_KEYHELD && !count(&(meta->cd), 10)))
			&& elem->metadata->neighbours[i])
			{
				select = 0;
				currentTarget = elem->metadata->neighbours[i];
				currentTarget->metadata->selectStatus = 1;
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
	SDLX_GUIInfo *node;

	input = SDLX_InputGet();
	oldselector = (selector << 1) & 2;
	newselector = 0;
	node = _intern.head->next;
	while(node)
	{
		if (SDL_PointInRect(&input.mouse, node->elem.sprite.dstptr))
		{
			newselector = 1;
			break ;
		}
		node = node->next;
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
	SDLX_GUIMeta *meta;
	SDLX_GUIInfo *node;
	SDLX_Input 	input;
	int mouseHover;
	int select;
	int oldSelect;


	_GetSelector();
	node = _intern.head->next;
	while (node)
	{
		meta = &node->meta;
		if (meta->active)
		{
			select =  meta->isSelectFn(&node->elem);
			oldSelect = meta->selectStatus;

			if (select == SDLX_TRUE && oldSelect == SDLX_FALSE)
			{
				meta->UIFuncs[STARTSELECT](&node->elem);
			}
			else if (select == SDLX_TRUE && oldSelect == SDLX_TRUE)
			{
				meta->UIFuncs[STAY](&node->elem);
			}
			else if (select == SDLX_FALSE && oldSelect == SDLX_TRUE)
			{
				meta->UIFuncs[ENDSELECT](&node->elem);
			}
			// SDL_Log("FUNC");
			meta->selectStatus = select;
			if (select != SDLX_FALSE && node->elem.triggered)
			{
				SDL_Log("Triggered %s\n", node->elem.name);
				meta->UIFuncs[CLICKED](&node->elem);
			}
			// if (&node->>autotrigger) Maybe?
			node->elem.triggered = SDLX_FALSE;
		}
		node= node->next;
	}
}
