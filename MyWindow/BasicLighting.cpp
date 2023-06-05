#include "BasicLighting.h"
#include "DrawUtil.h"
#include "CameraCtrl.h"


BasicLighting::BasicLighting(void) : m_lightPos(0, 0, 0)
{
	m_pEffect = NULL;
}

BasicLighting::~BasicLighting(void)
{
	SAFE_DELETE_RELEASE(m_pEffect);
}

bool BasicLighting::Init(IDirect3DDevice9* pD3DDevice)
{
	m_pEffect = DrawUtil::GetInstance()->LoadEffect(pD3DDevice, "Shader\\BasicLighting.fx");

	return ShaderSimpler::Init(pD3DDevice);
}

void BasicLighting::Render()
{
	if (m_pEffect == NULL)
		return;

	float t = timeGetTime() / 1000.0f;
	float r = 150;
	m_lightPos.x = sinf(t) * r;
	m_lightPos.z = cosf(t) * r;
	m_lightPos.y = sinf(t) * r;;

	m_pEffect->SetFloatArray("lightPos", (float*)&m_lightPos, 3);

	//-- 设置effect参数
	D3DXMATRIX matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXMATRIX matWorldViewProj = matWorld * g_camera.GetViewMat() * g_camera.GetProjectMat();

	m_pEffect->SetMatrix("matWorldViewPrj", &matWorldViewProj);
	m_pEffect->SetMatrix("matWorld", &matWorld);

	//-- 渲染球体
	HRESULT hr;
	UINT numPass = 0;
	hr = m_pEffect->Begin(&numPass, 0);

	for (UINT i = 0; i < numPass; i++)
	{
		m_pEffect->BeginPass(i);
		DrawMesh();
		m_pEffect->EndPass();
	}

	hr = m_pEffect->End();

	//--画出灯光的位置
	//DrawingUtil::getInst()->drawLight(m_lightPos);

	ShaderSimpler::Render();
}