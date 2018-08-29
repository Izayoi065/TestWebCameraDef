/**
* @file C_MainApplication.h
* @brief The main part necessary for running Windows application is described.
* @author Tomoki Kondo
* @date 2018/07/31
*/
#pragma once

/* インクルードファイル */
#include "C_Application.h"	// アプリケーションクラス

/* 前方宣言 */
class CApplication;

class CMainApplication : public CApplication {
public:
	/* publicメンバ関数 */
	CMainApplication();				// コンストラクタ
	virtual ~CMainApplication();	// デストラクタ

	/* 仮想関数 */
	virtual BOOL InitInstance(HINSTANCE hInstance, LPTSTR lpCmdLine, int nShowCmd);	// インスタンス初期化関数 InitInstance
	virtual int Run();

protected:
private:
};