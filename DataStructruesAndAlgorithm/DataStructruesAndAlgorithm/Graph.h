#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream>
#include <cstdio>
using namespace std;

//�ڽӱ�
const int maxn = 100; //��󶥵���
int n, m; //������������

struct arcnode //�ڽӱ߽�� 
{
	int vertex; //���ͷ���ڵĶ�����
	int weight = 0; //Ȩ
	arcnode *next;
	arcnode() {}
	arcnode(int v) :vertex(v), next(NULL) {}
};

struct  vernode //���㣬��ͷ��㼯
{
	int vex; //��ǰ������
	arcnode *firarc; //�ڽӱ�ָ��
}Ver[maxn];

void Init()
{
	for (int i = 1; i <= n; i++)
	{
		Ver[i].vex = i;
		Ver[i].firarc = NULL;
	}
}
#endif