#include "snake.h"
int main()
{
    srand((unsigned int)time(0)); //生成随机数种子
    int result;

    // 使用无限循环来持续显示菜单，直到用户选择退出
    while (1) {
        result = Menu();
        switch (result) {
        case 1:
            InitMap();
            while (MoveSnake());
            break;
        case 2:
            Help();
            break;
        case 3:
            About();
            break;
        case 0:
            return 0; // 退出整个程序
        default:
            // 当用户选择无效选项，再次显示菜单
            break;
        }
    }
    return 0;
}