/**
* @file C_Application.h
* @brief The template required for running the Windows application is described.
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once

/* 前方宣言 */
class C_ViewDirectX11;	// ウィンドウクラス

class CApplication {
public:
	/* publicメンバ変数 */
	HINSTANCE m_hInstance;	// アプリケーションインスタンスハンドルm_hInstance
	C_ViewDirectX11 *m_pWindow;		// ウィンドウクラスポインタm_pWindow

	/* publicメンバ関数 */
	CApplication();				// コンストラクタ
	virtual ~CApplication();	// デストラクタ

	/* 仮想関数 */
	virtual int Run();	// メッセージループ関数Run
	virtual int ExitInstance();	// インスタンス終了処理関数ExitInstance
	virtual BOOL OnIdle(LONG lCount);	// アイドル処理関数OnIdle

	/* 純粋仮想関数 */
	virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd) = 0;		// インスタンス初期化関数 InitInstance

protected:
private:
};