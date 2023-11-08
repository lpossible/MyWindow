#pragma once
#include "header.h"

class CRenderTarget
{
public:
	CRenderTarget(int width, int height, int usage, D3DFORMAT format);
	~CRenderTarget();
public:
	bool BeginRenderTarget(ID3DDevice* pDevice);
	bool EndRenderTarget(ID3DDevice* pDevice);
	bool CreateRenderTarget(ID3DDevice* pDevice);
	bool SaveToFile(const char* path);
	bool SaveToFileA(const char* path,ID3DDevice* pDevice);
	bool GetBackBufferSurFace(ID3DDevice* pDevice);
public:
	int m_iwidth, m_iheight;
	int m_usage;
	D3DFORMAT m_format;
	ID3DTexture* m_pTex = nullptr;
	ID3DSurface* m_pOldSurface = nullptr;
	ID3DSurface* m_pOffScreenSurface = nullptr;
};