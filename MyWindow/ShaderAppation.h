#pragma once
#include "header.h"
#include "ShaderSimpler.h"
#include "RenderTarget.h"


enum  EShaderType
{
	EST_BasicLighting,
	ESS_PongShading,
	EST_End
};


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
	void OpenSampler(EShaderType e);
	void CallFPS();

	//
	void SetScreenShot(bool flag) { m_bStartShoot = flag; }
	bool GetScreenShot() { return m_bStartShoot; }
private:
	IDirect3D9* m_d3d;
	IDirect3DDevice9* m_d3ddevice;


	ShaderSimpler* m_pSimpler;

	D3DXVECTOR3	m_lightPos = D3DXVECTOR3(0, 0, 0);
	HWND m_hwnd;

	//
	float FPS;

	//
	bool m_bStartShoot = false;
	CRenderTarget* m_shotRender = nullptr;
};