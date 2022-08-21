#include <iostream>
#include <vector>
#include "board.h"
#include "score.h"

using namespace std;

#ifndef evaluator_h
#define evaluator_h

namespace evaluator {
    Score evaluate_board(Board b, char player_1, char player_2);
    Score evaluate_board(Board b, Score score, int x, int y, char player_1, char player_2);
    void test_evaluator();
    struct Position;
    int get_longest_sequence(int x, int y, Board b);
    int check_horizontal(Position p, Board b);
    int check_vertical(Position p, Board b);
    int check_diagonal_from_west(Position p, Board b);
    int check_diagonal_from_east(Position p, Board b);
    int wrap_x(int x, Board b);
    bool empty_cell(Position p, Board b);
    Position north_west(Position p);
    Position north(Position p);
    Position north_east(Position p);
    Position west(Position p);
    Position east(Position p);
    Position south_west(Position p);
    Position south(Position p);
    Position south_east(Position p);
    void print_position(string msg, Position p);
};

#endif
