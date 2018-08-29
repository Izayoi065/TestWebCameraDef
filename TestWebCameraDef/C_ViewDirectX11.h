/**
* @file C_ViewDirectX11.h
* @brief
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once
/* インクルードファイル */
#include "C_WinBase.h"		// 基底ウィンドウクラス

/* 前方宣言 */
class C_WinBase;
class CApplication;

typedef class C_ViewDirectX11 : public C_WinBase {
public:
	/* メンバ変数 */
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

	/* メンバ関数 */
	C_ViewDirectX11(CApplication *pApp);	// コンストラクタ C_ViewDirectX11
	virtual ~C_ViewDirectX11();				// デストラクタ C_ViewDirectX11

	HRESULT InitDirectX11(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);
	void ViewRender(cv::Mat orgImage);

	/* 仮想関数 */
	virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);	// ウィンドウ作成時のハンドラOnCreate
	virtual void OnDestroy();	// ウィンドウ破棄時のハンドラ Ondestroy
protected:
private:
};