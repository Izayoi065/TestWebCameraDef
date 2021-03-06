/**
* @file C_WinBase.h
* @brief
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once
// std::stringとstd::wstringの切り替え.
#ifdef UNICODE
#define tstring std::wstring
#else
#define tstring std::string
#endif

//------------------------------------------------------------------------------------------------------------------------------------------------
// 定義関数
//------------------------------------------------------------------------------------------------------------------------------------------------
#define apiLoadImage(h,id,type,cast)    ((cast)LoadImage(h,MAKEINTRESOURCE(id),type,0,0,(LR_DEFAULTSIZE | LR_SHARED)))
#define apiLoadIcon(h,id)               apiLoadImage(h,id,IMAGE_ICON,HICON)
#define apiLoadCursor(h,id)             apiLoadImage(h,id,IMAGE_CURSOR,HCURSOR)

/* 前方宣言 */
class CApplication;		// アプリケーションクラス CApplication

class C_WinBase {
public:
	/* メンバ変数 */
	HWND m_hWnd;			// ウィンドウハンドルm_hWnd
	CApplication * m_pApp;	// アプリケーションオブジェクトポインタm_pApp
	static std::map<HWND, C_WinBase *> m_mapWindowMap;	// ウィンドウハンドルからウィンドウオブジェクトを引くマップ.

	/* メンバ関数 */
	C_WinBase(CApplication *pApp);	// コンストラクタC_WinBase(pApp)
	virtual ~C_WinBase();			// デストラクタ~C_WinBase
	static BOOL RegisterClass(HINSTANCE hInstance);	// ウィンドウクラス登録関数RegisterClass.
	static LRESULT CALLBACK StaticWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);	// 最初にシステムからメッセージが届くウィンドウプロシージャStaticWindowProc.

	/* 仮想関数 */
	virtual BOOL Create(LPCTSTR lpctszClassName, LPCTSTR lpctszWindowName, DWORD dwStyle,
		const RECT & rect, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance);					// ウィンドウ作成関数 Create
	virtual BOOL Create(LPCTSTR lpctszWindowName, const RECT & rect);							// ウィンドウ作成関数 Create(ウィンドウ名とサイズのみのオーバーロード関数)
	virtual BOOL ShowWindow(int nCmdShow);														// ウィンドウ表示関数 ShowWindow
	virtual LRESULT DynamicWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);		// StaticWindowProcから各ウィンドウオブジェクトごとに呼び出されるウィンドウプロシージャ DynamicWindowProc

	/* 純粋仮想関数 */
	virtual int OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct) = 0;		// ウィンドウ作成時のハンドラ OnCreate
	virtual void OnDestroy() = 0;
protected:
private:
};