#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream>
#include <cstdio>
using namespace std;

//邻接表
const int maxn = 100; //最大顶点数
int n, m; //顶点数，边数

struct arcnode //邻接边结点 
{
	int vertex; //与表头相邻的顶点编号
	int weight = 0; //权
	arcnode *next;
	arcnode() {}
	arcnode(int v) :vertex(v), next(NULL) {}
};

struct  vernode //顶点，表头结点集
{
	int vex; //当前顶点编号
	arcnode *firarc; //邻接表指针
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