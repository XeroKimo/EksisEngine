#pragma once

class EEngineTimer
{
public:
	EEngineTimer();
	void Tick();
	bool CanTick();
	bool Ticked();

	double GetTime();
	double GetTimerFrequency();

	double GetDelta();
	double GetElapsedTime();

	void SetTargetFrameRate(unsigned int FPS);
	void ToggleFrameLimit();
private:
	bool m_firstFrame;
	bool m_limitFrames;
	bool m_ticked;

	double m_deltaTime;
	double m_elapsedTime;
	double m_currentTime;
	double m_previousTime;
	double m_targetFrameTime;
};