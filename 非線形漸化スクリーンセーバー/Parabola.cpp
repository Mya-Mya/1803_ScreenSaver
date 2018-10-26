#include "Parabola.h"
#include"DxLib.h"
#include"fromMathPlane.h"
#include <stdlib.h>
#include<string>
using namespace std;

Parabola::Parabola(int Width, int Height, long double start, long double r)
{
	WIDTH = Width, HEIGHT = Height;
	START = start, R = r;
	S = START, T = 0;

	Plane= new fromMathPlane(Width*0.85, Width*0.1, Height-Height*0.1);
	ShapeScreen = MakeScreen(Width, Height, FALSE);
	SetDrawScreen(ShapeScreen);

	double mathX, mathY, DxX, DxY;
	
	mathX = 0, mathY = 0, DxX = 0, DxY = 0;
	DxX = Plane->toX(mathX);//数学平面x=0から始める
	for (0; mathX < 1; DxX++) {//数学平面x<0まで
		//線の描画はDxLib平面上のピクセル単位ですすめる
		mathX = Plane->fromX(DxX);//一回数学で考える

		/*放物線描く*/
		mathY = func_Parabola(mathX);
		DxY = Plane->toY(mathY);//算出された数学y座標をDxLiby座標へ
		DrawCircle(DxX, DxY, 2, GetColor(160, 160, 160), TRUE);

		/*直線描く*/
		mathY = func_Straight(mathX);
		DxY = Plane->toY(mathY);
		DrawCircle(DxX, DxY, 1, GetColor(160, 160, 160), TRUE);
	}

	mathX = 0, mathY = 0, DxX = 0, DxY = 0;
	DxX = Plane->toX(-0.2);//数学平面x=-0.2から始める
	for (0; mathX < 1.2; DxX++) {//数学平面x<1.2まで
		 //線の描画はDxLib平面上のピクセル単位ですすめる
		mathX = Plane->fromX(DxX);//一回数学で考える

		/*x軸描く*/
		DxY = Plane->toY(0);
		DrawCircle(DxX, DxY, 1, GetColor(120, 120, 120), TRUE);
	}
	

	mathX = 0, mathY = 0, DxX = 0, DxY = 0;
	DxY = Plane->toY(-0.2);//数学平面y=-0.2から始める
	for (0; mathY < 1.2; DxY--) {//数学平面y<1.2まで
		mathY = Plane->fromY(DxY);//一回数学で考える

		/*y軸描く*/
		DxX = Plane->toX(0);
		DrawCircle(DxX, DxY, 1, GetColor(120, 120, 120), TRUE);
	};
	SetDrawScreen(DX_SCREEN_BACK);

	FONT = CreateFontToHandle("メイリオ", 43, 6, DX_FONTTYPE_NORMAL);
	Noti = new Notify();
}

void Parabola::DO()
{
	static int timer = 120;

	//複雑な図形の描画
	DrawGraph(0, 0, ShapeScreen, FALSE);

	//玉の移動
	long double MovingSpeed = 0.02;

	switch(NOW){
	case sOpening:
		timer--;
		if (timer == 0)NOW = sUp;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WIDTH, HEIGHT, GetColor(250, 250, 250), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatStringToHandle(0, 200, GetColor(0, 0, 0), FONT,
			"a[n+1]=ra[n](1-a[n]) \n\n次の項=定数ｒ×自分の項×（１－自分の項）\n\n初項 = %lf\n定数r = %lf", START, R);
		break;
	case sUp:
		T += MovingSpeed;
		if (T > func_Parabola(S)) { //放物線より上に行った
			T = func_Parabola(S);
			if (T < (func_Straight(S))) NOW = sLeft;//直線より下にいたら左へ行け
			if (T > (func_Straight(S))) NOW = sRight;//直線より上にいたら右へ行け
			if(T== (func_Straight(S))) NOW = sDown;//直線上にいたら下れ
		}
		break;
	case sLeft:
		S -= MovingSpeed;
		if (T > func_Straight(S)) {//直線より上に抜けたら下れ
			T = func_Straight(S);
			NOW = sDown;
		}
		break;
	case sRight:
		S += MovingSpeed;
		if (T < func_Straight(S)) {//直線より下に抜けたら下れ
			T = func_Straight(S);
			NOW = sDown;
		}
		break;
	case sDown:
		T -= MovingSpeed;
		if(T<0){//X軸より下に行ったら登れ
			T = 0;
			NOW = sUp;
			for (int i = 0; i < 70; i++)Noti->MakeCircle(Plane->toX(S)+rand()%35-17, Plane->toY(T) + rand() %35- 17, GetColor(150 + rand() % 72, 150 + rand() % 72, 150 + rand() % 72));
		}
		if (S > 1)S = 1;
		if (S < 0)S = 0;//端数調整
		break;
	}
	DrawCircle(Plane->toX(S), Plane->toY(T), 7, GetColor(255, 255, 255), TRUE);
	
	for (int i = 0; i < 3;i++)Noti->MakeCircle(Plane->toX(S), Plane->toY(T), GetColor(194 + rand() % 25, 125 + rand() % 90, 50 + rand() % 60));

	//通知系UIの表示
	Noti->DO();
}

long double Parabola::func_Straight(long double x)
{
	return x;
}

long double Parabola::func_Parabola(long double x)
{
	return R * x*(1 - x);
}
