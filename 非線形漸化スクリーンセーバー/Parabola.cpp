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
	DxX = Plane->toX(mathX);//���w����x=0����n�߂�
	for (0; mathX < 1; DxX++) {//���w����x<0�܂�
		//���̕`���DxLib���ʏ�̃s�N�Z���P�ʂł����߂�
		mathX = Plane->fromX(DxX);//��񐔊w�ōl����

		/*�������`��*/
		mathY = func_Parabola(mathX);
		DxY = Plane->toY(mathY);//�Z�o���ꂽ���wy���W��DxLiby���W��
		DrawCircle(DxX, DxY, 2, GetColor(160, 160, 160), TRUE);

		/*�����`��*/
		mathY = func_Straight(mathX);
		DxY = Plane->toY(mathY);
		DrawCircle(DxX, DxY, 1, GetColor(160, 160, 160), TRUE);
	}

	mathX = 0, mathY = 0, DxX = 0, DxY = 0;
	DxX = Plane->toX(-0.2);//���w����x=-0.2����n�߂�
	for (0; mathX < 1.2; DxX++) {//���w����x<1.2�܂�
		 //���̕`���DxLib���ʏ�̃s�N�Z���P�ʂł����߂�
		mathX = Plane->fromX(DxX);//��񐔊w�ōl����

		/*x���`��*/
		DxY = Plane->toY(0);
		DrawCircle(DxX, DxY, 1, GetColor(120, 120, 120), TRUE);
	}
	

	mathX = 0, mathY = 0, DxX = 0, DxY = 0;
	DxY = Plane->toY(-0.2);//���w����y=-0.2����n�߂�
	for (0; mathY < 1.2; DxY--) {//���w����y<1.2�܂�
		mathY = Plane->fromY(DxY);//��񐔊w�ōl����

		/*y���`��*/
		DxX = Plane->toX(0);
		DrawCircle(DxX, DxY, 1, GetColor(120, 120, 120), TRUE);
	};
	SetDrawScreen(DX_SCREEN_BACK);

	FONT = CreateFontToHandle("���C���I", 43, 6, DX_FONTTYPE_NORMAL);
	Noti = new Notify();
}

void Parabola::DO()
{
	static int timer = 120;

	//���G�Ȑ}�`�̕`��
	DrawGraph(0, 0, ShapeScreen, FALSE);

	//�ʂ̈ړ�
	long double MovingSpeed = 0.02;

	switch(NOW){
	case sOpening:
		timer--;
		if (timer == 0)NOW = sUp;
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
		DrawBox(0, 0, WIDTH, HEIGHT, GetColor(250, 250, 250), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		DrawFormatStringToHandle(0, 200, GetColor(0, 0, 0), FONT,
			"a[n+1]=ra[n](1-a[n]) \n\n���̍�=�萔���~�����̍��~�i�P�|�����̍��j\n\n���� = %lf\n�萔r = %lf", START, R);
		break;
	case sUp:
		T += MovingSpeed;
		if (T > func_Parabola(S)) { //����������ɍs����
			T = func_Parabola(S);
			if (T < (func_Straight(S))) NOW = sLeft;//������艺�ɂ����獶�֍s��
			if (T > (func_Straight(S))) NOW = sRight;//��������ɂ�����E�֍s��
			if(T== (func_Straight(S))) NOW = sDown;//������ɂ����牺��
		}
		break;
	case sLeft:
		S -= MovingSpeed;
		if (T > func_Straight(S)) {//��������ɔ������牺��
			T = func_Straight(S);
			NOW = sDown;
		}
		break;
	case sRight:
		S += MovingSpeed;
		if (T < func_Straight(S)) {//������艺�ɔ������牺��
			T = func_Straight(S);
			NOW = sDown;
		}
		break;
	case sDown:
		T -= MovingSpeed;
		if(T<0){//X����艺�ɍs������o��
			T = 0;
			NOW = sUp;
			for (int i = 0; i < 70; i++)Noti->MakeCircle(Plane->toX(S)+rand()%35-17, Plane->toY(T) + rand() %35- 17, GetColor(150 + rand() % 72, 150 + rand() % 72, 150 + rand() % 72));
		}
		if (S > 1)S = 1;
		if (S < 0)S = 0;//�[������
		break;
	}
	DrawCircle(Plane->toX(S), Plane->toY(T), 7, GetColor(255, 255, 255), TRUE);
	
	for (int i = 0; i < 3;i++)Noti->MakeCircle(Plane->toX(S), Plane->toY(T), GetColor(194 + rand() % 25, 125 + rand() % 90, 50 + rand() % 60));

	//�ʒm�nUI�̕\��
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
