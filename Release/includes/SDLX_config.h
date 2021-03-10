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
# define WIN_W (NAN_VAL)
# define WIN_H (NAN_VAL)
# define WIN_X (NAN_VAL)
# define WIN_Y (NAN_VAL)

# define SAVE_FILE_PATH NULL
# define ASSETS_PATH NULL

/* Used in FPSAdjust to controle framerate and deliver consistent FPS */
# define FRAMERATE (60)
# define FRAME_TIME 1000 / FRAMERATE

# define INPUT_AMOUNT 5

# endif
