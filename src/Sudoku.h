#include "lib/dlx.hpp"
#include "lib/fastIO.hpp"
class Sudoku {
public:
	int d[9][9];//Êý×Ö¾ØÕó
	Sudoku() noexcept;
	void init();
	void out_s();
	void out_c();
};
inline void work_c(int);
inline void work_s();
inline int init(int, char**);

static int block[9][9];
static int a[11] =	 { 0,1,2,3,4,5,6,7,8,9,0 };
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