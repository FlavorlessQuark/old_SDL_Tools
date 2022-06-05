#ifndef SDLX_UI_H
# define SDLX_UI_H
# include "SDLX_structs.h"


void SDLX_GUIElem_Create(SDLX_GUIElem *dest,
			SDLX_Sprite *sprite, const char *name,
			SDLX_UIFunc isSelectFn,
			SDLX_UIFunc OnSelectEnterFn,SDLX_UIFunc OnSelectExitFn,
			SDLX_UIFunc OnSelectStayFn,	SDLX_UIFunc OnClickFn);
void	SDLX_GUIElem_SetActive(SDLX_GUIElem *elem, int isActive);
void	SDLX_GUIUpdate(void);

/**
 * @brief Sets the keybindings for up, down left and right (when selecting buttons)
 * 
 * @param up 
 * @param down 
 * @param left 
 * @param right 
 * @param select 
 */
void	SDLX_GUI_KeyMap(int up, int down, int left, int right, int select);
void	SDLX_GUIElem_SetKbTarget(int isTarget,SDLX_GUIElem *target, SDLX_GUIElem *up, SDLX_GUIElem *down, SDLX_GUIElem *left, SDLX_GUIElem *right);
/**
 * @brief Set the elem that should be focused at first
 * 
 * @param defaultTarget this should be, for example, the top most button
 */
void	SDLX_GUIElem_SetDefaultTarget(SDLX_GUIElem *defaultTarget);
int		SDLX_DefaultGUISelect(SDLX_GUIElem *elem);

#endif
