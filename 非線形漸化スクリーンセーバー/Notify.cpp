#include "Notify.h"
#include"DxLib.h"
#include <stdlib.h>

iNotifyCircle::iNotifyCircle(int x, int y, int color)
{
	X = x+rand()%10-5;
	Y = y + rand() % 10 - 5;
	COLOR = color;
}

int iNotifyCircle::DO()
{
	SetDrawBlendMode(DX_BLENDMODE_ADD, 255/clockmax*clock*0.8);
	DrawCircle(X, Y,rand()%4, COLOR, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	clock--;
	if (clock == 0)return DELETECODE;
	return REGULRARCODE;
}

iNotifyMessage::iNotifyMessage(int x, int y, int color, string message)
{
	X = x, Y = y, COLOR = color, MESSAGE = message;
	FONT= CreateFontToHandle("ƒƒCƒŠƒI", 30, 4, DX_FONTTYPE_NORMAL);
}

int iNotifyMessage::DO()
{
	DrawFormatStringToHandle(X, Y, COLOR, FONT, MESSAGE.c_str());

	clock--;
	if (clock == 0)return DELETECODE;
	return REGULRARCODE;
}

Notify::Notify()
{
}

void Notify::DO()
{
	itr = list.begin();
	while (itr!=list.end()) {
		if ((*itr)->DO() == (*itr)->DELETECODE) {
			itr=list.erase(itr);
		}
		++itr;
	}
}

void Notify::MakeCircle(int x, int y, int color)
{
	list.push_back((biNotify*)new iNotifyCircle(x, y, color));
}

void Notify::MakeMessage(int x, int y, int color, string message)
{
	list.push_back((biNotify*)new iNotifyMessage(x, y, color,message));
}
