#include "utils.h"
#include "Player.h"
#include "World.h"
#include <string>
#include <iostream>


#ifdef WIN32
#include <windows.h>
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
int main(int argc, char *argv[])
#endif
{
    if(SDL_Init(SDL_INIT_EVERYTHING)==-1) throw;
    //crea la finestra
    SDL_Surface* screen = NULL;
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE);
    SDL_WM_SetCaption("Bon Any Nou!", NULL);
    Timer* timer = new Timer;
    World world (screen, timer);

    timer->update();
    while(world.update());
    delete timer;
    SDL_Quit();
    return 0;
}
