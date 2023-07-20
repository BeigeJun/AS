#ifndef NODE_H
#define NODE_H

typedef struct node{
   struct node* m_pNext;
   struct node* m_Previous;
   int m_iObject;
}Node;

#endif
