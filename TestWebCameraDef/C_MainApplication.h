/**
* @file C_MainApplication.h
* @brief The main part necessary for running Windows application is described.
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once

/* �C���N���[�h�t�@�C�� */
#include "C_Application.h"	// �A�v���P�[�V�����N���X

/* �O���錾 */
class CApplication;

class CMainApplication : public CApplication {
public:
	/* public�����o�֐� */
	CMainApplication();				// �R���X�g���N�^
	virtual ~CMainApplication();	// �f�X�g���N�^

	/* ���z�֐� */
	virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// �C���X�^���X�������֐� InitInstance
	virtual int Run();

protected:
private:
};