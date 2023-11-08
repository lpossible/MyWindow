#include "RenderTarget.h"

CRenderTarget::CRenderTarget(int width, int height, int usage, D3DFORMAT format)
:m_iwidth(width),m_iheight(height)
,m_usage(usage),m_format(format)
{

}

CRenderTarget::~CRenderTarget()
{
	SAFE_DELETE_RELEASE(m_pTex);
	SAFE_DELETE_RELEASE(m_pOldSurface);
	SAFE_DELETE_RELEASE(m_pOffScreenSurface);
}


bool CRenderTarget::BeginRenderTarget(ID3DDevice* pDevice)
{
	HRESULT hr;
	hr = pDevice->GetRenderTarget(0, &m_pOldSurface);
	if (FAILED(hr))
	{
		return false;
	}

	ID3DSurface* pSur = nullptr;
	hr = m_pTex->GetSurfaceLevel(0, &pSur);
	if (FAILED(hr))
	{
		return false;
	}

	hr = pDevice->SetRenderTarget(0, pSur);
	if (FAILED(hr))
	{
		return false;
	}

	SAFE_DELETE_RELEASE(pSur);
	return true;
}

bool CRenderTarget::EndRenderTarget(ID3DDevice* pDevice)
{
	if (!m_pTex || !m_pOldSurface)
	{
		return false;
	}
	HRESULT hr;
	hr = pDevice->SetRenderTarget(0, m_pOldSurface);
	SAFE_DELETE_RELEASE(m_pOldSurface);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool CRenderTarget::CreateRenderTarget(ID3DDevice* pDevice)
{
	if (!pDevice)
		return false;

	//初始化纹理
	HRESULT hr;
	hr = pDevice->CreateTexture(m_iwidth, m_iwidth, 1, m_usage, m_format, D3DPOOL_DEFAULT, &m_pTex, nullptr);
	if (FAILED(hr))
	{
		return false;
	}

	//初始化离屏表面
	hr = pDevice->CreateOffscreenPlainSurface(m_iwidth, m_iheight, m_format, D3DPOOL_SYSTEMMEM, &m_pOffScreenSurface, nullptr);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool CRenderTarget::SaveToFile(const char* path)
{
	if (!path)
	{
		return false;
	}

	if (!m_pTex)
	{
		return false;
	}

	HRESULT hr;
	ID3DSurface* pSur = nullptr;
	hr = m_pTex->GetSurfaceLevel(0, &pSur);
	if (FAILED(hr))
	{
		return false;
	}

	hr = D3DXLoadSurfaceFromSurface(m_pOffScreenSurface, nullptr, nullptr, pSur, nullptr, nullptr, D3DX_FILTER_TRIANGLE, 0);
	if (FAILED(hr))
	{
		return false;
	}
	
	//保存到文件
	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 600;
	D3DXSaveSurfaceToFileA(path, D3DXIFF_JPG, m_pOffScreenSurface, nullptr,nullptr);
	SAFE_DELETE_RELEASE(pSur);
	return true;
}

bool CRenderTarget::SaveToFileA(const char* path, ID3DDevice* pDevice)
{
	if (!path)
	{
		return false;
	}

	if (!m_pTex)
	{
		return false;
	}

	//检索显示模式的空间分辨率、颜色分辨率和刷新频率。
	D3DDISPLAYMODE displayMode;
	pDevice->GetDisplayMode(0, &displayMode);
	//创建屏幕外图面。
	ID3DSurface* pSurface = nullptr;
	HRESULT hr;
	hr = pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	if (FAILED(hr))
	{
		return false;
	}
	ID3DSurface* pOffSurface = nullptr;
	hr = pDevice->CreateOffscreenPlainSurface(800, 600, D3DFMT_X8B8G8R8, D3DPOOL_SCRATCH, &pOffSurface, nullptr);
	if (FAILED(hr))
	{
		return false;
	}
	hr = pDevice->GetRenderTargetData(pSurface, pOffSurface);
	if (FAILED(hr))
	{
		return false;
	}

	//保存到文件
	D3DXSaveSurfaceToFileA(path, D3DXIFF_PNG, m_pOffScreenSurface, nullptr, nullptr);
	SAFE_DELETE_RELEASE(pSurface);
	SAFE_DELETE_RELEASE(pOffSurface);
	return true;
}

bool CRenderTarget::GetBackBufferSurFace(ID3DDevice* pDevice)
{
	if (!pDevice)
	{
		return false;
	}
	ID3DSurface* pSur = nullptr;
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSur);
	D3DXSaveSurfaceToFileA("C:\\Users\\luoping\\Desktop\\test\\test.png", D3DXIFF_PNG, pSur, nullptr, nullptr);
	SAFE_DELETE_RELEASE(pSur);
	return true;
}

