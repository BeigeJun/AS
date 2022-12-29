#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include"Node.h"

typedef struct {
	Node* m_pHead;
	Node* m_pTail;
	unsigned int m_uCount; //0과 양수만 표현 가능
	Node* m_pCurrent;
}LinkedList;

#endif
