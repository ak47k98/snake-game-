#include "snake.h"
int main()
{
    srand((unsigned int)time(0)); //�������������
    int result;

    // ʹ������ѭ����������ʾ�˵���ֱ���û�ѡ���˳�
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
            return 0; // �˳���������
        default:
            // ���û�ѡ����Чѡ��ٴ���ʾ�˵�
            break;
        }
    }
    return 0;
}