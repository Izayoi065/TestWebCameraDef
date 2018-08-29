/**
* @file C_WinBase.cpp
* @brief
* @author Tomoki Kondo
* @date 2018/07/31
*/
/* �C���N���[�h�t�@�C�� */
#include "C_Application.h"	// �A�v���P�[�V�����N���X
#include "C_WinBase.h"		// ���E�B���h�E�N���X
#include "resource.h"		// ���\�[�X�t�@�C��

// static�����o�ϐ��̒�`.
std::map<HWND, C_WinBase *> C_WinBase::m_mapWindowMap;	// static�����o�ϐ�C_WinBase::m_mapWindowMap�͐錾�ƕʂɂ����ɒ�`���Ȃ��Ƃ����Ȃ�.

INT_PTR CALLBACK    Dialog(HWND, UINT, WPARAM, LPARAM);

/* �R���X�g���N�^ C_WinBase */
C_WinBase::C_WinBase(CApplication * pApp) {
	// �����o�̏�����
	m_hWnd = NULL;	// m_hWnd��NULL.
	m_pApp = pApp;	// m_pApp��pApp.
}

/* �f�X�g���N�^ ~C_WinBase */
C_WinBase::~C_WinBase() {

}

/* �E�B���h�E�N���X�o�^�֐� RegisterClass */
BOOL C_WinBase::RegisterClass(HINSTANCE hInstance) {
	/* �ϐ��̐錾 */
	WNDCLASSEX wcex = { 0 };	// �E�B���h�E�N���XEX wcex

								/* �E�B���h�E�N���X"C_WinBase"�̐ݒ� */
	wcex.cbSize = sizeof(WNDCLASSEX);						// �\���̂̃T�C�Y
	wcex.style = (CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS);	// �N���X�̃X�^�C��
	wcex.lpfnWndProc = C_WinBase::StaticWindowProc;				// �E�B���h�E�v���V�[�W���̐ݒ�
	wcex.cbClsExtra = 0;										// �g���T�C�Y�E�f�[�^�T�C�Y
	wcex.cbWndExtra = 0;										// �g���E�B���h�E�E�f�[�^�T�C�Y
	wcex.hInstance = hInstance;								// �C���X�^���X�E�n���h��
	wcex.hIcon = apiLoadIcon(NULL, IDI_APPLICATION);		// �A�C�R���̃n���h��
	wcex.hIconSm = apiLoadIcon(NULL, IDI_APPLICATION);		// �������A�C�R���̃n���h��
	wcex.hCursor = apiLoadCursor(NULL, IDC_ARROW);			// �J�[�\���̃n���h��
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);		// �w�i�u���V�̃n���h��
	wcex.lpszMenuName = (LPCWSTR)IDR_TESTWEBCAMERADEF;						// ���j���[�o�[�̎��ʕ�����
																//wcex.lpszMenuName = NULL;										// ���j���[�o�[�̎��ʕ�����
	wcex.lpszClassName = _T("C_WinBase");							// �E�B���h�E�N���X��"C_WinBase"

																	/* �E�B���h�E�N���X�̓o�^ */
	if (!::RegisterClassEx(&wcex)) {	// WindowsAPI��RegisterClass�֐��œo�^
		return FALSE;
	}

	// �����Ȃ�TRUE
	return TRUE;
}

/* static�E�B���h�E�v���V�[�W�� StaticWindowProc */
LRESULT C_WinBase::StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	// �|�C���^�̐錾
	C_WinBase *pWindow = NULL;		// C_WinBase �I�u�W�F�N�g�|�C���^ pWindow

	/* ���b�Z�[�W�E�B���h�E���� */
	switch (uMsg) {
		/* �E�B���h�E�̍쐬���J�n���ꂽ�� */
	case WM_CREATE:
		// WM_CREATE�̃u���b�N
	{
		// �|�C���^�̏�����
		LPCREATESTRUCT lpCreateStruct = NULL;	// CREATESTRUCT�\���̂ւ̃|�C���^lpCreateStruct��NULL

												/* lParam����lpCreateStruct�����o�� */
		lpCreateStruct = (LPCREATESTRUCT)lParam;	// lParam��(LPCREATESTRUCT)�ɃL���X�g
		if (lpCreateStruct->lpCreateParams != NULL) {	// NULL�łȂ��ꍇ
														// lpCreateStruct->lpCreateParams��(C_WinBase *)�ɃL���X�g��pWindow�ɓ����
			pWindow = (C_WinBase *)lpCreateStruct->lpCreateParams;
			// C_WinBase::m_mapWindowMap��hwnd��pWindow�̃y�A��o�^
		C_WinBase:m_mapWindowMap.insert(std::pair < HWND, C_WinBase *>(hwnd, pWindow));
		}
	}
	// ����̏����ֈȍ~
	break;
	/* ���� */
	default:
		// default�̃u���b�N
	{
		// hwnd�ŃE�B���h�E�I�u�W�F�N�g�|�C���^����������CpWindow�Ɋi�[
		if (C_WinBase::m_mapWindowMap.find(hwnd) != C_WinBase::m_mapWindowMap.end()) {	// hwnd��map�̍Ō�ɂɓo�^����Ă���ꍇ
																						// pWindow��hwnd�ň�����C_WinBase�I�u�W�F�N�g�|�C���^����
			pWindow = C_WinBase::m_mapWindowMap[hwnd];
		}
	}
	// ����̏����ֈȍ~
	break;
	}

	/* �E�B���h�E�I�u�W�F�N�g���擾�ł��Ȃ��ꍇ */
	if (pWindow == NULL) {	// pWindow��NULL
							// DefWindowProc�ɔC����.
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	else {		// pWindow��������
				// ���̃E�B���h�E��DynamicWindowProc�ɓn��.
		return pWindow->DynamicWindowProc(hwnd, uMsg, wParam, lParam);	// pWindow->DynamiProc�ɓn��.
	}
}

/* �E�B���h�E�쐬�֐� */
BOOL C_WinBase::Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle, const RECT & rect, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance) {
	// �E�B���h�E���쐬����.
	m_hWnd = CreateWindow(lpctszClassName, lpctszWindowName, dwStyle, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, hWndParent, hMenu, hInstance, this);	// CreateWindow�Ŏw�肳�ꂽ�������g���ăE�B���h�E���쐬.
	if (m_hWnd == NULL) {	// NULL�Ȃ玸�s.
							// FALSE��Ԃ�.
		return FALSE;
	}

	// �����Ȃ�TRUE.
	return TRUE;
}

/* �E�B���h�E�쐬�֐� Create�i�E�B���h�E���ƃT�C�Y�݂̂̃I�[�o�[���[�h�֐��j */
BOOL C_WinBase::Create(LPCTSTR lpctszWindowName, const RECT & rect) {

	// �A�v���P�[�V�����I�u�W�F�N�g�|�C���^�̃`�F�b�N
	if (m_pApp == NULL) {
		return FALSE;
	}

	// �f�t�H���g�̃E�B���h�E�쐬
	return C_WinBase::Create(_T("C_WinBase"), lpctszWindowName, WS_OVERLAPPEDWINDOW, rect, NULL, NULL, m_pApp->m_hInstance);	// �t���o�[�W������Create�ŃE�B���h�E�쐬.
}

/* �E�B���h�E�\���֐� ShowWindow */
BOOL C_WinBase::ShowWindow(int nCmdShow) {
	/* �E�B���h�E�\�� */
	return ::ShowWindow(m_hWnd, nCmdShow);	// WindowsAPI��ShowWindow��m_hWnd��\��.
}

/* �_�C�i�~�b�N�E�B���h�E�v���V�[�W�� DynamicWindowProc */
LRESULT C_WinBase::DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {

	switch (uMsg) {
		/* �E�B���h�E�̍쐬���J�n���ꂽ�� */
	case WM_CREATE:
		// WM_CREATE�u���b�N
	{
		// OnCreate�ɔC����.
		return OnCreate(hwnd, (LPCREATESTRUCT)lParam);	// hwnd��lParam��OnCreate�ɓn���Ă��Ƃ͔C����
	}
	// ����̏���
	break;
	/* �E�B���h�E���j�����ꂽ�� */
	case WM_DESTROY:
		// WM_DESTROY�u���b�N
	{
		// OnDestroy�ɔC����.
		OnDestroy();	// OnDestroy���Ă�
	}
	// ����̏���
	break;
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// �I�����ꂽ���j���[�̉��:
		switch (wmId)
		{
		case IDM_EXIT:
		{
			// OnDestroy�ɔC����.
			OnDestroy();	// OnDestroy���Ă�
		}
		// ����̏���
		break;
		case IDM_ABOUT:
		{
			DialogBox(C_WinBase::m_mapWindowMap[hwnd]->m_pApp->m_hInstance, MAKEINTRESOURCE(IDD_ABOUTBOX), C_WinBase::m_mapWindowMap[hwnd]->m_hWnd, Dialog);
		}
		// ����̏���
		break;
		}
	}
	// ����̏���
	break;
	/* ���̑� */
	default:
	{

	}
	// ����̏���
	break;
	}

	// DefWindowProc�ɔC����.
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

// �o�[�W�������{�b�N�X�̃��b�Z�[�W �n���h���[�ł��B
INT_PTR CALLBACK Dialog(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}