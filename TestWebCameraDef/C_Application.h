/**
* @file C_Application.h
* @brief The template required for running the Windows application is described.
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once

class CApplication {
public:
	/* public�����o�ϐ� */
	/* public�����o�֐� */
	CApplication();				// �R���X�g���N�^
	virtual ~CApplication();	// �f�X�g���N�^
	/* ���z�֐� */
	virtual int Run();	// ���b�Z�[�W���[�v�֐�Run
	virtual int ExitInstance();	// �C���X�^���X�I�������֐�ExitInstance
	virtual BOOL OnIdle(LONG lCount);	// �A�C�h�������֐�OnIdle
	/* �������z�֐� */
	virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) = 0;		// �C���X�^���X�������֐� InitInstance
protected:
private:
};