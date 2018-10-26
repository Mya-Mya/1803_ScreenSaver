#include"DxLib.h"
#include"Parabola.h"
#include"fromMathPlane.h"
#include <stdlib.h> /* �����֐��𗘗p����̂ɕK�v */
#include <time.h>   /* �����֐��̂��߂Ɏg���i�������𗘗p�j */

const int WIDTH = 900;
const int HEIGHT = 900;

int WINAPI WinMain(HINSTANCE,HINSTANCE,LPSTR,int) {
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

	srand(time(NULL)*time(NULL));
	long double start, r;
	start = (double)rand() / RAND_MAX;
	//r = (double)rand() / RAND_MAX * 4;
	r = 3.9;
	Parabola inst(WIDTH, HEIGHT,start,r);

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {
		inst.DO();
	}
	DxLib_End();
	return 0;
}