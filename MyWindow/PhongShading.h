#pragma once
#include "ShaderSimpler.h"

class PhongShading:public ShaderSimpler
{
public:
	PhongShading();
	~PhongShading();

public:
	virtual bool Init(IDirect3DDevice9* pD3DDevice)override;
	virtual void Render()override;
	virtual void DrawMesh()override;
private:
	ID3DXEffect* m_pEffect;
	D3DXVECTOR3 m_v3LightPos;
};
