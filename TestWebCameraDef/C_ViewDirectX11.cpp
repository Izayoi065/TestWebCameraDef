/**
* @file C_ViewDirectX11.cpp
* @brief 
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

/* インクルードファイル */
#include "C_ViewDirectX11.h"	// DirectX11関連の初期化クラス

/* コンストラクタ C_ViewDirectX11(pApp) */
C_ViewDirectX11::C_ViewDirectX11(CApplication * pApp) : C_WinBase(pApp) {
	MessageBox(NULL, TEXT("C_Viewオブジェクトの生成に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);
	/* メンバの初期化 */
	hpDevice = NULL;
	hpDeviceContext = NULL;
	hpDXGIFactory = NULL;
	hpDXGI = NULL;
	hpAdapter = NULL;
}

/* デストラクタ ~C_ViewDirectX11() */
C_ViewDirectX11::~C_ViewDirectX11() {
	SAFE_RELEASE(hpRenderTargetView);
	SAFE_RELEASE(hpBackBuffer);
	SAFE_RELEASE(hpDXGISwpChain);
	SAFE_RELEASE(hpDXGIFactory);
	SAFE_RELEASE(hpAdapter);
	SAFE_RELEASE(hpDXGI);
	SAFE_RELEASE(hpDeviceContext);
	SAFE_RELEASE(hpDevice);
}

HRESULT C_ViewDirectX11::InitDirectX11(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) {
	MessageBox(NULL, TEXT("InitDirectX11の起動に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* デバイスの作成 */
	HRESULT hr;
	hr = D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&hpDevice,
		NULL,
		&hpDeviceContext);

	if (FAILED(hr)) {
		MessageBox(m_hWnd, _T("D3D11CreateDevice"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}

	MessageBox(NULL, TEXT("デバイスの作成に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* インターフェース取得 */
	if (FAILED(hpDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&hpDXGI))) {
		MessageBox(m_hWnd, _T("QueryInterface"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("インターフェースの取得に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* アダプター取得 */
	if (FAILED(hpDXGI->GetAdapter(&hpAdapter))) {
		MessageBox(m_hWnd, _T("GetAdapter"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}

	/* ファクトリー取得 */
	hpAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&hpDXGIFactory);
	if (hpDXGIFactory == NULL) {
		MessageBox(m_hWnd, _T("GetParent"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}

	/* ALT+Enterでフルスクリーンを許可する */
	if (FAILED(hpDXGIFactory->MakeWindowAssociation(m_hWnd, 0))) {
		MessageBox(m_hWnd, _T("MakeWindowAssociation"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("ALT+Enterフルスクリーンを許可しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* スワップチェイン作成 */
	hDXGISwapChainDesc.BufferDesc.Width = 1980;
	hDXGISwapChainDesc.BufferDesc.Height = 1080;
	hDXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	hDXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	hDXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	hDXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	hDXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	hDXGISwapChainDesc.SampleDesc.Count = 1;
	hDXGISwapChainDesc.SampleDesc.Quality = 0;
	hDXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	hDXGISwapChainDesc.BufferCount = 1;
	hDXGISwapChainDesc.OutputWindow = m_hWnd;		//////////
	hDXGISwapChainDesc.Windowed = TRUE;
	hDXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	hDXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	if (FAILED(hpDXGIFactory->CreateSwapChain(hpDevice, &hDXGISwapChainDesc, &hpDXGISwpChain))) {
		MessageBox(m_hWnd, _T("CreateSwapChain"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("スワップチェインの作成に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//そのスワップチェインのバックバッファ取得
	if (FAILED(hpDXGISwpChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&hpBackBuffer))) {
		MessageBox(m_hWnd, _T("SwpChain GetBuffer"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("スワップチェインのバックバッファ取得に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//そのバックバッファから描画ターゲット生成
	if (FAILED(hpDevice->CreateRenderTargetView(hpBackBuffer, NULL, &hpRenderTargetView))) {
		MessageBox(m_hWnd, _T("CreateRenderTargetView"), _T("Err"), MB_ICONSTOP);
	}
	MessageBox(NULL, TEXT("バックバッファから描画ターゲット生成に成功しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//更にその描画ターゲットをコンテキストに設定
	hpDeviceContext->OMSetRenderTargets(1, &hpRenderTargetView, NULL);
	MessageBox(NULL, TEXT("描画ターゲットをコンテキストに設定しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//ビューポート設定
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 720;
	vp.Height = 600;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	hpDeviceContext->RSSetViewports(1, &vp);
	MessageBox(NULL, TEXT("ビューポートを設定しました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	MessageBox(NULL, TEXT("InitDirectX11は無事に処理を終えました!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	return MB_OK;
}

void C_ViewDirectX11::ViewRender(cv::Mat orgImage) {
	HRESULT hr = S_OK;

	cv::Mat convertedImg;
	cv::cvtColor(orgImage, convertedImg, CV_BGR2BGRA); //CV_8UC3 -> CV_8UC4

	int imageWidth = orgImage.cols;
	int imageHeight = orgImage.rows;
	unsigned char* pImage = new unsigned char[orgImage.total()];
	memcpy(pImage, orgImage.data, orgImage.total());

	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = orgImage.cols;
	desc.Height = orgImage.rows;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D* pTexture2D = NULL;
	this->hpDevice->CreateTexture2D(&desc, NULL, &pTexture2D);

	// テクスチャリソースをマップする
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	hr = this->hpDeviceContext->Map(pTexture2D,
		D3D11CalcSubresource(0, 0, 1),
		D3D11_MAP_WRITE_DISCARD,
		0,
		&MappedResource);
	// テクスチャにリソースを書き込む
	UCHAR* pTexels = (UCHAR*)MappedResource.pData;
	for (UINT row = 0; row < desc.Height; row++) {	// 行（高さ方向）
		UINT rowStart = row * MappedResource.RowPitch;
		cv::Vec3b *src = orgImage.ptr<cv::Vec3b>(row);
		for (UINT col = 0; col < desc.Width; col++) {	// 列（幅方向）
			UINT colStart = col * 4;
			cv::Point3_<uchar>* p = orgImage.ptr<cv::Point3_<uchar> >(row, col);
			pTexels[rowStart + colStart + 0] = p->z;	// R
			pTexels[rowStart + colStart + 1] = p->y;	// G
			pTexels[rowStart + colStart + 2] = p->x;	// B
			pTexels[rowStart + colStart + 3] = 32;	// A
		}
	}

	float ClearColor[] = { (float)rand() / RAND_MAX * 0.5f + 0.5f,(float)rand() / RAND_MAX * 1.0f,(float)rand() / RAND_MAX * 1.0f,(float)rand() / RAND_MAX * 1.0f };
	this->hpDeviceContext->ClearRenderTargetView(this->hpRenderTargetView, ClearColor);
	this->hpDXGISwpChain->Present(0, 0);

	//this->m_pWindow->hpDeviceContext->ClearRenderTargetView(this->m_pWindow->hpRenderTargetView, ClearColor);
	//this->m_pWindow->hpDXGISwpChain->Present(0, 0);

}

/* ウィンドウ作成時のハンドラ OnCreate */
int C_ViewDirectX11::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
	// ウィンドウ作成成功
	return 0;
}

/* ウィンドウ破棄時のハンドラ OnDestroy */
void C_ViewDirectX11::OnDestroy() {
	// メッセージループ終了
	PostQuitMessage(0);	// PostQuitMessageでメッセージループを終わらせる
}
