#include <sstream>
#include <iostream>

#include "2048.h"

//进度条
void Game_2048::Proc()
{
	std::ostringstream oss;
	oss << "      /\\\\\\\\\\\\\\\\            /\\\\\\\\\\\\\\\\                  /\\\\\\          /\\\\\\\\\\\\\\\\\\\n \
    /\\\\\\//////\\\\\\        /\\\\\\/////\\\\\\\\              /\\\\\\\\\\        /\\\\\\///////\\\\\\\n \
    \\///     \\//\\\\\\      \\/\\\\\\    \\//\\\\\\           /\\\\\\/\\\\\\       \\/\\\\\\     \\/\\\\\\\n \
              /\\\\\\/       \\/\\\\\\    \\//\\\\\\         /\\\\\\/\\/\\\\\\       \\///\\\\\\\\\\\\\\\\\\/\n \
            /\\\\\\//         \\/\\\\\\    \\//\\\\\\       /\\\\\\/  \\/\\\\\\        /\\\\\\///////\\\\\\\n \
           /\\\\\\//           \\/\\\\\\    \\//\\\\\\     /\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    /\\\\\\      \\//\\\\\\ \n \
         /\\\\\\\\/              \\/\\\\\\    \\//\\\\\\    \\//////////\\\\\\///    \\//\\\\\\      /\\\\\\ \n \
        /\\\\\\\\\\\\\\\\\\\\\\\\\\\\       \\///\\\\\\\\\\\\\\\\\\/              \\/\\\\\\        \\///\\\\\\\\\\\\\\\\\\/\n \
        \\//////////////          \\/////////                \\///           \\///////// \n";

	std::string shower(oss.str());
	for (auto e : shower)
	{
		usleep(10000);
		std::cout << e << std::flush;
	}
}
//打印函数
void Game_2048::Echo()
{
	int i = 0;
	int j = 0;
	printf("\033[0;0H");
	for (i = 0; i < _row; ++i)
	{
		printf("---------------------\n");
		for (j = 0; j < _col; ++j)
		{
			if (0 != _map[i][j])
			{
				if (10 > _map[i][j])
					printf("|   %d", _map[i][j]);
				else if (10 <= _map[i][j] && 100 > _map[i][j])
					printf("|  %d", _map[i][j]);
				else if (100 <= _map[i][j] && 1000 > _map[i][j])
					printf("| %d", _map[i][j]);
				else
					printf("|%d", _map[i][j]);
			}
			else
				printf("|    ");
		}
		printf("|\n");
	}
	printf("---------------------\n");
}

//判断是否满

int Game_2048::IsFull()
{
	int i = 0;
	int j = 0;
	for (i = 0; i < _row; ++i)
	{
		for (j = 0; j < _col; ++j)
		{
			if (0 == _map[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}
//判断是否失败 返回0表示未失败 返回1表示失败
int Game_2048::IsDown()
{
	int row = 0;
	int col = 0;
	if (!IsFull())
	{
		return 0;
	}

	int first;
	int second;
	//检测数据周围是否有可以合并的数字
	for (row = 0; row < _row; ++row)
	{
		for (col = 0; col < _col - 1; ++col)
		{
			first = _map[row][col];
			second = _map[row][col + 1];
			if (first == second)
			{
				return 0;
			}
		}
	}
	for (col = 0; col < _col; ++col)
	{
		for (row = 0; row < _row - 1; ++row)
		{
			first = _map[row][col];
			second = _map[row + 1][col];
			if (first == second)
			{
				return 0;
			}
		}
	}

	return 1;
}

//播种
void Game_2048::Seed()
{
	int row = 0;
	int col = 0;
	int flag = 0;
	if (IsDown())
	{
		printf("你输了！\n");
		return;
	}
	srand((unsigned)time(NULL)); //用程序运行时间作为生成随机数种子
	do
	{
		flag = 0;
		row = rand() % _row;
		col = rand() % _col;
		if (0 == _map[row][col])
		{
			_map[row][col] = 2;
		}
		else if (2 == _map[row][col])
		{
			flag = 1;
		}
	} while (!(2 == _map[row][col] && 0 == flag));
}

//移动地图
void Game_2048::MoveMap()
{
	char point = '0';
	if (IsDown())
	{
		printf("你输了！\n");
		return;
	}
	printf("w:up s:down a:left d:right\nq:quit\n");
	//设置不输入回车直接读取字符
	system("stty raw");
	point = getchar();
	system("stty -raw");
	switch (point)
	{
	case 'w':
		IsSeedW();
		MovePointW();
		break;
	case 's':
		IsSeedS();
		MovePointS();
		break;
	case 'a':
		IsSeedA();
		MovePointA();
		break;
	case 'd':
		IsSeedD();
		MovePointD();
		break;
	case 'q':
		printf("quit...\r\n\033[?25h");
		exit(0);
	default:
		printf("非法输入！\n");
		break;
	}
}

struct POS
{
	int row;
	int col;
};

/*
使用两个位置分别标记行不是0的第一位和第二位
若第一位和第二位相等 就让他们相加 结果赋给第一位的位置 并把标记清空 继续向后寻找
若不相等 让把第二位的位置赋给第一位 清楚寻找第二位的标记 继续向后寻找第二位
*/
//向上运算函数W
void Game_2048::CountFuncW()
{
	int flag_1 = 0;
	int flag = 0;
	struct POS pos;
	struct POS first;
	struct POS second;
	//列遍历二位数组 从上向下
	for (pos.col = 0; pos.col < _col; ++pos.col)
	{
		flag = 0;
		for (pos.row = 0; pos.row < _row; ++pos.row)
		{
			if (0 != _map[pos.row][pos.col] && 0 == flag)
			{
				first.col = pos.col;
				first.row = pos.row;
				flag = 1;
			}
			else if (0 != _map[pos.row][pos.col] && 1 == flag)
			{
				second.row = pos.row;
				second.col = pos.col;
				flag_1 = 1;
			}
			if (1 == flag_1)
			{
				if (_map[first.row][first.col] == _map[second.row][second.col])
				{
					_map[first.row][first.col] *= 2;
					_map[second.row][second.col] = 0;
					flag = 0;
					Flag_Seed = 1;
				}

				else
				{
					first.col = second.col;
					first.row = second.row;
				}

				flag_1 = 0;
			}
		}
	}
}
void Game_2048::MovePointW()
{
	struct POS pos;
	struct POS start;
	//运算函数
	CountFuncW();

	//列遍历二维数组 从上向下
	for (start.col = 0; start.col < _col; ++start.col)
	{
		pos.col = start.col;
		pos.row = 0;
		for (start.row = 0; start.row < _row; ++start.row)
		{
			//找出最近的0的位置
			while (0 != _map[pos.row][pos.col] && pos.row < _row)
			{
				++pos.row;
			}
			if (pos.row == _row)
				continue;

			//在pos下面 如果有位置不是0 就把它换到pos的位置
			if (0 != _map[start.row][start.col] && start.row > pos.row)
			{
				_map[pos.row][pos.col] = _map[start.row][start.col];
				_map[start.row][start.col] = 0;
			}
		}
	}
}

void Game_2048::CountFuncS()
{
	int flag_1 = 0;
	int flag = 0;
	struct POS pos;
	struct POS first;
	struct POS second;
	//列遍历二位数组 从上向下
	for (pos.col = _col - 1; pos.col >= 0; --pos.col)
	{
		flag = 0;
		for (pos.row = _row - 1; pos.row >= 0; --pos.row)
		{
			if (0 != _map[pos.row][pos.col] && 0 == flag)
			{
				first.col = pos.col;
				first.row = pos.row;
				flag = 1;
			}
			else if (0 != _map[pos.row][pos.col] && 1 == flag)
			{
				second.row = pos.row;
				second.col = pos.col;
				flag_1 = 1;
			}
			if (1 == flag_1)
			{
				if (_map[first.row][first.col] == _map[second.row][second.col])
				{
					_map[first.row][first.col] *= 2;
					_map[second.row][second.col] = 0;
					flag = 0;
					Flag_Seed = 1;
				}

				else
				{
					first.col = second.col;
					first.row = second.row;
				}

				flag_1 = 0;
			}
		}
	}
}
void Game_2048::MovePointS()
{
	struct POS pos;
	struct POS start;

	CountFuncS();
	//列遍历二维数组 从下向上
	for (start.col = _col - 1; start.col >= 0; --start.col)
	{
		pos.col = start.col;
		pos.row = _row - 1;
		for (start.row = _row - 1; start.row >= 0; --start.row)
		{
			while (0 != _map[pos.row][pos.col] && pos.row >= 0)
			{
				--pos.row;
			}
			if (pos.row == -1)
				continue;
			if (0 != _map[start.row][start.col] && start.row < pos.row)
			{
				_map[pos.row][pos.col] = _map[start.row][start.col];
				_map[start.row][start.col] = 0;
			}
		}
	}
}

void Game_2048::CountFuncA()
{
	int flag_1 = 0;
	int flag = 0;
	struct POS pos;
	struct POS first;
	struct POS second;
	//列遍历二位数组 从上向下
	for (pos.row = 0; pos.row < _row; ++pos.row)
	{
		flag = 0;
		for (pos.col = 0; pos.col < _col; ++pos.col)
		{
			if (0 != _map[pos.row][pos.col] && 0 == flag)
			{
				first.col = pos.col;
				first.row = pos.row;
				flag = 1;
			}
			else if (0 != _map[pos.row][pos.col] && 1 == flag)
			{
				second.row = pos.row;
				second.col = pos.col;
				flag_1 = 1;
			}
			if (1 == flag_1)
			{
				if (_map[first.row][first.col] == _map[second.row][second.col])
				{
					_map[first.row][first.col] *= 2;
					_map[second.row][second.col] = 0;
					flag = 0;
					Flag_Seed = 1;
				}

				else
				{
					first.col = second.col;
					first.row = second.row;
				}

				flag_1 = 0;
			}
		}
	}
}
void Game_2048::MovePointA()
{
	struct POS pos;
	struct POS start;

	CountFuncA();
	//行遍历二维数组 从左向右
	for (start.row = 0; start.row < _row; ++start.row)
	{
		pos.row = start.row;
		pos.col = 0;
		for (start.col = 0; start.col < _col; ++start.col)
		{
			//找出最近的0的位置
			while (0 != _map[pos.row][pos.col] && pos.row < _col)
			{
				++pos.col;
			}
			if (pos.row == _col)
				continue;

			//在pos后面 如果有位置不是0 就把它换到pos的位置
			if (0 != _map[start.row][start.col] && start.col > pos.col)
			{
				_map[pos.row][pos.col] = _map[start.row][start.col];
				_map[start.row][start.col] = 0;
			}
		}
	}
}

void Game_2048::CountFuncD()
{
	int flag_1 = 0;
	int flag = 0;
	struct POS pos;
	struct POS first;
	struct POS second;
	//列遍历二位数组 从上向下
	for (pos.row = _row - 1; pos.row >= 0; --pos.row)
	{
		flag = 0;
		for (pos.col = _col - 1; pos.col >= 0; --pos.col)
		{
			if (0 != _map[pos.row][pos.col] && 0 == flag)
			{
				first.col = pos.col;
				first.row = pos.row;
				flag = 1;
			}
			else if (0 != _map[pos.row][pos.col] && 1 == flag)
			{
				second.row = pos.row;
				second.col = pos.col;
				flag_1 = 1;
			}
			if (1 == flag_1)
			{
				if (_map[first.row][first.col] == _map[second.row][second.col])
				{
					_map[first.row][first.col] *= 2;
					_map[second.row][second.col] = 0;
					flag = 0;
					Flag_Seed = 1;
				}

				else
				{
					first.col = second.col;
					first.row = second.row;
				}
				int Flag_Seed = 1; //设置全局变量作为是否生成种子的标记 0;
			}
		}
	}
}
void Game_2048::MovePointD()
{
	struct POS pos;
	struct POS start;

	CountFuncD();
	//行遍历二维数组 从右向左
	for (start.row = _row - 1; start.row >= 0; --start.row)
	{
		pos.row = start.row;
		pos.col = _col - 1;
		for (start.col = _col - 1; start.col >= 0; --start.col)
		{
			while (0 != _map[pos.row][pos.col] && pos.col >= 0)
			{
				--pos.col;
			}
			if (pos.col == -1)
				continue;
			if (0 != _map[start.row][start.col] && start.col < pos.col)
			{
				_map[pos.row][pos.col] = _map[start.row][start.col];
				_map[start.row][start.col] = 0;
			}
		}
	}
}

//判断是否需要生成种子
void Game_2048::IsSeedW()
{
	int flag_first_0 = 0; //标记是否找到第一个0
	struct POS start;

	//列遍历二维数组 从上向下
	for (start.col = 0; start.col < _col; ++start.col)
	{
		flag_first_0 = 0; //当完成一列的对比时 将flag_first_0该为0
		for (start.row = 0; start.row < _row; ++start.row)
		{
			if (0 == _map[start.row][start.col] && 0 == flag_first_0)
			{
				flag_first_0 = 1; //表示找到第一个0
			}
			else if (0 != _map[start.row][start.col] && 1 == flag_first_0)
			{
				Flag_Seed = 1;
				return;
			}
		}
	}
}
void Game_2048::IsSeedS()
{
	int flag_first_0 = 0; //标记是否找到第一个0
	struct POS start;

	//列遍历二维数组 从上向下
	for (start.col = _col - 1; start.col >= 0; --start.col)
	{
		flag_first_0 = 0; //当完成一列的对比时 将flag_first_0该为0
		for (start.row = _row - 1; start.row >= 0; --start.row)
		{
			if (0 == _map[start.row][start.col] && 0 == flag_first_0)
			{
				flag_first_0 = 1; //表示找到第一个0
			}
			else if (0 != _map[start.row][start.col] && 1 == flag_first_0)
			{
				Flag_Seed = 1;
				return;
			}
		}
	}
}
void Game_2048::IsSeedA()
{
	int flag_first_0 = 0; //标记是否找到第一个0
	struct POS start;

	//列遍历二维数组 从上向下
	for (start.row = 0; start.row < _row; ++start.row)
	{
		flag_first_0 = 0; //当完成一列的对比时 将flag_first_0该为0
		for (start.col = 0; start.col < _col; ++start.col)
		{
			if (0 == _map[start.row][start.col] && 0 == flag_first_0)
			{
				flag_first_0 = 1; //表示找到第一个0
			}
			else if (0 != _map[start.row][start.col] && 1 == flag_first_0)
			{
				Flag_Seed = 1;
				return;
			}
		}
	}
}
void Game_2048::IsSeedD()
{
	int flag_first_0 = 0; //标记是否找到第一个0
	struct POS start;

	//列遍历二维数组 从上向下
	for (start.row = _row - 1; start.row >= 0; --start.row)
	{
		flag_first_0 = 0; //当完成一列的对比时 将flag_first_0该为0
		for (start.col = _col - 1; start.col >= 0; --start.col)
		{
			if (0 == _map[start.row][start.col] && 0 == flag_first_0)
			{
				flag_first_0 = 1; //表示找到第一个0
			}
			else if (0 != _map[start.row][start.col] && 1 == flag_first_0)
			{
				Flag_Seed = 1;
				return;
			}
		}
	}
}

int Game_2048::Game()
{
	Proc();
	sleep(3);
	printf("\033[2J");
	while (!IsDown())
	{
		if (1 == Flag_Seed)
		{
			Seed();
			Flag_Seed = 0;
		}
		Echo();
		MoveMap();
	}
	printf("\033[?25h");
	return 0;
}

bool Game_2048::Init(uint32_t row, uint32_t col)
{
	// init vector
	_row = row;
	_col = col;
	Flag_Seed = 1;

	for (int i = 0; i < _row; ++i)
	{
		_map.push_back(std::vector<int>());
		for (int j = 0; j < _col; ++j)
		{
			_map.back().push_back(0);
		}
	}
	return true;
}
