#pragma once
#include "header.h"


class ShaderSimpler
{
public:
	ShaderSimpler();
	virtual ~ShaderSimpler();

	virtual bool Init(IDirect3DDevice9* pD3DDevice);
	virtual void Render() = 0;

	virtual void OnKeyDown(DWORD vk)
	{
		if (vk==VK_TAB)
		{
			const int max_mesh = 5;
		}
	}

protected:
	void DrawMesh();
	ID3DXMesh* LoadMeshFVF(IDirect3DDevice9* pD3DDevice, const char* szFileName, DWORD fvf);
private:
	//����
	ID3DXMesh* m_pMeshSphere;
	//������
	ID3DXMesh* m_pMeshBox;
	//���
	ID3DXMesh* m_pMeshTeapot;
	//
	ID3DXMesh* m_pMeshTorus;

	DWORD m_activeMesh = 4;
};