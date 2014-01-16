#ifndef _TIMER_H_
#define _TIMER_H_
#include "SDL.h"

class Timer
{
private:

    Uint32 startTicks;
    Uint32 lastTime;
    bool started;

public:
    //Initializes variables
    Timer(void);
    Uint16 dt;
    //actions
    void start(void);
    void stop(void);
    Uint32 getTime(void);
    Uint16 update(void);
};

#endif
