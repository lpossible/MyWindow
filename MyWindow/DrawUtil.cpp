#include "DrawUtil.h"
#include "CameraCtrl.h"

DrawUtil* DrawUtil::GetInstance()
{
	static DrawUtil drawUtil;
	return &drawUtil;
}

DrawUtil::DrawUtil()
{
	m_pEffect = NULL;
	m_pLightBox = NULL;
	m_pD3DFont = NULL;
}

DrawUtil::~DrawUtil()
{
	SAFE_DELETE_RELEASE(m_pD3DFont);
	SAFE_DELETE_RELEASE(m_pLightBox);
	SAFE_DELETE_RELEASE(m_pEffect);
}

void DrawUtil::Destory()
{

}

bool DrawUtil::Init(IDirect3DDevice9* pD3DDevice)
{
	//创建字体
	HRESULT hr;
	D3DXFONT_DESC fontDesc;
	memset(&fontDesc, 0, sizeof(fontDesc));
	fontDesc.Height = 14;
	fontDesc.Weight = 500;
	fontDesc.MipLevels = D3DX_DEFAULT;
	fontDesc.Italic = FALSE;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH;
	lstrcpy(fontDesc.FaceName, "宋体");

	hr = D3DXCreateFontIndirect(pD3DDevice, &fontDesc, &m_pD3DFont);
	
	//加载灯光和shader
	hr = D3DXCreateBox(pD3DDevice, 10, 10, 10, &m_pLightBox, NULL);
	m_pEffect = LoadEffect(pD3DDevice, "Shader\\SimpleDraw.fx");
	if (SUCCEEDED(hr))
	{
		return true;
	}
	return false;
}

void DrawUtil::DrawLight(D3DXVECTOR3 pos)
{
	D3DXMATRIX matWorld;
	D3DXMatrixTranslation(&matWorld, pos.x, pos.y, pos.z);
	
	D3DXMATRIX matWorldViewProj = matWorld * g_camera.GetViewMat() * g_camera.GetProjectMat();
	m_pEffect->SetMatrix("matWorldViewPrj", &matWorldViewProj);

	UINT numPass = 0;
	m_pEffect->Begin(&numPass, 0);
	m_pEffect->BeginPass(0);
	if (m_pLightBox)
	{
		m_pLightBox->DrawSubset(0);
	}
	m_pEffect->EndPass();
	m_pEffect->End();
}

ID3DXEffect* DrawUtil::LoadEffect(IDirect3DDevice9* pD3DDevice, const char* szFileName)
{
	HRESULT hr;
	ID3DXEffect* pEffect = NULL;

	DWORD flag = 0;

	ID3DXBuffer* pError = NULL;
	
	
	hr = D3DXCreateEffectFromFile(pD3DDevice, szFileName, NULL, NULL, flag, NULL, &pEffect, &pError);

	if (FAILED(hr))
	{
		if (pError)
		{
			const char* szError = (const char*)pError->GetBufferPointer();
			::MessageBox(NULL, szError, "Error", MB_OK);
		}
	}

	return pEffect;
}

void DrawUtil::DrawMyText(const char* szText, int x, int y, D3DCOLOR color /* = 0xffffffff */)
{
	RECT rc;
	rc.left = x;
	rc.top = y;
	rc.right = 200;
	rc.bottom = 400;

	int len = strlen(szText);

	m_pD3DFont->DrawTextA(NULL, szText, len, &rc, DT_TOP | DT_LEFT, color);
}









