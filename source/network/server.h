#ifndef SERVER_H
#define SERVER_H

#include "client.h"
#include "net_utils.h"

// server command codes which will be sent to the client/lobby
typedef enum {
    SV_STATE_START = 100,               // STATE START
        SV_STATE_IDLE,                  // post idle ...................................... || "1xx", code
        SV_STATE_CONFIRM,               // post confirm ................................... || "1xx", code
        SV_STATE_DENY,                  // post deny ...................................... || "1xx", code
    SV_STATE_END,                       // STATE END

    SV_REQ_START = 200,                 // REQ START
        SV_REQ_NICKNAME,                // server asking for nickname of client ........... || "2xx", code
    SV_REQ_END,                         // REQ END

    SV_REQ_LOBBY_START,                 // REQ LOBBY_START
        SV_REQ_LOBBY_SYNC,              // server asking confirmation on sync ............. || "2xx", code
    SV_REQ_LOBBY_END,                   // REQ LOBBY_END

    SV_POST_START = 300,                // POST START
    SV_POST_END,                        // POST END

    SV_POST_LOBBY_START,                // POST LOBBY_START
        SV_POST_LOBBY_INIT,             // lobby initialized and ready .................... || "3xx w 8/8/3k4/8/8/3K4/8/8 - - 0 0", code, player_view, fen_board, fen_castle, fen_passant, fen_halfm, fen_fullm
        SV_POST_LOBBY_PARTNER_LEFT,     // the partner left the game ...................... || "3xx", code
        SV_POST_LOBBY_TIME,             // prompting new time for timers to sync .......... || "3xx 2189432", code, time_in_clock
    SV_POST_LOBBY_END                   // POST LOBBY_END

} SERVER_CMD;

int svcode_status_STATE(int code);
int svcode_status_REQ(int code);
int svcode_status_LOBBY_REQ(int code);
int svcode_status_POST(int code);
int svcode_status_LOBBY_POST(int code);

int svcode_REQ_redirect(int code, cli_t *client, int room, char *buffer);
int svcode_POST_redirect(int code, cli_t *client, int room, char *buffer);

int svcode_redirect(int code, cli_t *client, int room, char *buffer);
int SV_HandleCli_Packet(cli_t *client, char *buffer);

#endif
