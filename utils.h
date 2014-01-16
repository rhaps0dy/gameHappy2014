#ifndef _UTILS_H_
#define _UTILS_H_

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_BPP 32
#define FLIP_HORIZONTAL 0x01
#define FLIP_VERTICAL 0x02

#include "SDL.h"
#include "SDL_image.h"
#include <string>
#include <cmath>

SDL_Surface* loadImage(std::string filename);
void applySurface(int x, int y, SDL_Surface* src, SDL_Surface* dest, SDL_Rect* clip=NULL);

// int round(double num);

Uint32 getPixel32(SDL_Surface* surf, int x, int y);
void putPixel32(SDL_Surface* surf, int x, int y, Uint32 pixel);

SDL_Surface* flipSurface(SDL_Surface* surf, int flags);
void composite(SDL_Surface* src, SDL_Surface *dest, int offsetX=0, int offsetY=0);
#endif

