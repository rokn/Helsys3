#include "AGE_Graphics.h"
#include "AGE_Input.h"

void AGE_SetCameraTransform(AGE_Vector v)
{
	camera_age.Offset = v;
	AGE_ViewRect.X = camera_age.Offset.X;
	AGE_ViewRect.Y = camera_age.Offset.Y;
	AGE_Mouse.TransformedPosition.X = AGE_Mouse.Position.x + camera_age.Offset.X;
	AGE_Mouse.TransformedPosition.Y = AGE_Mouse.Position.y + camera_age.Offset.Y;
}

void AGE_ChangeCameraTransform(AGE_Vector v)
{
	camera_age.Offset = AGE_VectorAdd(camera_age.Offset, v);
	AGE_ViewRect.X = camera_age.Offset.X;
	AGE_ViewRect.Y = camera_age.Offset.Y;
	AGE_Mouse.TransformedPosition.X = AGE_Mouse.Position.x + camera_age.Offset.X;
	AGE_Mouse.TransformedPosition.Y = AGE_Mouse.Position.y + camera_age.Offset.Y;
}

AGE_Vector AGE_GetCameraOffset()
{
	return camera_age.Offset;
}

void AGE_CameraUpdate()
{
	if(camera_age.IsFocusing)
	{
		camera_age.velocity = AGE_VectorMultiply(camera_age.velocity, camera_age.focusMultiplier);

		if(AGE_RectContainsRect(AGE_ViewRect, camera_age.focusRect))
		{
			camera_age.IsFocusing = false;
		}		
	}
	else
	{
		if(AGE_VectorLength(camera_age.velocity) > 1)
		{
			camera_age.velocity = AGE_VectorDivide(camera_age.velocity, 2);
		}
		else if(AGE_VectorLength > 0)
		{
			camera_age.velocity.X = 0;
			camera_age.velocity.Y = 0;
		}	
	}

	camera_age.Offset = AGE_VectorAdd(camera_age.Offset, camera_age.velocity);		
}

void AGE_FocusCamera(AGE_Rect focusRect, float multiplier)
{
	if(AGE_RectContainsRect(AGE_ViewRect, focusRect))
	{
		return;
	}
	camera_age.focusMultiplier = multiplier;
	camera_age.focusRect = focusRect;
	camera_age.IsFocusing = true;
	AGE_Vector viewCenter = {AGE_ViewRect.X + AGE_ViewRect.Width/2, AGE_ViewRect.Y + AGE_ViewRect.Height/2};
	AGE_Vector targetCenter = {focusRect.X + focusRect.Width/2, focusRect.Y + focusRect.Height/2};
	camera_age.velocity = AGE_Helper_FindDirection(viewCenter, targetCenter);
	camera_age.velocity = AGE_VectorMultiply(camera_age.velocity, 2);
}