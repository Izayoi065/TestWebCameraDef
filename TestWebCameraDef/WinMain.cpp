/**
* @file WinMain.cpp
* @brief 
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define FRAME_RATE      (1000/25)   // �t���[�����[�g

/* �C���N���[�h�t�@�C���̒ǉ� */
#include "WinMain.h"
int APIENTRY _tWinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR    lpCmdLine, 
	int       nCmdShow)
{
	::timeBeginPeriod(1);	// Windows�^�C�}�[�̍ŏ����x(15msec)��1msec�ɂ���
	DWORD dwTime = ::timeGetTime() + FRAME_RATE;


	::timeEndPeriod(1);	// Windows�^�C�}�[�̍ŏ����x��߂�

	return 0;
}
