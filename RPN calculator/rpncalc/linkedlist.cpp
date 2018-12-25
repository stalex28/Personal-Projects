#include "linkedlist.h"

Stack::Stack(){
    head = nullptr;
}

Stack::~Stack(){
    //std::cout << "destruct";
}

void Stack::push(float input){
    Node *newNode = new Node;
    newNode->data = input;
    newNode->next = head;
    head = newNode;
}

float Stack::pop(){
    if(!isEmpty()){
        Node *temp = head;
        head = head->next;
        float holder = temp->data;
        delete temp;
        return holder;
    }
    return -1;
}

bool Stack::isEmpty(){
    if(head == nullptr)
        return true;
    return false;
}

int Stack::getTop(){
    int counter = 0;
    Node *tracer = head;
    while(tracer != nullptr){
        tracer = tracer->next;
        counter ++;
    }
    return counter;
}
