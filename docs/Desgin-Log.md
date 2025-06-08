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

