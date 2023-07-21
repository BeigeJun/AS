#pragma once
#include<iostream>
#include"Node2.h"
class Node :public Node2 {
public:
	Node* m_pNext = NULL;
	Node* m_Previous = NULL;
	int m_iObject = -1;
	char name[20];
	char adress[100];
	char phone[20];
	Node2* medicine_head = NULL;
	unsigned int medicine_num = 0;
};

