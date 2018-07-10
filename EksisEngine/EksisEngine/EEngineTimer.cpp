#include "EEngineTimer.h"
#include <Windows.h>
#include <WinBase.h>

EEngineTimer::EEngineTimer() : 
	m_deltaTime(0.0),
	m_elapsedTime(0.0),
	m_currentTime(0.0),
	m_previousTime(0.0),
	m_limitFrames(false),
	m_targetFrameTime(0.0016)

{
}

void EEngineTimer::Tick()
{
	if (CanTick() == true)
	{
		m_previousTime = m_currentTime;

		m_currentTime = GetTime();

		m_deltaTime = m_currentTime - m_previousTime;

		m_firstFrame = m_elapsedTime > 0.0;

		m_elapsedTime += m_deltaTime;
	}
}

bool EEngineTimer::CanTick()
{
	if (m_limitFrames == true)
	{
		double frameTime = (GetTime() - m_currentTime) * 1000.0;
		if (frameTime < m_targetFrameTime)
		{
			return false;
		}
	}
	return true;
}

double EEngineTimer::GetTime()
{
	static const double time = GetTimerFrequency();

	LARGE_INTEGER largeInt;
	QueryPerformanceCounter(&largeInt);
	return (double)largeInt.QuadPart * time;
	return 0.0;
}

double EEngineTimer::GetTimerFrequency()
{
	LARGE_INTEGER largeInt;
	if (QueryPerformanceFrequency(&largeInt) != 0 && largeInt.QuadPart != 0)
	{
		return 1.0 / (double)largeInt.QuadPart;
	}
	return 0.0;
}

double EEngineTimer::GetDelta()
{
	if (m_firstFrame)
	{
		return m_deltaTime;
	}
	return 0.0;
}

double EEngineTimer::GetElapsedTime()
{
	return m_elapsedTime;
}

void EEngineTimer::SetTargetFrameRate(unsigned int FPS)
{
	m_targetFrameTime = 1000.0 / FPS;
}

void EEngineTimer::ToggleFrameLimit()
{
}
