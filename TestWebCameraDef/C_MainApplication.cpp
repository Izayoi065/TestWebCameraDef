/**
* @file C_MainApplication.cpp
* @brief The main part necessary for running Windows application is described.
* @author Tomoki Kondo
* @date 2018/07/31
*/
/* インクルードファイル */
#include "C_Application.h"	// アプリケーションクラス
#include "C_MainApplication.h"	// メインアプリケーションクラス
#include "C_ViewDirectX11.h"	// DirectX11関連の初期化クラス

/* コンストラクタ CMainApplication */
CMainApplication::CMainApplication() {
}

/* デストラクタ ~CMainApplication */
CMainApplication::~CMainApplication() {

}

/* インスタンス初期化関数 InitInstance */
BOOL CMainApplication::InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) {
	// 変数の宣言
	RECT rc;	// ウィンドウサイズ rc

	// インスタンスハンドルをメンバにセット
	m_hInstance = hInstance;	// m_hInstanceにhInstanceをセット

	/* ウィンドウクラス"C_WinBase"の登録 */
	if (!C_WinBase::RegisterClass(m_hInstance)) {	// C_WinBase::RegisterClassで登録
		// エラー処理
		MessageBox(NULL, _T("ウィンドウクラスの登録に失敗しました!"), _T("C_WinBase"), MB_OK | MB_ICONHAND);	// MessageBoxで"ウィンドウクラスの登録に失敗しました!"と表示
		return -1;	// 異常終了
	}

	/* ウィンドウオブジェクトの作成 */
	//m_pWindow = new C_View(this);
	m_pWindow = new C_ViewDirectX11(this);

	/* ウィンドウサイズのセット */
	rc.left = 100;		// 100
	rc.top = 100;		// 100
	rc.right = 900;		// 100 + 800
	rc.bottom = 700;	// 100 + 600

	/* ウィンドウの作成 */
	if (!m_pWindow->Create(_T("C_WinBase"), rc)) {	// Createの省略版でウィンドウ作成
		// エラー処理
		MessageBox(NULL, _T("ウィンドウ作成に失敗しました!"), _T("C_WinBase"), MB_OK | MB_ICONHAND);	// MessageBoxで"ウィンドウ作成に失敗しました!"と表示
		return FALSE;	// FALSEを返す
	}

	/* ウィンドウ表示 */
	m_pWindow->ShowWindow(SW_SHOW);		// ShowWindowで表示

	// DirectX11の設定
	m_pWindow->InitDirectX11(hInstance, lpCmdLine, nShowCmd);

	// TRUEで返す
	return TRUE;
}

int CMainApplication::Run() {
	// 変数の宣言
	MSG msg;			// メッセージ情報msg
	LONG lCount = 0;	// ループ回数lCount

	/* メッセージループ */
	while (TRUE) {
		// メッセージが来ているかを確認
		if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE)) {	// PeekMessageでメッセージを確認
			if (GetMessage(&msg, NULL, 0, 0) > 0) {	// GetMessageでメッセージ取得.
													/* ウィンドウメッセージの送出 */
				DispatchMessage(&msg);	// DispatchMessageでウィンドウプロシージャに送出
				TranslateMessage(&msg);	// TranslateMessageで仮想キーメッセージを文字へ変換
			}
			else {	// WM_QUITまたはエラー
					// メッセージループを抜ける
				break;	// breakで抜ける
			}
		}
		else {	// メッセージが来ていない場合
				/* アイドル処理 */
			if (OnIdle(lCount)) {	// OnIdleにlCountを渡して, この中でアイドル処理をする
				lCount++;	// TRUEで返ってくるたびにlCountを増やす
			}
		}
	}

	/* 終了処理 */
	return ExitInstance();	// ExitInstanceの戻り値を返す
}
