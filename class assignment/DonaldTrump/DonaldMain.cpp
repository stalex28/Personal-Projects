/** Alex Djordjevic ICS4U assignment

    This is a class I made for an assignment.
    It was supposed to be just boring practice for
    making classes, but I decided to make it fun :)
    Please don't find this offensive, it is just a joke.

*/
#include <iostream>
#include "TheDonald.h"
#include <apstring.cpp>

using namespace std;

int main(){

    Trump Donald(50.0);
    int tallWall = 50;
    int hours = 4;

    cout << "Approval after talking about China: " << Donald.china() << "%" << endl;
    cout << "Immigrants deported by ICE raid: " << Donald.ICERaid() << endl;
    Donald.wall(tallWall);
    cout << "Approval after tweet: " << Donald.tweet(100) << "%" << endl;
    cout << "Approval after 4 hour meeting with Kanye: " << Donald.KanyeMeeting(4) << "%" << endl;
    cout << "Approval after some dank memes and a parody music video: " << Donald.memes(10) << "%" << endl;

    return 0;
}
