#pragma once
#include "header.h"


class WinAppation
{
public:
	WinAppation();
	virtual ~WinAppation();

	//创建窗口
	bool CreateWind(HINSTANCE hInstance, int width, int height, const char* name);
	void DestoryWind();

	//创建d3d对象
	bool CreateD3dDevice();
	void CleanD3dDevice();

	//
	void Render();

private:
	IDirect3D9* m_d3d;
	IDirect3DDevice9* m_d3ddevice;
	HWND m_hwnd;
};