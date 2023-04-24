#pragma once
#include "header.h"

class DrawUtil
{
public:
	DrawUtil();
	~DrawUtil();

	static DrawUtil* GetInstance();
	bool Init(IDirect3DDevice9* pD3DDevice);
	void Destory();
	
	ID3DXEffect* LoadEffect(IDirect3DDevice9* pD3DDevice, const char* szFileName);

	void DrawLight(D3DXVECTOR3 pos);
	void DrawMyText(const char* szText, int x, int y, D3DCOLOR color = 0xffffffff);
public:
	ID3DXFont* m_pD3DFont;
	ID3DXMesh* m_pLightBox;
	ID3DXEffect* m_pEffect;
};