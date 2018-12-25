#include "TheDonald.h"
#include <iostream>
#include <time.h>

using namespace std;

Trump::Trump(){
    netWorth = 8737540000;
    approval = 75.0;
    currentWife = "Melania";
}

Trump::Trump(float popularity){
    netWorth = 8737540000;
    approval = popularity;
    currentWife = "Melania";
}

Trump::Trump(long money, float popularity){
    netWorth = money;
    approval = popularity;
    currentWife = "Melania";
}

Trump::~Trump(){
    cout << endl << "Trump destructor" << endl;
}

float Trump::tweet(int lengthOfTweet){
    srand(time(NULL));
    if(rand()%2 == 0){
        approval += rand() % 5 + 1;
    }
    else{
        approval -= rand() % 5 + 1;
    }
    if(approval > 100){
        approval = 100;
    }
    if(approval < 0){
        approval = 0;
    }
    return approval;
}

void Trump::wall(int height){
    for(int i = 0; i <= height; i++){
        if(i%2 == 0){
            cout << "|_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_|" << endl;
        }
        else{
            cout << "-|_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_|" << endl;
        }
    }
}

int Trump::ICERaid(){
    srand(time(NULL));
    return rand() % 9900 + 100;
    netWorth += 100000000;
}

float Trump::KanyeMeeting(int hours){
    approval += hours/2;
    netWorth += 1000000;
    if(approval > 100){
        approval = 100;
    }
    return approval;
}

float Trump::memes(int dankness){
    if(dankness < 0){
        approval -= 5;
    }
    else{
        approval += 5;
        netWorth += 1000000;
    }
    if(approval > 100){
        approval = 100;
    }
    if(approval < 0){
        approval = 0;
    }
    return approval;
}

float Trump::china(){
    approval += 2.5;
    netWorth += 1000000;
    if(approval > 100){
        approval = 100;
    }
    return approval;
}
