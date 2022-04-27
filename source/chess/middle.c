#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "../global.h"
#include "event.h"
#include "chess.h"
#include "dot.h"
#include "core.h"
#include "touch.h"
#include "middle.h"

int MIDDLE_TouchToTile(TOUCH_POS touch_pos) {

    int result = -1;

    for (int n = 0; n < 64; n++) {

        if (touch_pos.x >= glo_chess_core_tile[n].rect.x && touch_pos.x <= (glo_chess_core_tile[n].rect.x + glo_chess_core_tile[n].rect.w)
        && touch_pos.y >= glo_chess_core_tile[n].rect.y && touch_pos.y <= (glo_chess_core_tile[n].rect.y + glo_chess_core_tile[n].rect.h)) {

            printf("MIDDLE_TouchToTile:\n  piece = %p\n  tile[%d] tag[%c%d]", glo_chess_core_tile[n].piece, n, glo_chess_core_tile[n].tag.col, glo_chess_core_tile[n].tag.row);
            if (glo_chess_core_tile[n].piece != NULL)
            {
                printf(" name[%d] player[%d]\n", glo_chess_core_tile[n].piece->enum_piece, glo_chess_core_tile[n].piece->player);

            } else printf("\n");

            result = n; break;
        }

    }

    return (result);
}

int MIDDLE_TagToTile(CHESS_CORE_TILE_TAG tag) {
    int tile = -1;
    for (int n = 0; n < 64; n++) {
        if (tag.col == glo_chess_core_tile[n].tag.col && tag.row == glo_chess_core_tile[n].tag.row) { tile = n; break; }
    }

    return (tile);
}

CHESS_CORE_TILE_TAG MIDDLE_TileToTag(int tile) {
    CHESS_CORE_TILE_TAG tag = glo_chess_core_tile[tile].tag;
    return (tag);
}

int MIDDLE_ReturnRowTile(int tile) {
    int result;
    result = glo_chess_core_tile[tile].tag.row;
    return (result);
}

int MIDDLE_ReturnColTile(int tile) {

    int col_pos = 0;
    char alpha[] = "abcdefgh";

    //result = glo_chess_core_tile[tile].tag.col;

    for (int n = 0; n < 8; n++) {
        if (alpha[n] == glo_chess_core_tile[tile].tag.col) { col_pos = n; break; }
    }

    return (col_pos);
}

void MIDDLE_UpdatePositionPiece(CHESS_CORE_TILE *chess_tile, int old, int new) {

    if (old == new) return;
    if ((old < 0 || old > 63) || (new < 0 || old > 63)) return;
    if (chess_tile[old].piece == NULL) return;

    printf("MIDDLE_UpdatePositionPiece:\n  chess_tile[old] = %p, %c%d\n  chess_tile[new] = %p, %c%d\n", chess_tile[old].piece, chess_tile[old].tag.col, chess_tile[old].tag.row, chess_tile[new].piece, chess_tile[new].tag.col, chess_tile[new].tag.row);

    if (chess_tile[new].piece != NULL) CORE_GlobalDestroyPiece(chess_tile[new].piece);

    chess_tile[new].piece = chess_tile[old].piece;
    chess_tile[new].piece->rect = chess_tile[new].rect;
    chess_tile[old].piece = NULL;

    return;
}

void MIDDLE_UnsafePosition_Copy(CHESS_CORE_TILE *unsafe_tile) {

    memcpy(unsafe_tile, glo_chess_core_tile, sizeof(glo_chess_core_tile));

    return;
}

int MIDDLE_UpdateChangeState(SDL_Event *event, CHESS_CORE_PLAYER player, CHESS_PIECE_ATK check) {

    (void)check;

    int result = -1;
    static int position_old = -1;
    static int position_new = -1;
    TOUCH_POS touch_pos;

    touch_pos = TOUCH_MouseState(event);

    // select choosen piece from mem
    if (touch_pos.iner != -1 && position_old == -1) {
        result = MIDDLE_TouchToTile(touch_pos);
        if (result != -1 && glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[result].piece->player == player) {

            position_old = result;
            //CHESS_RedirectPiecePattern(glo_chess_core_tile, result, player, check);

            CHESS_PiecePattern_RangeAllowed(glo_chess_core_tile, result);
        }
    }

    // deselect choosen piece from mem
    else if (touch_pos.iner != -1 && position_old != -1) {
        result = MIDDLE_TouchToTile(touch_pos);

        if (result != -1) {

            if (glo_chess_dot[result].state == true) {

                // if is a valid move, start changing piece state
                position_new = result;

                MIDDLE_UpdatePositionPiece(glo_chess_core_tile, position_old, position_new);
                DOT_StateGlobalDotReset();
                position_new = -1; position_old = -1; result = -2;


            } else if (glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[position_old].piece->player == glo_chess_core_tile[result].piece->player) {

                DOT_StateGlobalDotReset();
                position_old = result;
                //CHESS_RedirectPiecePattern(glo_chess_core_tile, result, player, check);

                CHESS_PiecePattern_RangeAllowed(glo_chess_core_tile, result);

            } else if ((glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[position_old].piece->player != glo_chess_core_tile[result].piece->player) || glo_chess_core_tile[result].piece == NULL) {

                DOT_StateGlobalDotReset();
                position_old = -1;

            }

        }
    }

    /* old
    if (check == ATTACK || check == CHECK_KING)
    {
        // select choosen piece from mem
        if (touch_pos.iner != -1 && position_old == -1) {
            result = MIDDLE_TouchToTile(touch_pos);
            if (result != -1 && glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[result].piece->player == player) {

                position_old = result;
                CHESS_RedirectPiecePattern(glo_chess_core_tile, result, player, check);

            }
        }

        // deselect choosen piece from mem
        else if (touch_pos.iner != -1 && position_old != -1) {
            result = MIDDLE_TouchToTile(touch_pos);

            if (result != -1) {

                if (glo_chess_dot[result].state == true) {

                    // if is a valid move, start changing piece state
                    position_new = result;

                    MIDDLE_UpdatePositionPiece(glo_chess_core_tile, position_old, position_new);
                    DOT_StateGlobalDotReset();
                    position_new = -1; position_old = -1; result = -2;


                } else if (glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[position_old].piece->player == glo_chess_core_tile[result].piece->player) {

                    // choosing another piece same player
                    DOT_StateGlobalDotReset();
                    position_old = result;
                    CHESS_RedirectPiecePattern(glo_chess_core_tile, result, player, check);

                } else if ((glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[position_old].piece->player != glo_chess_core_tile[result].piece->player) || glo_chess_core_tile[result].piece == NULL) {

                    DOT_StateGlobalDotReset();
                    position_old = -1;

                }
            }
        }
    }
    */

    /* old old
    // select choosen piece from mem
    if (touch_pos.iner != -1 && position_old == -1) {
        result = MIDDLE_TouchToTile(touch_pos);
        if (result != -1 && glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[result].piece->player == player) {

            position_old = result;
            CHESS_RedirectPiecePattern(glo_chess_core_tile, result, player, check);

        }
    }

    // deselect choosen piece from mem
    else if (touch_pos.iner != -1 && position_old != -1) {
        result = MIDDLE_TouchToTile(touch_pos);

        if (result != -1) {

            if (glo_chess_dot[result].state == true) {

                // if is a valid move, start changing piece state
                position_new = result;

                MIDDLE_UpdatePositionPiece(glo_chess_core_tile, position_old, position_new);
                DOT_StateGlobalDotReset();
                position_new = -1; position_old = -1; result = -2;


            } else if (glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[position_old].piece->player == glo_chess_core_tile[result].piece->player) {

                DOT_StateGlobalDotReset();
                position_old = result;
                CHESS_RedirectPiecePattern(glo_chess_core_tile, result, player, check);

            } else if ((glo_chess_core_tile[result].piece != NULL && glo_chess_core_tile[position_old].piece->player != glo_chess_core_tile[result].piece->player) || glo_chess_core_tile[result].piece == NULL) {

                DOT_StateGlobalDotReset();
                position_old = -1;

            }

        }
    }
    */

    //if (check == ATTACK || check == CHECK_KING) result = -1;
    return (result);
}
