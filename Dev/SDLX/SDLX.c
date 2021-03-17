#include "SDLX/SDLX.h"
# define ANIMS_CT 5
# define QUEUE_CT 3


// This struct to be visible within this file only
// It is necessary to internally keep track of input, animations and render queues in orde rto update them properly
// Any animator or rander queue not created with the functions within this file or not added via one of these functions
// cannot be kept track of and therefore cannot be automagically updated

typedef struct _SDLX_Intern
{
	SDLX_Display		*display;
	SDLX_Animator		*animators;
	SDLX_RenderQueue 	*renderQueues;

	int				animatorCount;
	int				animatorMax;
	int				queuesCount;
	int				queuesMax;
}				_SDLX_Intern;

static _SDLX_Intern _intern;

void SDLX_Init(void)
{
	int i;

	//SDL_Log("New Animator  %p\n", _intern.animators);
	i = 0;
	_intern.animatorCount = 0;
	_intern.animatorMax = ANIMS_CT;

	_intern.queuesCount = QUEUE_CT;
	_intern.queuesMax = QUEUE_CT;
	_intern.display = SDLX_DisplayGet();
	_intern.animators = calloc(ANIMS_CT, sizeof(SDLX_Animator));
	_intern.renderQueues = calloc(QUEUE_CT, sizeof(SDLX_RenderQueue));
	while (i < QUEUE_CT)
	{
		_intern.renderQueues[i].sprites = calloc(5,sizeof(SDLX_Sprite));
		_intern.renderQueues[i].amount = 0;
		_intern.renderQueues[i].capacity = 5;
		i++;
	}
}
void	SDLX_RenderQueueAdd(int queue, SDLX_Sprite sprite)
{
	if (queue < 0 || queue >= _intern.queuesCount)
		return ;
	if (_intern.renderQueues[queue].capacity == _intern.renderQueues[queue].amount)
	{
		_intern.renderQueues[queue].capacity *= 2;
		_intern.renderQueues[queue].sprites = SDL_realloc(_intern.renderQueues[queue].sprites,_intern.renderQueues[queue].capacity * sizeof(SDLX_Sprite));
	}
	_intern.renderQueues[queue].sprites[_intern.renderQueues[queue].amount] = sprite;
	_intern.renderQueues[queue].amount++;
}

// In case user needs a render q to modifiy it
SDLX_RenderQueue **SDLX_RenderQueueFetch(int *amount)
{
	if (amount)
		*amount = _intern.queuesCount;
	return &_intern.renderQueues;
}

// This create an aimator from sratch or as a copy of another.
// Indeed the copying may be useful if (when)  two different entities use the saem set of animatons and therefore
// might be on different frames / state of animation

SDLX_Animator *SDLX_AnimatorInstantiate(SDLX_Animator *copy, SDLX_Anim **anims, int amount, SDL_Rect *dst)
{
	int i;

	i = _intern.animatorCount;
	//SDL_Log("Instantiating animator %d\n", i);
	if (i >= _intern.animatorMax)
	{
		_intern.animatorMax *= 2;
		SDL_realloc(_intern.animators, _intern.animatorMax);
	}
	if (copy)
	{
		_intern.animators[i].amount = copy->amount;
		_intern.animators[i].anims = copy->anims;
		_intern.animators[i].dst = copy->dst;
		_intern.animators[i].dstptr = &_intern.animators[i].dst;
	}
	else
	{
		_intern.animators[i].amount = amount;
		_intern.animators[i].anims = anims;
	}
	if (dst)
	{
		_intern.animators[i].dst = *dst;
		_intern.animators[i].dstptr = &_intern.animators[i].dst;
	}
	else
		_intern.animators[i].dstptr = NULL;
	_intern.animators[i].frameNo = 0;
	_intern.animators[i].state = 0;
	_intern.animatorCount++;
	return &_intern.animators[i];
}


void SDLX_AnimationUpdate(void)
{
	int i;
	int frame;
	int state;
	int queue;
	i = 0;
	while (i < _intern.animatorCount)
	{
		frame = _intern.animators[i].frameNo;
		state = _intern.animators[i].state;
		queue = _intern.animators[i].anims[state]->queue;
		if (_intern.animators[i].anims[state]->loop != SDL_FALSE)
			frame = (frame + 1) % _intern.animators[i].anims[state]->cycle;
		else
			frame += 1 * (frame < _intern.animators[i].anims[state]->cycle - 1);
		if (_intern.animators[i].dstptr)
			_intern.animators[i].anims[state]->sprites[frame].dstptr = _intern.animators[i].dstptr;
		SDLX_RenderQueueAdd(queue, _intern.animators[i].anims[state]->sprites[frame]);
		_intern.animators[i].frameNo = frame;
		i++;
	}
}

void SDLX_FPSAdjust()
{
	static int start;
	int delay;

	// This if statement else first frame is delayed by > 1000 ms
	// Workaround is to pass start time but requires variable from outside func
	// Somehow set start to an appropriate starting value
	// This only slows game if it is rendering too fast - but it also halts loop
	// Need to :  if too fast render extra frames of non animated things
	// Render less if too slow
	if (start != 0)
	{
		delay = start - SDL_GetTicks();
		delay = MAX(FRAME_TIME - delay , 0);
		SDL_Delay(delay);
	}
	start = SDL_GetTicks();
}
