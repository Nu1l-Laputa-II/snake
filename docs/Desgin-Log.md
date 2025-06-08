## Step0 创建开始界面

```
程序启动，首先清屏然后输出游戏开始的界面，选择0开始，1退出。
```

### 实现

- 清屏操作

```cpp
std::system("clear || cls");
```

- 设置console为绿色

```cpp
std::cout << "\033[32m"
```

- 欢迎界面设定

```cpp
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
```

### 流程

1. 清屏
2. console字体设置为绿色
3. 输出欢迎界面
4. 等待输入

## step1 创建蛇结构体，食物的结构体

```
蛇的结构体要素为蛇每个身体的位置（采用deque实现，蛇头在队尾，蛇尾在队头），蛇头的动向。
```

#### 实现

- 位置

```cpp
struct Position {
    int x;
    int y;
};
```

- 蛇

```cpp
class Snake {
private:
    int length;
    deque<Position> body; // position of snake's body, snake's head in rear of queue, snake's rear in front of queue
    int direction; // 0: up, 1: right, 2: down, 3: left

public:
    // TODO: 实现Snake类方法
};
```

- 食物

```cpp
class Food {
private:
    Position position; // position of food

public:
    // TODO: 实现Food类方法
};
```

## step2 设计蛇的算法，食物生成的算法

### TODO

- [x] 蛇
  - [x] 碰撞
    - [x] 边界检测
    - [x] 身体检测
  - [x] 更新蛇体
- [x] 食物
  - [x] 生成位置

### 实现

- 蛇-碰撞

```cpp
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
```

- 蛇-更新

```cpp
void update(Food& food)
{
    Position head = body.back();
    Position nextHead = head + direction;

    if (nextHead == food.getPosition()) {
        length++; // 吃到食物，蛇变长
        body.push_back(nextHead);
    } else {
        body.push_back(nextHead);
        body.pop_front(); // 去掉尾部
	}
}
```

- 食物-生成位置

```cpp
void generateFood(const Snake& snake)
{
    // 随机生成食物位置，确保不与蛇身重叠
    do {
        position.x = rand() % MAP_SIZE;
        position.y = rand() % MAP_SIZE;
    } while (snake.inBody(position));
}
```

## Step3 显示模块

```
打印地图，打印蛇（x)，打印食物(o)，墙壁(#)。
```

### 实现

```cpp
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
```

