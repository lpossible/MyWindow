#include "ShaderSimpler.h"


ShaderSimpler::ShaderSimpler()
{
}

ShaderSimpler::~ShaderSimpler()
{

}

bool ShaderSimpler::Init(IDirect3DDevice9* pD3DDevice)
{
	//
	HRESULT hr;
	//���
	hr = D3DXCreateTeapot(pD3DDevice, &m_pMeshTeapot, NULL);
	//�����������
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

	switch (m_activeMesh)
	{
	case 1:
		if (m_pMeshTeapot)
		{
			m_pMeshTeapot->DrawSubset(0);
		}
		break;
	case 2:
		if (m_pMeshTorus)
		{
			m_pMeshTorus->DrawSubset(0);
		}
		break;
	case 3:
		if (m_pMeshSphere)
		{
			m_pMeshSphere->DrawSubset(0);
		}
		break;
	default:
		if (m_pMeshBox)
		{
			m_pMeshBox->DrawSubset(0);
		}
		break;
	}
}

ID3DXMesh* ShaderSimpler::LoadMeshFVF(IDirect3DDevice9* pD3DDevice, const char* szFileName, DWORD fvf)
{

}