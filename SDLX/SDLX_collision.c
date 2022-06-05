# include "SDLX/SDLX_collisions.h"

static SDLX_Collision *_collisions;
static SDLX_Collider  **_colliders;
static int colliderCap;
static int collisionCap;
static int colliderSize;
static int collisionSize;

# define NCOLL 10

void SDLX_CollisionsInit(void)
{
	_colliders = calloc( NCOLL, sizeof(*_colliders));
	_collisions = calloc( NCOLL, sizeof(*_collisions));

	colliderCap = NCOLL;
	collisionCap = NCOLL;
	colliderSize  = 0;
	collisionSize  = 0;
}

void _AddCollision(SDLX_Collider *self, SDLX_Collider *other)
{
	if (collisionSize >= collisionCap)
	{
		collisionCap *= 2;
		_collisions = realloc(_collisions, collisionCap * sizeof(*_collisions));
	}
	_collisions[collisionSize].collidedWith = other;
	_collisions[collisionSize].self = self;
	collisionSize++;
}

SDLX_Display *SDLX_DisplayGet();

void SDLX_PollCollisions(void)
{
	int i;
	int n;
	int coll;

	i = 0;
	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 255, 0, 0, 255);
	while (i < colliderSize)
	{
		n = 0;
		if (_colliders[i]->active)
		{
			SDL_RenderDrawRect(SDLX_DisplayGet()->renderer, _colliders[i]->collisionBoxPtr);
			while (n < colliderSize)
			{
				if ( i != n && _colliders[i] && _colliders[n]->active && _colliders[i]->collisionFn
					&& (_colliders[i]->layerMask & _colliders[n]->layerMask)
					&& _colliders[i]->collisionFn(_colliders[i], _colliders[n]))
						_AddCollision(_colliders[i], _colliders[n]);
				n++;
			}
		}
		i++;
	}
	SDL_SetRenderDrawColor(SDLX_DisplayGet()->renderer, 0, 0, 0, 255);
}

void SDLX_ResolveCollisions(void)
{
	int i;

	i = 0;
	while (i < collisionSize)
	{
		if (_collisions[i].self->reactionFn)
			_collisions[i].self->reactionFn(_collisions[i].self, _collisions[i].collidedWith);
		i++;
	}
	collisionSize = 0;
}

void	SDLX_ColliderCreate(int layerMask, int type, void *collisionBox, SDLX_Collider *dst,
	SDLX_CollisionFn collisionFn, SDLX_ReactionFn reactionFn, void *data)
{
	if (colliderSize >= colliderCap)
	{
		colliderCap *= 2;
		_colliders = realloc(_colliders, colliderCap * sizeof(*_colliders));
	}
	_colliders[colliderSize] = dst;
	dst->layerMask = layerMask;
	dst->collisionBoxPtr = collisionBox;
	dst->collisionFn = collisionFn;
	dst->reactionFn = reactionFn;
	dst->data = data;
	colliderSize++;
}


