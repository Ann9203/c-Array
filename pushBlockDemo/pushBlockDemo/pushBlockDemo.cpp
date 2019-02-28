// pushBlockDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include "pch.h"
#include <iostream>
#include <iomanip>
#include <conio.h>

using namespace std;


const unsigned short MAP_ROW = 8; //行
const unsigned short MAP_COL = 8; //列

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
bool isFirstSuc = false; //第一次是否闯关成功

/*设置最大box数量*/
const unsigned int MAX_BOX = 5;
int box_count = 0; //盒子数量
int postion = 0; //指针指向position 箱子

/*玩家坐标*/
unsigned int x = 1;
unsigned int y = 1;



/*箱子数组坐标*/
unsigned int boxes[MAX_BOX * 2];
/*终点数组坐标*/
unsigned int finals[MAX_BOX * 2];





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
	{ 1, 1, 1, 1, 1, 1 ,1 ,1 },
	{ 1, 4, 0 ,0 ,0 ,0 ,5 ,1 },
	{ 1, 0, 0, 0, 3, 0 ,0 ,1 },
	{ 1, 0, 3 ,0, 2, 0 ,0 ,1 },
	{ 1, 3, 0, 0, 2, 0 ,0 ,1 },
	{ 1, 5, 0 ,0 ,5, 0 ,0 ,1 },
	{ 1, 1, 1, 1, 1, 1 ,1 ,1 }
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

/*判断某个位置是否有盒子, 这个位置付给position position引用*/
bool IsBox(unsigned int x, unsigned y, int& postion)
{
	for (int  i = 0; i < box_count; i++)
	{
		if (x == boxes[i*2] && y == boxes[i*2+1])
		{
			postion = i;
			return true;
		}
	}
	return false;
}

/*判断是否为终点*/
bool IsFinal(unsigned int x, unsigned int y)
{
	for (int i = 0; i < box_count; i++)
	{
		if (x == finals[i*2] && y == finals[i*2+1])
		{
			return true;
		}
	}
	return false;
}

/*判断是否为墙壁*/
bool IsWall(unsigned int x, unsigned int y)
{
	return MapData[y][x] == WALL;
}

/*判断是否为草地*/
bool IsGrass(unsigned int x, unsigned int y)
{
	return MapData[y][x] == GRASS;
}

/*是否为障碍物*/
bool IsBlock(unsigned int x, unsigned int y)
{
	return IsWall(x, y) || IsGrass(x, y);
}

/*判断盒子是否处于边界*/
bool IsBoxAtBound(unsigned int bx, unsigned int by)
{
	return bx == 1 || bx == MAP_COL - 2 || by == 1 || by == MAP_ROW - 2;
}

/*判断当前箱子是否位于两个障碍物组成的拐角部分*/
bool IsBoxAtCorner(unsigned int bx, unsigned by)
{
	return( (IsBlock(bx - 1, by) || IsBlock(bx + 1, by)) && (IsBlock(bx, by + 1) || IsBlock(bx, by - 1)));
}



/*打印地图数据
	有多個终点, 判断是否是人到终点 还是箱子到达终点了
*/
void PrintMAp(unsigned short mapData[MAP_ROW][MAP_COL])
{
	
	
	for (int i = 0; i < MAP_ROW; i++)
	{
		cout << "\t      ";
		for (int  j = 0; j < MAP_COL; j++)
		{
			if (mapData[i][j] == FINAL)
			{
				if (x == j && y == i)
				{
					cout << setw(2) << STRPLAY;
				}
				else if (IsBox(j, i, postion))
				{
					cout << setw(2) << STRBOX;
				}
				else
				{
					cout << setw(2) << STRFINAL;
				}

			}
			else
				cout << setw(2) << GetData(mapData[i][j]);



			//单独判断是否是为玩家  箱子 
			//玩家
		//	if (x == j && y == i)
			//{
				//cout << setw(2) << STRPLAY;
			//}
			//箱子
			//else if (bx == j && by == i)
			//{
			//	cout << setw(2) << STRBOX;
			//}
			//其他固定位置摆好
			//else
			//{
				//cout << setw(2) << GetData(mapData[i][j]);
			
			//}
		}
		cout << endl;
	}
}

/*改变地图数据*/
void SetMapData(unsigned row, unsigned col, unsigned short data)
{
	MapData[row][col] = data;
}

/*判断游戏是否取得胜利*/
bool IsSuccess(unsigned int finals[], unsigned int boxs[], int count)
{
	for (int i = 0; i < count; i++)
	{
		unsigned tbx = boxes[i*2];
		unsigned tby = boxes[i * 2 + 1];
		bool isMatch = false;
		for (int  j = 0; j < count; j++)
		{
			unsigned tfx = finals[j * 2];
			unsigned tfy = finals[j * 2 + 1];
			if (tbx == tfx && tby == tfy)
			{
				isMatch = true;
				
			}
		}
		if (!isMatch)
		{
			return false;
		}
	}
	return true;
}

/*找到玩家在地图中的位置*/
void FindPlayer(unsigned short mapData[MAP_ROW][MAP_COL])
{
	for (int  i = 0; i < MAP_ROW; i++)
	{
		for (int  j = 0; j < MAP_COL; j++)
		{
			if ( mapData[i][j] == PLAYE)
			{
				x = j;
				y = i;
				break;
			}
		}
		cout << endl;
	}
}

/*找到终点在地图的位置*/
void FindFinal(unsigned short mapData[MAP_ROW][MAP_COL])
{
	int index = 0;
	for (int  i = 0; i < MAP_ROW; i++)
	{
		for (int  j = 0; j < MAP_COL; j++)
		{
			if (mapData[i][j] == FINAL)
			{
				finals[index++] = j;
				finals[index++] = i;
				
			}

		}
		cout << endl;
	}
}

/*找到箱子所在的位置*/
void FindBox(unsigned short mapData[MAP_ROW][MAP_COL])
{
	int index = 0;
	for (int  i = 0; i < MAP_ROW; i++)
	{
		for (int j = 0; j < MAP_COL; j++)
		{
			if (mapData[i][j] == BOX)
			{
				boxes[index++] = j;
				boxes[index++] = i;
			}
		}
		cout << endl;
	}
	box_count = index / 2;
}


/*打印标题*/
void PrintTitle()
{

	cout << "*****************************************" << endl;
	cout << "*             推箱子重构版本版              *" << endl;
	cout << "*****************************************" << endl;
}
/*打印游戏是否是成功与否*/
void PrintTips()
{
	if (isWin)
	{
		cout << "恭喜您闯关成功" ;
	}
	else if (isDead)
	{
		cout << "很抱歉, 您已走入死路" ;
	}
}
 
/*从地图读取各种信息*/
//void ReadMapInfo(unsigned short mapData[MAP_ROW][MAP_COL])
//{
	//for (int i = 0; i < MAP_ROW; i++)
	//{
		//for (int j = 0; j < MAP_COL; j++)
		//{
			//找出玩儿家的地址
		//	if (mapData[i][j] == PLAYE)
			//{
			//	x = j;
			//	y = i;
			//	mapData[i][j] = NUL;
			//} 
			//找到盒子位置
		//	else if (mapData[i][j] == BOX)
		//	{
			//	bx = j;
			//	by = i;
			//	mapData[i][j] = NUL;
			//} 
			//找出终点位置
			//else if (mapData[i][j] == FINAL) 
			//{
				//fx = j;
				//fy = i;
			//}
		//}
	//}
//aa}


/*玩儿家移动*/
void PlayerMove(int dx, int dy) {
	x += dx;
	y += dy;
}

/*四个元素 判断是哪个箱子移动*/
bool BoxMove(unsigned int& bx, unsigned int &by, int dx, int dy)
{
	//bx += dx;
	//by += dy;

	if (IsBlock(bx+dx, by+dy) || IsBox(bx+dx, by+dy, postion))
	{
		return false;
	}
	if (!IsFinal(bx, by))
	{
		SetMapData(by ,bx , NUL);
	}
	bx += dx;
	by += dy;

	if (IsSuccess(finals, boxes, box_count))
	{
		isWin = true;
	}
	else if (IsBoxAtCorner(bx, by) && !IsFinal(bx, by))
	{
		isDead = true;
	}
	if (!IsFinal(bx, by)) 
	{
		SetMapData(by, bx, BOX);
	}
	return true;
}

/*判断在地图中的位置是否可以移动*/



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
	PrintMAp(MapData);
	FindPlayer(MapData);
	FindFinal(MapData);
	FindBox(MapData);
	

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
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, NUL);
			}
			PlayerMove(-1, 0);
			if (IsBlock(x, y))
			{
				PlayerMove(1, 0);
			}
			else if (IsBox(x, y, postion))
			{
				if (!BoxMove(boxes[postion * 2], boxes[postion * 2 + 1], -1, 0))
				{
					PlayerMove(1, 0);
				}
				
			}
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, PLAYE);
			}


			break;
		case D:
			//向右
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, NUL);
			}
			PlayerMove(1, 0);
			if (IsBlock(x, y))
			{
				PlayerMove(-1, 0);
			}
			else if(IsBox(x, y, postion))
			{
				if (!BoxMove(boxes[postion * 2], boxes[postion * 2 + 1], 1, 0))
				{
					PlayerMove(-1, 0);
				}
			}
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, PLAYE);
			}
			break;
		case W:
			//向上
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, NUL);
			}
			PlayerMove(0, -1);
			if (IsBlock(x, y))
			{
				PlayerMove(0, 1);
			}
			else if (IsBox(x, y, postion))
			{
				if (!BoxMove(boxes[postion * 2], boxes[postion * 2 + 1], 0, -1))
				{
					PlayerMove(0, 1);
				}
			}
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, PLAYE);
			}
			break;
		case S:
			//向下
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, NUL);
			}
			PlayerMove(0, 1);
			if (IsBlock(x, y))
			{
				PlayerMove(0, -1);
			}
			else if (IsBox(x, y, postion))
			{
				if (!BoxMove(boxes[postion * 2], boxes[postion * 2 + 1], 0, 1))
				{
					PlayerMove(0, -1);
				}
			}
			if (!IsFinal(x, y))
			{
				SetMapData(y, x, PLAYE);
			}
			break;
		}

		system("cls");
		PrintTitle();
		PrintMAp(MapData);
		PrintTips();
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
