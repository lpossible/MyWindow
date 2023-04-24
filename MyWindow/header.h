#pragma once
#include <windows.h>
#include <windowsx.h>
#include <winuser.h>
#include <Mmsystem.h>
#pragma comment(lib,"Winmm.lib")

#include <stdio.h>
#include <assert.h>

#if defined(DEBUG) | defined(_DEBUG)
#define D3D_DEBUG_INFO
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9effect.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")



#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_DELETE_RELEASE(p)	{ if(p) { (p)->Release(); (p)=NULL; } }

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;