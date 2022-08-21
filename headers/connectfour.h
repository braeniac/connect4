#include <iostream>
#include <vector>
#include "board.h"
#include "score.h"
#include "evaluator.h"
#include "ai.h"

using namespace std;

#ifndef connectfour_h
#define connectfour_h

class ConnectFour {
public:
    ConnectFour();
    ~ConnectFour();
    char whos_turn();
    bool can_place_piece_at(int column);
    void place_piece_at(int column);
    void switch_player_turn();
    bool is_game_over();
    bool is_someone_winning();
    char who_is_winning();
    int highest_score();
    int ai_make_move();
    string to_string();
    ConnectFour* clone();
    Board* board;
    Score* score;
    char PLAYER_1;
    char PLAYER_2;
    int DEFAULT_SIZE;
    int GAME_OVER;
    bool player_1_turn;
    bool is_bottom_row_full();
    void remove_bottom_row();
};

#endif
