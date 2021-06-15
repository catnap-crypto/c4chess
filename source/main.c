#include <stdio.h>
#include <stdlib.h>

#include "pp4m/pp4m.h"
#include "pp4m/pp4m_image.h"
#include "pp4m/pp4m_draw.h"

#include "main.h"
#include "game.h"

SDL_Window *global_window;
SDL_Renderer *global_renderer;

int main (void) {

    global_renderer = pp4m_Init(global_window, "scacchi", SCREEN_WIDTH, SCREEN_HEIGHT);

    GAME_InitializeChessboard();

    SDL_DestroyRenderer(global_renderer);
    SDL_DestroyWindow(global_window);
    pp4m_Quit();

    return 0;
}
