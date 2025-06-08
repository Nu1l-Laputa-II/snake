#include <iostream>
#include <cstdlib>
#include <string>

const std::string banner = R"(
-------------------------------------------------------
 ______     __   __     ______     __  __     ______    
/\  ___\   /\ "-.\ \   /\  __ \   /\ \/ /    /\  ___\   
\ \___  \  \ \ \-.  \  \ \  __ \  \ \  _"-.  \ \  __\   
 \/\_____\  \ \_\\"\_\  \ \_\ \_\  \ \_\ \_\  \ \_____\ 
  \/_____/   \/_/ \/_/   \/_/\/_/   \/_/\/_/   \/_____/
-------------------------------------------------------)";

const std::string welcomeMessage = R"(
Welcome to the Snake Game!
This is a simple console-based snake game implemented in C++.
[0] Start the game
[1] Exit the game
Please choose an option:)";

int main()
{
    // clear the console screen
    std::system("clear || cls");

    // set all output to green
    std::cout << "\033[32m";

    // print the banner and welcome message
    std::cout << banner << "\n";
    std::cout << welcomeMessage;

    // wait for user input
    int choice;
    std::cin >> choice;

    if (choice == 0)
    {
        std::cout << "Starting the game...\n";
        // TODO: loop of game
    }
    else if (choice == 1)
    {
        std::cout << "Exiting the game. Goodbye!\n";
    }
    else
    {
        std::cout << "Invalid choice. Please restart the game and choose a valid option.\n";
    }

    return 0;
}