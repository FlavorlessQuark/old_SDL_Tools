#ifndef SDLX_UI_H
# define SDLX_UI_H
# include "SDLX/SDLX_structs.h"


SDLX_GUIElem *SDLX_GUIElem_Create(SDLX_Sprite *sprite, const char *name, SDLX_UIFunc isSelectFn, SDLX_UIFunc OnSelectEnterFn,	SDLX_UIFunc OnSelectExitFn,
							SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickFn);
void	SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive);
void	SDLX_GUIUpdate(void);
void	SDLX_GUI_KeyMap(int up, int down, int left, int right, int select);
void	SDLX_GUIElem_SetKbTarget(int isTarget,SDLX_GUIElem *target, SDLX_GUIElem *up, SDLX_GUIElem *down, SDLX_GUIElem *left, SDLX_GUIElem *right);
void	SDLX_GUIElem_SetDefaultTarget(SDLX_GUIElem *defaultTarget);
int		SDLX_DefaultGUISelect(SDLX_GUIElem *elem);

#endif
