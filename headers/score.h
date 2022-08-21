#ifndef stats_h
#define stats_h

struct Score {
    int player_1;
    int player_2;
    Score(int player_1, int player_2)
    {
        this->player_1 = player_1;
        this->player_2 = player_2;
    }
    Score* clone()
    {
        Score* s = new Score(player_1, player_2);
        return s;
    }
};

#endif
