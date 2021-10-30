#include <stdio.h>
#include <malloc.h>
#define SPageSize 1
#define SRowSize 1
#define SColSize 2
#define PageSize 1
#define RowSize 1
#define ColSize 2

typedef struct _TData {
	double(**RATE)[SColSize];
	int(**MIN_BALANCE)[SColSize];
	int si, sj, sk, SPSize, SRSize, SCSize;
}TData;

TData** inputdata(TData ***Number, int, int, int, int, int, int);
TData& printdata(TData ***Number, int, int, int, int, int, int);

int main(void) {
	//--입력-변수 선언--------------------------
	TData ***Number;
	int i, j, k, PSize, RSize, CSize;
	//입력-변수 초기화--------------------------
	i = j = k = 0;
	PSize = PageSize;
	RSize = RowSize;
	CSize = ColSize;

	Number = (TData***)malloc(sizeof(TData**) * PageSize);
	for (i = 0; i < PSize; i++)
	{
		*(Number + i) = (TData**)malloc(sizeof(TData*) * RowSize);
		for (j = 0; j < RSize; j++)
		{
			*(*(Number + i) + j) = (TData*)malloc(sizeof(TData) * ColSize);
			for (k = 0; k < CSize; k++)
			{
				(*(*(Number+i)+j)+k)->si = (*(*(Number + i) + j) + k)->sj = (*(*(Number + i) + j) + k)->sk = 0;
				(*(*(Number + i) + j) + k)->SPSize = SPageSize;
				(*(*(Number + i) + j) + k)->SRSize = SRowSize;
				(*(*(Number + i) + j) + k)->SCSize = SColSize;

				(*(*(Number+i)+j)+k)->RATE = (double(**)[SColSize])malloc(sizeof(double(*)[SColSize]) * (*(*(Number+i)+j)+k)->SPSize);
				(*(*(Number+i)+j))[k].MIN_BALANCE = (int(**)[SColSize])malloc(sizeof(int(*)[SColSize]) * (*(*(Number + i) + j) + k)->SPSize);
				for (((*(*(Number+i)+j)+k)->si) = 0; ((*(*(Number+i)+j) + k)->si) < (*(*(Number+i)+j) + k)->SPSize; ((*(*(Number+i)+j) + k)->si)++)
				{
					*((*(*(Number+i)+j)+k)->RATE+(*(*(Number+i)+j)+k)->si) = (double(*)[SColSize])malloc(sizeof(double) * (*(*(Number+i)+j)+k)->SRSize * (*(*(Number + i) + j) + k)->SCSize);
					*((*(*(Number+i)+j)+k)->MIN_BALANCE+(*(*(Number+i)+j)+k)->si) = (int(*)[SColSize])malloc(sizeof(int) * (*(*(Number + i) + j) + k)->SRSize * (*(*(Number + i) + j) + k)->SCSize);
				}
			}
		}
	}

	*Number = inputdata(Number, i, j, k, PSize, RSize, CSize);
	**Number = &(printdata(Number, i, j, k, PSize, RSize, CSize));

	for (i = 0; i < PSize; i++)
	{
		for (j = 0; j < RSize; j++)
		{
			for (k = 0; k < CSize; k++)
			{
				for (((*(*(Number+i)+j)+k)->si) = 0; ((*(*(Number + i) + j) + k)->si) < Number[i][j][k].SPSize; ((*(*(Number + i) + j) + k)->si)++)
				{
					free(*((*(*(Number+i)+j))[k].RATE+(*(*(Number+i)+j)+k)->si));
					free(*((*(*(Number+i)+j)+k)->MIN_BALANCE+(*(*(Number+i)+j)+k)->si));
				}
				free((*(*(Number+i)+j))[k].RATE);
				free((*(*(Number + i) + j))[k].MIN_BALANCE);
			}
		}
	}

	return 0;
}

TData** inputdata(TData ***Number, int i, int j, int k, int PSize, int RSize, int CSize)
{
	for (i = 0; i < PSize; i++)
	{
		for (j = 0; j < RSize; j++)
		{
			for (k = 0; k < CSize; k++)
			{
				for (((*(*(Number+i)+j)+k)->si) = 0; ((*(*(Number + i) + j) + k)->si) < (*(*(Number+i)+j)+k)->SPSize; ((*(*(Number + i) + j) + k)->si)++)
				{
					for (((*(*(Number + i) + j) + k)->sj) = 0; ((*(*(Number + i) + j) + k)->sj) < (*(*(Number + i) + j) + k)->SRSize; ((*(*(Number + i) + j) + k)->sj)++)
					{
						for (((*(*(Number + i) + j) + k)->sk) = 0; ((*(*(Number + i) + j) + k)->sk) < (*(*(Number + i) + j) + k)->SCSize; ((*(*(Number + i) + j) + k)->sk)++)
						{
							scanf("%lf", (*(*((*(*(Number + i) + j) + k)->RATE + (*(*(Number + i) + j) + k)->si) + (*(*(Number + i) + j) + k)->sj) + (*(*(Number + i) + j) + k)->sk));
							scanf("%d", (*(*((*(*(Number + i) + j) + k)->MIN_BALANCE + (*(*(Number + i) + j) + k)->si) + (*(*(Number + i) + j) + k)->sj) + (*(*(Number + i) + j) + k)->sk));
						}
					}
				}
			}
		}
	}
	return *Number;
}
TData& printdata(TData ***Number, int i, int j, int k, int PSize, int RSize, int CSize)
{
	for (i = 0; i < PSize; i++)
	{
		for (j = 0; j < RSize; j++)
		{
			for (k = 0; k < CSize; k++)
			{
				for (((*(*(Number + i) + j) + k)->si) = 0; ((*(*(Number + i) + j) + k)->si) < (*(*(Number + i) + j) + k)->SPSize; ((*(*(Number + i) + j) + k)->si)++)
				{
					for (((*(*(Number + i) + j) + k)->sj) = 0; ((*(*(Number + i) + j) + k)->sj) < (*(*(Number + i) + j) + k)->SRSize; ((*(*(Number + i) + j) + k)->sj)++)
					{
						for (((*(*(Number + i) + j) + k)->sk) = 0; ((*(*(Number + i) + j) + k)->sk) < (*(*(Number + i) + j) + k)->SCSize; ((*(*(Number + i) + j) + k)->sk)++)
						{
							printf("%lf\n", *(*(*((*(*(Number + i) + j) + k)->RATE + (*(*(Number + i) + j) + k)->si) + (*(*(Number + i) + j) + k)->sj) + (*(*(Number + i) + j) + k)->sk));
							printf("%d\n", *(*(*((*(*(Number + i) + j) + k)->MIN_BALANCE + (*(*(Number + i) + j) + k)->si) + (*(*(Number + i) + j) + k)->sj) + (*(*(Number + i) + j) + k)->sk));
						}
					}
				}
			}
		}
	}
	return ***Number;
}
