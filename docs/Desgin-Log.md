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

## Step4 实现初步游戏

```
首先创建蛇，食物实体，进入{等待输入，更新游戏，输出}循环
```

### 实现

```cpp
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
```

## 中途测试

- 整体逻辑实现完全
- collision有BUG，碰撞墙有问题
- 蛇移动也有问题，应该不能向原本方向的反方向走
- 食物会生成在墙上
- 每次进入游戏食物生成的位置一样

## 暂停NEXT

- [x] 修复以上BUG
- [ ] 将交互改成异步的多线程的，而非while一套
- [ ] 美化显示，要求正方形
- [ ] 对比AI生成SNAKE的代码
- [ ] 开始重构代码
- [ ] 录制项目视频

## Step5 修复BUG

### TODO

- [x] collision修复
- [x] 设置不可以往反方向走
- [x] generateFood修复
- [x] rand制造种子

### 实现

### collision

- 修复前

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

- 修复后

```cpp
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
```

BUG：边界碰撞没有包含了边界

#### 禁止往反方向走

```cpp
if(nextDirection != snake.getDirection()) // 确保方向改变
{
	snake.setDirection(nextDirection); // 设置新的方向
}
```

BUG：蛇不应该往反方向走

### generateFood

- 修复前

```cpp
void Food::generateFood(const Snake& snake) {
    do {
        position.x = rand() % MAP_SIZE;
        position.y = rand() % MAP_SIZE;
    } while (snake.inBody(position));
}
```

- 修复后

```cpp
void Food::generateFood(const Snake& snake) {
    do {
        position.x = rand() % (MAP_SIZE - 2) + 1;   // 确保食物不在边界上
        position.y = rand() % (MAP_SIZE - 2) + 1;
    } while (snake.inBody(position));
}
```

BUG：食物生成在[0, MAP_SIZE - 1]，应该在[1, MAP_SIZE - 2]

#### 给rand种子

```cpp
// 设置随机数种子
srand(time(nullptr));
```

BUG：不设置种子，每次启动程序基于随机数的食物生成会按照相同模式生成

