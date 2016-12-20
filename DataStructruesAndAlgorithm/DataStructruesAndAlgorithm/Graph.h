#ifndef _GRAPH_H_
#define _GRAPH_H_

#include<iostream>
#include <vector>
using namespace std;

const int MAX = 100;

// �ڽӱ�
class ListDG
{
private:
	// �ڽӱ��б��Ӧ������Ķ���
	class ENode
	{
	public:
		int ivex;					 // �ñ���ָ��Ķ����λ��
		ENode *nextEdge;  // ָ����һ������ָ��
	};

	// �ڽӱ��б�Ķ���
	class VNode
	{
	public:
		char data;				 // ������Ϣ
		ENode *firstEdge;  // ָ���һ�������ö���Ļ�
	};

private:
	int mVexNum;			 // ͼ�Ķ������Ŀ
	int mEdgeNum;		 // ͼ�ıߵ���Ŀ
	VNode mVexs[MAX];
};
#endif