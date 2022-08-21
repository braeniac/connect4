#include "headers/connectfour.h"

ConnectFour::ConnectFour()
{
    PLAYER_1 = 'X';
    PLAYER_2 = 'O';
    DEFAULT_SIZE = 8;
    GAME_OVER = 4;
    player_1_turn = true;
    board = new Board(DEFAULT_SIZE, DEFAULT_SIZE, '-');
    score = new Score(0, 0);
}

ConnectFour::~ConnectFour()
{
    delete board;
    delete score;
}

char ConnectFour::whos_turn()
{
    return (player_1_turn) ? PLAYER_1 : PLAYER_2;
}

bool ConnectFour::can_place_piece_at(int column)
{
    
    if (column < 0 || column >= DEFAULT_SIZE)
    {
        cout << "Invalid Argument Exception: column out of bounds" << endl;
        throw std::exception();
    }
    
    int x = column;
    for (int y = DEFAULT_SIZE - 1; y >= 0; y--)
    {
        char cell = board->get_tile(x, y);
        char empty = board->get_empty();
        
        if (cell == empty)
        {
            return true;
        }
    }
    
    return false;
}

void ConnectFour::place_piece_at(int column)
{
    if (column < 0 || column >= DEFAULT_SIZE)
    {
        cout << "Invalid column selected. Must be between 0 and 7, inclusive." << endl;
        throw std::exception();
    }
    
    int x = column;
    for (int y = DEFAULT_SIZE - 1; y >= 0; y--)
    {
        char cell = board->get_tile(x, y);
        char empty = board->get_empty();
        
        if (cell == empty)
        {
            board->set_tile(x, y, whos_turn());
        
            board->get_tile(0,0);
            Score temp = evaluator::evaluate_board(*board, *score, x, y, PLAYER_1, PLAYER_2);
            score->player_1 = temp.player_1;
            score->player_2 = temp.player_2;
            
            switch_player_turn();
            
            if (is_game_over())
                return;
            
            if (is_bottom_row_full())
                remove_bottom_row();
            
            return;
        }
    }
    
    cout << "Wasn't able to place the piece here. Something went wrong." << endl;
    throw std::exception();
}

int ConnectFour::ai_make_move()
{
    ConnectFour* copy = clone();
    int move = ai::get_best_move(copy);
    delete copy;
    place_piece_at(move);
    return move;
}

void ConnectFour::switch_player_turn()
{
    player_1_turn = !player_1_turn;
}

bool ConnectFour::is_game_over()
{
    return score->player_1 == GAME_OVER || score->player_2 == GAME_OVER;
}

bool ConnectFour::is_someone_winning()
{
    return score->player_1 != score->player_2;
}

char ConnectFour::who_is_winning()
{
    if (!is_someone_winning())
    {
        cout << "Nobody is winning." << endl;
        throw std::exception();
    }
    return (score->player_1 > score->player_2) ? PLAYER_1 : PLAYER_2;
}

int ConnectFour::highest_score()
{
    return (score->player_1 > score->player_2) ? score->player_1 : score->player_2;
}

string ConnectFour::to_string()
{
    return board->get_string();
}

bool ConnectFour::is_bottom_row_full()
{
    for (int x = 0; x < board->get_width(); x++)
    {
        if (board->get_tile(x, board->get_height() - 1) == board->get_empty())
        {
            return false;
        }
    }
    return true;
}

void ConnectFour::remove_bottom_row()
{
    for (int x = 0; x < board->get_width(); x++)
    {
        for (int y = board->get_height() - 1; y >= 0; y--)
        {
            if (y == 0)
            {
                board->set_tile(x, y, board->get_empty());
                break;
            }
            
            board->set_tile(x, y, board->get_tile(x, y - 1));
        }
    }
    
    Score temp = evaluator::evaluate_board(*board, PLAYER_1, PLAYER_2);
    score->player_1 = temp.player_1;
    score->player_2 = temp.player_2;
}

ConnectFour* ConnectFour::clone()
{
    ConnectFour* cf = new ConnectFour;
    delete cf->board;
    delete cf->score;
    cf->board = board->clone();
    cf->score = score->clone();
    cf->player_1_turn = player_1_turn;
    return cf;
}
