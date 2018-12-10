#include<bits/stdc++.h>
using namespace std;
int main()
{
    freopen("sudoku.in","w",stdout);
    for (int i=1;i<=100000;i++)
	{
        puts("0 0 0 0 8 0 0 0 0");
		puts("0 2 7 0 0 0 3 4 0");
		puts("8 9 0 4 0 7 0 1 5");
		puts("6 0 0 2 0 5 0 0 9");
		puts("0 8 0 0 0 0 0 3 0");
		puts("2 0 0 8 0 9 0 0 4");
		puts("1 4 0 7 0 6 0 9 3");
		puts("0 6 5 0 0 0 2 7 0");
		puts("0 0 0 0 9 0 0 0 0");
        if (i!=100000)puts("");
	}
    return 0;
}