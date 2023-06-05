#pragma once
#include "ShaderSimpler.h"

class BasicLighting:public ShaderSimpler
{
public:
	BasicLighting();
	~BasicLighting();
public:
	void Render()override;
	bool Init(IDirect3DDevice9* pD3DDevice)override;
private:
	ID3DXEffect* m_pEffect;
	D3DXVECTOR3 m_lightPos;
};