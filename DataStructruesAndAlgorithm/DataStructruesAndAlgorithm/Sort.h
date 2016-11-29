#ifndef __SORT_H_
#define __SORT_H_

#define  LeftChild(i) ((i)*2+1)

namespace SORT
{

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
			A[j] = tmp;
		}
		return A;
	}

	int* ShellSort(int A[], int N)
	{
		int i, j, increment;
		for (increment = N / 2; increment > 0; increment/=2)
		{
			for (i = increment; i < N; ++i)//分组的插入排序
			{
				int tmp = A[i];
				for (j = i; A[j - increment]>tmp && j>=increment; 
					j-=increment)
				{
					A[j] = A[j - increment];
				}
				A[j] = tmp;
			}
		}
		return A;
	}

	void Swap(int *L, int *R)
	{
		int tmp = *L;
		*L = *R;
		*R = tmp;
	}

	void HeapFilerDown(int A[], int i/*下滤的根节点*/, int N)
	{
		int Child;
		int Tmp;
		for (Tmp = A[i]; LeftChild(i) < N; i = Child)
		{
			Child = LeftChild(i);
			if (Child != N - 1 && A[Child + 1]>A[Child])
				Child++;
			if (Tmp < A[Child])
				A[i] = A[Child];
			else
				break;
		}
		A[i] = Tmp;
	}

	int* HeapSort(int A[], int N)
	{
		int i;
		for (i = N / 2; i > 0; i--)
		{
			HeapFilerDown(A, i, N);//构建最大堆
		}
		for (i = N - 1; i > 0; i--)
		{
			Swap(&A[0], &A[i]);//删除最大值（事实是放到末尾）
			HeapFilerDown(A, 0, i);//重新构建根节点的堆序性，也即再找出最大值
		}
		return A;
	}
}


#endif // !_INSETION_SORT_
