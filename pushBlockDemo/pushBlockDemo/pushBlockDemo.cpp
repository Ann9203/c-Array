// pushBlockDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;


const unsigned short MAP_ROW = 7; //行
const unsigned short MAP_COL = 7; //列

const unsigned short NUL = 0;
const unsigned short WALL = 1;
const unsigned short GRASS = 2;
const unsigned short BOX = 3;
const unsigned short PLAYE = 4;
const unsigned short FINAL = 5;

const char* STRNULL = "  ";//空地
const char* STRWALL = "口";//墙
const char* STRGRESS = "▓"; //草地
const char* STRBOX = "田"; //箱子
const char* STRPLAY = "♀"; //玩家
const char* STRFINAL = "◎"; //终点

/*判断游戏是否胜利*/
bool isWin = false;
bool isDead = false;

/*玩家坐标*/
unsigned int x = 1;
unsigned int y = 1;

/*箱子坐标*/
unsigned int bx = 0;
unsigned int by = 0;

/*终点坐标*/
unsigned int fx = 0;
unsigned int fy = 0;

/*键值*/
enum KeyBoardValu
{
	A = 97,
	D = 100,
	W = 119,
	S = 115
};

/*初始化地图数据*/
unsigned short MapData[MAP_ROW][MAP_COL]
{
	{ 1, 1, 1, 1, 1, 1 ,1 },
	{ 1, 4 ,0 ,0 ,5 ,5 ,1 },
	{ 1, 0, 0, 0, 2, 0 ,1 },
	{ 1, 0 ,3 ,0 ,2 ,0 ,1 },
	{ 1, 0, 0, 1, 0, 0 ,1 },
	{ 1, 0 ,0 ,0 ,0 ,0 ,1 },
	{ 1, 1, 1, 1, 1, 1 ,1 }
};
/*根据现有数据绘制*/
const char* GetData(unsigned short data) 
{
	switch (data)
	{
	case NUL:
		return STRNULL;
	case WALL:
		return STRWALL;
	case GRASS:
		return STRGRESS;
	case BOX:
		return STRBOX;
	case PLAYE:
		return STRPLAY;
	case FINAL:
		return STRFINAL;
	default:
		return STRNULL;
	}
}

/*打印地图数据*/
void PrintMAp(unsigned short mapData[MAP_ROW][MAP_COL])
{
	
	
	for (int i = 0; i < MAP_ROW; i++)
	{
		cout << "\t      ";
		for (int  j = 0; j < MAP_COL; j++)
		{
			//单独判断是否是为玩家  箱子 
			//玩家
			if (x == j && y == i)
			{
				cout << setw(2) << STRPLAY;
			}
			//箱子
			else if (bx == j && by == i)
			{
				cout << setw(2) << STRBOX;
			}
			//其他固定位置摆好
			else
			{
				cout << setw(2) << GetData(mapData[i][j]);
			
			}
		}
		cout << endl;
	}
}

/*打印标题*/
void PrintTitle()
{

	cout << "*****************************************" << endl;
	cout << "*             推箱子简单版              *" << endl;
	cout << "*****************************************" << endl;
}
/*打印游戏是否是成功与否*/
void PrintTips()
{
	if (isWin)
	{
		cout << "恭喜您闯关成功" << endl;
	}
	else if (isDead)
	{
		cout << "很抱歉, 您已走入死路" << endl;
	}
}
 
/*从地图读取各种信息*/
void ReadMapInfo(unsigned short mapData[MAP_ROW][MAP_COL])
{
	for (int i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			//找出玩儿家的地址
			if (mapData[i][j] == PLAYE)
			{
				x = j;
				y = i;
				mapData[i][j] = NUL;
			} 
			//找到盒子位置
			else if (mapData[i][j] == BOX)
			{
				bx = j;
				by = i;
				mapData[i][j] = NUL;
			} 
			//找出终点位置
			else if (mapData[i][j] == FINAL) 
			{
				fx = j;
				fy = i;
			}
		}
	}
}


/*玩儿家移动*/
void PlayerMove(int dx, int dy) {
	x += dx;
	y += dy;
}

/*箱子移动*/
void BoxMove(int dx, int dy)
{
	bx += dx;
	by += dy;
}

/*判断在地图中的位置是否可以移动*/
bool IsAvailable(int x, int y, unsigned short mapData[MAP_ROW][MAP_COL])
{
	return (mapData[y][x] == NUL || mapData[y][x] == FINAL) && (x != bx || y != by);
}

/*判断地图上是否有一个纸盒子*/
bool IsBox(unsigned int x, unsigned int y) 
{
	return(bx == x && by == y);
}

/*判断某个位置是否是终点点*/
bool IsFinal(unsigned x, unsigned y, unsigned short mapData[MAP_ROW][MAP_COL])
{
	return mapData[y][x] == FINAL;
}

/*判断死亡*/
bool IsDead(unsigned x, unsigned y, unsigned short mapData[MAP_ROW][MAP_COL])
{
	return (mapData[y + 1][x] == WALL && mapData[y][x + 1] == WALL) || (mapData[y - 1][x] == WALL && mapData[y][x + 1] == WALL) ||
		(mapData[y - 1][x] == WALL && mapData[y][x - 1] == WALL) || (mapData[y + 1][x] == WALL && mapData[y - 1][x] == WALL)||
		(mapData[y+1][x] == GRASS && mapData[y][x+1]==WALL);
}



 

int main()
{
  //初始化各种数据
	PrintTitle();
	ReadMapInfo(MapData);
	PrintMAp(MapData);
	

	//KEYBOARDVALUE ch = A;
	KeyBoardValu ch;
	//while循环
	while (!isWin && !isDead && ( ch  = (KeyBoardValu)_getch())/*如果输入的恩建*/)
	{
		
		switch (ch)
		{
		case A:
			//向左
			//判断人物是否可以走
			if (IsAvailable(x-1, y, MapData))
			{
				PlayerMove(-1, 0);
			} 
			//可以走但是有箱子
			else if (IsBox(x-1, y) && IsAvailable(x-2, y, MapData))
			{
				BoxMove(-1, 0);
				PlayerMove(-1, 0);
				
			}
			break;
		case D:
			//向右
			if (IsAvailable(x + 1, y, MapData))
			{
				PlayerMove(1, 0);
			}
			//可以走但是有箱子
			else if (IsBox(x + 1, y) && IsAvailable(x + 2, y, MapData))
			{
				BoxMove(1, 0);
				PlayerMove(1, 0);
				
			}
			break;
		case W:
			//向上
			if (IsAvailable(x , y - 1, MapData))
			{
				PlayerMove(0, -1);
			}
			//可以走但是有箱子
			else if (IsBox(x , y-1) && IsAvailable(x, y - 2, MapData))
			{
				BoxMove(0, -1);
				PlayerMove(0, -1);
				
			}
			break;
		case S:
			//向下
			if (IsAvailable(x, y + 1, MapData))
			{
				PlayerMove(0, 1);
			}
			//可以走但是有箱子
			else if (IsBox(x, y + 1) && IsAvailable(x, y + 2, MapData))
			{
				BoxMove(0, 1);
				PlayerMove(0, 1);
				
			}
			break;
		}

		//胜利失败判定
		if (IsFinal(bx, by, MapData))
		{
			isWin = true;
			isDead = false;
		}
		else if (IsDead(bx, by, MapData))
		{
			isWin = false;
			isDead = true;
		}
		
		system("cls");

		//绘制游戏中的内容
		PrintTitle();
		PrintMAp(MapData);
		
	}
	PrintTips();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
