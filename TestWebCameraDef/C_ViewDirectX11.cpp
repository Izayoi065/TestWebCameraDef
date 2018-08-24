/**
* @file C_ViewDirectX11.cpp
* @brief 
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define SAFE_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

/* �C���N���[�h�t�@�C�� */
#include "C_ViewDirectX11.h"	// DirectX11�֘A�̏������N���X

/* �R���X�g���N�^ C_ViewDirectX11(pApp) */
C_ViewDirectX11::C_ViewDirectX11(CApplication * pApp) : C_WinBase(pApp) {
	MessageBox(NULL, TEXT("C_View�I�u�W�F�N�g�̐����ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);
	/* �����o�̏����� */
	hpDevice = NULL;
	hpDeviceContext = NULL;
	hpDXGIFactory = NULL;
	hpDXGI = NULL;
	hpAdapter = NULL;
}

/* �f�X�g���N�^ ~C_ViewDirectX11() */
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
	MessageBox(NULL, TEXT("InitDirectX11�̋N���ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* �f�o�C�X�̍쐬 */
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

	MessageBox(NULL, TEXT("�f�o�C�X�̍쐬�ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* �C���^�[�t�F�[�X�擾 */
	if (FAILED(hpDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&hpDXGI))) {
		MessageBox(m_hWnd, _T("QueryInterface"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("�C���^�[�t�F�[�X�̎擾�ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* �A�_�v�^�[�擾 */
	if (FAILED(hpDXGI->GetAdapter(&hpAdapter))) {
		MessageBox(m_hWnd, _T("GetAdapter"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}

	/* �t�@�N�g���[�擾 */
	hpAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&hpDXGIFactory);
	if (hpDXGIFactory == NULL) {
		MessageBox(m_hWnd, _T("GetParent"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}

	/* ALT+Enter�Ńt���X�N���[���������� */
	if (FAILED(hpDXGIFactory->MakeWindowAssociation(m_hWnd, 0))) {
		MessageBox(m_hWnd, _T("MakeWindowAssociation"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("ALT+Enter�t���X�N���[���������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* �X���b�v�`�F�C���쐬 */
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
	MessageBox(NULL, TEXT("�X���b�v�`�F�C���̍쐬�ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//���̃X���b�v�`�F�C���̃o�b�N�o�b�t�@�擾
	if (FAILED(hpDXGISwpChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&hpBackBuffer))) {
		MessageBox(m_hWnd, _T("SwpChain GetBuffer"), _T("Err"), MB_ICONSTOP);
		OnDestroy();
	}
	MessageBox(NULL, TEXT("�X���b�v�`�F�C���̃o�b�N�o�b�t�@�擾�ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//���̃o�b�N�o�b�t�@����`��^�[�Q�b�g����
	if (FAILED(hpDevice->CreateRenderTargetView(hpBackBuffer, NULL, &hpRenderTargetView))) {
		MessageBox(m_hWnd, _T("CreateRenderTargetView"), _T("Err"), MB_ICONSTOP);
	}
	MessageBox(NULL, TEXT("�o�b�N�o�b�t�@����`��^�[�Q�b�g�����ɐ������܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//�X�ɂ��̕`��^�[�Q�b�g���R���e�L�X�g�ɐݒ�
	hpDeviceContext->OMSetRenderTargets(1, &hpRenderTargetView, NULL);
	MessageBox(NULL, TEXT("�`��^�[�Q�b�g���R���e�L�X�g�ɐݒ肵�܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	//�r���[�|�[�g�ݒ�
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 720;
	vp.Height = 600;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	hpDeviceContext->RSSetViewports(1, &vp);
	MessageBox(NULL, TEXT("�r���[�|�[�g��ݒ肵�܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	MessageBox(NULL, TEXT("InitDirectX11�͖����ɏ������I���܂���!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

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

	// �e�N�X�`�����\�[�X���}�b�v����
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	hr = this->hpDeviceContext->Map(pTexture2D,
		D3D11CalcSubresource(0, 0, 1),
		D3D11_MAP_WRITE_DISCARD,
		0,
		&MappedResource);
	// �e�N�X�`���Ƀ��\�[�X����������
	UCHAR* pTexels = (UCHAR*)MappedResource.pData;
	for (UINT row = 0; row < desc.Height; row++) {	// �s�i���������j
		UINT rowStart = row * MappedResource.RowPitch;
		cv::Vec3b *src = orgImage.ptr<cv::Vec3b>(row);
		for (UINT col = 0; col < desc.Width; col++) {	// ��i�������j
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

/* �E�B���h�E�쐬���̃n���h�� OnCreate */
int C_ViewDirectX11::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) {
	// �E�B���h�E�쐬����
	return 0;
}

/* �E�B���h�E�j�����̃n���h�� OnDestroy */
void C_ViewDirectX11::OnDestroy() {
	// ���b�Z�[�W���[�v�I��
	PostQuitMessage(0);	// PostQuitMessage�Ń��b�Z�[�W���[�v���I��点��
}
