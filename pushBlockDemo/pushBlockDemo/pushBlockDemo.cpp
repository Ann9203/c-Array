// pushBlockDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
   // std::cout << "Hello World!\n"; 
	//推箱子demo
	//根据二维数组拼接推箱子地形图
	//元素 草地  箱子  墙体 小人  重点  空隙
	const char* STRNULL = "  ";//空地
	const char* STRWALL = "口";//墙
	const char* STRGRESS = "▓"; //草地
	const char* STRBOX = "田"; //箱子
	const char* STRPLAY = "♀"; //玩家
	const char* STRFINAL = "◎"; //终点
	const char* map[7][7] =
	{   { STRWALL, STRWALL, STRWALL, STRWALL, STRWALL, STRWALL, STRWALL},
		{ STRWALL, STRNULL, STRNULL, STRNULL, STRPLAY, STRBOX, STRWALL},
		{ STRWALL, STRNULL, STRNULL, STRNULL, STRGRESS, STRNULL, STRWALL},
		{ STRWALL, STRNULL, STRNULL, STRNULL, STRGRESS, STRNULL, STRWALL},
		{ STRWALL, STRNULL, STRNULL, STRWALL, STRNULL, STRNULL, STRWALL},
		{ STRWALL, STRNULL, STRNULL, STRNULL, STRNULL, STRNULL, STRWALL},
		{ STRWALL, STRWALL, STRWALL, STRWALL, STRWALL, STRWALL, STRWALL}
	};
	//打印数组
	cout << setw(50) << endl;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++) {
			cout << map[i][j];
		}
		cout<< setw(50) << endl;
	}
	cout << endl;

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
