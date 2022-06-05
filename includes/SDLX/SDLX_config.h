/**
 *	@file	SDLX_config.h
 *
 *	@author: FlavorlessQuark
 *
 *	Last Modified: 2021-03-09 21:42:10
 *
 *	@brief: Defines used to setup SDLX
 */

#ifndef SDLX_CONFIG_H
# define SDLX_CONFIG_H

# define NAN_VAL 0

/* Window settings */
# define WIN_TITLE "DEFAULT"
# define H_SCALE (1.75)
# define W_SCALE (1.25)
# define WIN_W (500 * W_SCALE)
# define WIN_H (500 * H_SCALE)
# define WIN_X (SDL_WINDOWPOS_CENTERED)
# define WIN_Y (SDL_WINDOWPOS_CENTERED)

# define SAVE_FILE_PATH NULL
# define ASSETS_PATH "Assets/"

/* Used in FPSAdjust to controle framerate and deliver consistent FPS */
# define FRAMERATE (30)
# define FRAME_TIME 1000 / FRAMERATE

# define INPUT_AMOUNT 10

# define MAX_LEVELS 10

# endif
