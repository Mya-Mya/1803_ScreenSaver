#pragma once
class fromMathPlane {
private:
	double EXT;
	double SHIFTX;
	double SHIFTY;
public:
	//(�g�嗦,�E�ւ̈ړ�����,���ւ̈ړ�����)
	fromMathPlane(double Ext, double ShiftX, double ShiftY);
	//���w��DxLib
	double toX(double mathX);
	//���w��DxLib
	double toY(double mathY);
	//DxLib�����w
	double fromX(double DxX);
	//DxLib�����w
	double fromY(double DxY);
};