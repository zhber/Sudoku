namespace fastIO {
	struct fileIO {
		FILE *__fastIOInFile=NULL,*__fastIOOutFile=NULL;
		~fileIO(){if(__fastIOInFile!=NULL)fclose(__fastIOInFile);if(__fastIOOutFile!=NULL)fclose(__fastIOOutFile);}
	}fIO;
	inline bool refreshIn(const char* file){fopen_s(&fIO.__fastIOInFile,file,"r");return fIO.__fastIOInFile!=NULL;}
	inline bool refreshOut(const char* file){fopen_s(&fIO.__fastIOOutFile,file,"w");return fIO.__fastIOOutFile!=NULL;}
	//返回值为是否修改成功
	#define BUF_SIZE 100000
	bool IOerror=0;
	//fread
	static char ibuf[BUF_SIZE],*pi=ibuf+BUF_SIZE-1,*iend=ibuf+BUF_SIZE;
	#define GC if(++pi==iend){if((iend=ibuf+fread(pi=ibuf,1,BUF_SIZE,fIO.__fastIOInFile))==ibuf)IOerror=1;}
	inline bool blank(const register char &ch){return ch==' '||ch=='\n'||ch=='\r';}
	inline void read(register int &x){GC;while(blank(*pi))GC;(*pi&48)==48&&(*pi&15)<10?x=*pi&15:IOerror=1;}
	#undef GC
	//fwrite
	static char obuf[BUF_SIZE],*po=obuf;
	const static char *oend=obuf+BUF_SIZE;
	struct Ostream_fwrite {
		char *buf,*p1,*pend;
		Ostream_fwrite(){}
		void out(const register char &ch){*po=ch;if (++po==oend)fwrite(po=obuf,1,BUF_SIZE,fIO.__fastIOOutFile);}
		~Ostream_fwrite(){if(po!=obuf)fwrite(obuf,1,po-obuf,fIO.__fastIOOutFile);}
	}Ostream;
	#define print(x) Ostream.out(x)
	#undef BUF_SIZE
};
