#include "calculator.h"
#include <math.h>

Calculator::Calculator(){
    Stack();
}

Calculator::~Calculator(){
    //std::cout << "calc destructor";
}

float Calculator::add(){
    if(getTop() >= 1){
        x = pop();
        y = pop();
        float sum = x + y;
        push(sum);
        return sum;
    }
    if(getTop() == 0){
        return display();
    }
    std::cout << "empty stack";
    return -1;
}

float Calculator::subtract(){
    if(getTop() >= 1){
        x = pop();
        y = pop();
        float difference = y - x;
        push(difference);
        return difference;
    }
    if(getTop() == 0){
        x = pop();
        push(-x);
        return -x;
    }
    std::cout << "empty stack";
    return -1;
}

float Calculator::multiply(){
    if(getTop() >= 1){
        x = pop();
        y = pop();
        float product = x*y;
        push(product);
        return product;
    }
    if(getTop() == 0){
        pop();
        push(0);
        return 0;
    }
    std::cout << "empty stack";
    return -1;
}

float Calculator::divide(){
    if(getTop() >= 0){
        x = pop();
        if(x == 0){
            std::cout << "divide by 0";
            return -1;
        }
        y = pop();
        float quotient = y / x;
        push(quotient);
        return quotient;
    }
    std::cout << "empty stack";
    return -1;
}

float Calculator::sqrroot(){
    x = sqrt(pop());
    push(x);
    return x;
}

float Calculator::power(){
    x = pop();
    y = pow(pop(), x);
    push(y);
    return y;
}

float Calculator::recip(){
     x = 1.00/pop();
     push(x);
     return x;
}

float Calculator::display(){
    x = pop();
    push(x);
    return x;
}

void Calculator::swap(){
    x = pop();
    y = pop();
    push(x);
    push(y);
}

void Calculator::clear(){
    for(int i = 0; i < getTop(); i++){
        pop();
    }
}
