/**
* @file WinMain.cpp
* @brief 
* @author Tomoki Kondo
* @date 2018/07/31
*/
#define FRAME_RATE      (1000/25)   // フレームレート
#define SAFE_DALETE(x) {if(x) {delete (x); (x) = NULL;}}	// 生成したオブジェクトを開放し，NULLを代入する

/* インクルードファイルの追加 */
#include "stdafx.h"
#include "WinMain.h"
#include "C_MainApplication.h"	// メインアプリケーションクラス

int APIENTRY _tWinMain(HINSTANCE hInstance, 
	HINSTANCE hPrevInstance, 
	LPTSTR    lpCmdLine, 
	int       nCmdShow)
{
	// 変数・オブジェクトの宣言
	CApplication *pApp;	// CApplicationオブジェクトポインタpApp
	int iRet;	// Runの戻り値:iRet

	::timeBeginPeriod(1);	// Windowsタイマーの最小制度(15msec)を1msecにする
	DWORD dwTime = ::timeGetTime() + FRAME_RATE;

	// メインアプリケーションオブジェクトの生成
	pApp = new CMainApplication();	// CMainApplicationオブジェクトを作成

	// インスタンス初期化
	if (!pApp->InitInstance(hInstance, lpCmdLine, nCmdShow)) {	// InitInstanceで初期化
		/* FALSEなら終了処理 */
		pApp->ExitInstance();	// ExitInstanceで終了処理
		delete pApp;			// pAppを解放
		return -1;				// 異常終了なので-1を返す
	}

	// メッセージループ
	iRet = pApp->Run();	// Runでメッセージループ, 終了したら戻り値をiRetに


	::timeEndPeriod(1);	// Windowsタイマーの最小制度を戻す

	// アプリケーションオブジェクトの開放
	SAFE_DALETE(pApp);

	// プログラムの終了
	return 0;	// 正常終了の0を返す
}
