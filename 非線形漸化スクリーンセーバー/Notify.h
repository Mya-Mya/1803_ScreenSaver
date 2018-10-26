#pragma once
#include<vector>
using namespace std;

class biNotify {
public:
	virtual int DO()=0;
	const int DELETECODE = 1;
	const int REGULRARCODE = 0;
};

class iNotifyCircle:public biNotify{
private:
	const int clockmax = 35;
	int X, Y, COLOR;
	int clock = clockmax;
public:
	iNotifyCircle(int x, int y, int color);
	int DO() override;
};

class iNotifyMessage :public biNotify {
private:
	string MESSAGE;
	int X, Y, COLOR;
	int clock = 120;
	int FONT;
public:
	iNotifyMessage(int x, int y, int color, string Message);
	int DO() override;
};

class Notify {
private:
	vector<biNotify*>list;
	vector<biNotify*>::iterator itr;
public:
	Notify();
	void DO();
	void MakeCircle(int x, int y, int color);
	void MakeMessage(int x,int y,int color,string message);
};