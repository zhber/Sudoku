/*
 * 精确覆盖问题：
 *	 给个01矩阵，选出一些行的集合，使得集合中每一列**恰好**一个1
 *	 用法 bool ans=dlx.dfs(0) 参数是dfs层数不用管
 *	 多组数据要 dlx.init(n,m)
 * 矩阵单点0改1：link(x,y)
 * 输出方案：dlx.ans[k]是取的行,0<=k<dlx.cnt
 */
struct DLX
{
	const static int maxn=740;
	const static int maxm=330;
	const static int maxnode=200010;//矩阵中最多'1'的个数

	#define FF(i,A,s) for(i=A[s];i!=s;i=A[i])

	int L[maxnode],R[maxnode],U[maxnode],D[maxnode];
	int size,col[maxnode],row[maxnode],s[maxm],H[maxn];
	bool vis[maxm];
	int ans[maxn],cnt;
	void init(int n,int m)
	{
		register int i;
		for(i=0;i<=m;i++)
		{
			L[i]=i-1;
			R[i]=i+1;
			U[i]=D[i]=i;
			s[i]=0;
		}
		for(i=1;i<=n;i++)H[i]=-1;
		L[0]=m;
		R[m]=0;
		size=m+1;
		cnt=-1;
	}
	void link(int r, int c)
	{
		U[size]=c;
		D[size]=D[c];
		U[D[c]]=size;
		D[c]=size;
		if(H[r]<0)H[r]=L[size]=R[size]=size;
		else
		{
			L[size]=H[r];
			R[size]=R[H[r]];
			L[R[H[r]]]=size;
			R[H[r]]=size;
		}
		s[c]++;
		col[size]=c;
		row[size]=r;
		size++;
	}

	void del(int c)
	{
		L[R[c]]=L[c];
		R[L[c]]=R[c];
		register int i,j;
		FF(i,D,c)FF(j,R,i)
			U[D[j]]=U[j],D[U[j]]=D[j],--s[col[j]];
	}
	void add(int c)
	{
		R[L[c]]=L[R[c]]=c;
		register int i,j;
		FF(i,U,c)FF(j,L,i)
			++s[col[U[D[j]]=D[U[j]]=j]];
	}
	bool dfs(int k)
	{
		if(!R[0])
		{
			cnt=~cnt?(k<cnt?k:cnt):k;
			return true;
		}
		if(~cnt&&k>=cnt)return false;
		int c=R[0];
		bool mk=0;
		register int i,j;
		FF(i,R,0) if(s[c]>s[i])c=i;
		del(c);
		FF(i,D,c)
		{
			FF(j,R,i) del(col[j]);
			ans[k]=row[i];
			if(dfs(k+1))return true; /* 只要输出一解 */
			FF(j,L,i)add(col[j]);
		}
		add(c);
		return mk;
	}
	#undef FF
};