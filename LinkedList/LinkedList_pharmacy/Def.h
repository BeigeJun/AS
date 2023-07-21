#pragma once
#include<iostream>
#include<cstring> 
#include"LinkedList.h"
using namespace std;
class DEF : public LinkedList {
public:
	LinkedList* Create();
	void Destroy(LinkedList* _ptList);
	Node* GetNode();
	Node2* GetNode2();
	Node* Read(LinkedList* _ptList);
	void Traversal(LinkedList* _ptList);
	Node* AppendFromHead(LinkedList* _ptList);
	Node* AppendFromTail(LinkedList* _ptList);
	Node* DeleteFromHead(LinkedList* _ptList);
	Node* DeleteFromHead2(Node* base);
	Node2* AppendFromHead2(Node* base);
	Node* InsertBefor(LinkedList* _ptList);
	Node* InsertAfter(LinkedList* _ptList);
	Node* DeleteFromTail(LinkedList* _ptList);
	void DeleteAll2(Node* base);
	void DeleteAll(LinkedList* _ptList);
	Node* Delete(LinkedList* _ptList);
	Node* Delete2(LinkedList* _ptList);
	Node* Modify(LinkedList* _ptList);
	Node* Modify2(LinkedList* _ptList);
	Node* veiw(LinkedList* _ptList);
	void SortByBubble(LinkedList* _ptList);
	int SortByInsertion(LinkedList* _ptList);
	void SortBySelection(LinkedList* _ptList);
	int NUM();
	int Gumsa(Node* base, Node2* pointer);
	Node* LinearSearchByUnique(LinkedList* _ptList);
	Node* LinearSearchByDuplicate(LinkedList* _ptList);
	Node* BinarySearchByUnique(LinkedList* _ptList, char target[], int start, int end);
	Node* BinarySearchByDuplicate(LinkedList* _ptList, char target[], int start, int end);
	int menu();
};
LinkedList* DEF::Create()
{
	LinkedList* _ptList = new LinkedList;
	_ptList->m_pHead = _ptList->m_pTail;
	_ptList->m_pTail = _ptList->m_pHead;
	_ptList->m_pCurrent = NULL;
	_ptList->m_uCount = 0;
	return _ptList;
}
void DEF::Destroy(LinkedList* _ptList)
{
	delete(_ptList);
}
Node* DEF::GetNode()
{
	Node* pNode = new Node;
	pNode->m_pNext = pNode;
	pNode->m_Previous = pNode;
	cout << "이름: ";
	cin >> pNode->name;
	cout << "나이: ";
	while (pNode->m_iObject == -1) {
		pNode->m_iObject = NUM();
	}
	cout << "전화번호: ";
	cin >> pNode->phone;
	cout << "주소: ";
	cin >> pNode->adress;
	AppendFromHead2(pNode);
	return pNode;
}
Node2* DEF::GetNode2()
{
	Node2* pNode = new Node2;
	pNode->m_pNext = pNode;
	pNode->m_Previous = pNode;
	cout << "약 이름: ";
	cin >> pNode->name;
	return pNode;
}
Node* DEF::Read(LinkedList* _ptList)
{
	char a[20];
	cout << "이름을 입력하시오: ";
	cin >> a;
	Node* pointer = new Node;
	pointer = _ptList->m_pHead;
	for (int i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, a) == 0)
		{
			cout << "나이: " << pointer->m_iObject << " 전화번호: " << pointer->phone << " 주소: " << pointer->adress << endl;
			cout << "약 :";
			Node2* pointer2 = pointer->medicine_head;
			for (int i = 0; i != pointer->medicine_num; i++)
			{
				cout << pointer2->name << " ";
				pointer2 = pointer2->m_pNext;
			}
			cout << endl;
			pointer2 = NULL;
			pointer = NULL;
			free(pointer);
			free(pointer2);
			return 0;
		}
		pointer = pointer->m_pNext;
	}
	cout << a << " 저장된 손님의 정보가 없습니다." << endl;
	pointer = NULL;
	free(pointer);
	return 0;
}
void DEF::Traversal(LinkedList* _ptList)
{
	_ptList->m_pCurrent = _ptList->m_pHead;
	for (int i = 0; i != _ptList->m_uCount; i++) {

		cout << _ptList->m_pCurrent->name << " ";
		_ptList->m_pCurrent = _ptList->m_pCurrent->m_pNext;
	}
	cout << endl;
}
Node* DEF::AppendFromHead(LinkedList* _ptList)
{
	_ptList->m_pCurrent = GetNode();

	if (_ptList->m_pHead) {
		_ptList->m_pCurrent->m_pNext = _ptList->m_pHead;
		_ptList->m_pHead->m_Previous = _ptList->m_pCurrent;
	}
	else
		_ptList->m_pTail = _ptList->m_pCurrent;

	_ptList->m_pHead = _ptList->m_pCurrent;
	(_ptList->m_uCount)++;
	return 0;
}
Node* DEF::AppendFromTail(LinkedList* _ptList)
{
	_ptList->m_pCurrent = GetNode();
	if (_ptList->m_pTail) {
		_ptList->m_pTail->m_pNext = _ptList->m_pCurrent;
		_ptList->m_pCurrent->m_Previous = _ptList->m_pTail;
	}
	else
		_ptList->m_pHead = _ptList->m_pCurrent;

	_ptList->m_pTail = _ptList->m_pCurrent;
	(_ptList->m_uCount)++;
	return 0;
}
Node2* DEF::AppendFromHead2(Node* base)
{
	int num = 0;
	cout << "추가 할 약의 갯수를 입력하시오:";
	num = NUM();
	while (1)
	{
		if (num == -1)
		{
			num = NUM();
		}
		else { break; }
	}
	for (int i = 0; i != num; i++)
	{
		Node2* pointer = GetNode2();
		if (Gumsa(base, pointer) == -1)
		{
			free(pointer);
			continue;
		}
		else
		{
			Node2* pre_pointer;
			if (base->medicine_num == 0)
			{
				base->medicine_head = pointer;
				(base->medicine_num)++;
			}
			else
			{
				pre_pointer = base->medicine_head;
				for (int i = 1; i != base->medicine_num; i++)
				{
					pre_pointer = pre_pointer->m_pNext;
				}
				pre_pointer->m_pNext = pointer;
				pointer->m_Previous = pre_pointer;
				base->medicine_num = base->medicine_num + 1;
			}
		}
	}
	return 0;
}
Node* DEF::DeleteFromHead(LinkedList* _ptList)
{
	if (_ptList->m_uCount == 0)
	{
		cout << "정보가 없습니다" << endl;
	}
	else if (_ptList->m_uCount == 1)
	{
		Node* pointer;
		pointer = _ptList->m_pHead;
		free(pointer);
		_ptList->m_pHead = NULL;
		_ptList->m_pTail = NULL;
		_ptList->m_pCurrent = NULL;
		_ptList->m_uCount = 0;
	}
	else {
		Node* pointer;
		pointer = _ptList->m_pHead;
		pointer = pointer->m_pNext;
		pointer->m_Previous = pointer;
		pointer = _ptList->m_pHead;
		_ptList->m_pHead = pointer->m_pNext;
		(_ptList->m_uCount)--;
		free(pointer);
	}
	return 0;
}
Node* DEF::DeleteFromHead2(Node* base)
{
	if (base->medicine_num == 1)
	{
		Node2* pointer;
		pointer = base->medicine_head;
		free(pointer);
		base->medicine_head = NULL;
		base->medicine_num = 0;
	}
	else {
		Node2* pointer;
		pointer = base->medicine_head;
		pointer = pointer->m_pNext;
		pointer->m_Previous = pointer;
		pointer = base->medicine_head;
		base->medicine_head = pointer->m_pNext;
		(base->medicine_num)--;
		free(pointer);
	}
	return 0;
}
Node* DEF::DeleteFromTail(LinkedList* _ptList)
{
	if (_ptList->m_uCount == 0)
	{
		cout << "정보가 없습니다" << endl;
	}
	else if (_ptList->m_uCount == 1)
	{
		Node* pointer;
		pointer = _ptList->m_pHead;
		free(pointer);
		_ptList->m_pHead = NULL;
		_ptList->m_pTail = NULL;
		_ptList->m_pCurrent = NULL;
		_ptList->m_uCount = 0;
	}
	else {
		Node* pointer;
		pointer = _ptList->m_pTail;
		pointer = pointer->m_Previous;
		pointer->m_pNext = pointer;
		pointer = _ptList->m_pTail;
		_ptList->m_pTail = pointer->m_Previous;
		free(pointer);
		(_ptList->m_uCount)--;
	}
	return 0;
}
void DEF::DeleteAll2(Node* base)
{
	Node2* pointer = base->medicine_head;
	for (int i = base->medicine_num; i > 1; i--)
	{
		pointer = pointer->m_pNext;
		free(pointer->m_Previous);
	}
	free(pointer);
	base->medicine_head = NULL;
	base->medicine_num = 0;
}
void DEF::DeleteAll(LinkedList* _ptList)
{
	Node* pointer = _ptList->m_pHead;
	for (int i = _ptList->m_uCount; i > 1; i--)
	{
		pointer = pointer->m_pNext;
		DeleteAll2(pointer->m_Previous);
		free(pointer->m_Previous);
	}
	free(pointer);
	_ptList->m_pCurrent = NULL;
	_ptList->m_pHead = NULL;
	_ptList->m_pTail = NULL;
	_ptList->m_uCount = 0;
}
Node* DEF::InsertBefor(LinkedList* _ptList)
{
	cout << "추가할 위치를 입력하시오 : ";
	int num = -1;
	while (num == -1) {
		num = NUM();
	}
	if (_ptList->m_uCount < 1)
	{
		cout << "저장된 손님의 정보가 없습니다." << endl;
		return 0;
	}
	if (_ptList->m_uCount < num)
	{
		cout << num << "번째 손님은 없습니다." << endl;
		return 0;
	}
	if (num == 1)
	{
		AppendFromHead(_ptList);
	}
	else {
		Node* pointer = _ptList->m_pHead;
		Node* pointer_before;
		Node* New = GetNode();
		for (int i = 0; i != num - 1; i++)
		{
			pointer = pointer->m_pNext;
		}
		pointer_before = pointer->m_Previous;
		New->m_pNext = pointer;
		pointer->m_Previous = New;
		New->m_Previous = pointer_before;
		pointer_before->m_pNext = New;
		(_ptList->m_uCount)++;
	}
	return 0;
}
Node* DEF::InsertAfter(LinkedList* _ptList)
{
	cout << "추가할 위치를 입력하시오 : ";
	int num = -1;
	while (num == -1) {
		num = NUM();
	}
	if (_ptList->m_uCount < 1)
	{
		cout << "저장된 손님의 정보가 없습니다." << endl;
		return 0;
	}
	else if (_ptList->m_uCount < num)
	{
		cout << num << "번째 손님은 없습니다." << endl;
		return 0;
	}
	if (num == _ptList->m_uCount)
	{
		AppendFromTail(_ptList);
	}
	else {
		Node* pointer = _ptList->m_pHead;
		Node* pointer_next;
		Node* New = GetNode();
		for (int i = 0; i != num - 1; i++)
		{
			pointer = pointer->m_pNext;
		}
		pointer_next = pointer->m_pNext;
		New->m_pNext = pointer_next;
		pointer->m_pNext = New;
		New->m_Previous = pointer;
		pointer_next->m_Previous = New;
		(_ptList->m_uCount)++;
	}
	return 0;
}
Node* DEF::Delete(LinkedList* _ptList)
{
	char name[20];
	int count = 1;
	cout << "삭제할 손님의 이름을 입력하시오";
	cin >> name;
	Node* SomeThing;
	Node* SomeThingBefore;
	Node* SomeThingNext;
	if (_ptList->m_uCount == 0)
	{
		cout << "저장된 정보가 없습니다." << endl;
	}
	else {
		SomeThing = _ptList->m_pHead;
		for (int i = 0; i != _ptList->m_uCount; i++)
		{
			if (strcmp(SomeThing->name, name) == 0)
			{
				if (_ptList->m_uCount == count) {
					DeleteFromTail(_ptList);
					return 0;
				}
				else if (count == 1) {
					DeleteFromHead(_ptList);
					return 0;
				}
				else {
					SomeThingBefore = SomeThing->m_Previous;
					SomeThingNext = SomeThing->m_pNext;
					SomeThingBefore->m_pNext = SomeThingNext;
					SomeThingNext->m_Previous = SomeThingBefore;
					DeleteAll2(SomeThing);
					SomeThingBefore = NULL;
					SomeThingNext = NULL;
					free(SomeThingBefore);
					free(SomeThingNext);
					free(SomeThing);
					(_ptList->m_uCount)--;
					return 0;
				}
			}
			SomeThing = SomeThing->m_pNext;
			count++;
		}
		cout << "해당 손님이 저장되어있지 않습니다.";
		return 0;
	}
}
Node* DEF::Delete2(LinkedList* _ptList)
{
	char name1[20];
	int count1 = 1;
	cout << "이름을 입력하시오 :";
	cin >> name1;
	Node* pointer = new Node;
	pointer = _ptList->m_pHead;
	if (_ptList->m_uCount == 0)
	{
		cout << name1 << " 저장된 손님의 정보가 없습니다." << endl;
		pointer = NULL;
		free(pointer);
		return 0;
	}
	for (int i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, name1) == 0)
		{
			break;
		}
		pointer = pointer->m_pNext;
		count1++;
	}
	if (count1 > _ptList->m_uCount)
	{
		cout << name1 << "손님이 저장되어있지 않습니다." << endl;
		pointer = NULL;
		free(pointer);
		return 0;
	}

	char name[20];
	int count = 1;
	cout << "약의 이름을 입력하시오 :";
	cin >> name;
	Node2* SomeThing;
	Node2* SomeThingBefore;
	Node2* SomeThingNext;
	if (pointer->medicine_num == 0)
	{
		cout << "저장된 정보가 없습니다." << endl;
	}
	else {
		SomeThing = pointer->medicine_head;
		for (int i = 0; i != pointer->medicine_num; i++)
		{
			if (strcmp(SomeThing->name, name) == 0)
			{
				if (pointer->medicine_num == count) {
					SomeThing = SomeThing->m_Previous;
					free(SomeThing->m_pNext);
					(pointer->medicine_num)--;
					return 0;
				}
				else if (count == 1) {
					DeleteFromHead2(pointer);
					return 0;
				}
				else {
					SomeThingBefore = SomeThing->m_Previous;
					SomeThingNext = SomeThing->m_pNext;
					SomeThingBefore->m_pNext = SomeThingNext;
					SomeThingNext->m_Previous = SomeThingBefore;
					SomeThingBefore = NULL;
					SomeThingNext = NULL;
					free(SomeThingBefore);
					free(SomeThingNext);
					free(SomeThing);
					(pointer->medicine_num)--;
					return 0;
				}
			}
			SomeThing = SomeThing->m_pNext;
			count++;
		}
		cout << "해당 약이 저장되어있지 않습니다.";
		return 0;
	}
}
Node* DEF::Modify(LinkedList* _ptList)
{

	char a[20];
	cout << "이름을 입력하시오: ";
	cin >> a;
	Node* pointer = new Node;
	pointer = _ptList->m_pHead;
	for (int i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, a) == 0)
		{
			cout << "변경전:" << endl;
			cout << "나이: " << pointer->m_iObject << " 전화번호: " << pointer->phone << " 주소: " << pointer->adress << endl;
			cout << "변경할 내용을 입력하시오:" << endl;
			cout << "이름: ";
			cin >> pointer->name;
			cout << "나이: ";
			pointer->m_iObject = NUM();
			if (pointer->m_iObject == -1)
			{
				while (pointer->m_iObject == -1)
				{
					pointer->m_iObject = NUM();
				}
			}
			cout << "전화번호: ";
			cin >> pointer->phone;
			cout << "주소: ";
			cin >> pointer->adress;
			pointer = NULL;
			free(pointer);
			return 0;
		}
		pointer = pointer->m_pNext;
	}
	cout << a << " 손님의 정보가 없습니다." << endl;
	pointer = NULL;
	free(pointer);
	return 0;
}
Node* DEF::Modify2(LinkedList* _ptList)
{

	char a[20];
	cout << "이름을 입력하시오: ";
	cin >> a;
	Node* pointer = new Node;
	pointer = _ptList->m_pHead;
	for (int i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, a) == 0)
		{
			Node2* M_pointer = pointer->medicine_head;
			int a;
			cout << "변경전:" << endl;
			for (int i = 0; i < pointer->medicine_num; i++)
			{
				cout << M_pointer->name << " ";
				M_pointer = M_pointer->m_pNext;
			}
			cout << endl;
			M_pointer = NULL;
			free(M_pointer);
			AppendFromHead2(pointer);

			pointer = NULL;
			free(pointer);
			return 0;
		}
		pointer = pointer->m_pNext;
	}
	cout << a << " 손님의 정보가 없습니다." << endl;
	pointer = NULL;
	free(pointer);
	return 0;
}
Node* DEF::veiw(LinkedList* _ptList)
{

	Node* pointer = new Node;
	Node2* pointer2 = new Node2;
	pointer = _ptList->m_pHead;
	for (int i = 0; i != _ptList->m_uCount; i++)
	{
		cout << "이름: " << pointer->name << " 나이: " << pointer->m_iObject << "전화번호: " << pointer->phone << " 주소: " << pointer->adress << endl;
		cout << "약 :";
		pointer2 = pointer->medicine_head;
		for (int i = 0; i != pointer->medicine_num; i++)
		{
			cout << pointer2->name << " ";
			pointer2 = pointer2->m_pNext;
		}
		cout << endl;
		pointer = pointer->m_pNext;
	}
	pointer2 = NULL;
	pointer = NULL;
	free(pointer);
	free(pointer2);
	return 0;
}
void DEF::SortByBubble(LinkedList* _ptList)
{

	for (int i = 1; i != _ptList->m_uCount; i++)
	{
		if (_ptList->m_uCount == 0)
		{
			cout << "저장된 데이터가 없습니다." << endl;
			break;
		}
		if (_ptList->m_uCount == 1)
		{
			break;
		}
		if (_ptList->m_uCount == 2)
		{
			Node* pointer = _ptList->m_pHead;
			Node* pointerNext = pointer->m_pNext;
			if (pointer->name < pointerNext->name)
			{
				_ptList->m_pHead = pointerNext;
				_ptList->m_pTail = pointer;
				pointerNext->m_Previous = pointerNext;
				pointerNext->m_pNext = pointer;
				pointer->m_Previous = pointerNext;
				pointer->m_pNext = pointer;
				break;
			}
			break;
		}
		Node* pointerPre = _ptList->m_pHead;
		Node* pointer = _ptList->m_pHead->m_pNext;
		for (int j = 1; j != _ptList->m_uCount; j++)
		{
			if (pointerPre->name[0] > pointer->name[0])
			{
				if (pointerPre == _ptList->m_pHead)
				{
					Node* pointerNext = pointer->m_pNext;
					_ptList->m_pHead = pointer;
					pointer->m_Previous = pointer;
					pointer->m_pNext = pointerPre;

					pointerPre->m_Previous = pointer;
					pointerPre->m_pNext = pointerNext;

					pointerNext->m_Previous = pointerPre;

					pointer = pointer->m_pNext;
					pointerPre = pointerPre->m_Previous;
				}
				else if (pointer == _ptList->m_pTail)
				{
					Node* pointerPrePre = pointerPre->m_Previous;
					_ptList->m_pTail = pointerPre;
					pointerPre->m_Previous = pointer;
					pointerPre->m_pNext = pointerPre;

					pointer->m_Previous = pointerPrePre;
					pointer->m_pNext = pointerPre;

					pointerPrePre->m_pNext = pointer;

					pointer = pointer->m_pNext;
					pointerPre = pointerPre->m_Previous;
				}
				else
				{
					Node* pointerPrePre = pointerPre->m_Previous;
					Node* pointerNext = pointer->m_pNext;
					pointer->m_pNext = pointerPre;
					pointer->m_Previous = pointerPrePre;

					pointerPre->m_pNext = pointerNext;
					pointerPre->m_Previous = pointer;

					pointerPrePre->m_pNext = pointer;
					pointerNext->m_Previous = pointerPre;

					pointer = pointer->m_pNext;
					pointerPre = pointerPre->m_Previous;
				}
			}
			pointerPre = pointerPre->m_pNext;
			pointer = pointer->m_pNext;
		}
	}
}
int DEF::SortByInsertion(LinkedList* _ptList)
{
	if (_ptList->m_uCount == 0)
	{
		cout << "저장된 손님의 정보가 없습니다." << endl;
		return 0;
	}
	Node* pointer = _ptList->m_pHead;
	for (int i = 1; i < _ptList->m_uCount; i++)
	{
		if (_ptList->m_uCount == 1)
		{
			break;
		}
		Node* Next_pointer = pointer->m_pNext;
		for (int k = 1; k < _ptList->m_uCount; k++)
		{
			if (strcmp(pointer->name, Next_pointer->name) == 1)
			{
				int temp;
				unsigned int temp1;
				char temp2[20];
				char temp3[30];
				char temp4[20];
				Node2* temp5;
				//나이
				temp = pointer->m_iObject;
				pointer->m_iObject = Next_pointer->m_iObject;
				Next_pointer->m_iObject = temp;
				//약갯수
				temp1 = pointer->medicine_num;
				pointer->medicine_num = Next_pointer->medicine_num;
				Next_pointer->medicine_num = temp1;
				//이름
				strcpy(temp2, pointer->name);
				strcpy(pointer->name, Next_pointer->name);
				strcpy(Next_pointer->name, temp2);
				//주소
				strcpy(temp3, pointer->adress);
				strcpy(pointer->adress, Next_pointer->adress);
				strcpy(Next_pointer->adress, temp3);
				//전화번호
				strcpy(temp4, pointer->phone);
				strcpy(pointer->phone, Next_pointer->phone);
				strcpy(Next_pointer->phone, temp4);
				//약 리스트
				temp5 = pointer->medicine_head;
				pointer->medicine_head = Next_pointer->medicine_head;
				Next_pointer->medicine_head = temp5;
			}
			Next_pointer = Next_pointer->m_pNext;
		}
		pointer = pointer->m_pNext;
	}
	return 0;
}
void DEF::SortBySelection(LinkedList* _ptList)
{

	for (int z = 0; z < _ptList->m_uCount - 1; z++)
	{
		if (_ptList->m_uCount == 0)
		{
			cout << "저장된 손님의 정보가 없습니다." << endl;
			break;
		}
		if (_ptList->m_uCount == 1)
		{
			break;
		}
		Node* pointer = _ptList->m_pHead;
		Node* head = _ptList->m_pHead;
		char Min[20];

		for (int x = 0; x < z; x++)
		{
			pointer = pointer->m_pNext;
		}
		strcpy(Min, pointer->name);

		for (int i = z; i < _ptList->m_uCount; i++)
		{
			if (strcmp(pointer->name, Min) == -1)
			{
				strcpy(Min, pointer->name);
			}
			pointer = pointer->m_pNext;
		}

		pointer = _ptList->m_pHead;
		for (int x = 0; x < z; x++)
		{
			pointer = pointer->m_pNext;
		}

		for (int x = 0; x < _ptList->m_uCount; x++)
		{
			if (strcmp(pointer->name, Min) != 0)
			{
				pointer = pointer->m_pNext;
			}
		}

		for (int x = 0; x < z; x++)
		{
			head = head->m_pNext;
		}
		int temp;
		unsigned int temp1;
		char temp2[20];
		char temp3[30];
		char temp4[20];
		Node2* temp5;
		//나이
		temp = pointer->m_iObject;
		pointer->m_iObject = head->m_iObject;
		head->m_iObject = temp;
		//약갯수
		temp1 = pointer->medicine_num;
		pointer->medicine_num = head->medicine_num;
		head->medicine_num = temp1;
		//이름
		strcpy(temp2, pointer->name);
		strcpy(pointer->name, head->name);
		strcpy(head->name, temp2);
		//전화번호
		strcpy(temp4, pointer->phone);
		strcpy(pointer->phone, head->phone);
		strcpy(head->phone, temp4);
		//주소
		strcpy(temp3, pointer->adress);
		strcpy(pointer->adress, head->adress);
		strcpy(head->adress, temp3);
		//약 리스트
		temp5 = pointer->medicine_head;
		pointer->medicine_head = head->medicine_head;
		head->medicine_head = temp5;
	}
}
int DEF::NUM()
{
	int number;
	int word = 0;
	char tmp[100];
	rewind(stdin);
	gets_s(tmp);
	for (int f = 0; tmp[f] != '\0'; f++)
	{
		if (tmp[f] >= '0' && tmp[f] <= '9')
		{
		}
		else
		{
			word = word + 1;
			break;
		}
	}
	if (word != 0)
	{
		system("cls");
		word = 0;
		cout << "문자가 포함되어있음 다시 입력하시오" << endl;
		return -1;
	}
	number = atoi(tmp);
	if (number > 2147483647 && number < 0)
	{
		cout << "2147483647이하의 양의 정수를 입력해주십시오" << endl;
		return -1;
	}
	return number;
}
int DEF::Gumsa(Node* base, Node2* pointer)
{
	if (base->medicine_num != 0)
	{
		Node2* scan = base->medicine_head;
		for (int i = 0; i < base->medicine_num; i++)
		{
			if (strcmp(scan->name, pointer->name) == 0)
			{
				cout << "약이 중복입니다. 하나를 넘어갑니다." << endl;
				scan = NULL;
				free(scan);
				return -1;
			}
			scan = scan->m_pNext;
		}
	}
	else if (base->medicine_num == 0)
	{

	}
	return 0;
}
Node* DEF::LinearSearchByUnique(LinkedList* _ptList)
{
	if (_ptList->m_uCount < 1)
	{
		cout << "정보가 없습니다." << endl;
		return 0;
	}
	char a[20];
	cout << "이름을 입력하시오: ";
	cin >> a;
	int ox = 0;
	int i = 0;
	Node* pointer = _ptList->m_pHead;
	for (i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, a) == 0)
		{
			cout << i + 1 << "번째에 있습니다." << endl;
			break;
			ox++;
		}
		pointer = pointer->m_pNext;
		if (i == _ptList->m_uCount - 1) {
			if (ox != 0)
			{
				continue;
			}
			else if (ox == 0) {
				cout << "없는 이름 입니다" << endl;
			}
		}
	}
	return 0;
}
Node* DEF::LinearSearchByDuplicate(LinkedList* _ptList)
{
	if (_ptList->m_uCount < 1)
	{
		cout << "정보가 없습니다." << endl;
		return 0;
	}
	char a[20];
	cout << "이름을 입력하시오: ";
	cin >> a;
	int ox = 0;
	int i = 0;
	Node* pointer = _ptList->m_pHead;
	for (i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, a) == 0)
		{
			cout << i + 1 << "번째";
			ox++;
		}
		pointer = pointer->m_pNext;
		if (i == _ptList->m_uCount - 1) {
			if (ox != 0)
			{
				cout << "에 있습니다." << endl;
			}
			else if (ox == 0) {
				cout << "없는 이름 입니다." << endl;
			}
		}
	}
	return 0;
}
Node* DEF::BinarySearchByUnique(LinkedList* _ptList, char target[], int start, int end) {
	if (_ptList->m_uCount == 0)
	{
		cout << "저장된 손님의 정보가 없습니다." << endl;
		return 0;
	}
	Node* pointer = _ptList->m_pHead;
	int where = 1;
	int ox = 0;
	int i = 0;
	int half;
	for (i = 0; i != _ptList->m_uCount; i++)
	{
		if (strcmp(pointer->name, target) == 0)
		{
			ox++;
		}
		pointer = pointer->m_pNext;
		if (i == _ptList->m_uCount - 1) {
			if (ox != 0)
			{
				continue;
			}
			else if (ox == 0) {
				cout << "없는 이름 입니다." << endl;
				return 0;
			}
		}
	}

	pointer = _ptList->m_pHead;
	half = (start + end) / 2;

	for (int i = 1; i < half; i++)
	{
		pointer = pointer->m_pNext;
		where = where + 1;
	}

	if (strcmp(pointer->name, target) == 0)
	{
		cout << where << "번째" << endl;
		return 0;
	}

	else if (strcmp(pointer->name, target) == -1)
	{
		where = where + 1;
		pointer = pointer->m_pNext;
		BinarySearchByUnique(_ptList, target, where, end);
	}
	else if (strcmp(pointer->name, target) == 1)
	{
		where = where - 1;
		pointer = pointer->m_Previous;
		BinarySearchByUnique(_ptList, target, start, where);
	}
}
Node* DEF::BinarySearchByDuplicate(LinkedList* _ptList, char target[], int start, int end)
{

	if (end < 1 || start > _ptList->m_uCount || start > end)
	{
	}
	else
	{
		if (_ptList->m_uCount == 0)
		{
			cout << "저장된 손님의 정보가 없습니다." << endl;
			return 0;
		}
		Node* pointer = _ptList->m_pHead;
		int where = 1;
		int ox = 0;
		int i = 0;
		int half;

		for (i = 0; i != _ptList->m_uCount; i++)
		{
			if (strcmp(pointer->name, target) == 0)
			{
				ox++;
			}
			pointer = pointer->m_pNext;
			if (i == _ptList->m_uCount - 1) {
				if (ox != 0)
				{
					continue;
				}
				else if (ox == 0) {
					cout << "없는 이름 입니다." << endl;
					return 0;
				}
			}
		}


		pointer = _ptList->m_pHead;
		half = (start + end) / 2;

		for (int i = 1; i < half; i++)
		{
			pointer = pointer->m_pNext;
			where = where + 1;
		}

		if (strcmp(pointer->name, target) == 0)
		{
			cout << where << "번째 ";

			BinarySearchByDuplicate(_ptList, target, where + 1, end);
			BinarySearchByDuplicate(_ptList, target, start, where - 1);
		}
		else if (strcmp(pointer->name, target) == -1)
		{
			BinarySearchByDuplicate(_ptList, target, where + 1, end);
		}
		else if (strcmp(pointer->name, target) == 1)
		{
			BinarySearchByDuplicate(_ptList, target, start, where - 1);
		}

	}
}
int DEF::menu()
{
	LinkedList* master = Create();
	int number;
	while (1)
	{
		cout << endl;
		cout << " ------------기능을 선택해 주십쇼--------------" << endl;
		cout << "|1.새 손님 정보 업로드(맨 앞 쪽에다가)         |" << endl;
		cout << "|2.새 손님 정보 업로드(맨 뒤 쪽에다가)         |" << endl;
		cout << "|3.지정 위치 앞에 업로드                       |" << endl;
		cout << "|4.지정 위치 뒤에 업로드                       |" << endl;
		cout << "|5.맨 앞 손님 정보 삭제                        |" << endl;
		cout << "|6.맨 뒤 손님 정보 삭제                        |" << endl;
		cout << "|7.손님 정보 보기                              |" << endl;
		cout << "|8.손님 정보 변경(이름 나이 주소)              |" << endl;
		cout << "|9.손님 약 정보 추가                           |" << endl;
		cout << "|10.손님 약 정보 부분 삭제                     |" << endl;
		cout << "|11.모든 손님 정보 지우기                      |" << endl;
		cout << "|12.지정 손님 정보 지우기                      |" << endl;
		cout << "|13.모든 손님 이름 출력                        |" << endl;
		cout << "|14.모든 손님 정보 출력                        |" << endl;
		cout << "|15.모든 정보 지우기(끝내기)                   |" << endl;
		cout << "|16.손님 이름 버블정렬                         |" << endl;
		cout << "|17.손님 이름 삽입정렬                         |" << endl;
		cout << "|18.손님 이름 선택정렬                         |" << endl;
		cout << "|19.단일 선형탐색으로 손님위치 찾기            |" << endl;
		cout << "|20.다중 선형탐색으로 손님위치 찾기            |" << endl;
		cout << "|21.단일 이진탐색으로 손님위치 찾기            |" << endl;
		cout << "|22.다중 이진탐색으로 손님위치 찾기            |" << endl;
		cout << " ----------------------------------------------" << endl;
		cout << "입력 : ";

		number = NUM();
		system("cls");

		if (number == 1)
		{
			AppendFromHead(master);
		}
		else if (number == 2)
		{
			AppendFromTail(master);
		}
		else if (number == 3)
		{
			InsertBefor(master);
		}
		else if (number == 4)
		{
			InsertAfter(master);
		}
		else if (number == 5)
		{
			DeleteFromHead(master);
		}
		else if (number == 6)
		{
			DeleteFromTail(master);
		}
		else if (number == 7)
		{
			Read(master);
		}
		else if (number == 8)
		{
			Modify(master);
		}
		else if (number == 9)
		{
			Modify2(master);
		}
		else if (number == 10)
		{
			Delete2(master);
		}
		else if (number == 11)
		{
			DeleteAll(master);
		}
		else if (number == 12)
		{
			Delete(master);
		}
		else if (number == 13)
		{
			Traversal(master);
		}
		else if (number == 14)
		{
			veiw(master);
		}
		else if (number == 15)
		{
			DeleteAll(master);
			Destroy(master);
			cout << "종료합니다.";
			return 0;
		}
		else if (number == 16)
		{
			SortByBubble(master);
		}
		else if (number == 17)
		{
			SortByInsertion(master);
		}
		else if (number == 18)
		{
			SortBySelection(master);
		}
		else if (number == 19)
		{
			LinearSearchByUnique(master);
		}
		else if (number == 20)
		{
			LinearSearchByDuplicate(master);
		}
		else if (number == 21)
		{
			char target[20];
			cout << "이름을 입력하시오: ";
			cin >> target;
			SortByBubble(master);
			BinarySearchByUnique(master, target, 1, master->m_uCount);
		}
		else if (number == 22)
		{
			char target[20];
			cout << "이름을 입력하시오: ";
			cin >> target;
			SortByBubble(master);
			BinarySearchByDuplicate(master, target, 1, master->m_uCount);
		}
	}
}
