#include "PhongShading.h"
#include "DrawUtil.h"
#include "CameraCtrl.h"


PhongShading::PhongShading()
{
	m_pEffect = NULL;
}

PhongShading::~PhongShading()
{
	SAFE_DELETE_RELEASE(m_pEffect);
}

bool PhongShading::Init(IDirect3DDevice9* pD3DDevice)
{
	m_pEffect = DrawUtil::GetInstance()->LoadEffect(pD3DDevice, "Shader\\PhongShading.fx");

	return ShaderSimpler::Init(pD3DDevice);
}

void PhongShading::DrawMesh()
{
	if (m_pMeshTeapot)
	{
		m_pMeshTeapot->DrawSubset(0);
	}
}


void PhongShading::Render()
{
	if (!m_pEffect)
	{
		return;
	}

	float t = timeGetTime() / 4000.0f;
	float r = 150;
	m_v3LightPos.x = sinf(t) * r;
	m_v3LightPos.y = cosf(t) * r;
	m_v3LightPos.z = sinf(t) * r;

	HRESULT hr;
	hr = m_pEffect->SetFloatArray("lightPos", (float*)&m_v3LightPos, 3);
	hr = m_pEffect->SetFloatArray("eyePos", (float*)&g_camera.GetEyePos(), 3);

	//
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIX matWorldViewProj = matWorld * g_camera.GetViewMat() * g_camera.GetProjectMat();
	hr = m_pEffect->SetMatrix("matWorld", &matWorld);
	hr = m_pEffect->SetMatrix("matWorldViewPrj", &matWorldViewProj);
	
	//µ÷ÓÃshader
	UINT numPass = 0;
	hr = m_pEffect->Begin(&numPass, 0);

	for (UINT i=0;i<numPass;i++)
	{
		hr = m_pEffect->BeginPass(i);
		DrawMesh();
		hr = m_pEffect->EndPass();
	}

	hr = m_pEffect->End();

	DrawUtil::GetInstance()->DrawLight(m_v3LightPos);

	ShaderSimpler::Render();
}