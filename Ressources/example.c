#include "SDLX/SDLX.h"
#include "SDL2/SDL_image.h"

typedef struct t_example
{
	SDLX_Sprite  dragon;
	SDLX_Sprite  buttonSprite;

	SDLX_GUIElem button;

	SDLX_Animator dragonAnimator;
	SDLX_Animator buttonAnimator;
}				t_example;

t_example example;

int buttonHover(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(&example.buttonAnimator, 1, SDLX_NONE);
}

int buttonClick(SDLX_GUIElem *elem)
{
	SDLX_Animator_StateSet(&example.buttonAnimator, 2, SDLX_NONE);
	SDL_Log("CLICK %s\n", elem->name);
}

void init()
{
	SDLX_Display *display;
	SDLX_Input 	input;
	SDLX_Anim	**dragonanim;
	SDLX_Anim	**buttonanim;
	SDL_Texture *dragontex;
	SDL_Texture *buttontex;
	
	SDLX_Start("DEFAULT", WIN_X, WIN_Y, WIN_H, WIN_W, SDL_WINDOW_SHOWN);
	
	dragonanim = calloc(1, sizeof(SDLX_Anim *));
	buttonanim = calloc(2, sizeof(SDLX_Anim *));
	display = SDLX_DisplayGet();

	SDLX_InputMap(SDL_SCANCODE_W, 1, SDLX_UP, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_A, 1, SDLX_LEFT, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_S, 1, SDLX_DOWN, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_D, 1, SDLX_RIGHT,1, -1);

	SDLX_InputMap(SDL_SCANCODE_UP, 1, SDLX_UP, 	1, -1);
	SDLX_InputMap(SDL_SCANCODE_LEFT, 1, SDLX_LEFT, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_DOWN, 1, SDLX_DOWN, 1, -1);
	SDLX_InputMap(SDL_SCANCODE_RIGHT, 1, SDLX_RIGHT,1, -1);

	dragontex = SDL_CreateTextureFromSurface(display->renderer, IMG_Load("Assets/test.png"));
	buttontex = SDL_CreateTextureFromSurface(display->renderer, IMG_Load("Assets/button.png"));
	
	dragonanim[0] = SDLX_AnimLoadHorizontal(dragontex, 8, 32, 32, SDLX_TRUE, 0, 0);

	buttonanim[0] = SDLX_AnimLoadHorizontal(buttontex, 1, 64, 64, SDLX_FALSE, 0, 0);
	buttonanim[1] = SDLX_AnimLoadHorizontal(buttontex, 9, 64, 64, SDLX_FALSE, 0, 0);
	buttonanim[2] = SDLX_AnimLoadHorizontal(buttontex, 2, 64, 64, SDLX_FALSE, 64 * 8, 0);

	SDLX_SpriteCreate(&example.dragon, dragontex, NULL, &(SDL_Rect){(WIN_W / 2) - 128, (WIN_H / 2) - 256, 256, 256});
	SDLX_SpriteCreate(&example.buttonSprite, buttontex, NULL, &(SDL_Rect){(WIN_W / 2) - 128, (WIN_H / 2), 256, 256});
	
	SDLX_GUIElem_Create(&example.button, &example.buttonSprite, "button", SDLX_DefaultGUISelect, buttonHover, SDLX_NullGUIFunc, SDLX_NullGUIFunc, buttonClick);

	SDLX_AnimatorCreate(&example.dragonAnimator, dragonanim, 1, &example.dragon);
	SDLX_AnimatorCreate(&example.buttonAnimator, buttonanim, 3, &example.buttonSprite);

	SDLX_GUIElem_SetDefaultTarget(&example.button);

	example.button.active = SDLX_TRUE;
}

int main()
{
	SDLX_Display *display;
	SDLX_Input input;

	init();
	display = SDLX_DisplayGet();
	while (1)
	{
		SDLX_ResetWindow(display);
		SDLX_InputLoop();
		SDLX_InputUpdate();
		{
			input = SDLX_InputGet();
			example.dragon.dst->y += (input.input[SDLX_UP] * -5) + (input.input[SDLX_DOWN] * 5); 
			example.dragon.dst->x += (input.input[SDLX_RIGHT] * 5) + (input.input[SDLX_LEFT] * -5); 
		}
		SDLX_GUIUpdate();
		SDLX_AnimationUpdate();
		SDLX_RenderQueueAdd(0, example.dragon);
		SDLX_Render_DisplayAll(display);
		SDL_RenderPresent(display->renderer); 
		SDLX_FPSAdjust();
	}
}