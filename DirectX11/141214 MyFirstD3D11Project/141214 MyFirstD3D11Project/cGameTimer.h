#pragma once
class cGameTimer
{
public:
	cGameTimer();
	~cGameTimer();

	float GameTime() const; // in sec
	float DeltaTime() const; // in sec
	float TotalTime() const;

	void Reset(); // Call before message loop
	void Start(); // call when unpuased
	void Stop(); // call when paused
	void Tick(); // Call every Frame;

private:
	double m_dSecondsPerCount;
	double m_dDeltaTime;

	__int64 m_BaseTime;
	__int64 m_PausedTime;
	__int64 m_stopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_bStopped;
};

