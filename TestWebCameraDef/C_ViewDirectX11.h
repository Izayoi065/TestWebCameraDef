/**
* @file C_ViewDirectX11.h
* @brief
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once
/* �C���N���[�h�t�@�C�� */
#include "C_WinBase.h"		// ���E�B���h�E�N���X

/* �O���錾 */
class C_WinBase;
class CApplication;

typedef class C_ViewDirectX11 : public C_WinBase {
public:
	/* �����o�ϐ� */
	ID3D11Device * hpDevice;
	ID3D11DeviceContext* hpDeviceContext;
	IDXGIFactory* hpDXGIFactory;
	IDXGIDevice1* hpDXGI;
	IDXGIAdapter* hpAdapter;
	IDXGISwapChain* hpDXGISwpChain;
	DXGI_SWAP_CHAIN_DESC hDXGISwapChainDesc;
	ID3D11Texture2D* hpBackBuffer;
	ID3D11RenderTargetView *hpRenderTargetView;
	D3D11_VIEWPORT vp;

	/* �����o�֐� */
	C_ViewDirectX11(CApplication *pApp);	// �R���X�g���N�^ C_ViewDirectX11
	virtual ~C_ViewDirectX11();				// �f�X�g���N�^ C_ViewDirectX11

	HRESULT InitDirectX11(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);
	void ViewRender(cv::Mat orgImage);

	/* ���z�֐� */
	virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// �E�B���h�E�쐬���̃n���h��OnCreate
	virtual void OnDestroy();	// �E�B���h�E�j�����̃n���h�� Ondestroy
protected:
private:
};