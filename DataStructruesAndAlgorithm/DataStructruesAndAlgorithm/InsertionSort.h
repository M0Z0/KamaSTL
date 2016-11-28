#ifndef _INSETION_SORT_
#define _INSETION_SORT_

int* InsertionSort(int A[], int cout)
{
	int i, j;
	int tmp;
	for (i = 1; i < cout; ++i)
	{
		tmp = A[i];
		for (j = i; j>0 && A[j - 1] > tmp; j--)//使已有序列有序
		{
			A[j] = A[j - 1];
		}
		A[j] = tmp;//插入
	}
	return A;
}

#endif // !_INSETION_SORT_
