#include "stack.h"

Stack::Stack(){
    top = -1;
    pile.resize(20);
    for(int i = 0; i < 20; i++){
        pile[i] = 0;
    }
}

Stack::~Stack(){
    //std::cout << "destruct";
}

void Stack::push(float input){
    top ++;
    pile[top] = input;
}

float Stack::pop(){
    if(top >= 0)
        return pile[top--];
    return 0;
}

bool Stack::isEmpty(){
    if(top == -1){
        return true;
    }
    return false;
}

int Stack::getTop(){
    return top;
}
