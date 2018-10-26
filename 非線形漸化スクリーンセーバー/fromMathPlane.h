#pragma once
class fromMathPlane {
private:
	double EXT;
	double SHIFTX;
	double SHIFTY;
public:
	//(拡大率,右への移動距離,下への移動距離)
	fromMathPlane(double Ext, double ShiftX, double ShiftY);
	//数学→DxLib
	double toX(double mathX);
	//数学→DxLib
	double toY(double mathY);
	//DxLib→数学
	double fromX(double DxX);
	//DxLib→数学
	double fromY(double DxY);
};