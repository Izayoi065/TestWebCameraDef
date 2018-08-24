#include "C_Application.h"
/**
* @file C_Application.cpp
* @brief The template required for running the Windows application is described.
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define SAFE_DALETE(x) {if(x) {delete (x); (x) = NULL;}}	// 生成したオブジェクトを開放し，NULLを代入する

/* インクルードファイル */
#include "C_Application.h"	// アプリケーションクラス

/* コンストラクタ CApplication */
CApplication::CApplication() {
	/* メンバの初期化 */
	m_hInstance = NULL;	// インスタンスハンドルをNULL
	m_pWindow = NULL;	// ウィンドウオブジェクトをNULL
}

/* デストラクタ ~CApplication */
CApplication::~CApplication() {
	/* ウィンドウオブジェクトが残っていたら解放 */
	SAFE_DALETE(m_pWindow);
}

/* システムの実行部分 Run */
int CApplication::Run() {
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
		float ClearColor[] = { 0.0f, 1.0f, 1.0f, 1.0f };

	}

	/* 終了処理 */
	return ExitInstance();	// ExitInstanceの戻り値を返す
}

/* インスタンス終了処理関数 ExitInstance */
int CApplication::ExitInstance() {
	/*インスタンス終了処理の通知 */
	MessageBox(NULL, TEXT("インスタンス終了処理を行った!!"), TEXT("Message"), MB_OK | MB_ICONWARNING);

	/* ウィンドウオブジェクトが残っていたら解放 */
	SAFE_DALETE(m_pWindow);

	/* 正常終了 */
	return 0;
}

/* アイドル処理関数 OnIdle */
BOOL CApplication::OnIdle(LONG lCount) {
	// とりあえずTRUE
	return TRUE;
}
