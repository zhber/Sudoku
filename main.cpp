#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
struct Sudoku{
    int d[10][10];//数字矩阵
    int col[10][10],row[10][10],block[4][4][10];//每行每列每块某个数字有没有出现过
    int ansnum;//解的数量
    vector<pair<int,int> >pos;//记录松弛后还未填好的位置
    #define mem(a) memset(a,0,sizeof a)
    Sudoku()//初始化
    {
    	mem(d);mem(col);mem(row);mem(block);
        pos.clear();ansnum=0;
        char s[15];
        for (int i=1;i<=9;i++)
		{
			scanf("%s",s+1);
			for (int j=1;j<=9;j++)d[i][j]=s[j]-'0';
		}
		for (int i=1;i<=9;i++)
			for (int j=1;j<=9;j++)
				if (d[i][j])col[i][d[i][j]]=row[j][d[i][j]]=block[(i-1)/3+1][(j-1)/3+1][d[i][j]]=1;
    }
    #undef mem
    int findnum(int x,int y)//如果这个位置的值能根据其他位置当前填的值确定就返回这个值，否则返回0
    {
        int ans=0;
        for (int i=1;i<=9;i++)if (!col[x][i]&&!row[y][i]&&!block[(x-1)/3+1][(y-1)/3+1][i])
        {
            if (ans)return 0;
            else ans=i;
        }
        return ans;
    }
    void print()
    {
        for (int i=1;i<=9;i++)
        {
            for (int j=1;j<=9;j++)
				printf("%d",d[i][j]);
			puts("");
        }
    }
    void dfs(int now)
    {
        if (now==pos.size())
		{
            if (!ansnum)print();
            ansnum++;
            return;
		}
        int nowx=pos[now].first,nowy=pos[now].second;
        for (int i=1;i<=9;i++)if (!col[nowx][i]&&!row[nowy][i]&&!block[(nowx-1)/3+1][(nowy-1)/3+1][i])
		{
			col[nowx][i]=row[nowy][i]=block[(nowx-1)/3+1][(nowy-1)/3+1][i]=1;
            d[nowx][nowy]=i;
            dfs(now+1);
            if(ansnum)return;
			col[nowx][i]=row[nowy][i]=block[(nowx-1)/3+1][(nowy-1)/3+1][i]=0;
            d[nowx][nowy]=0;
		}
    }
    void solve()
    {
    	//如果有些位置能直接确定就直接确定，并且确定了之后可能又能确定新的位置
        bool finish=0;
        for (int T=1;T<=81&&!finish;T++)//松弛最多81次
		{
            finish=1;
            for (int i=1;i<=9&&finish;i++)
				for (int j=1;j<=9&&finish;j++)
					if (!d[i][j]&&findnum(i,j))
					{
                        d[i][j]=findnum(i,j);
                        col[i][d[i][j]]=row[j][d[i][j]]=block[(i-1)/3+1][(j-1)/3+1][d[i][j]]=1;
                        finish=0;
					}
		}
		//如果有一些位置不能确定，就爆搜
		for (int i=1;i<=9;i++)
			for (int j=1;j<=9;j++)
				if (!d[i][j])pos.push_back(make_pair(i,j));
        dfs(0);
    }
};
int main(int argc,char** argv)
{
    int T;scanf("%d",&T);
    while (T--)
	{
		Sudoku S;
		S.solve();
	}
}
