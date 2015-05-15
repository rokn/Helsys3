#include "AGE.h"

AGE_Vector AGE_Helper_RotatedVectorMove(AGE_Vector position, float rotation, float speed)
{
    position.X += speed * (float)cos(rotation);
    position.Y += speed * (float)sin(rotation);
    return position;
}

float AGE_Helper_FindRotation(AGE_Vector position, AGE_Vector targetPosition)
{
	AGE_Vector place = {targetPosition.X - position.X, targetPosition.Y - position.Y};
	// printf("place:%f,%f\n",place.X,place.Y);
    float rotation = (float)atan2(place.Y, place.X);
	// printf("rotation:%f\n",rotation);
	rotation *= 180.0 / M_PI;
    return rotation;
}

AGE_Vector AGE_Helper_AngleToVector(float angle)
{
	AGE_Vector vector = {(float)cos(angle), (float)sin(angle)};

	return vector;
}

AGE_Vector AGE_Helper_FindDirection(AGE_Vector position, AGE_Vector targetPosition)
{
	AGE_Vector dir = AGE_VectorSubtract(targetPosition, position);
	dir = AGE_VectorNormalize(dir);
	return dir;
}

AGE_Vector AGE_Helper_RectCenter(AGE_Rect rect)
{
	AGE_Vector center = {rect.X + rect.Width/2, rect.Y + rect.Height/2};	
	return center;
}