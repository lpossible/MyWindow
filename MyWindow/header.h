#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <windows.h>



#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_DELETE_RELEASE(p)	{ if(p) { (p)->Release(); (p)=NULL; } }

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;