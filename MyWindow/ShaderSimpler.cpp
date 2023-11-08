#include "ShaderSimpler.h"


ShaderSimpler::ShaderSimpler()
{
	m_pMeshBox = NULL;
	m_pMeshSphere = NULL;
	m_pMeshTeapot = NULL;
	m_pMeshTorus = NULL;
}

ShaderSimpler::~ShaderSimpler()
{
	SAFE_DELETE_RELEASE(m_pMeshBox);
	SAFE_DELETE_RELEASE(m_pMeshSphere);
	SAFE_DELETE_RELEASE(m_pMeshTeapot);
	SAFE_DELETE_RELEASE(m_pMeshTorus);
}

bool ShaderSimpler::Init(IDirect3DDevice9* pD3DDevice)
{
	//
	HRESULT hr;
	//²èºø
	hr = D3DXCreateTeapot(pD3DDevice, &m_pMeshTeapot, NULL);
	//µ÷Õû²èºø×ø±ê
	if (SUCCEEDED(hr))
	{
		DWORD numVert = m_pMeshTeapot->GetNumVertices();
		D3DXVECTOR3* pVb = NULL;
		hr = m_pMeshTeapot->LockVertexBuffer(0, (void**)&pVb);
		{
			if (SUCCEEDED(hr))
			{
				float s = 150;
				for (DWORD i=0;i<numVert;i++)
				{
					(*pVb) *= s;
					pVb += 2;
				}
				m_pMeshTeapot->UnlockVertexBuffer();
			}
		}
	}

	//
	hr = D3DXCreateSphere(pD3DDevice, 100, 32, 32, &m_pMeshSphere, NULL);
	hr = D3DXCreateBox(pD3DDevice, 400, 10, 400, &m_pMeshBox, NULL);
	hr = D3DXCreateTorus(pD3DDevice, 50, 100, 32, 32, &m_pMeshTorus, NULL);

	return SUCCEEDED(hr);

}

void ShaderSimpler::Render()
{

}

void ShaderSimpler::DrawMesh()
{
	if (m_pMeshSphere)
		m_pMeshSphere->DrawSubset(0);
	if (m_pMeshBox)
		m_pMeshBox->DrawSubset(0);
	if (m_pMeshTeapot)
	{
		m_pMeshTeapot->DrawSubset(0);
	}
}

ID3DXMesh* ShaderSimpler::LoadMeshFVF(IDirect3DDevice9* pD3DDevice, const char* szFileName, DWORD fvf)
{
	return NULL;
}