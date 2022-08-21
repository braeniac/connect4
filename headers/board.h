#include <iostream>
#include <vector>

using namespace std;

#ifndef board_h
#define board_h

class Board {
public:
    Board(int width, int height, char default_char);
    int width;
    int height;
    int get_width();
    int get_height();
    vector< vector<char> > board;
    char get_tile(int x, int y);
    void set_tile(int x, int y, char c);
    char get_empty();
    char default_char;
    void create_board(int width, int height);
    void create_width();
    void set_empty(char c);
    Board* clone();
    string get_string();
    ~Board();
};

#endif
