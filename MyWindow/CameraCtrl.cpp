#include "CameraCtrl.h"

CameraCtrl g_camera;

inline D3DXVECTOR3 operator * (const D3DXVECTOR3& v, const D3DXMATRIX& m)
{
	return D3DXVECTOR3(v.x * m._11 + v.y * m._21 + v.z * m._31 + m._41,
		v.x * m._12 + v.y * m._22 + v.z * m._32 + m._42,
		v.x * m._13 + v.y * m._23 + v.z * m._33 + m._43);
}

CameraCtrl::CameraCtrl()
{
	D3DXMatrixIdentity(&m_matPrj);
	SetDefaultView();
	m_bDrag = false;
}

CameraCtrl::~CameraCtrl()
{

}

void CameraCtrl::SetDefaultView()
{
	m_v3LookAt = D3DXVECTOR3(0, 0, 0);
	m_dist = 400;
	D3DXQuaternionRotationYawPitchRoll(&m_rotate, 0, 0, 0);

	UpdateViewMat();
}

void CameraCtrl::UpdateViewMat()
{
	D3DXMATRIX matR;
	D3DXMatrixRotationQuaternion(&matR, &m_rotate);

	D3DXVECTOR3 viewDir = D3DXVECTOR3(0, 0, 1);
	D3DXVECTOR3 up(0, 1, 0);

	viewDir = viewDir * matR;
	up = up * matR;

	m_v3EyePos = viewDir * m_dist + m_v3LookAt;

	D3DXMatrixLookAtLH(&m_matView, &m_v3EyePos, &m_v3LookAt, &up);
}

void CameraCtrl::SetPerspective(float fov, int clientw, int clienth, float znear, float zfar)
{
	float aspect = float(clientw) / clienth;
	D3DXMatrixPerspectiveFovLH(&m_matPrj, fov, aspect, znear, zfar);
}

void CameraCtrl::onKeyDown(DWORD vk)
{
	D3DXVECTOR3 vX(m_matView._11, m_matView._21, m_matView._31);
	D3DXVECTOR3 vY(m_matView._12, m_matView._22, m_matView._32);
	D3DXVECTOR3 vZ(m_matView._13, m_matView._23, m_matView._33);

	float s = 10;
	switch (vk)
	{
	case 'W':
		m_v3LookAt += vZ * s;
		break;
	case 'S':
		m_v3LookAt -= vZ * s;
		break;
	case 'A':
		m_v3LookAt += vX * s;
		break;
	case 'D':
		m_v3LookAt -= vX * s;
		break;
	case 'Z':
		m_v3LookAt += vY * s;
		break;
	case 'X':
		m_v3LookAt -= vY * s;
		break;
	default:
		break;
	}

	UpdateViewMat();
}

void CameraCtrl::onLButtonDown(int x, int y)
{
	m_bDrag = true;
	m_lastDragPt.x = x;
	m_lastDragPt.y = y;

	trackball((float*)m_lastRotate, 0, 0, 0, 0);
}

void CameraCtrl::onLbuttonUp()
{
	m_bDrag = false;
}

D3DXVECTOR2 _normalize(int x, int y)
{
	return  D3DXVECTOR2(((2.0f * x) / WIN_WIDTH) - 1,
		-(((2.0f * y) / WIN_HEIGHT) - 1));
}

void CameraCtrl::onMouseMove(int x, int y)
{
	if (m_bDrag)
	{
		D3DXVECTOR2 lastPt = _normalize(m_lastDragPt.x, m_lastDragPt.y);
		D3DXVECTOR2 nowPt = _normalize(x, y);

		trackball((float*)&m_lastRotate, lastPt.x, lastPt.y, nowPt.x, nowPt.y);

		m_lastDragPt.x = x;
		m_lastDragPt.y = y;

		add_quats((float*)&m_lastRotate, (float*)&m_rotate, (float*)&m_rotate);

		UpdateViewMat();
	}
}

void CameraCtrl::onMouseWheel(int delta)
{
	m_dist += delta * 0.2f;

	UpdateViewMat();
}