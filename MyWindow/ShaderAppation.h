#pragma once
#include "header.h"


enum EShaderType
{
	EST_BasicLighting,
	EST_End
};


class WinAppation
{
public:
	WinAppation();
	virtual ~WinAppation();

	//��������
	bool CreateWind(HINSTANCE hInstance, int width, int height, const char* name);
	void DestoryWind();

	//����d3d����
	bool CreateD3dDevice();
	void CleanD3dDevice();

	//
	void Render();

private:
	IDirect3D9* m_d3d;
	IDirect3DDevice9* m_d3ddevice;
	HWND m_hwnd;
};