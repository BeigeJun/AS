#pragma once
#include<iostream>
#include"Node.h"
class LinkedList : public Node {
public:
	Node* m_pHead = NULL;
	Node* m_pTail = NULL;
	unsigned int m_uCount = 0;
	Node* m_pCurrent = NULL;
};
