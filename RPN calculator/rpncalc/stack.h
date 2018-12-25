#ifndef _STACK_H
#define _STACK_H

#include <apvector.h>

class Stack{
    public:
       Stack();
       ~Stack();
       void push(float input);
       float pop();
       bool isEmpty();
       int getTop();
    private:
        apvector<float> pile;
        int top;
};

#endif // _STACK_H
