#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

struct Node{
    float data;
    Node *next;
};

class Stack{
    public:
       Stack();
       ~Stack();
       void push(float input);
       float pop();
       bool isEmpty();
       int getTop();
    private:
        Node *head;
};

#endif // _LINKEDLIST_H
