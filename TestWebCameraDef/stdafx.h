// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

/* Direct3D 11関連のライブラリのリンク */
#pragma comment( lib, "d3d11.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx11d.lib")
#else
#pramga comment(lib, "d3dx11.lib")
#endif
#pragma comment( lib, "dxerr.lib" )

/* OpenCV関連のライブラリのリンク */
#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world340" CV_EXT)

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <Windows.h>	// 標準WindowsAPI

/* C ランタイムヘッダーファイル */
#include <tchar.h>		// TCHAR型
#include <string>		// std::string
#include <map>			// std::map
#include <crtdbg.h>		// 
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

// TODO: プログラムに必要な追加ヘッダーをここで参照してください
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#include <sstream>
#include <iostream>
#include <time.h>

/* DirectX関連 */
#include <d3dx11.h>		// 
#include <dxerr.h>		// 

/* OpenCV関連 */
#include <opencv2/opencv.hpp>