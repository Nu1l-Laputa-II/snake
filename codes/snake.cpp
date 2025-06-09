#include <iostream>
#include <cstdlib>
#include <string>
#include <deque>
#include <ctime>
#include <conio.h>
#include <windows.h>

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

inline bool operator!=(const Position& a, const Position& b) {
    return !(a == b);
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
    Snake() : length(2), direction(Right)
    {
        // 初始化蛇身，初始位置在地图中心，尾巴在左，头在右
        Position tail = {(MAP_SIZE - 1) / 2, (MAP_SIZE - 1 ) / 2};
        Position head = {tail.x + 1, tail.y};
        body.push_back(tail); // 尾巴
        body.push_back(head); // 头
    }

    int getLength() const {
        return length;
    }

    Position getDirection() const {
        return direction;
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
        if (nextHead.x <= 0 || nextHead.x >= MAP_SIZE - 1 || nextHead.y <= 0 || nextHead.y >= MAP_SIZE - 1)
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
        position.x = rand() % (MAP_SIZE - 2) + 1;   // 确保食物不在边界上
        position.y = rand() % (MAP_SIZE - 2) + 1;
    } while (snake.inBody(position));
}

void display(const Snake& snake, const Food& food)
{
    // 使用缓冲区避免闪烁
    string buffer;
    buffer.reserve(MAP_SIZE * (MAP_SIZE + 1) * 2);
    for (int y = 0; y < MAP_SIZE; ++y) {
        for (int x = 0; x < MAP_SIZE; ++x) {
            Position pos = {x, y};
            char ch;
            if (snake.inBody(pos)) {
                ch = snakeSign;
            } else if (pos == food.getPosition()) {
                ch = foodSign;
            } else if (x == 0 || x == MAP_SIZE - 1 || y == 0 || y == MAP_SIZE - 1) {
                ch = wallSign;
            } else {
                ch = emptySign;
            }
            buffer += ch;
            buffer += ch; // 每格输出两次，视觉上更接近正方形
        }
        buffer += '\n';
    }
    // 光标移动到左上角
    cout << "\033[H" << buffer;
}

int main()
{
    // 设置随机数种子
    srand(time(nullptr));
    
    // clear the console screen
    // system("cls"); // 不再清屏

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
        // 隐藏光标
        cout << "\033[?25l";
        Snake snake;
        Food food(snake);
        Position nextDirection = Right; // 初始方向为右
        
        // 输出初始画面，移动光标到左上角
        cout << "\033[2J\033[H";
        while(true)
        {
            if (_kbhit())
            {
                char input = _getch(); // 获取键盘输入
                switch(input) {
                    case 'w': nextDirection = Up; break;
                    case 's': nextDirection = Down; break;
                    case 'a': nextDirection = Left; break;
                    case 'd': nextDirection = Right; break;
                    case 'q': goto gameEnd;  // 退出游戏
                }
            }

            // 判断是否为反方向
            auto isOpposite = [](const Position& a, const Position& b) {
                return a.x == -b.x && a.y == -b.y;
            };
            if(nextDirection != snake.getDirection() && !isOpposite(nextDirection, snake.getDirection())) // 不是原方向也不是反方向
            {
                snake.setDirection(nextDirection); // 设置新的方向
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

            Sleep(314); // 暂停314毫秒
        }
        gameEnd:;
        // 恢复光标
        cout << "\033[?25h";
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