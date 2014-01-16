#include "Rectangle.h"

Rectangle::Rectangle(double ix, double iy, double iw, double ih)
{
	x = ix;
	y = iy;
	w = iw;
	h = ih;
	actualitza();
	updateRectangle();
	return;
}

void Rectangle::actualitza(void)
{
	left = x;
	top = y;
	right = x+w;
	bottom = y+h;
	return;
}

bool Rectangle::collides_with(Rectangle* rect)
{
	actualitza();
	//els rectangles son superficies, no linies.
	if(rect->left > this->right) return false;
	if(rect->right < this->left) return false;
	if(rect->top > this->bottom) return false;
	if(rect->bottom < this->top) return false;
	return true;
}

bool Rectangle::collides_with(double pointx, double pointy)
{
	actualitza();
	//De fet no es un punt sino un rectangle 1x1
	pointx -= 1.;
	pointy -= 1.;
	if((pointx >= left && pointx <= right)&&(pointy <= bottom && pointy >= top))
		return true;
	return false;
}

Rectangle* Rectangle::coll_rect(Rectangle* rect)
{
	if(!this->collides_with(rect)) return NULL;
	Rectangle *rect1, *rect2; // Per reduir el nombre de casos
	double nx, ny, nw, nh;

	if(rect->top < top)
	{
		rect1 = rect;
		rect2 = this;
	}
	else
	{
		rect1 = this;
		rect2 = rect;
	}

	ny = rect2->y;

	if(rect->left < left)
		nx = x;
	else
		nx = rect->x;

	if(rect1->bottom < rect2->bottom)
		nh = rect1->bottom - rect2->top;
	else
		nh = rect2->h;

	if((rect1->right < rect2->right) && (rect1->left < rect2->left))
	{
		nw = rect1->right - rect2->left;
	}
	else if((rect1->right >= rect2->right) && (rect1->left < rect2->left))
	{
		nw = rect2->w;
	}
	else if((rect1->right < rect2->right) && (rect1->left >= rect2->left))
	{
		nw = rect1->w;
	}
	else // r1 > r2 i l1 > l2
	{
		nw = rect2->right - rect1->left;
	}
	return new Rectangle(nx, ny, nw, nh);
}

SDL_Rect *Rectangle::updateRectangle()
{
	rectangle.x = round(x);
	rectangle.y = round(y);
	rectangle.w = round(w);
	rectangle.h = round(h);
	return &rectangle;
}