#include "stdafx.h"
#include "cGameTimer.h"


cGameTimer::cGameTimer()
{
	m_dSecondsPerCount = 0.0;
	m_dDeltaTime = -1.0;

	m_BaseTime = 0;
	m_PausedTime = 0;
	m_stopTime = 0;
	m_PrevTime = 0;
	m_CurrTime = 0;

	m_bStopped = false;
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	m_dSecondsPerCount = 1.0 / (double)countsPerSec;
}


cGameTimer::~cGameTimer()
{
}

float cGameTimer::GameTime() const{
	return 0.0f;
}

float cGameTimer::TotalTime() const{
	// If we are stopped, do not count the time that has passed since we stopped.
	// Moreover, if we previously already had a pause, the distance 
	// mStopTime - mBaseTime includes paused time, which we do not want to count.
	// To correct this, we can subtract the paused time from mStopTime:  
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mStopTime    mCurrTime

	if (m_bStopped)
	{
		return (float)(((m_stopTime - m_PausedTime) - m_BaseTime)*m_dSecondsPerCount);
	}

	// The distance mCurrTime - mBaseTime includes paused time,
	// which we do not want to count.  To correct this, we can subtract 
	// the paused time from mCurrTime:  
	//
	//  (mCurrTime - mPausedTime) - mBaseTime 
	//
	//                     |<--paused time-->|
	// ----*---------------*-----------------*------------*------> time
	//  mBaseTime       mStopTime        startTime     mCurrTime

	else
	{
		return (float)(((m_CurrTime - m_PausedTime) - m_BaseTime)*m_dSecondsPerCount);
	}
}

float cGameTimer::DeltaTime() const{
	return (float)m_dDeltaTime;
}

void cGameTimer::Reset(){
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_stopTime = 0;
	m_bStopped = false;
}
void cGameTimer::Start(){
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);


	// Accumulate the time elapsed between stop and start pairs.
	//
	//                     |<-------d------->|
	// ----*---------------*-----------------*------------> time
	//  mBaseTime       mStopTime        startTime     

	if (m_bStopped)
	{
		m_PausedTime += (startTime - m_stopTime);

		m_PrevTime = startTime;
		m_stopTime = 0;
		m_bStopped = false;
	}
}
void cGameTimer::Stop(){
	if (!m_bStopped)
	{
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		m_stopTime = currTime;
		m_bStopped = true;
	}
}
void cGameTimer::Tick(){
	if (m_bStopped)
	{
		m_dDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	// Time difference between this frame and the previous.
	m_dDeltaTime = (m_CurrTime - m_PrevTime)*m_dSecondsPerCount;

	// Prepare for next frame.
	m_PrevTime = m_CurrTime;

	// Force nonnegative.  The DXSDK's CDXUTTimer mentions that if the 
	// processor goes into a power save mode or we get shuffled to another
	// processor, then mDeltaTime can be negative.
	if (m_dDeltaTime < 0.0)
	{
		m_dDeltaTime = 0.0;
	}
}