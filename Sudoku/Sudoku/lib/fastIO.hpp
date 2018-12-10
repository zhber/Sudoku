namespace fastIO {
	#define BUF_SIZE 100000
	#define OUT_SIZE 100000
	//fread -> read
	bool IOerror=0;
	struct fileIO{
		FILE *__fastIOInFile=NULL,*__fastIOOutFile=NULL;
		~fileIO(){if (__fastIOInFile != NULL)fclose(__fastIOInFile);if (__fastIOOutFile != NULL)fclose(__fastIOOutFile);}
	}fIO;
	inline bool refreshIn(const char* file){fopen_s(&fIO.__fastIOInFile,file,"r");return fIO.__fastIOInFile!=NULL;}
	inline bool refreshOut(const char* file){fopen_s(&fIO.__fastIOOutFile, file, "w");return fIO.__fastIOOutFile!=NULL;}
	//返回值为是否修改成功
	inline char nc(){static char buf[BUF_SIZE],*p1=buf+BUF_SIZE,*pend=buf+BUF_SIZE;if(p1==pend){p1=buf;pend=buf+fread(buf,1,BUF_SIZE,fIO.__fastIOInFile);if (pend==p1){IOerror=1;return -1;}}return *p1++;}
	inline bool blank(const char &ch){return ch==' '||ch=='\n'||ch=='\r';}
	inline void read(int &x){char ch;while (blank(ch = nc()));(ch<'0'||ch>'9')?IOerror=1:x=ch-'0';}
	//fwrite
	struct Ostream_fwrite {
		char *buf,*p1,*pend;
		Ostream_fwrite(){buf=new char[BUF_SIZE];p1=buf;pend=buf+BUF_SIZE;}
		void out(const char &ch){if(p1==pend){fwrite(buf,1,BUF_SIZE,fIO.__fastIOOutFile);p1=buf;}*p1++=ch;}
		void flush(){if(p1!=buf){fwrite(buf,1,p1-buf,fIO.__fastIOOutFile);p1=buf;}}
		~Ostream_fwrite(){flush();delete[] buf;}
	}Ostream;
	inline void print(const char &x){Ostream.out(x);}
	inline void println(){Ostream.out('\n');}
	inline void flush(){Ostream.flush();}
	#undef BUF_SIZE
	#undef OUT_SIZE
};
