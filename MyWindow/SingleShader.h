#pragma once

#include "d3d9.h"
#include "d3dx9.h"

using ID3DTexture = IDirect3DTexture9;


class SingleShader
{
public:
	SingleShader();
	~SingleShader();
	bool LoadTexFromJepg(IDirect3DDevice9* pDevice,char* path);
	void Render(IDirect3DDevice9* pDevice);
private:
	ID3DTexture* m_pTex;
	int m_width;
	int m_height;
};
