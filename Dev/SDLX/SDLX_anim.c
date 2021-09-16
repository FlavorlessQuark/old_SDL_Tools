#include "SDLX/SDLX.h"
#include "SDL2/SDL_image.h"

# define ANIMS_CT 5

typedef struct SDLX_AnimatorMeta
{
	int			stateLock;
	int			nextAnim;
}				SDLX_AnimatorMeta;

typedef struct SDLX_AnimatorInfo
{
	SDLX_Animator		*elem;
	SDLX_AnimatorMeta 	meta;
}				SDLX_AnimatorInfo;

typedef struct Anim_intern
{
	SDLX_AnimatorInfo *anims;

	size_t animatorCount;
	size_t animatorCap;
}			Anim_intern;

static Anim_intern _intern;
/// !!!!!!!!!!!!!IMPORTANT !!!!!!!!!!!!
// Now that this is an array, the ptr to meta will be invalid after realloc
// Either find a way to store it sneakily or get rid of it
// Meta controls animations and how to go from one to the next
// i.e when switching anims, whether to wait for curent to finish or override


void SDLX_AnimInit(void)
{
	_intern.animatorCount = 0;
	_intern.animatorCap = 0;
	_intern.anims = calloc(sizeof(SDLX_Animator *), ANIMS_CT);
}

void SDLX_AnimatorCreate(SDLX_Animator *dest, SDLX_Anim **anims, int amount, SDLX_Sprite *sprite)
{
	SDLX_AnimatorInfo *info;

	info = &_intern.anims[_intern.animatorCount];

	if (_intern.animatorCount >= _intern.animatorCap)
	{
		_intern.animatorCap *= 2;
		_intern.anims = realloc(_intern.anims, _intern.animatorCount);
	}

	info->elem = dest;
	if (!dest)
		return ;
	info->elem->anims = anims;
	info->elem->amount = amount;

	if (sprite)
	{
		info->elem->sprite = sprite;
		info->elem->sprite->dstptr = &(info->elem->sprite->dst);
	}

	// else

	info->elem->frameNo = 0;
	info->elem->state = 0;

	info->meta.stateLock = -1;
	info->meta.nextAnim = -1;
	info->elem->metadata = &info->meta;

	info->elem->active = SDLX_TRUE;

}

SDLX_Anim	*SDLX_AnimLoadVertical(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off)
{
	SDLX_Anim	*anim;
	SDLX_Display *display;
	int i;
	int x;
	int y;

	display = SDLX_DisplayGet();
	anim = calloc(1, sizeof(*anim));
	anim->cycle = cycle;
	anim->start = 0;
	anim->loop = loop;
	anim->srcs = calloc(cycle, sizeof(SDL_Rect));

	i = 0;
	x = x_off;
	y = y_off;
	anim->sprite_sheet = tex;
	while (i < cycle)
	{
		anim->srcs[i].x = x;
		anim->srcs[i].y = y;
		anim->srcs[i].h = cell_h;
		anim->srcs[i].w = cell_w;

		y += cell_h;
		i++;
	}
	return anim;
}

//potentially pass destination ptr instead of returning alloc

SDLX_Anim	*SDLX_AnimLoadHorizontal(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off)
{
	SDLX_Anim	*anim;
	SDLX_Display *display;
	int i;
	int x;
	int y;

	anim = calloc(1, sizeof(*anim));
	anim->cycle = cycle;
	anim->start = 0;
	anim->loop = loop;
	anim->srcs = calloc(cycle, sizeof(SDL_Rect));

	i = 0;
	x = x_off;
	y = y_off;
	anim->sprite_sheet = tex;
	while (i < cycle)
	{
		anim->srcs[i].x = x;
		anim->srcs[i].y = y;
		anim->srcs[i].h = cell_h;
		anim->srcs[i].w = cell_w;

		x += cell_w;
		i++;
	}
	return anim;
}

void SDLX_AnimationUpdate(void)
{
	int i;
	int frame;
	int state;
	int queue;

	SDLX_Animator	*animator;
	SDLX_AnimatorMeta *meta;

	i = 0;
	while (i < _intern.animatorCount)
	{
		if (_intern.anims[i].elem->active == SDLX_TRUE && _intern.anims[i].elem->anims)
		{
			animator = _intern.anims[i].elem;
			state = animator->state;
			frame = animator->frameNo;
			meta = &_intern.anims[i].meta;
			queue = animator->sprite->queue;

			if (animator->anims[state]->loop != SDL_FALSE)
				animator->frameNo = (frame + 1) % animator->anims[state]->cycle;
			else
				animator->frameNo += 1 * (frame < animator->anims[state]->cycle - 1);

			animator->sprite->srcptr = &animator->anims[state]->srcs[frame];
			animator->sprite->sprite_sheet = animator->anims[state]->sprite_sheet;

			SDLX_RenderQueueAdd(queue, *animator->sprite);
			if (meta->stateLock == frame)
			{
				meta->stateLock = -1;
				animator->state = meta->nextAnim;
				animator->frameNo = 0;
			}
		}
		i++;
	}
}

//refactor this
void SDLX_Animator_StateSet(SDLX_Animator *anim, int newState, int awaitCurrent)
{
	SDLX_AnimatorMeta *meta;

	meta = anim->metadata;
	if (newState > anim->amount)
		return ;
	if (awaitCurrent == SDLX_AWAITANIM || awaitCurrent >= anim->anims[anim->state]->cycle)
	{
		meta->stateLock = anim->anims[anim->state]->cycle - 1;
		meta->nextAnim = newState;
	}
	else if (awaitCurrent > 0)
	{
		meta->stateLock = awaitCurrent;
		meta->nextAnim = newState;
	}
	else
	{
		meta->stateLock = -1;
		anim->frameNo = 0;
		anim->state = newState;
	}
}

void SDLX_AnimatorCopy(SDLX_Animator *dst, SDLX_Animator *src)
{
	dst->state = src->state;
	dst->active = src->active;
	dst->amount = src->amount;
	dst->frameNo = src->frameNo;

	dst->anims = src->anims;
	dst->amount = src->amount;
	dst->state = src->state;
}
