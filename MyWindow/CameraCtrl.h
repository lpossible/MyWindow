#pragma once
#include "header.h"
#include "SGITrackball.h"

class CameraCtrl
{
public:
	CameraCtrl();
	~CameraCtrl();

	void SetPerspective(float fov, int clientw, int clienth, float znear, float zfar);

	void SetDefaultView();

	const D3DXMATRIX& GetProjectMat() { return m_matPrj; };
	const D3DXMATRIX& GetViewMat() { return m_matView; };
	const D3DXVECTOR3& GetEyePos() { return m_v3EyePos; };

	void onKeyDown(DWORD vk);
	void onLButtonDown(int x, int y);
	void onLbuttonUp();
	void onMouseMove(int x, int y);
	void onMouseWheel(int delta);
private:
	void UpdateViewMat();
private:
	D3DXMATRIX m_matPrj;
	D3DXMATRIX m_matView;

	D3DXVECTOR3 m_v3EyePos;
	D3DXVECTOR3 m_v3LookAt;
	float m_dist;
	D3DXQUATERNION m_rotate;
	D3DXQUATERNION m_lastRotate;

	//
	bool m_bDrag;
	POINT m_lastDragPt;
};

extern CameraCtrl g_camera;