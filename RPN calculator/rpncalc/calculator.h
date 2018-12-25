#ifndef _CALCULATOR_H
#define _CALCULATOR_H

#include "stack.h"


class Calculator: public Stack{
    public:
        Calculator();
        ~Calculator();
        float add();
        float subtract();
        float multiply();
        float divide();
        float sqrroot();
        float power();
        float recip();
        float display();
        void swap();
        void clear();
    private:
        float x;
        float y;
};

#endif // _CALCULATOR_H
