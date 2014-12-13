#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
	LStrarted = false;
	LPaused = false;
}


Timer::~Timer()
{
}

void Timer::Start_Timer()
{
	LStrarted = true;
	LPaused = false;

	LTimer_Started = SDL_GetTicks();
}

void Timer::Stop_Timer()
{
	if (LStrarted == true)
	{
		LStrarted = false;
		LPaused = false;
		LTimer_Started = 0;
		LTimer_Paused = 0;
	}

}

void Timer::Pause_Timer()
{
	if (LStrarted == true)
	{
		LStrarted = false;
		LPaused = true;
		LTimer_Paused = SDL_GetTicks() - LTimer_Started;
	}
}

void Timer::Unpause_Timer()
{
	if (LPaused == true)
	{
		LPaused = false;
		LStrarted = true;
		LTimer_Started = SDL_GetTicks() - LTimer_Paused;
		LTimer_Paused = 0;
	}
}

int Timer::Get_Ticks()
{
	Uint32 Time_Now = 0;
	if (LStrarted)
	{
		if (LPaused)
		{
			Time_Now = LTimer_Paused;
		}
		else
		{
			Time_Now = SDL_GetTicks() - LTimer_Started;
		}
	}
	return Time_Now;
}

int Timer::Get_Time_In_Seconds()
{
	return Get_Ticks() / 1000;
}

std::string Timer::Get_FPS()
{
	int avgFPS = countedFrames / (Get_Ticks() / 1000.f);

	if (avgFPS > 2000000) { avgFPS = 0; }
	Stream.str("");
	Stream << "FPS = " << avgFPS;
	return Stream.str().c_str();
}

void Timer::Push_Fps(int Fps)
{
	countedFrames = Fps;
}

