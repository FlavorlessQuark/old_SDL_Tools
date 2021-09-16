#ifndef SDLX_ANIM_H
# define SDLX_ANIM_H


#include "SDLX/SDLX_structs.h"

void			SDLX_AnimationUpdate(void);
void			SDLX_Animator_StateSet(SDLX_Animator *anim,int newState, int awaitCurrent);

/**
 * @brief Creates an animtor from scratch or as a copy of another
 * @param copy animator to copy. NULL if creating a new animator
 * @param anims the set of animtions to add to the animator
 * @param amount the number of animation to add.  This shiuld be the length of anims
 * @param dst	the destination rectangle to render the anim
 */
void SDLX_AnimatorCreate(SDLX_Animator *dest, SDLX_Anim **anims, int amount, SDLX_Sprite *sprite);

/**
 * @brief Loads an animation from a sprite_sheet.
 * User should make their own function as this assues all frames of an animation are within the same row
 * @param cycle the number of frames in the animation
 * @param cell_w the width in pixels of a single frame
 * @param ceell_h the height in pixels of a single frame
 * @param loop whether to make this  animation repeat or not
 * @param x_off offset in pixel of the leftmost frame from the border of te image
 * @param y_off offset in pixel of the topmost frame from the border of te image
 */
SDLX_Anim		*SDLX_AnimLoadHorizontal(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off);
SDLX_Anim		*SDLX_AnimLoadVertical(SDL_Texture *tex, int cycle, int cell_w, int cell_h, SDL_bool loop, int x_off, int y_off);
void SDLX_AnimatorCopy(SDLX_Animator *dst, SDLX_Animator *src);

#endif
