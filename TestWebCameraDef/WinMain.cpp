/**
* @file WinMain.cpp
* @brief 
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define FRAME_RATE      (1000/25)   // �t���[�����[�g
#define SAFE_DALETE(x) {if(x) {delete (x); (x) = NULL;}}	// ���������I�u�W�F�N�g���J�����CNULL��������

/* �C���N���[�h�t�@�C���̒ǉ� */
#include "stdafx.h"
#include "WinMain.h"
#include "C_MainApplication.h"	// ���C���A�v���P�[�V�����N���X

int APIENTRY _tWinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR    lpCmdLine, 
	int       nCmdShow)
{
	// �ϐ��E�I�u�W�F�N�g�̐錾
	CApplication *pApp;	// CApplication�I�u�W�F�N�g�|�C���^pApp
	int iRet;	// Run�̖߂�l:iRet

	::timeBeginPeriod(1);	// Windows�^�C�}�[�̍ŏ����x(15msec)��1msec�ɂ���
	DWORD dwTime = ::timeGetTime() + FRAME_RATE;

	// ���C���A�v���P�[�V�����I�u�W�F�N�g�̐���
	pApp = new CMainApplication();	// CMainApplication�I�u�W�F�N�g���쐬

	// �C���X�^���X������
	if (!pApp->InitInstance(hInstance, lpCmdLine, nCmdShow)) {	// InitInstance�ŏ�����
		/* FALSE�Ȃ�I������ */
		pApp->ExitInstance();	// ExitInstance�ŏI������
		delete pApp;			// pApp�����
		return -1;				// �ُ�I���Ȃ̂�-1��Ԃ�
	}

	// ���b�Z�[�W���[�v
	iRet = pApp->Run();	// Run�Ń��b�Z�[�W���[�v, �I��������߂�l��iRet��


	::timeEndPeriod(1);	// Windows�^�C�}�[�̍ŏ����x��߂�

	// �A�v���P�[�V�����I�u�W�F�N�g�̊J��
	SAFE_DALETE(pApp);

	// �v���O�����̏I��
	return 0;	// ����I����0��Ԃ�
}
