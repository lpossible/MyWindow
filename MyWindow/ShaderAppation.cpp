#include "ShaderAppation.h"
#include "resource.h"

//初始化窗口实例
WinAppation app;


//窗口回调函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_Exit:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
		break;
	}
	return 0;
}

//入口win main
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (!app.CreateWind(hInstance, WIN_WIDTH, WIN_HEIGHT, "MySimpleShader"))
	{
		return -1;
	}

	//消息循环
	MSG uMsg;
	memset(&uMsg, 0, sizeof(MSG));

	while (uMsg.message != WM_QUIT)
	{
		if (PeekMessage(&uMsg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&uMsg);
			DispatchMessage(&uMsg);
		}
		else
		{
			app.Render();
		}
	}

	app.DestoryWind();
	return 0;
}

WinAppation::WinAppation()
{
	m_hwnd = nullptr;
	m_d3d = nullptr;
	m_d3ddevice = nullptr;
}

WinAppation::~WinAppation()
{
	SAFE_DELETE_RELEASE(m_d3d);
	SAFE_DELETE_RELEASE(m_d3ddevice);
}

bool WinAppation::CreateWind(HINSTANCE hInstance, int width, int height, const char* name)
{
	//窗口类
	WNDCLASSEX winClass;
	memset(&winClass, 0, sizeof(WNDCLASSEX));

	winClass.lpszClassName = L"MyWin";
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = WindowProc;
	winClass.hInstance = hInstance;
	winClass.hIcon = NULL;
	winClass.hIconSm = NULL;
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	winClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;

	//窗口注册
	if (!RegisterClassEx(&winClass))
	{
		return false;
	}

	//设置窗口的位置
	int srcW = ::GetSystemMetrics(SM_CXSCREEN);
	int srcH = ::GetSystemMetrics(SM_CYSCREEN);

	RECT winRect;
	winRect.left = (srcW - width) / 2;
	winRect.top = (srcH - height) / 2;
	winRect.right = winRect.left + width;
	winRect.bottom = winRect.top + height;

	//调整位置
	DWORD style = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	AdjustWindowRect(&winRect, style, TRUE);

	//创建窗口
	m_hwnd = CreateWindowEx(NULL, L"MyWin", L"MySimpleShader", style, winRect.left, winRect.top, width, height, NULL, NULL, hInstance, NULL);
	if (m_hwnd==NULL)
	{
		::MessageBox(m_hwnd, L"窗口创建失败", L"Error", MB_OK);
		return false;
	}

	//显示窗口
	ShowWindow(m_hwnd, SW_SHOW);
	UpdateWindow(m_hwnd);

	//创建d3d设备
	if (!CreateD3dDevice())
	{
		::MessageBox(m_hwnd, L"d3d设备创建失败", L"Error", MB_OK);
		return false;
	}

	return true;
}

void WinAppation::DestoryWind()
{
	CleanD3dDevice();
}

bool WinAppation::CreateD3dDevice()
{
	HRESULT hr;

	//--创建d3d对象
	m_d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_d3d == NULL)
	{
		::MessageBox(m_hwnd, L"D3D Create failed.", L"Error", MB_OK);
		return false;
	}

	//--测试shader版本
	D3DCAPS9 caps;
	hr = m_d3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);
	if (caps.VertexShaderVersion < D3DVS_VERSION(2, 0)
		|| caps.PixelShaderVersion < D3DPS_VERSION(2, 0))
	{
		::MessageBox(m_hwnd, L"显卡支持的Shader版本太低", L"Error", MB_OK);
		return false;
	}

	//D3DDEVICE参数设置
	D3DPRESENT_PARAMETERS d3dpp;
	memset(&d3dpp, 0, sizeof(d3dpp));

	d3dpp.BackBufferFormat			= D3DFMT_X8R8G8B8;
	d3dpp.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed					= TRUE;
	d3dpp.EnableAutoDepthStencil	= TRUE;
	d3dpp.AutoDepthStencilFormat	= D3DFMT_D16;
	d3dpp.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	//
	DWORD dwBehaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	D3DDEVTYPE devType = D3DDEVTYPE_HAL;

#ifdef SHADER_DEBUG
	devType = D3DDEVTYPE_REF;
#endif

	hr = m_d3d->CreateDevice(D3DADAPTER_DEFAULT, devType, m_hwnd, dwBehaviorFlags, &d3dpp, &m_d3ddevice);
	if (hr==D3DERR_DEVICELOST)
	{
		::MessageBox(m_hwnd, L"D3DERR_DEVICELOST", L"Error", MB_OK);
		return false;
	}
	else if (hr==D3DERR_INVALIDCALL)
	{
		::MessageBox(m_hwnd, L"D3DERR_INVALIDCALL", L"Error", MB_OK);
		return false;
	}
	else if (hr == D3DERR_NOTAVAILABLE)
	{
		::MessageBox(m_hwnd, L"D3DERR_NOTAVAILABLE", L"Error", MB_OK);
		return false;
	}
	else if (hr == D3DERR_OUTOFVIDEOMEMORY)
	{
		::MessageBox(m_hwnd, L"D3DERR_OUTOFVIDEOMEMORY", L"Error", MB_OK);
		return false;
	}
	return SUCCEEDED(hr);
}

void WinAppation::CleanD3dDevice()
{
	SAFE_DELETE_RELEASE(m_d3d);
	SAFE_DELETE_RELEASE(m_d3ddevice);
}

void WinAppation::Render()
{
	HRESULT hr;
	m_d3ddevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffff0000, 1.0f, 0);
	hr = m_d3ddevice->BeginScene();
	if (SUCCEEDED(hr))
	{
		m_d3ddevice->EndScene();
		m_d3ddevice->Present(NULL, NULL, NULL, NULL);
	}
}
