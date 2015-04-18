#include "AGE/AGE.h"

void AGE_RectSetPosition(AGE_Rect *rect, int X, int Y)
{
	rect->X = X;
	rect->Y = Y;
}

bool AGE_RectIntersects(AGE_Rect rect1, AGE_Rect rect2)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = rect1.X;
    rightA = rect1.X + rect1.Width;
    topA = rect1.Y;
    bottomA = rect1.Y + rect1.Height;

    //Calculate the sides of rect B
    leftB = rect2.X;
    rightB = rect2.X + rect2.Width;
    topB = rect2.Y;
    bottomB = rect2.Y + rect2.Height;

    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

bool AGE_RectContains(AGE_Rect rect, AGE_Vector point)
{
	int left;
    int right;
    int top;
    int bottom;

    //Calculate the sides of rect A
    left = rect.X;
    right = rect.X + rect.Width;
    top = rect.Y;
    bottom = rect.Y + rect.Height;

    if(point.X < left || point.X > right)
    {
    	return false;
    }

	if(point.Y < top || point.Y > bottom)
    {
    	return false;
    }

    return true;
}