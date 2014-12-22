#pragma once

#define g_pD3DDevice cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
	SINGLETONE(cDeviceManager);

private:
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;

public:
	void Destroy();
	LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pD3DDevice;
	}
};

