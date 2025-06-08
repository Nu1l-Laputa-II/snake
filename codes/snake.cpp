#include <iostream>
#include <cstdlib>
#include <string>
#include <queue>

using namespace std;

const string banner = R"(
-------------------------------------------------------
 ______     __   __     ______     __  __     ______    
/\  ___\   /\ "-.\ \   /\  __ \   /\ \/ /    /\  ___\   
\ \___  \  \ \ \-.  \  \ \  __ \  \ \  _"-.  \ \  __\   
 \/\_____\  \ \_\\"\_\  \ \_\ \_\  \ \_\ \_\  \ \_____\ 
  \/_____/   \/_/ \/_/   \/_/\/_/   \/_/\/_/   \/_____/
-------------------------------------------------------)";

const string welcomeMessage = R"(
Welcome to the Snake Game!
This is a simple console-based snake game implemented in C++.
[0] Start the game
[1] Exit the game
Please choose an option:)";

struct Position {
    int x;
    int y;
};

class Snake {
private:
    int length;
    queue<Position> body; // position of snake's body, snake's head in rear of queue, snake's rear in front of queue
    int direction; // 0: up, 1: right, 2: down, 3: left

public:
    // TODO: 实现Snake类方法
};

class Food {
private:
    Position position; // position of food

public:
    // TODO: 实现Food类方法
};

int main()
{
    // clear the console screen
    system("clear || cls");

    // set all output to green
    cout << "\033[32m";

    // print the banner and welcome message
    cout << banner << "\n";
    cout << welcomeMessage;

    // wait for user input
    int choice;
    cin >> choice;

    if (choice == 0)
    {
        cout << "Starting the game...\n";
        // TODO: loop of game
    }
    else if (choice == 1)
    {
        cout << "Exiting the game. Goodbye!\n";
    }
    else
    {
        cout << "Invalid choice. Please restart the game and choose a valid option.\n";
    }

    return 0;
}