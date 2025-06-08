#include <iostream>
#include <cstdlib>
#include <string>
#include <deque>

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

const int MAP_SIZE = 15; // size of the game map
const int INITIAL_SNAKE_LENGTH = 1; // initial length of the snake
const int INITIAL_SNAKE_DIRECTION = 1; // initial direction of the snake (1: right)

struct Position {
    int x;
    int y;
};

inline Position operator+(const Position& a, const Position& b) {
    return {a.x + b.x, a.y + b.y};
}

inline bool operator==(const Position& a, const Position& b) {
    return a.x == b.x && a.y == b.y;
}

const Position Up = {0, -1};
const Position Right = {1, 0};
const Position Down = {0, 1};
const Position Left = {-1, 0};

const char snakeSign = 'x';
const char foodSign = 'o';
const char emptySign = ' ';
const char wallSign = '#';

class Snake;  // 前向声明

class Food {
private:
    Position position;

public:
    Food() : position{MAP_SIZE/2, MAP_SIZE/2} {}  // 添加默认构造函数，食物初始位置在地图中心
    
    Food(const Snake& snake) {      
        generateFood(snake); // 生成初始食物位置
    }

    Position getPosition() const {
        return position;
    }

    void generateFood(const Snake& snake);  // 声明但不定义
};

class Snake {
private:
    int length;
    deque<Position> body; // 蛇身，头在队尾，尾在队首
    Position direction;   // 当前移动方向

public:
    Snake() : length(INITIAL_SNAKE_LENGTH), direction(Right)
    {
        // 初始化蛇身，初始位置在地图中心
        Position startPos = {(MAP_SIZE - 1) / 2, (MAP_SIZE - 1 ) / 2};
        body.push_back(startPos);
    }

    int getLength() const {
        return length;
    }

    bool inBody(const Position& pos) const
    {
        for (const auto& segment : body)
        {
            if (segment.x == pos.x && segment.y == pos.y)
            {
                return true; // 位置在蛇身上
            }
        }
        return false; // 位置不在蛇身上
    }

    bool collision()
    {
        Position head = body.back();
        Position nextHead = head + direction;
        // 边界碰撞
        if (nextHead.x < 0 || nextHead.x >= MAP_SIZE || nextHead.y < 0 || nextHead.y >= MAP_SIZE)
        {
            return true; // 撞墙
        }
        // 自身碰撞
        if (inBody(nextHead))
        {
            return true; // 撞到自己
        }
        return false;
    }

    void update(Food& food)
    {
        Position head = body.back();
        Position nextHead = head + direction;

        if (nextHead == food.getPosition()) {
            length++; // 吃到食物，蛇变长
            body.push_back(nextHead);
            food.generateFood(*this); // 生成新的食物
        } else {
            body.push_back(nextHead);
            body.pop_front(); // 去掉尾部
        }
    }

    void setDirection(Position newDir) {
        direction = newDir;
    }
};

void Food::generateFood(const Snake& snake) {
    do {
        position.x = rand() % MAP_SIZE;
        position.y = rand() % MAP_SIZE;
    } while (snake.inBody(position));
}

void display(const Snake& snake, const Food& food)
{
    system("clear || cls"); // 清屏

    // 逐行输出
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            Position pos = {x, y};
            if (snake.inBody(pos)) {
                cout << snakeSign; // 蛇身
            } else if (pos == food.getPosition()) {
                cout << foodSign; // 食物
            } else if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1) {
                cout << wallSign; // 墙壁
            } else  
            {
                cout << emptySign; // 空白
            }
        }
        cout << endl;
    }
}

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
        Snake snake;
        Food food(snake);
        
        while(true)
        {
            // 等待输入
            char input;
            cin >> input;
            switch(input) {
                case 'w': snake.setDirection(Up); break;
                case 's': snake.setDirection(Down); break;
                case 'a': snake.setDirection(Left); break;
                case 'd': snake.setDirection(Right); break;
                case 'q': goto gameEnd;  // 退出游戏
            }

            // 更新游戏
            if (snake.collision())
            {
                cout << "Game Over! You collided with the wall or yourself.\n";
                break; // 结束游戏
            }
            else
            {
                snake.update(food); // 更新蛇的位置
            }

            // 输出游戏画面
            display(snake, food);
            cout << "Snake Length: " << snake.getLength() << endl;
        }
        gameEnd:;  // 添加游戏结束标签
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