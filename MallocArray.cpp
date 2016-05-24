

# include <iostream>
using namespace std;
# include <assert.h>

# define ROW 3
# define COL 4

//用C语言的方式开辟二维数组
void MallocArray()
{
	//开辟一个中间数组，保存一维数组的地址
	int **p = (int**)malloc(sizeof(int*) * ROW);
	assert(p);
	//分别开辟ROW个一维数组
	for (int i = 0; i < ROW; ++i)
	{
		p[i] = (int*)malloc(sizeof(int) * COL);
		assert(*p);
	
	}

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			p[i][j] = i + j;
		}
	}

	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			printf("%d ",p[i][j]);
		}
		printf("\n");							
	}
	
	//先释放之后开辟的ROW个一维数组
	for(int i = 0; i < ROW; ++i)
	{
		free(p[i]);
	}
	//再释放之前开辟的一维数组
	free(p);
}


//用C++的方式开辟二维数组
//相比C语言的方式，C++直接开辟一个二维数组
void MallocArray()
{
	int (*p)[COL] = new int[ROW][COL];
	
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			p[i][j] = i + j;
		}
	}
	
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout << p[i][j] << " ";
		}
		cout << endl;
	}			
	
	delete[] p;
}


//方法三：
//由于二维数组，在内存中分布也是线性的
//所以，直接用以为数组的形式来开辟和访问
void MallocArray()
{
	int *p = new int[ROW*COL];
	
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			//访问方式
			p[i*COL + j] = i + j;
		}
	}
	
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COL; ++j)
		{
			cout << p[i*COL + j] << " ";
		}
		cout << endl;
	}

	delete []p;
}

