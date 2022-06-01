#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core.h"
#include "chess.h"
#include "archive.h"

char *glo_chess_archive_flow = NULL;
char *glo_chess_archive_flow_mark = "kpbnrq";

void ARCHIVE_Notation_EnrollMove(CHESS_CORE_TILE *chess_tile, int slot_old, int slot_new) {

    if (!glo_chess_archive_flow)
        glo_chess_archive_flow = malloc(sizeof(char*));

    ARCHIVE_NOTATION_PIECE piece_ntt;
    piece_ntt = ARCHIVE_Redirect_StateMove(chess_tile, slot_old);

    char buffer[3] = ""; int ind = 0;

    if (piece_ntt != NONE_A && piece_ntt != PAWN_A)
        buffer[ind++] = glo_chess_archive_flow_mark[piece_ntt];
    else if (piece_ntt == PAWN_A && chess_tile[slot_new].piece != NULL) {
        buffer[ind++] = chess_tile[slot_old].tag.col;
        buffer[ind++] = 'x';
    } else if (chess_tile[slot_new].piece != NULL)
        buffer[ind] = 'x';

    CHESS_CORE_TILE_TAG tag = chess_tile[slot_new].tag;

    char notation[16];
    sprintf(notation, "%s%c%d", buffer, tag.col, tag.row);

    printf("buffer [%s]\n", notation);

    return;
}


ARCHIVE_NOTATION_PIECE ARCHIVE_Redirect_StateMove(CHESS_CORE_TILE *chess_tile, int slot) {

    if (CHESS_Redirect_EnumKing(chess_tile, slot) == 0) return KING_A;
    else if (CHESS_Redirect_EnumPawn(chess_tile, slot) == 0) return PAWN_A;
    else if (CHESS_Redirect_EnumBishop(chess_tile, slot) == 0) return BISHOP_A;
    else if (CHESS_Redirect_EnumKnight(chess_tile, slot) == 0) return KNIGHT_A;
    else if (CHESS_Redirect_EnumRook(chess_tile, slot) == 0) return ROOK_A;
    else if (CHESS_Redirect_EnumQueen(chess_tile, slot) == 0) return QUEEN_A;
    else return NONE_A;
}
