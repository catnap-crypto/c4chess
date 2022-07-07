#ifndef INGAME_H
#define INGAME_H

#include <SDL2/SDL.h>
#include "../pp4m/pp4m.h"
#include "../pp4m/pp4m_input.h"
#include "gui_alias.h"

// init OBJ_BUTTON_LINK_OFF which will contain windowed chat as link
int GUI_Ingame_ChatInit(PP4M_HOOK *hook_list);

// init linked list containing windowed chat
PP4M_HOOK *GUI_Ingame_ChatInit_Window(void);

// by using OBJ_WINDOW, where going to create a chat floating
int GUI_Ingame_Chat_InnerWindow_Init(GUI_TextureAlias *window);

int GUI_Ingame_ChatUpdate(GUI_TextureAlias *inner_window_oob, char *pathname, SDL_Color color, int point, char **buffer);
int GUI_Ingame_ChatUpdate_ListUpdate(GUI_TextureAlias *inner_window);

#endif
