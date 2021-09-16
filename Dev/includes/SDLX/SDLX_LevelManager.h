#ifndef SDLX_LEVELMANAGER_H
# define SDLX_LEVELMANAGER_H

# include "SDLX_structs.h"
# include "SDLX_config.h"

void SDLX_LevelManagerAdd(int level, SDLX_LevelFunc lvlInit, SDLX_LevelFunc lvlLoop, SDLX_LevelFunc lvlCleanUp);
void SDLX_LevelManagerSwitch(int level, void *args);
void SDLX_LevelManagerStart(int level, void *args);
void SDLX_LevelRun(void);

#endif
