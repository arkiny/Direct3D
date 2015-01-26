#pragma once
class cSkinnedMesh
{
private:
	D3DXFRAME*					m_pRootFrame;
	LPD3DXANIMATIONCONTROLLER	m_pAnimControl;
	DWORD						m_dwCurrentTrack = 0;

	float						m_fAccumTime = 0.0f;
	float						m_fChangeTime = 0.0f;
	float						m_fActionTime = 0.0f;
	bool						m_bInAction = false;
	const float					m_cfTime = 1.0f;
	enum E_STATUS
	{
		ATTACK1,
		ATTACK2,
		ATTACK3,
		WALKING,
		IDLE
	};

	E_STATUS					m_eCurrentStatus	= ATTACK1;
	E_STATUS					m_eNextStatus		= IDLE;
	bool						m_bIsTransferAnimation = false;
	LPD3DXANIMATIONSET			m_pAnimationSetPrev = NULL;
	LPD3DXANIMATIONSET			m_pAnimationSetNext = NULL;
	SYNTHESIZE(bool, m_bAttack, IsAttack);
	
public:
	cSkinnedMesh(void);
	~cSkinnedMesh(void);

	void Setup(std::string sFolder, std::string sFile);
	void Render();
	void Update(float delta);

private:
	void SetAnimationIndex(DWORD dwIndex);
	
	void ChangeAnimation(float fTime);
	
	void SetupWorldMatrix(D3DXFRAME* pFrame, D3DXMATRIXA16* pmatParent);
	void Render(D3DXFRAME* pFrame);
	void SetupBoneMatrixPtrs(D3DXFRAME* pFrame);
	void UpdateSkinnedMesh(D3DXFRAME* pFrame);
};

