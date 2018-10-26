#pragma once
#include"fromMathPlane.h"
#include"Notify.h"

typedef enum eMODE{
	sOpening,
	sUp,
	sLeft,
	sRight,
	sDown
};

class Parabola {
private:
	fromMathPlane *Plane;
	Notify *Noti;
	int ShapeScreen;
	double START, R;
	int WIDTH, HEIGHT;
	long double S, T;
	eMODE NOW = sOpening;
	int FONT;
public:
	//a[n+1]=ra[n](1-a[n])‚Ì”—ñ‚ğUI‚ğ”º‚¢‚È‚ª‚çi‚Ş
	Parabola(int Width, int Height, long double start, long double r);
	void DO();
	long double func_Straight(long double x);
	long double func_Parabola(long double x);
};