#pragma once
class fromMathPlane {
private:
	double EXT;
	double SHIFTX;
	double SHIFTY;
public:
	//(gå¦,EÖÌÚ®£,ºÖÌÚ®£)
	fromMathPlane(double Ext, double ShiftX, double ShiftY);
	//w¨DxLib
	double toX(double mathX);
	//w¨DxLib
	double toY(double mathY);
	//DxLib¨w
	double fromX(double DxX);
	//DxLib¨w
	double fromY(double DxY);
};