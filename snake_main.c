#include "snake.h"
int main()
{
    srand((unsigned int)time(0)); //�������������
    int result;
    int score = 0;
    // ʹ������ѭ����������ʾ�˵���ֱ���û�ѡ���˳�
    while (1) {
        result = Menu();
        switch (result) {
        case 1:
            system("cls");
            InitMap();
            while (MoveSnake());
            break;
        case 2:
            system("cls");
            Help();
            break;
        case 3:
            system("cls");
            About();
            break;
        /*case 4:
            system("cls");
            Ranking();
            break;*/
        case 0:
            return 0; // �˳���������
        default:
            // ���û�ѡ����Чѡ��ٴ���ʾ�˵�
            break;
        }
    }
    return 0;
}