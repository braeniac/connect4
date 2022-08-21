#include "headers/ai.h"
#include "headers/connectfour.h"
#include <math.h>
#include <cstdlib>

namespace ai
{

    int get_best_move(ConnectFour* cf)
    {
        int win = does_player_have_winning_move(cf);
        int prevent_loss = does_opponent_have_winning_move(cf);
        int rand = random_move(cf);
        
        if (win != -1)
            return win;
        if (prevent_loss != -1)
            return prevent_loss;
        return rand;
    }
    
    // Return -1 if no winning move.
    int does_player_have_winning_move(ConnectFour* cf)
    {
        for (int i = 0; i < 8; i++)
        {
            //clone
            ConnectFour* clone = cf->clone();
            
            //do work
            if (clone->can_place_piece_at(i))
            {
                clone->place_piece_at(i);
                
                if (clone->is_game_over())
                {
                    delete clone;
                    return i;
                }
            }
            
            //delete
            delete clone;
        }
        
        return -1;
    }
    
    // Return -1 if no winning move.
    int does_opponent_have_winning_move(ConnectFour* cf)
    {
        cf->switch_player_turn();
        return does_player_have_winning_move(cf);
    }

    int random_move(ConnectFour* cf)
    {
        srand(time(0));
	int v1 = rand() % 8;

        return v1;
    }
    
}
