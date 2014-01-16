#ifndef _World_h_
#define _World_h_

#include "Timer.h"
#include "utils.h"

#include "Player.h"
#include <malloc.h>
#include <SDL_mixer.h>


#define RIGHTLIMIT SCREEN_WIDTH-400
#define LEFTLIMIT 400
#define BOTTOMLIMIT SCREEN_HEIGHT-100
#define TOPLIMIT 100

class World
{
protected:
    Timer* timer;
    SDL_Surface* screen;
    Rectangle **rectangles;
    Player *player;

    Rectangle **colList;
    void updateCollisionlist();

    int RECTARRAY_SIZE;

    Rectangle *rectangleMort;

public:
    World(SDL_Surface* scr, Timer* tmr);
    ~World();
    bool update();
    Rectangle **getCollisionList();
};

#endif