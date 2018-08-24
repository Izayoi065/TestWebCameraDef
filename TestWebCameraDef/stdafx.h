// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

/* Direct3D 11�֘A�̃��C�u�����̃����N */
#pragma comment( lib, "d3d11.lib")
#if defined(DEBUG) || defined(_DEBUG)
#pragma comment( lib, "d3dx11d.lib")
#else
#pramga comment(lib, "d3dx11.lib")
#endif
#pragma comment( lib, "dxerr.lib" )

/* OpenCV�֘A�̃��C�u�����̃����N */
#ifdef _DEBUG
#define CV_EXT "d.lib"
#else
#define CV_EXT ".lib"
#endif
#pragma comment(lib, "opencv_world340" CV_EXT)

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <Windows.h>	// �W��WindowsAPI

/* C �����^�C���w�b�_�[�t�@�C�� */
#include <tchar.h>		// TCHAR�^
#include <string>		// std::string
#include <map>			// std::map
#include <crtdbg.h>		// 
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

// TODO: �v���O�����ɕK�v�Ȓǉ��w�b�_�[�������ŎQ�Ƃ��Ă�������
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

#include <sstream>
#include <iostream>
#include <time.h>

/* DirectX�֘A */
#include <d3dx11.h>		// 
#include <dxerr.h>		// 

/* OpenCV�֘A */
#include <opencv2/opencv.hpp>