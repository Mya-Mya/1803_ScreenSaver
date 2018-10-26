#include "fromMathPlane.h"

fromMathPlane::fromMathPlane(double Ext, double ShiftX, double ShiftY)
{
	EXT = Ext;
	SHIFTX = ShiftX;
	SHIFTY = ShiftY;
}

double fromMathPlane::toX(double mathX)
{
	return EXT*(mathX)+SHIFTX;
}

double fromMathPlane::toY(double mathY)
{
	return -EXT*(mathY)+SHIFTY;
}

double fromMathPlane::fromX(double DxX)
{
	return (DxX - SHIFTX) / EXT;
}

double fromMathPlane::fromY(double DxY)
{
	return -(DxY - SHIFTY) / EXT;
}
