#ifndef _Rectangle_h_
#define _Rectangle_h_

#include <malloc.h>
#include "utils.h"

/*Classe que es fa servir per guardar la posició real dels sprites*
 * i calcular les col.lisions entre ells                          */

class Rectangle
{
protected:
	SDL_Rect rectangle;
public:
    double x, y, h, w, top, bottom, left, right;
	Rectangle(double ix, double iy, double iw, double ih);
	void actualitza(void);
    bool collides_with(Rectangle* rect);
    bool collides_with(double pointx, double pointy);
    Rectangle* coll_rect(Rectangle* rect);
	SDL_Rect *updateRectangle();
};


#endif

