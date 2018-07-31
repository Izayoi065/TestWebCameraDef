/**
* @file WinMain.cpp
* @brief 
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define FRAME_RATE      (1000/25)   // フレームレート

/* インクルードファイルの追加 */
#include "WinMain.h"
int APIENTRY _tWinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR    lpCmdLine, 
	int       nCmdShow)
{
	::timeBeginPeriod(1);	// Windowsタイマーの最小制度(15msec)を1msecにする
	DWORD dwTime = ::timeGetTime() + FRAME_RATE;


	::timeEndPeriod(1);	// Windowsタイマーの最小制度を戻す

	return 0;
}
