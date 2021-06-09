#include "main.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct QNode {
	QElemType data;
	struct QNode* next;
}QNode, * QueuePtr;

typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;

Status InitQueue(LinkQueue* Q);
Status DestroyQueue(LinkQueue* Q);
Status EnQueue(LinkQueue* Q);
Status DeQueue(LinkQueue* Q, QElemType* x);
Status GetHead(LinkQueue Q, QElemType* x);
int QueueLength(LinkQueue Q);
void PrintQueue(LinkQueue Q);

void main() {
	LinkQueue Q;
	QElemType x;
	int i, i_en;
	InitQueue(&Q);
	printf("请输入要入队多少个的数据：");
	scanf("%d", &i_en);
	for (i = 1; i <= i_en; i++)
	{
		printf("第%d个元素：", i);
		scanf("%d", &x);
		EnQueue(&Q, x);
	}
	printf("长度为：%d\n", QueueLength(Q));
	PrintQueue(Q);
	while (Q.front != Q.rear)
	{
		printf("是否出队一个元素（Y--1，N--0）：");
		scanf("%d", &x);
		if (x)
		{
			DeQueue(&Q, &x);
			printf("出队元素为：%d\n", x);
			PrintQueue(Q);
			continue;
		}
		break;
	}
	if (GetHead(Q, &x))
	{
		printf("展示队头元素：%d\n", x);
	}
	else
	{
		printf("队列为空！");
	}
}

Status InitQueue(LinkQueue* Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (Q->front == NULL)
	{
		exit(OVERFLOW);
	}
	Q->front->next = NULL;
	return OK;
}

Status DestroyQueue(LinkQueue* Q) {
	QueuePtr p;
	while (Q->front)
	{
		p = Q->front;
		Q->front = Q->front->next;
		free(p);
	}
	if (!Q->front)
	{
		return OK;
	}
	return ERROR;
}

Status EnQueue(LinkQueue* Q, QElemType x) {
	QueuePtr p = (QueuePtr)malloc(sizeof(QNode));
	if (!p)
	{
		exit(OVERFLOW);
	}
	p->data = x;
	p->next = NULL;
	Q->rear->next = p;
	Q->rear = p;
	return OK;
}

Status DeQueue(LinkQueue* Q, QElemType* x) {
	if (Q->rear == Q->front)
	{
		return ERROR;
	}
	QueuePtr p;
	p = Q->front->next;
	Q->front->next = p->next;
	*x = p->data;
	if (p == Q->rear)
	{
		Q->rear = Q->front;
	}
	free(p);
	return OK;
}

Status GetHead(LinkQueue Q, QElemType* x) {
	if (Q.front == Q.rear)
	{
		return ERROR;
	}
	*x = Q.front->next->data;
	return OK;
}

int QueueLength(LinkQueue Q) {
	int length = 0;
	while (Q.front != Q.rear)
	{
		Q.front = Q.front->next;
		length++;
	}
	return length;
}

void PrintQueue(LinkQueue Q) {
	int i;
	for (i = 1; Q.front != Q.rear; i++)
	{
		Q.front = Q.front->next;
		printf("第%d个元素：%d\n", i, Q.front->data);
	}
}