#include "Player.h"

bool Player::processEvents(Rectangle **rects)
{
    //mira si hem sortit amb x o escape
    SDL_Event event;
    SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUITMASK);
    SDL_PumpEvents();
    if(event.type==SDL_QUIT)
        return false;

    keyStates = SDL_GetKeyState(NULL);
    if(keyStates[SDLK_ESCAPE])
        return false;

    moving = true;
    if(keyStates[SDLK_LEFT])
        dirRight = false;
    else if(keyStates[SDLK_RIGHT])
        dirRight = true;
    else moving = false;


    ySpeed += 1.5 * timer->dt;

    //check collisions
    canUp = canLeft = canRight = canDown = true;
    for(int i=0; i<4; i++)
    {
        if(!rects[i]) break;
        //is it vertical or lateral collision?
        if(rects[i]->w > rects[i]->h) //vertical
        {
            if(rects[i]->top == top)
            {
                y = rects[i]->top + 0.1;
                canUp = false;
            }
            if(rects[i]->bottom == bottom)
            {
                y = rects[i]->top - h + 0.1;
                canDown = false;
            }
            ySpeed = 0;
        }
        else
        {
            if(rects[i]->left == left)
                canLeft=false;
            if(rects[i]->right == right)
                canRight=false;
        }
        delete (rects[i]);
    }

    if(keyStates[SDLK_UP])
    {
        if(!canDown)
        {
            jump=true;
            jumpTime = 300;
        }
        //funciona per overflow
        else if(jumpTime > 300 )
            jump = false;
        jumpTime -= timer->dt;
    }
    else jump=false;

    if(jump) ySpeed = -480;

    if(!canUp)
    {
        ySpeed = 0;
        jumpTime = 301;
    }

    y+= ySpeed * timer->dt/1000;


    if(moving) //anem a moure el pj
    {
        double mvmt = speed*(timer->dt)/1000.f;
        switch(dirRight)
        {
            case 1:
            if(canRight)
                x += mvmt;
            break;

            case 0:
            if(canLeft)
                x -= mvmt;
            break;
        }
    }
    actualitza();
    return true;
}
bool Player::updateAnimation(void)
{
    updateRectangle();
    animFrameTime += timer->dt;
    if(moving)
    {
        if(dirRight) SDL_BlitSurface(caminarAnimDreta, caminarFrames+counter, screen, &rectangle);
        else SDL_BlitSurface(caminarAnimEsquerra, caminarFrames+5-counter, screen, &rectangle);

        if(animFrameTime>=FRAME_TIME)
        {
            counter = (counter+1)%6;
            animFrameTime = 0;
        }
    }
    else
    {
        if(dirRight) SDL_BlitSurface(estaticAnimDreta, NULL, screen, &rectangle);
        else SDL_BlitSurface(estaticAnimEsquerra, NULL, screen, &rectangle);
        counter = 0;
    }

    SDL_Flip(screen);
    return true;
}

Player::Player(SDL_Surface* scr, Timer* tmr) : Rectangle(10., SCREEN_HEIGHT-200, 69, 181.)
// Player::Player(SDL_Surface* scr, Timer* tmr) : Rectangle(1400., -700, 69, 181.)
{
    screen = scr;
    timer = tmr;
    counter = 3;
    speed = 300.f;
    ySpeed = 0;
    animFrameTime = 0;
    jump = false;
    jumpTime = 0;

    SDL_Surface *cap;

    caminarAnimDreta = loadImage("images/caminar(6-69x185).png");
    estaticAnimDreta = loadImage("images/estatic(1-69x185).png");
    cap = loadImage("images/cap.png");

    composite(cap, estaticAnimDreta);

    //Posicionar els rectangles dels frames
    caminarFrames[0].x = 0;
    caminarFrames[0].y = 0;
    caminarFrames[0].w = 69;
    caminarFrames[0].h = 181;

    caminarFrames[1].x = 69;
    caminarFrames[1].y = 0;
    caminarFrames[1].w = 69;
    caminarFrames[1].h = 181;
    
    caminarFrames[2].x = 69*2;
    caminarFrames[2].y = 0;
    caminarFrames[2].w = 69;
    caminarFrames[2].h = 181;
    
    caminarFrames[3].x = 69*3;
    caminarFrames[3].y = 0;
    caminarFrames[3].w = 69;
    caminarFrames[3].h = 181;
    
    caminarFrames[4].x = 69*4;
    caminarFrames[4].y = 0;
    caminarFrames[4].w = 69;
    caminarFrames[4].h = 181;
    
    caminarFrames[5].x = 69*5;
    caminarFrames[5].y = 0;
    caminarFrames[5].w = 69;
    caminarFrames[5].h = 181;

    composite(cap, caminarAnimDreta, caminarFrames[0].x, 0);
    composite(cap, caminarAnimDreta, caminarFrames[1].x, 1);
    composite(cap, caminarAnimDreta, caminarFrames[2].x, 2);
    composite(cap, caminarAnimDreta, caminarFrames[3].x, 4);
    composite(cap, caminarAnimDreta, caminarFrames[4].x, 2);
    composite(cap, caminarAnimDreta, caminarFrames[5].x, 1);

    SDL_FreeSurface(cap);
    caminarAnimEsquerra = flipSurface(caminarAnimDreta, FLIP_HORIZONTAL);
    estaticAnimEsquerra = flipSurface(estaticAnimDreta, FLIP_HORIZONTAL);
 }

    Player::~Player(void)
    {
        SDL_FreeSurface(caminarAnimDreta);
        SDL_FreeSurface(estaticAnimEsquerra);
        SDL_FreeSurface(caminarAnimEsquerra);
        SDL_FreeSurface(estaticAnimDreta);
    }
