#include "snake.h"
Snake snake;
Food1 food1;
Food2 food2;
Barrier barrier;
char now_Dir = RIGHT;
char direction = RIGHT;


int Menu()  //主菜单
{
	GotoXY(40, 12);
	printf("欢迎来到贪吃蛇小游戏 ==== Ciallo~~~ ");
	GotoXY(43, 14);
	printf("1.开始游戏 ==== Link start !");
	GotoXY(43, 16);
	printf("2.帮助 ==== QvQ ！");
	GotoXY(43, 18);
	printf("3.关于 ==== 进♂来♂坐♂坐♂");
	GotoXY(43, 20);
	printf("4.排名");
	GotoXY(43, 22);
	printf("0.退出游戏 ==== =）");
	Hide();
	char ch;
	ch = _getch();
	switch (ch)
	{
	case '1':
		return 1;
	case '2':
		return 2;
	case '3':
		return 3;
	case '0':
		return 0; // 允许用户输入 '0' 退出程序
	default:
		// 没有匹配的选项，清屏后再次调用 Menu，相当于重新显示菜单
		system("cls");
		return 4; // 返回一个不退出程序的值
	}
}

void GotoXY(int x, int y)
{
	HANDLE hout;
	COORD cor;
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	cor.X = x;
	cor.Y = y;
	SetConsoleCursorPosition(hout, cor);
}

void Hide()
{
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cor_info = { 1,0 };
	SetConsoleCursorInfo(hout, &cor_info);
}

void About()
{
	GotoXY(43, 14);
	printf("==  ==");
	GotoXY(43, 16);
	printf("== from ak47k98 && sth ==");
	GotoXY(43, 18);
	printf("按任意键返回");
	Hide();
	char ch = _getch();
	system("cls");
}

void Help()
{
	GotoXY(40, 12);
	printf("w上");
	GotoXY(40, 14);
	printf("s下");
	GotoXY(40, 16);
	printf("d左");
	GotoXY(40, 18);
	printf("d右");
	GotoXY(40, 20);
	printf("当蛇撞到自身或墙结束游戏 =）");
	GotoXY(40, 22);
	printf("按任意键返回");
	Hide();
	char ch = _getch();
	system("cls");
}


void InitMap()   //生成随机地图
{
	Hide();
	snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
	snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
	GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
	printf("@");
	snake.length = 3;
	snake.speed = 250;
	now_Dir = RIGHT;

	// 初始化蛇身体的坐标
	for (int i = 1; i < snake.length; i++)
	{
		snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
		snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
		GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);
		printf("o");
	}

	// 打印地图的水平边界（上下）
	for (int i = 0; i < MAP_WIDTH; i++)
	{
		GotoXY(i, 0);
		printf("-");
		GotoXY(i, MAP_HEIGHT - 1);
		printf("-");
	}

	// 打印地图的垂直边界（左右）
	for (int i = 1; i < MAP_HEIGHT - 1; i++)
	{
		GotoXY(0, i);
		printf("|");
		GotoXY(MAP_WIDTH - 1, i);
		printf("|");
	}

	PrintFood1();
	PrintFood2();
}
void PrintFood1()   //生成食物一
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food1.x = rand() % (MAP_WIDTH - 2) + 1;
		food1.y = rand() % (MAP_HEIGHT - 2) + 1;
		for (int k = 0; k <= snake.length - 1; k++)
		{
			if (snake.snakeNode[k].x == food1.x && snake.snakeNode[k].y == food1.y|| food1.x== barrier.x&& food1.y== barrier.y|| food1.x == food2.x&&food1.y==food2.y)
			{				//保证生成的食物不会覆盖障碍物或蛇
				flag = 1;
				break;
			}
		}
	}
	GotoXY(food1.x, food1.y);
	printf("$");
}

void PrintFood2()  //生成食物2
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		food2.x = rand() % (MAP_WIDTH - 2) + 1;
		food2.y = rand() % (MAP_HEIGHT - 2) + 1;
		for (int k = 0; k <= snake.length - 1; k++)
		{
			if ((snake.snakeNode[k].x == food2.x && snake.snakeNode[k].y == food2.y )|| (food2.x == barrier.x && food2.y == barrier.y) || food1.x == food2.x && food1.y == food2.y)
			{				//保证生成的食物不会覆盖障碍物或蛇
				flag = 1;
				break;
			}
		}
	}
	GotoXY(food2.x, food2.y);
	printf("￥");
}
void Printbarrier()  //生成障碍物
{
	int flag = 1;
	while (flag)
	{
		flag = 0;
		barrier.x = (rand()%2+food2.x+1)% MAP_WIDTH;
		barrier.y = (rand()%2 + food2.y+1)% MAP_HEIGHT;
		for (int k = 0; k <= snake.length - 1; k++)
		{
			if ((snake.snakeNode[k].x == barrier.x && snake.snakeNode[k].y == barrier.y) || (barrier.x == food1.x && barrier.y == food1.y)|| (barrier.x == food2.x && barrier.y == food2.y))
			{
				flag = 1;
				break;
			}
		}
		GotoXY(barrier.x, barrier.y);
		printf("!");
	}
}
int MoveSnake()
{
	snakeNode temp;
	int flag = 0;
	temp = snake.snakeNode[snake.length-1];
	for (int i = snake.length - 1; i >= 1; i--)
	{
		snake.snakeNode[i] = snake.snakeNode[i - 1];
	}
	GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
	printf("o");
	if (_kbhit())
	{
		direction = _getch();
		switch(direction)
		{
			case UP :
				if (now_Dir != DOWN)
				{
					now_Dir = direction;
				}
				break; 
			case DOWN:
				if (now_Dir !=UP)
				{
					now_Dir = direction;
				}
				break;
			case LEFT:
				if (now_Dir != RIGHT)
				{
					now_Dir = direction;
				}
				break;
			case RIGHT :
				if (now_Dir != LEFT )
				{
					now_Dir = direction;
				}
				break;
		}


	}
	switch (now_Dir)
	{
		case UP:snake.snakeNode[0].y--; break;
		case DOWN:snake.snakeNode[0].y++; break;
		case LEFT:snake.snakeNode[0].x--; break;
		case RIGHT:snake.snakeNode[0].x++; break;
	}
	GotoXY(snake.snakeNode[0].x,snake.snakeNode[0].y);
	printf("@");

	if (snake.snakeNode[0].x == food1.x && snake.snakeNode[0].y == food1.y)
	{
		snake.length++;
		flag = 1;
		snake.snakeNode[snake.length - 1] = temp;
		PrintFood1();
	}
	if (snake.snakeNode[0].x == food2.x && snake.snakeNode[0].y == food2.y)
	{
		int i = 2;
		flag = 1;
		while(i>0)
		{
			snake.length++;
			snake.snakeNode[snake.length - 1] = temp;
			i--;
		}
		PrintFood2();
	}
	if (!flag)
	{
		GotoXY(temp.x, temp.y);
		printf(" ");
	}
	else
	{
		Printbarrier();
		GotoXY(50, 5);
		printf("now your point is :%d", snake.length - 3);
	}
	if (!IsCorrect())
	{
		system("cls");
		if (snake.length - 3 < 10)
		{
			GotoXY(45, 14);
			printf("输了吧，杂鱼 (￣▽￣)~*");
			GotoXY(45, 16);
			printf("怎么就只有:%d 分 :)", snake.length - 3);
		}
		else
		{
			GotoXY(45, 14);
			printf("GJ !(^ _−)☆  ");
			GotoXY(45, 16);
			printf(" ∑(っ°Д°;)っ居然有: % d 分 : )",snake.length - 3);
		}
		GotoXY(45,18); 
		printf("按任意键返回主菜单");
		char c = _getch();
		system("cls");
		return 0;
	}
	SpeedControl();
	Sleep(snake.speed);
	return 1;
}


int IsCorrect()
{
	int score;
	// 检查蛇头是否撞墙
	if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 ||
		snake.snakeNode[0].x == MAP_WIDTH - 1 || snake.snakeNode[0].y == MAP_HEIGHT - 1)
	{
		return 0; // 游戏结束
	}
	// 检查蛇头是否撞障碍物
	if (snake.snakeNode[0].x == barrier.x && snake.snakeNode[0].y == barrier.y)
	{
		return 0; // 游戏结束
	}

	// 检查蛇头是否撞到自身
	for (int i = 1; i < snake.length; i++)
	{
		if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y)
		{
			return 0; // 游戏结束
			score = snake.length - 3;
		}
	}
	return 1; // 游戏继续
}

void SpeedControl()
{
	switch (snake.length)
	{
	case 6:snake.speed = 200; break;
	case 9:snake.speed = 180; break;
	case 12:snake.speed = 160; break;
	case 15:snake.speed = 140; break;
	case 18:snake.speed = 120; break;
	case 21:snake.speed = 100; break;
	case 24:snake.speed = 80; break;
	case 27:snake.speed = 60; break;
	case 30:snake.speed = 40; break;
	default: break;
	}
}

/*void Ranking()
{
	FILE* fp;
	int ch;
	if (!(fp = fopen("C:\\Users\sth for noth\Desktop\snake\ranking.txt","rb+")))
	{
		printf("error");
		return;
	}

}*/