#include "World.h"
#include <fstream>

World::World(SDL_Surface* scr, Timer* tmr)
{
	timer = tmr;
	screen = scr;
	player = new Player(screen, timer);
	std::ifstream level;
	level.open("resources/level");
	int size;
	level >> size;
	RECTARRAY_SIZE = size;
	rectangles = (Rectangle **) malloc(RECTARRAY_SIZE*sizeof(Rectangle *));
	for(int i=0; i<RECTARRAY_SIZE; i++)
	{
		double a, b, c, d;
		level >> a;
		level >> b;
		level >> c;
		level >> d;
		rectangles[i] = new Rectangle(a, b, c, d);
	}
	level.close();

	colList = (Rectangle**) malloc(4*sizeof(Rectangle *));
	for(int i=0;i<4;i++)
		colList[i]=NULL;
	rectangleMort = new Rectangle(0, 2000, 1e5, 1e5);
	if( Mix_OpenAudio( 48000, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
		throw;
}

World::~World()
{
	free(colList);
	for(int i=0; i<RECTARRAY_SIZE; i++)
	{
		delete rectangles[i];
	}
	free(rectangles);
	delete player;
	delete rectangleMort;
}

bool World::update()
{
	timer->update();
    if(!player->processEvents(getCollisionList())) return false;


    //check if off limits
    if(player->left < LEFTLIMIT)
    {
    	double offset = LEFTLIMIT-player->left;
    	player->x += offset;
    	for(int i=0;i<RECTARRAY_SIZE;i++)
    	{
    		rectangles[i]->x += offset;
    		rectangles[i]->actualitza();
    	}
    		rectangleMort->x += offset;
    		rectangleMort->actualitza();
    }

	if(player->right > RIGHTLIMIT)
    {
    	double offset = RIGHTLIMIT-player->right;
    	player->x += offset;
    	for(int i=0;i<RECTARRAY_SIZE;i++)
    	{
    		rectangles[i]->x += offset;
    		rectangles[i]->actualitza();
    	}
    		rectangleMort->x += offset;
    		rectangleMort->actualitza();
    }
    if(player->top < TOPLIMIT)
    {
    	double offset = TOPLIMIT-player->top;
    	player->y += offset;
    	for(int i=0;i<RECTARRAY_SIZE;i++)
    	{
    		rectangles[i]->y += offset;
    		rectangles[i]->actualitza();
    	}
    		rectangleMort->y += offset;
    		rectangleMort->actualitza();
    }

	if(player->bottom > BOTTOMLIMIT)
    {
    	double offset = BOTTOMLIMIT-player->bottom;
    	player->y += offset;
    	for(int i=0;i<RECTARRAY_SIZE;i++)
    	{
    		rectangles[i]->y += offset;
    		rectangles[i]->actualitza();
    	}
    		rectangleMort->y += offset;
    		rectangleMort->actualitza();
    }

    SDL_FillRect(screen, &(screen->clip_rect), SDL_MapRGB(screen->format, 0xa0, 0xa0, 0xa0));
    for(int i=0; i<RECTARRAY_SIZE; i++)
    {
    	if(rectangles[i]->bottom < 0 || rectangles[i]->top > SCREEN_HEIGHT || rectangles[i]->right < 0 || rectangles[i]->left > SCREEN_WIDTH)
    		continue;
	    SDL_FillRect(screen, rectangles[i]->updateRectangle(), SDL_MapRGB(screen->format, 0x68, 0x4b, 0x18));
	}
	updateCollisionlist();
    if(!player->updateAnimation()) return false;
    if(player->collides_with(rectangleMort))
    {
    	SDL_Surface *a = loadImage("images/matasogres.png");
    	applySurface(0, 0, a, screen);
    	SDL_Flip(screen);
    	SDL_FreeSurface(a);

		Mix_Chunk *gameOver = Mix_LoadWAV( "resources/matasogres.wav" );
		Mix_PlayChannel( -1, gameOver, 0 );
		Uint32 startTime = timer->getTime();

		while(timer->getTime()-startTime < 10000)
		{
	    	SDL_Event event;
		    SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUITMASK);
		    SDL_PumpEvents();
		    if(event.type==SDL_QUIT)
		        break;
	    }
	    	return false;
    }
    return true;
}

Rectangle **World::getCollisionList()
{
	return colList;	
}
void World::updateCollisionlist()
{
	int i=0;
	for(int j=0;j<RECTARRAY_SIZE;j++)
	{
		colList[i] = player->coll_rect(rectangles[j]);
		if(colList[i]) i++;
	}
	for(;i<4;i++)
		colList[i]=NULL;

}
