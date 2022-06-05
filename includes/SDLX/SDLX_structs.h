#ifndef SDLX_structs_H
#define SDLX_structs_H

# include "../SDL2/SDL.h"
# include "SDLX_config.h"

# ifndef MAX
#  define MAX(a, b)\
	({ 	__typeof__ (a) _a = (a);\
		__typeof__ (b) _b = (b);\
		(_a > _b) ? (a) : (b);})\

# endif

# ifndef MIN
#  define MIN(a, b)			\
({ 	__typeof__ (a) _a = (a);\
	__typeof__ (b) _b = (b);\
	(_a < _b) ? (a) : (b);})\

# endif

struct SDLX_GUIMeta;
struct SDLX_Animator;
typedef struct SDLX_Collider SDLX_Collider;
typedef struct SDLX_GUIElem SDLX_GUIElem;
// typedef struct SDLX_GUIMeta  GUIMETA;

// typedef void (* SDLX_CollisionFn)(struct SDLX_Collider *, struct SDLX_Collider *);
// typedef void(*SDLX_ReactionFn)(struct SDLX_Collider *, struct SDLX_Collider *);

typedef int (* SDLX_UIFunc)(struct SDLX_GUIElem *);

typedef SDL_bool (* SDLX_CollisionFn)(SDLX_Collider *, SDLX_Collider *);
typedef void	 (* SDLX_ReactionFn)(SDLX_Collider *, SDLX_Collider *);

enum
{
	SDLX_AWAITANIM = -2,
	SDLX_NONE = -1,
	SDLX_FALSE = 0,
	SDLX_TRUE,
	SDLX_AUTO,
	SDLX_DELAYSWITCH
};

typedef enum SDLX_Keys
{
	SDLX_UP = 1,
	SDLX_DOWN,
	SDLX_LEFT,
	SDLX_RIGHT,
	SDLX_PAUSE
}			SDLX_Keys;

typedef enum SDLX_InputType
{
	SDLX_MOUSE = 0,
	SDLX_KEYBOARD,
	SDLX_CONTROLLER,
	SDLX_AXIS,
	SDLX_GESTURE,
	SDLX_KEYUP,
	SDLX_KEYDOWN,
	SDLX_KEYHELD
}				SDLX_InputType;

typedef struct	SDLX_Input
{
	int input[INPUT_AMOUNT]; // This is just assuming no more than 5 keys will be mapped but that is a terrible asusmption. This should be allocated
	int mouse_click;
	int key_down;

	SDL_Point mouse;
	SDL_Point mouse_delta;
}				SDLX_Input;

typedef struct SDLX_Display
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*background;
}	SDLX_Display;

typedef struct SDLX_Sprite
{
	SDL_Rect			_dst;
	SDL_Rect			_src;
	SDL_Rect			*src;
	SDL_Rect			*dst;

	SDL_RendererFlip	flip;

	SDL_Point			_center;
	SDL_Point			*center;

	SDL_Texture			*sprite_sheet;

	double				angle;
	int					queue;
}	SDLX_Sprite;

typedef struct SDLX_Anim
{
	int			cycle;
	int			start;

	SDL_bool	loop;
	SDL_Rect	*srcs;
	SDL_Texture *sprite_sheet;
}				SDLX_Anim;

typedef struct SDLX_Animator
{
	int			state;
	int			active;
	int			amount;
	int			frameNo;
	int			stateLock;
	int			nextAnim;

	SDLX_Anim	**anims;
	SDLX_Sprite	*sprite;

	void		*meta;
}				SDLX_Animator;

typedef struct SDLX_RenderQueue
{
	size_t		amount;
	size_t		capacity;

	SDLX_Sprite *sprites;
}	SDLX_RenderQueue;

typedef struct SDLX_Circle
{
	double x;
	double y;
	double radius;
}				SDLX_Circle;

typedef struct SDLX_GUIElem
{
	SDLX_Sprite *sprite;

	void *data;

	int cd;
	int active;
	int triggered;
	int autotrigger;
	int selectStatus;

	SDLX_UIFunc		isSelectFn;
	SDLX_UIFunc		UIFuncs[4];
	struct SDLX_GUIElem	*neighbours[4];

	const char *name;
}				SDLX_GUIElem;

typedef struct SDLX_Collider
{

	//POssibly union here to allow for rect & circle collision
	void	 	*collisionBoxPtr;
	SDL_Rect 	collisionBox;

	SDLX_CollisionFn collisionFn;
	SDLX_ReactionFn	 reactionFn;

	int			layerMask;
	int			active;
	void		*data;
}				SDLX_Collider;

typedef struct SDLX_Collision
{
	SDLX_Collider	*collidedWith;
	SDLX_Collider	*self;

}				SDLX_Collision;



typedef void (* SDLX_LevelFunc)(void *);


#endif
