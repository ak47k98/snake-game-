#include<stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define MAP_HEIGHT 30  
#define MAP_WIDTH 30   
#define UP 'w'         
#define DOWN 's'       
#define LEFT 'a'       
#define RIGHT 'd'      


typedef struct
{
	int x;
	int y;

}Food1,Food2, snakeNode,Barrier;

typedef struct
{
	snakeNode snakeNode[1000];
	int length;
	int speed;
}Snake;

void GotoXY(int x, int y);
void Hide();
int Menu();
void About();
void Help();
void InitMap();
void PrintFood1();
void PrintFood2();
int MoveSnake();
int IsCorrect();
void SpeedControl();

void Printbarrier();
void Ranking();