#ifndef _DISK_H
#define _DISK_H
#include <apvector.h>

struct disk{
    int size;
    int location;
};

class hanoi{
    public:
        hanoi();
        hanoi(int n);
        ~hanoi();
        void move(int mass, int place);
        int getLocation(int mass);
        int largeness(){return tower.length();}
        int topDisk(int peg);
        int disksUnder(int d);
        void reset();
        void changeSize(int s);
    private:
        apvector<disk> tower;
};
#endif // _DISK_H
