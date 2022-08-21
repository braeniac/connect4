#include <iostream>
#include "headers/connectfour.h"
#include "headers/evaluator.h"
#include <pthread.h>
#include <limits>

#define NUM_THREADS 1

ConnectFour* cf = new ConnectFour;

int get_user_int()
{
    int input;
    while(!(cin >> input)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Please enter an integer: ";
    }
    return input;
}

int get_user_1_or_2()
{
    int input = get_user_int();
    
    while (input != 1 && input != 2)
    {
        cout << "Invalid input. Must be 1 or 2. Try again: ";
        input = get_user_int();
    }

    return input;
}

int get_valid_move()
{
    int input = get_user_int();
    
    while(input < 0 || input > 7)
    {
        cout << "Invalid input. Must be between 0 and 7, inclusive. Try again: ";
        input = get_user_int();
    }
    
    return input;
}

// Details about the thread (used for debugging).
typedef struct _thread_data_t {
    int tid;
    double stuff;
} thread_data_t;

// The thread function.
void *thr_func(void *arg) {
    int move_ai_made = cf->ai_make_move();
    cout << endl << "AI dropped a piece at column " << move_ai_made << ": " << endl;
    cout << cf->to_string() << endl;
    
    pthread_exit(NULL);
}

// Start the thread.
void start_thread()
{
    pthread_t thr[NUM_THREADS];
    int i, rc;
    thread_data_t thr_data[NUM_THREADS];
    
    for (i = 0; i < NUM_THREADS; ++i) {
        thr_data[i].tid = i;
        if ((rc = pthread_create(&thr[i], NULL, thr_func, &thr_data[i]))) {
            cout << "error: pthread_create, rc: " << rc << endl;
        }
    }

    for (i = 0; i < NUM_THREADS; ++i) {
        pthread_join(thr[i], NULL);
    }
}

void choose_player()
{
    cout << "Would you like to player as Player 1 (X) or Player 2 (0)?" << endl;
    cout << "Enter 1 or 2: ";
    int choice = get_user_1_or_2();
    
    if (choice == 2)
    {
        cf->switch_player_turn();
    }
}

void play_game()
{
    while (!cf->is_game_over())
    {
        cout << "Select a column to perform a move: ";;
        int input = get_valid_move();
        cf->place_piece_at(input);
        cout << cf->to_string() << endl;
        
        if (cf->is_game_over())
            break;
        
        start_thread();
    }
    
    cout << endl << "Game Over." << endl;
    cout << "Player " << cf->who_is_winning() << " won!" << endl << endl;
}

int main(int argc, const char * argv[]) {
    choose_player();
    play_game();
    return 0;
}
