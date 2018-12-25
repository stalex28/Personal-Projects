#include <apstring.h>

class Trump{
    private:
        long netWorth;
        float approval;
        apstring currentWife;
    public:
        Trump(long money, float popularity);
        Trump(float popularity);
        Trump();

        ~Trump();

        float tweet(int lengthOfTweet);
        void wall(int height);
        int ICERaid();
        float KanyeMeeting(int hours);
        float memes(int dankness);
        float china();
};
