#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<pair<ull,ull>,pair<ull,ull> > pa;
namespace fastIO {
	struct fileIO {
		FILE *__fastIOInFile=NULL,*__fastIOOutFile=NULL;
		~fileIO(){if(__fastIOInFile!=NULL)fclose(__fastIOInFile);if(__fastIOOutFile!=NULL)fclose(__fastIOOutFile);}
	}fIO;
	inline bool refreshIn(const char* file){fIO.__fastIOInFile=fopen(file,"r");return fIO.__fastIOInFile!=NULL;}
	inline bool refreshOut(const char* file){fIO.__fastIOInFile=fopen(file,"w");return fIO.__fastIOOutFile!=NULL;}
	//返回值为是否修改成功
	#define BUF_SIZE 100000
	//======================fread======================
	bool IOerror=0;
	static char ibuf[BUF_SIZE],*pi=ibuf+BUF_SIZE-1;
	const static char *iend=ibuf+BUF_SIZE;
	#define GC if(++pi==iend){if((iend=ibuf+fread(pi=ibuf,1,BUF_SIZE,fIO.__fastIOInFile))==ibuf)IOerror=1;}
	inline bool blank(const register char &ch){return ch==' '||ch=='\n'||ch=='\r';}
	inline void read(register int &x){GC;while(blank(*pi))GC;(*pi&48)==48&&(*pi&15)<10?x=*pi&15:IOerror=1;}
	#undef GC
	//======================fwrite=====================
	static char obuf[BUF_SIZE],*po=obuf;
	const static char *oend=obuf+BUF_SIZE;
	struct Ostream_fwrite {
		void out(const register char &ch){*po=ch;if (++po==oend)fwrite(po=obuf,1,BUF_SIZE,fIO.__fastIOOutFile);}
		~Ostream_fwrite(){if(po!=obuf)fwrite(obuf,1,po-obuf,fIO.__fastIOOutFile);}
	}Ostream;
	#define print(x) Ostream.out(x)
	#undef BUF_SIZE
};
using namespace fastIO;
class Sudoku {
public:
	int d[9][9];//数字矩阵
	Sudoku()
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
						exit(0);
					}
				}
			}
	}
};
int x[81],y[81];
int rnd(int mod){return((ll)rand()<<32^(ll)rand()<<16^rand())%mod;}
inline void init(int argc,char** argv)
{
    assert(argc==2);
    std::regex checkPath("^([a-zA-Z]:[/\\\\])?([^/\\\\:\"\\?\\*<>\\|]+[/\\\\])*[^/\\\\:\"\\?\\*<>\\|]*$");
    if (!std::regex_match(argv[1], checkPath))
	{
		puts("Error : wrong file path.");
		exit(0);
	}
	if (!refreshIn((const char*)argv[1]))
	{
		puts("Error : fail to open the file.");
		exit(0);
	}
	for (int i=0;i<81;i++)x[i]=i/9,y[i]=i%9;
    for (int i=0;i<1000;i++)
	{
        int p=rnd(81),q=rnd(81);
        swap(x[p],y[p]);
        swap(x[q],y[q]);
	}
}
pa hsh[1000010];int len;
int main(int argc,char** argv)
{
    init(argc,argv);
	while (!IOerror)
	{
		Sudoku now;
        ull a=0,b=0,c=0,d=0;
        for (int i=0;i<9;i++)
            for (int j=0;j<9;j++)
			{
                a=a*17+now.d[i][j];
			}
        for (int j=0;j<9;j++)
            for (int i=0;i<9;i++)
			{
                b=b*23+now.d[i][j];
			}
        for (int block=0;block<9;block++)
            for (int i=block%3*3;i<block%3*3+3;i++)
				for (int j=block/3*3;j<block/3*3+3;j++)
				{
					c=c*29+now.d[i][j];
				}
		for (int i=0;i<81;i++)
		{
            d=d*31+now.d[x[i]][y[i]];
		}
        hsh[len++]=make_pair(make_pair(a,b),make_pair(c,d));
	}
    sort(hsh,hsh+len);
	assert(int(unique(hsh,hsh+len)-hsh)==len);
}