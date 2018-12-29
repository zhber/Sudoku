#include <cstdio>
#include <cstring>
#include <algorithm>
#include <regex>
#include <ctime>
#include "lib/dlx.hpp"
#include "lib/fastIO.hpp"
using namespace fastIO;
DLX dlx;
static int block[9][9];
static int a[11] = { 0,1,2,3,4,5,6,7,8,9,0 };
static int row[10] = { 0,1,2,3,4,5,6,7,8,9 };
static int col[10] = { 0,1,2,3,4,5,6,7,8,9 };
static int sample[9][9] = { { 1,4,3,6,2,8,5,7,9 },
							{ 5,7,2,1,3,9,4,6,8 },
							{ 9,8,6,7,5,4,2,3,1 },
							{ 3,9,1,5,4,2,7,8,6 },
							{ 4,6,8,9,1,7,3,5,2 },
							{ 7,2,5,8,6,3,9,1,4 },
							{ 2,3,7,4,8,1,6,9,5 },
							{ 6,1,9,2,7,5,8,4,3 },
							{ 8,5,4,3,9,6,1,2,7 } };
class Sudoku {
public:
	int d[9][9];//数字矩阵
	Sudoku()
	{
		memcpy(d, sample, sizeof d);
	}
	void init()//初始化
	{
		register int i, j;
		for (i = 0; i < 9; i++)
			for (j = 0; j < 9; j++)
			{
				if (read(d[i][j]), IOerror)
				{
					if (!i && !j) return;
					else
					{
						puts("Error : not valid input.");
						exit(23333);
					}
				}
			}
	}
	void out_s()//适用于-s操作的输出
	{
		register int i, j;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				print('0' | d[i][j]);
				print(j == 8 ? '\n' : ' ');
			}
		}
	}
	void out_c()//适用于-c操作的输出
	{
		register int i, j;
		for (i = 0; i < 9; i++)
		{
			for (j = 0; j < 9; j++)
			{
				print('0' | a[d[row[i]][col[j]]]);
				print(j == 8 ? '\n' : ' ');
			}
		}
	}
};
inline void work_c(int n)//处理参数是-c的情况
{
	refreshOut("sudoku.txt");
	if (n <= 0)return;
	Sudoku now;
	std::swap(a[1], a[now.d[0][0]]);
	std::swap(a[1], a[2]);
	register int i, j, k;
	for (i = 1; i <= 6; i++)
	{
		for (j = 1; j <= 6; j++)
		{
			for (k = 1; k <= 40320; k++)
			{
				now.out_c();
				if(!(--n))return;else print('\n');
				std::next_permutation(a+1, a + 9);
			}
			std::next_permutation(col + 3, col + 6);
		}
		std::next_permutation(row + 3, row + 6);
	}
}
inline void work_s()//处理参数是-s的情况
{
	refreshOut("sudoku.txt");
	Sudoku now;
	bool isFirstOne = 1;
	do
	{
		if(!isFirstOne)print('\n');
		isFirstOne = 0;
		dlx.init(729, 324);
		now.init();
		if (IOerror)return;

		register int i, _i, __i, j, _j, k, tmp;
		for (i = 0, _i = 0, __i = 0; i < 9; i++, _i += 9,__i += 81)
		{
			for (j = 0, _j = 0; j < 9; j++, _j += 9)
			{
				if (now.d[i][j])
				{
					tmp = __i + _j + now.d[i][j];
					dlx.link(tmp, _i + j + 1);
					dlx.link(tmp, 81 + _i + now.d[i][j]);
					dlx.link(tmp, 162 + _j + now.d[i][j]);
					dlx.link(tmp, 243 + block[i][j] + now.d[i][j]);
				}
				else
				{
					tmp = __i + _j;
					for (k = 1; k <= 9; k++)
					{
						dlx.link(tmp + k, _i + j + 1);
						dlx.link(tmp + k, 81 + _i + k);
						dlx.link(tmp + k, 162 + _j + k);
						dlx.link(tmp + k, 243 + block[i][j] + k);
					}
				}
			}
		}
		dlx.dfs(0);
		if (dlx.cnt != 81)
		{
			puts("Error : no solutions found.");
			exit(23333);
		}
		tmp = 0;
		int tmpx = 0, tmpy = 0;
		for (int i = 0; i < dlx.cnt; i++)
		{
			tmp = dlx.ans[i];
			tmpx = (tmp - 1) / 81; tmp -= tmpx * 81;
			tmpy = (tmp - 1) / 9; tmp -= tmpy * 9;
			now.d[tmpx][tmpy] = tmp;
		}
		now.out_s();
	}while (!IOerror);
}
int num;
inline int init(int argc,char** argv)//初始化 返回值 0: -c  1: -s
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			block[i][j] = i / 3 * 3 + j / 3;
			block[i][j] *= 9;
		}
	}
	if (argc == 1)
	{
		puts("Error : No args found");
		exit(-1);
	}
	if (argv[1][0]=='-'&&(argv[1][1]=='c'|| argv[1][1] == 'C')&&argv[1][2]=='\0')
	{
		if (argc==2)
		{
			puts("Error : no input number.");
			exit(233);
		}
		int len = int(strlen(argv[2]));
		num = 0;
		for (int i = 0; i < len; i++)
		{
			if (argv[2][i]<'0' || argv[2][i]>'9')
			{
				puts("Error : not a valid number.");
				exit(233);
			}
			num = num * 10 + argv[2][i] - '0';
		}
		return 0;
	}else if (argv[1][0] == '-' && (argv[1][1] == 's' || argv[1][1] == 'S') && argv[1][2] == '\0')
	{
		if (argc == 2)
		{
			puts("Error : no input directory.");
			exit(2333);
		}
		std::regex checkPath("^([a-zA-Z]:[/\\\\])?([^/\\\\:\"\\?\\*<>\\|]+[/\\\\])*[^/\\\\:\"\\?\\*<>\\|]*$");
		if (!std::regex_match(argv[2], checkPath))
		{
			puts("Error : wrong file path.");
			exit(2333);
		}
		if (!refreshIn((const char*)argv[2]))
		{
			puts("Error : fail to open the file.");
			exit(2333);
		}
		return 1;
	}
	else
	{
		puts("Error ：no valid command arguments.");
		exit(-1);
	}
}
int main(int argc,char* argv[])
{
	long _begin_time = clock();
	init(argc, argv) ? work_s() : work_c(num);
	long _end_time = clock();
	printf("time = %ld ms\n", _end_time - _begin_time);
	return 0;
}