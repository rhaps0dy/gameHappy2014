#include "Timer.h"
#include "SDL.h"

Timer::Timer(void)
{
    started = false;
    startTicks = 0;
    lastTime = 0;
}

void Timer::start(void)
{
    started = true;
    lastTime = startTicks = SDL_GetTicks();
}

void Timer::stop(void)
{
    started = false;
    startTicks = SDL_GetTicks();
}

Uint32 Timer::getTime(void)
{
    if(started) return SDL_GetTicks()-startTicks;
    else return startTicks;
}

Uint16 Timer::update(void)
{
    // do {
        dt = SDL_GetTicks()-lastTime;
    // }while(dt<1/60.);
    lastTime = SDL_GetTicks();
    return dt;
}
