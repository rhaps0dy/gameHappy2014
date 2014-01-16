#ifndef _FLOATRECT_H_
#define _FLOATRECT_H_
#include "utils.h"

// Rectagle amb coordenades de punt flotant
class FloatRect
{
public:
    float fleft, ftop, fwidth, fheight;
    SDL_Rect rectangle;

    FloatRect(float x, float y, float w, float h)
    {
        fleft = x;
        ftop = y;
        fwidth = w;
        fheight = h;
        updateRect();
    }

    SDL_Rect updateRect(void)
    {
        rectangle.x = round(fleft);
        rectangle.y = round(ftop);
        rectangle.w = round(fwidth);
        rectangle.h = round(fheight);
        return rectangle;
    }
};
#endif
