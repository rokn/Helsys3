#include "AGE.h"

void AGE_RectSetPosition(AGE_Rect *rect, int X, int Y)
{
	rect->X = X;
	rect->Y = Y;
}

bool AGE_RectIntersects(AGE_Rect rect1, AGE_Rect rect2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = rect1.X;
    rightA = rect1.X + rect1.Width;
    topA = rect1.Y;
    bottomA = rect1.Y + rect1.Height;

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

    return true;
}

bool AGE_RectContainsPoint(AGE_Rect rect, AGE_Vector point)
{
	int left;
    int right;
    int top;
    int bottom;

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

void AGE_RectPrint(AGE_Rect rect)
{
    printf("AGE_Rect: {X:%d, Y:%d, Width:%d, Height:%d}\n", rect.X, rect.Y, rect.Width, rect.Height);
}

bool AGE_RectContainsRect(AGE_Rect rect1, AGE_Rect rect2)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = rect1.X;
    rightA = rect1.X + rect1.Width;
    topA = rect1.Y;
    bottomA = rect1.Y + rect1.Height;

    leftB = rect2.X;
    rightB = rect2.X + rect2.Width;
    topB = rect2.Y;
    bottomB = rect2.Y + rect2.Height;

    if(leftB > leftA && rightB < rightA && topB > topA && bottomB < bottomA)
    {
        return true;
    }
    
    return false;
}