#include "headers/evaluator.h"

namespace evaluator
{
    
    struct Position {
        int x;
        int y;
        
        Position(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        
        Position clone()
        {
            Position p(x, y);
            return p;
        }
        
    };

    // Evaluate the entire grid.
    Score evaluate_board(Board b, char player_1, char player_2)
    {
        Score score(0, 0);
        
        for (int y = 0; y < b.get_height(); y++)
        {
            for (int x = 0; x < b.get_width(); x++)
            {
                int sequence = get_longest_sequence(x, y, b);
                
                if (b.get_tile(x, y) == player_1 && score.player_1 < sequence)
                    score.player_1 = sequence;
                else if (b.get_tile(x,y) == player_2 && score.player_2 < sequence)
                    score.player_2 = sequence;
            }
        }
        
        return score;
    }
    
    // Evaluate only one cell in the grid.
    Score evaluate_board(Board b, Score score, int x, int y, char player_1, char player_2)
    {
        int sequence = get_longest_sequence(x, y, b);
        
        if (b.get_tile(x, y) == player_1 && score.player_1 < sequence)
            score.player_1 = sequence;
        else if (b.get_tile(x,y) == player_2 && score.player_2 < sequence)
            score.player_2 = sequence;
        
        return score;
    }
    
    int get_longest_sequence(int x, int y, Board b)
    {
        Position p(x, y);
        int horizontal = check_horizontal(p, b);
        int vertical = check_vertical(p, b);
        int diagonal1 = check_diagonal_from_east(p, b);
        int diagonal2 = check_diagonal_from_west(p, b);
        
        int sequence = horizontal;
        if (sequence < vertical)
        {
            sequence = vertical;
            //cout << "Vertical" << endl;
        }
        if (sequence < diagonal1)
        {
            sequence = diagonal1;
            //cout << "Diagonal1" << endl;
        }
        if (sequence < diagonal2)
        {
            sequence = diagonal2;
            //cout << "Diagonal2" << endl;
        }
        
        return sequence;
    }
    
    int check_horizontal(Position p, Board b)
    {
        int sequence = 0;
        
        if (empty_cell(p, b))
        {
            return sequence;
        }
        
        char player = b.get_tile(p.x, p.y);
        
        sequence++;
        
        Position ptr_west = p.clone();
        Position ptr_east = p.clone();
        
        // Check to the west of the position.
        for (int i = 0; i < b.get_width() - 1; i++)
        {
            ptr_west = west(ptr_west);
            ptr_west.x = wrap_x(ptr_west.x, b);
            
            if (b.get_tile(ptr_west.x, ptr_west.y) != player)
            {
                break;
            }
            
            sequence++;
        }
        
        // Check to the east of the position.
        for (int i = 0; i < b.get_width() - 1; i++)
        {
            ptr_east = east(ptr_east);
            ptr_east.x = wrap_x(ptr_east.x, b);
            
            if (ptr_east.x == ptr_west.x || b.get_tile(ptr_east.x, ptr_east.y) != player)
            {
                break;
            }
            
            sequence++;
        }
        
        return sequence;
    }
    
    int check_vertical(Position p, Board b)
    {
        int sequence = 0;
        
        if (empty_cell(p, b))
        {
            return sequence;
        }
        
        char player = b.get_tile(p.x, p.y);
        
        sequence++;
        
        Position ptr_north = p.clone();
        Position ptr_south = p.clone();
        
        // Check to the north of the position.
        for (int i = 0; i < b.get_height() - 1; i++)
        {
            ptr_north = north(ptr_north);
            if (ptr_north.y < 0 || b.get_tile(ptr_north.x, ptr_north.y) != player)
            {
                break;
            }
            sequence++;
        }
        
        // Check to the south of the position.
        for (int i = 0; i < b.get_height() - 1; i++)
        {
            ptr_south = south(ptr_south);
            if (ptr_south.y == ptr_north.y || ptr_south.y >= b.get_height() || b.get_tile(ptr_south.x, ptr_south.y) != player)
            {
                break;
            }
            sequence++;
        }
        
        return sequence;
    }
    
    int check_diagonal_from_west(Position p, Board b)
    {
        int sequence = 0;
        
        if (empty_cell(p, b))
        {
            return sequence;
        }
        
        char player = b.get_tile(p.x, p.y);
        
        sequence++;
        
        Position ptr_nw = p.clone();
        Position ptr_se = p.clone();
        
        // Check to the north west.
        for (int i = 0; i < b.get_width() - 1; i++)
        {
            ptr_nw = north_west(ptr_nw);
            ptr_nw.x = wrap_x(ptr_nw.x, b);
            if (ptr_nw.y < 0 || b.get_tile(ptr_nw.x, ptr_nw.y) != player)
            {
                break;
            }
            sequence++;
        }
        
        // Check to the south east.
        for (int i = 0; i < b.get_width() - 1; i++)
        {
            ptr_se = south_east(ptr_se);
            ptr_se.x = wrap_x(ptr_se.x, b);
            if (ptr_se.x == ptr_nw.x || ptr_se.y >= b.get_height() || b.get_tile(ptr_se.x, ptr_se.y) != player)
            {
                break;
            }
            sequence++;
        }
        
        return sequence;
    }
    
    int check_diagonal_from_east(Position p, Board b)
    {
        int sequence = 0;
        
        if (empty_cell(p, b))
        {
            return sequence;
        }
        
        char player = b.get_tile(p.x, p.y);
        
        sequence++;
        
        Position ptr_ne = p.clone();
        Position ptr_sw = p.clone();
        
        // Check to the north east.
        for (int i = 0; i < b.get_width() - 1; i++)
        {
            ptr_ne = north_east(ptr_ne);
            ptr_ne.x = wrap_x(ptr_ne.x, b);
            if (ptr_ne.y < 0 || b.get_tile(ptr_ne.x, ptr_ne.y) != player)
            {
                break;
            }
            sequence++;
        }
        
        // Check to the south west.
        for (int i = 0; i < b.get_width() - 1; i++)
        {
            ptr_sw = south_west(ptr_sw);
            ptr_sw.x = wrap_x(ptr_sw.x, b);
            if (ptr_sw.x == ptr_ne.x || ptr_sw.y >= b.get_height() || b.get_tile(ptr_sw.x, ptr_sw.y) != player)
            {
                break;
            }
            sequence++;
        }
        
        return sequence;
    }
    
    int wrap_x(int x, Board b)
    {
        return (x + b.get_width()) % b.get_width();
    }
    
    bool empty_cell(Position p, Board b)
    {
        return b.get_tile(p.x, p.y) == b.get_empty();
    }

    Position north_west(Position p)
    {
        return Position(p.x - 1, p.y - 1);
    }

    Position north(Position p)
    {
        return Position(p.x, p.y - 1);
    }

    Position north_east(Position p)
    {
        return Position(p.x + 1, p.y - 1);
    }

    Position west(Position p)
    {
        return Position(p.x - 1, p.y);
    }

    Position east(Position p)
    {
        return Position(p.x + 1, p.y);
    }

    Position south_west(Position p)
    {
        return Position(p.x - 1, p.y + 1);
    }

    Position south(Position p)
    {
        return Position(p.x, p.y + 1);
    }

    Position south_east(Position p)
    {
        return Position(p.x + 1, p.y + 1);
    }

    void print_position(string msg, Position p)
    {
        cout << msg << ": (" << p.x << ", " << p.y << ")" << endl;
    }

    void test_evaluator()
    {
        Position p1(5, 5);
        print_position("original", p1);
        
        Position p2 = north_west(p1);
        print_position("north west", p2);
        
        Position p3 = north(p1);
        print_position("north", p3);
        
        Position p4 = north_east(p1);
        print_position("north east", p4);
        
        Position p5 = west(p1);
        print_position("west", p5);
        
        Position p6 = east(p1);
        print_position("east", p6);
        
        Position p7 = south_west(p1);
        print_position("south west", p7);
        
        Position p8 = south(p1);
        print_position("south", p8);
        
        Position p9 = south_east(p1);
        print_position("south east", p9);
    }
}

