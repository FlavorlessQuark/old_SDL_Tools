#ifndef SDLX_COLLISIONS_H
# define SDLX_COLLISIONS_H

# include "SDLX_structs.h"

void 	SDLX_CollisionsInit(void);
void	SDLX_PollCollisions(void);
void	SDLX_ResolveCollisions(void);
void	SDLX_ColliderCreate(int layerMask, int type, void *collisionBox, SDLX_Collider *dst,
							SDLX_CollisionFn collisionFn, SDLX_ReactionFn reactionFn, void *data);


#endif
