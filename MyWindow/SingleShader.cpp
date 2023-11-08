#include "SingleShader.h"

SingleShader::SingleShader():m_width(0),m_height(0),m_pTex(NULL)
{
}

SingleShader::~SingleShader()
{
	if (m_pTex)
	{
		m_pTex->Release();
	}
}

void SingleShader::Render(IDirect3DDevice9* pDevice)
{
	pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);
	pDevice->BeginScene();
	pDevice->SetTexture(0, m_pTex);
	pDevice->EndScene();
	pDevice->Present(0, 0, 0, 0);
}

bool SingleShader::LoadTexFromJepg(IDirect3DDevice9* pDevice, char* path)
{	
	HRESULT hr = pDevice->CreateTexture(64, 64, 1, 0, D3DFMT_A8B8G8R8, D3DPOOL_DEFAULT, &m_pTex, NULL);
	if (m_pTex)
	{ 
		D3DXCreateTextureFromFile(pDevice, path, &m_pTex);
	}
	return hr;
}