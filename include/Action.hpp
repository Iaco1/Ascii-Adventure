#include <chrono>

enum class Animation{CLIMB_UP, CLIMB_DOWN, LEFT, RIGHT, STILL, JUMPING, FALLING, QUIT, PAUSE};
enum class AnimationDelay{ CLIMB_UP = 0, CLIMB_DOWN = 0, LEFT = 0, RIGHT = 0, STILL = 0, JUMPING = 100, FALLING = 100, 
                            QUIT = 0, PAUSE = 0};
enum class Initiator{ USER, LOGIC};

class Action{
    protected:
    Animation animation;
    int x, y; //affected position
    std::chrono::milliseconds delay;
    Initiator initiator;

    public:
    Action();
    Action(Animation animation, int x, int y, AnimationDelay ec_delay, Initiator initiator);
    Action(Animation animation, int x, int y, int delay, Initiator initiator);
    Animation getAnimation();
    int getX();
    int getY();
    int getDelay();
    Initiator getInitiator();
};