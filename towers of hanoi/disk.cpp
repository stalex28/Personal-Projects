#include "disk.h"

hanoi::hanoi(){
    tower.resize(4);
    for(int i = 0; i < 4; i++){
        tower[i].size = i;
        tower[i].location = 0;
    }
}

hanoi::hanoi(int n){
    tower.resize(n);
    for(int i = 0; i < n; i++){
        tower[i].size = i;
        tower[i].location = 0;
    }
}

hanoi::~hanoi(){

}

void hanoi::move(int mass, int place){
    tower[mass].location = place;
}

int hanoi::getLocation(int mass){
    return tower[mass].location;
}

int hanoi::topDisk(int peg){
    for(int i = 0; i < tower.length(); i++){
        if(tower[i].location == peg)
            return i;
    }
    return -1;
}

int hanoi::disksUnder(int d){
    int pos = tower[d].location;
    int counter = 0;
    for(int i = 0; i < tower.length(); i++){
        if(tower[i].size > tower[d].size && tower[i].location == tower[d].location)
            counter ++;
    }
    return counter;
}

void hanoi::reset(){
    for(int i = 0; i < tower.length(); i++)
        tower[i].location = 0;
}

void hanoi::changeSize(int s){
    tower.resize(s);
    for(int i = 0; i < s; i++){
        tower[i].size = i;
        tower[i].location = 0;
    }
}
