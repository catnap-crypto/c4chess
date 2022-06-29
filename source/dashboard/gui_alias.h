#ifndef GUI_ALIAS_H
#define GUI_ALIAS_H

#include <SDL2/SDL.h>
#include "../pp4m/pp4m_input.h"

/* structures & variables */

typedef enum {
    OBJ_NONE,                   // ignore object
    OBJ_NULL,                   // drop itineration

    OBJ_BUTTON_TXTBOX,          // object to toggle OBJ_TEXTBOX_INPUT usage

    OBJ_BUTTON_LINK_OFF,        // indicates *link as linked list toggled off
    OBJ_BUTTON_LINK_ON,         // indicates *link as linked list toggled on

    OBJ_BUTTON_RETURN,          // go back
    OBJ_BUTTON_EXIT,            // terminate any loop

    OBJ_SCROLL_VERTICAL,        // with input, scroll up and down
    OBJ_SCROLL_HORIZONTAL,      // with input, scroll left or right

    OBJ_TEXTBOX_LINK,           // texture behind OBJ_TEXTBOX_INPUT + *link as linked list
    OBJ_TEXTBOX_ALIAS,          // texture behind OBJ_TEXTBOX_INPUT + *link as GUI_TextureAlias

    OBJ_TEXTBOX_INPUT_OFF,      // init, reset, update and modify texture's input
    OBJ_TEXTBOX_INPUT_ON,

    OBJ_LINK_PTR                // treat object as linked list

} GUI_ALIAS_OBJ;

typedef struct {
    GUI_ALIAS_OBJ obj;
    void *link;
    SDL_Rect rect;
    SDL_Texture *texture;
} GUI_TextureAlias;

/* prototypes */
int GUI_Alias_InputOnObj(PP4M_INPUT_POS input, SDL_Rect rect);

int GUI_Alias_IsColor(SDL_Color *color);
int GUI_Alias_ResetColor(SDL_Color *color);

SDL_Texture *GUI_Alias_CreateSnapshot(SDL_Renderer *renderer, int width, int height);

int GUI_Alias_Textbox_Empty(GUI_TextureAlias *alias_ttr, char *pathname, SDL_Color color, int point, char *buffer);
int GUI_Alias_Textbox_UpdateTexture(GUI_TextureAlias *alias_ttr, char *pathname, SDL_Color color, int point);
int GUI_Alias_Textbox_UpdateRect(GUI_TextureAlias *alias_ttr, SDL_Rect *rect);

int GUI_Alias_Textbox_Backspace(char *buf);

int GUI_Alias_Textbox_InitAlias(GUI_TextureAlias *alias_ttr, char *pathname, SDL_Color color, int point, char *buffer);
char *GUI_Alias_Textbox_UpdateAlias(GUI_TextureAlias *alias_ttr, char *pathname, SDL_Color color, int point, int key);
int GUI_Alias_Textbox_DestrAlias(GUI_TextureAlias *alias_ptr);

#endif
