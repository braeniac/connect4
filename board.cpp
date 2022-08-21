#include "headers/board.h"

Board::Board(int width, int height, char default_char)
{
    Board::default_char = default_char;
    create_board(width, height);
}

void Board::create_board(int width, int height)
{
    if (width < 0 || height < 0)
    {
        string msg = "x and y must be positive.";
        cout << msg << endl;
        throw std::exception();
    }

    this->width = width;
    this->height = height;

    create_width();
    set_empty(Board::default_char);
}

void Board::create_width()
{
    for (int i = 0 ; i < height ; i++)
    {
        vector<char> tmp(width);
        board.push_back(tmp);
    }
}

Board::~Board()
{
    
}

int Board::get_width()
{
    return width;
}

int Board::get_height()
{
    return height;
}

char Board::get_tile(int x, int y)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        string msg = "x and y are out of bounds.";
        cout << msg << endl;
        throw std::exception();
    }
    return board[y][x];
}

void Board::set_tile(int x, int y, char c)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
    {
        string msg = "x and y are out of bounds.";
        cout << msg << endl;
        throw std::exception();
    }
    board[y][x] = c;
}

string Board::get_string()
{
    string str = "";

    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0; x < width ; x++)
        {
            str += board[y][x];
            str += " ";
        }
        if (y == height - 1)
        {
            break;
        }
        str += "\n";
    }

    return str;
}

Board* Board::clone()
{
    Board* clone = new Board(get_width(), get_height(), default_char);
    
    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0; x < width ; x++)
        {
            clone->set_tile(x, y, get_tile(x, y));
        }
    }
    return clone;
}

void Board::set_empty(char c)
{
    for (int y = 0 ; y < height ; y++)
    {
        for (int x = 0 ; x < width ; x++)
        {
            set_tile(x, y, c);
        }
    }
}

char Board::get_empty()
{
    return Board::default_char;
}
