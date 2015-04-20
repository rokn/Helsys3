#include "AGE.h"


AGE_Vector 	AGE_VectorAdd(AGE_Vector v1,AGE_Vector v2)
{
	AGE_Vector newVector;
	newVector.X = v1.X + v2.X;
	newVector.Y = v1.Y + v2.Y;
	return newVector;
}

AGE_Vector AGE_VectorSubtract(AGE_Vector v1, AGE_Vector v2)
{
	AGE_Vector newVector;
	newVector.X = v1.X - v2.X;
	newVector.Y = v1.Y - v2.Y;
	return newVector;
}

AGE_Vector AGE_VectorMultiply(AGE_Vector v, float value)
{
	AGE_Vector newVector;
	newVector.X = v.X * value;
	newVector.Y = v.Y * value;
	return newVector;
}

AGE_Vector AGE_VectorDivide(AGE_Vector v, float value)
{
	AGE_Vector newVector;
	newVector.X = v.X / value;
	newVector.Y = v.Y / value;
	return newVector;
}

float AGE_VectorDistance(AGE_Vector v1, AGE_Vector v2)
{
	float x = pow(v2.X - v1.X, 2);
	float y = pow(v2.Y - v1.Y, 2);
	return sqrt(x+y);
}

float AGE_VectorLength(AGE_Vector v)
{
	float x = pow(v.X, 2);
	float y = pow(v.Y, 2);
	return sqrt(x+y);
}

AGE_Vector AGE_VectorNormalize(AGE_Vector v)
{
	return AGE_VectorDivide(v, AGE_VectorLength(v));
}