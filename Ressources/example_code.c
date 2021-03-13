#include "SDLX/SDLX.h"

int main()
{
	SDLX_Anim	*anim;
	SDLX_Display *display;
	SDLX_Animator *animator;

	SDL_Rect 	dst;
	SDL_Texture *tex;

// This also initializes SDL and creates a display of the size defined in SDLX.h
	SDLX_Start();

// Input mapping
	SDLX_InputMap(SDL_SCANCODE_RIGHT, 			  SDLX_KEYBOARD,	SDLX_RIGHT, -1);
	SDLX_InputMap(SDL_SCANCODE_D, 				  SDLX_KEYBOARD,	SDLX_RIGHT, -1);
	SDLX_InputMap(SDL_GAMECONTROLLER_BUTTON_RIGHT,SDLX_CONTROLLER,	SDLX_RIGHT, 0);

	SDLX_InputMap(SDL_SCANCODE_LEFT, 			  SDLX_KEYBOARD,	SDLX_LEFT, -1);
	SDLX_InputMap(SDL_SCANCODE_A, 				  SDLX_KEYBOARD,	SDLX_LEFT, -1);
	SDLX_InputMap(SDL_GAMECONTROLLER_BUTTON_LEFT, SDLX_CONTROLLER,	SDLX_LEFT, 0);

//Creating the animation from a sprite sheet
	dst.h = 32;
	dst.w = 32;
	dst.x = 100;
	dst.y = 100;
	tex = SDL_CreateTextureFromSurface(display->renderer, IMG_Load("SpriteSheet.png"));
	anim = SDLX_AnimLoad(tex, 8, 32, 32, SDL_TRUE, 0, 0);
// Animator takes care of the animation looping
	anmator = SDLX_AnimatorInstantiate(NULL, &anim, 1, &dst);
	animator.state = 0; // Renders the first animation


// Get the display fron anywhere within the program with DisplayGet()
	display = SDLX_DisplayGet();
	SDLX_BackgroundSet(IMG_Load("BackGround.png"));

	while(42)
	{
		SDLX_ResetWindow();
		SDLX_InputLoop();
		SDLX_InputUpdate();
		SDLX_AnimationUpdate();

		{
			SDLX_Input	input;

			input = SDLX_InputGet();
			*anim.dstptr.x += input.input[SDLX_RIGHT]
			*anim.dstptr.x -= input.input[SDLX_LEFT]
		}

		SDLX_RenderQueueDisplay(SDLX_RenderQueueFetch(NULL)[0], display);
		SDL_RenderPresent(display->renderer);
		//ConsistentFramerate
		SDLX_FPAdjust();
	}
}


