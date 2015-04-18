#include "AGE/AGE.h"

AGE_Vector AGE_Helper_RotatedVectorMove(AGE_Vector position, float rotation, float speed)
{
    position.X += speed * (float)cos(rotation);
    position.Y += speed * (float)sin(rotation);
    return position;
}

float AGE_Helper_FindRotation(AGE_Vector position, AGE_Vector targetPosition, float scale)
{
	AGE_Vector place = {targetPosition.X - position.X * scale, targetPosition.Y - position.Y * scale};

    float rotation = (float)atan2(place.Y, place.X);

    return rotation;
}

AGE_Vector AGE_Helper_AngleToVector(float angle)
{
	AGE_Vector vector = {(float)cos(angle), (float)sin(angle)};

	return vector;
}