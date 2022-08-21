#include <iostream>
#include "score.h"
class ConnectFour;

using namespace std;

#ifndef ai_h
#define ai_h

namespace ai {
    int get_best_move(ConnectFour* cf);
    int does_player_have_winning_move(ConnectFour* cf);
    int does_opponent_have_winning_move(ConnectFour* cf);
    int random_move(ConnectFour* cf);
};

#endif
