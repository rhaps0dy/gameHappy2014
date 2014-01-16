#ifndef _PLAYER_H_
#define _PLAYER_H_
#define FRAME_TIME 100

#include "Rectangle.h"
#include "Timer.h"

class Player: public Rectangle
{
private:
    double speed;
    double ySpeed;
    SDL_Surface* screen;

    SDL_Surface* caminarAnimDreta;
    SDL_Surface* caminarAnimEsquerra;
    SDL_Rect caminarFrames[6];
    SDL_Surface* estaticAnimDreta;
    SDL_Surface* estaticAnimEsquerra;

    bool canUp, canRight, canLeft, canDown;

    Timer* timer;
    char counter;
    char dirMove;
    bool dirRight;
    bool moving;
    Uint8* keyStates;
    Uint8 animFrameTime;

    bool jump;
    Uint16 jumpTime;
public:

    Player(SDL_Surface* scr, Timer* tmr);
    ~Player(void);
    bool processEvents(Rectangle **rects); //retorna fals si hi ha hagut quit.
    bool updateAnimation(void);
};

#endif
