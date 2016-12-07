#ifndef __SORT_H_
#define __SORT_H_
#include <iostream>
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
			for (j = i; j>0 && A[j - 1] > tmp; j--)//ʹ������������
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
			for (i = increment; i < N; ++i)//����Ĳ�������
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

	void HeapFilerDown(int A[], int i/*���˵ĸ��ڵ�*/, int N)
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
		for (i = N / 2; i >= 0; i--)
		{
			HeapFilerDown(A, i, N);//��������
		}
		for (i = N - 1; i >0; i--)
		{
			Swap(&A[0], &A[i]);//ɾ�����ֵ����ʵ�Ƿŵ�ĩβ��
			HeapFilerDown(A, 0, i);//���¹������ڵ�Ķ����ԣ�Ҳ�����ҳ����ֵ
		}
		return A;
	}

	//int* MergeArray(int a[], int N, int b[], int M, int c[])
	//{
	//	int i, j, k;
	//	i = j = k = 0;
	//	for (; i < N&&j < M; )//��������Ԫ�����αȽϣ���С�ķ�����������飬���ƣ������Ƚ�
	//	{
	//		if (a[i] < b[j])
	//			c[k++] = a[i++];
	//		else
	//			c[k++] = b[j++];
	//	}

	//	for (; i < N;)
	//		c[k++] = a[i++];
	//	for (; j < M;)
	//		c[k++] = b[j++];

	//	return c;
	//}

	void MergeArray(int a[], int first, int mid, int last, int tmp[])
	{
		int i = first, j = mid + 1;
		int m = mid, n = last;
		int k = 0;

		for (; i <= m&&j <= n;)//��������Ԫ�����αȽϣ���С�ķ�����������飬���ƣ������Ƚ�
		{
			if (a[i] < a[j])
				tmp[k++] = a[i++];
			else
				tmp[k++] = a[j++];
		}

		for (; i <= m;)
			tmp[k++] = a[i++];
		for (; j <= n;)
			tmp[k++] = a[j++];

		for (i = 0; i < k; i++)
			a[first + i] = tmp[i];
	}

	void MergeSort(int a[], int first, int last, int tmp[])
	{
		if (first<last)
		{
			int mid = (first + last) / 2;
			MergeSort(a, first, mid, tmp);//������� 
			MergeSort(a, mid+1, last, tmp);//�ұ�����
			MergeArray(a, first, mid, last, tmp);//�ٽ������������кϲ�  
		}
	}

	bool MergeSortMe(int a[], int n)
	{
		int *p = new int[n];
		if (p == NULL)
			return false;
		MergeSort(a, 0, n - 1, p);
		for (int i = 0; i < 9;i++)
		{
			std::cout << a[i] << std::endl;
		}
		delete[] p;
		return true;
	}

	void QuickSort(int s[], int l, int r)
	{
		if (l < r)
		{
			//Swap(s[l], s[(l + r) / 2]); //���м��������͵�һ��������
			int i = l, j = r, x = s[l];
			while (i<j) 
			{
				while (i < j&&s[j] >= x)// ���������ҵ�һ��С��x����
					j--;
				if (l < r)
					s[i++] = s[j];

				while (i < j&&s[i] <= x)// ���������ҵ�һ�����ڵ���x����
					i++;
				if (l < r)
					s[j--] = s[i];
			}
			s[i] = x;//�˳�ʱ��i����j����x�������С� 
			QuickSort(s, l, i - 1);// �ݹ����
			QuickSort(s, i+1, r);
		}
	}

}


#endif // !_INSETION_SORT_
