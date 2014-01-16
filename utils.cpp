#include "utils.h"

SDL_Surface* loadImage(std::string filename)
{
    SDL_Surface* loadedImage = NULL;

    loadedImage = IMG_Load(filename.c_str());

    if(loadedImage!=NULL)
    {
        SDL_Surface *optimizedImage;
        optimizedImage = SDL_DisplayFormatAlpha(loadedImage);
        SDL_FreeSurface(loadedImage);
        return optimizedImage;
    }
    else
    {
        throw;
    }
}

void applySurface(int x, int y, SDL_Surface* src, SDL_Surface* dest, SDL_Rect* clip)
{
    SDL_Rect rectangle;
    rectangle.x = x;
    rectangle.y = y;
    SDL_BlitSurface(src, clip, dest, &rectangle);
    return;
}

Uint32 getPixel32(SDL_Surface* surf, int x, int y)
{
    if(x>surf->w || y>surf->h) return 0;
    if(x<0 || y<0) return 0;
    Uint32* pixels = (Uint32*)surf->pixels;
    return pixels[(y * surf->w) + x];
}

void putPixel32(SDL_Surface* surf, int x, int y, Uint32 pixel)
{
    Uint32* pixels = (Uint32*)surf->pixels;
    pixels[(y*surf->w) + x] = pixel;
}

SDL_Surface* flipSurface(SDL_Surface* surf, int flags)
{
    SDL_Surface* flipped = NULL;
    flipped = SDL_CreateRGBSurface( SDL_SWSURFACE, surf->w, surf->h, surf->format->BitsPerPixel, surf->format->Rmask,
                                    surf->format->Gmask, surf->format->Bmask, surf->format->Amask );

    if(SDL_MUSTLOCK(surf)) SDL_LockSurface(surf);

    for(int x=0, rx=flipped->w - 1; x < flipped->w; x++, rx--)
        for(int y=0, ry=flipped->h-1; y<flipped->h; y++, ry--)
        {
            Uint32 pixel = getPixel32(surf, x, y);
            if((flags & FLIP_HORIZONTAL) && (flags & FLIP_VERTICAL)) putPixel32(flipped, rx, ry, pixel);
            else if(flags & FLIP_VERTICAL) putPixel32(flipped, x, ry, pixel);
            else putPixel32(flipped, rx, y, pixel);
        }
    if(SDL_MUSTLOCK(surf)) SDL_UnlockSurface(surf);

    return flipped;
}

void composite(SDL_Surface* src, SDL_Surface *dest, int offsetX, int offsetY)
{
    if(SDL_MUSTLOCK(dest)) SDL_LockSurface(dest);
    if(SDL_MUSTLOCK(src)) SDL_LockSurface(src);

    for(int x=0; x < src->w; x++)
        for(int y=0; y<src->h; y++)
        {
            Uint32 srcpixel = getPixel32(src, x, y);
            if(srcpixel & 0xff000000)
            {
                putPixel32(dest, x+offsetX, y+offsetY, srcpixel);
                continue;
            }
            Uint32 destpixel = getPixel32(dest, x+offsetX, y+offsetY);
            putPixel32(dest, x+offsetX, y+offsetY, destpixel);
        }

    if(SDL_MUSTLOCK(dest)) SDL_UnlockSurface(dest);
    if(SDL_MUSTLOCK(src)) SDL_UnlockSurface(src);
}