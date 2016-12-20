#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream>
#include <vector>
using namespace std;

const int MAX = 100;

// 邻接表
class ListDG
{
private:
	// 邻接表中表对应的链表的顶点
	class ENode
	{
	public:
		int ivex;					 // 该边所指向的顶点的位置
		ENode *nextEdge;  // 指向下一条弧的指针
	};

	// 邻接表中表的顶点
	class VNode
	{
	public:
		char data;				 // 顶点信息
		ENode *firstEdge;  // 指向第一条依附该顶点的弧
	};

private:
	int mVexNum;			 // 图的顶点的数目
	int mEdgeNum;		 // 图的边的数目
	VNode mVexs[MAX];
};
#endif