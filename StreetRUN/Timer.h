#pragma once
//fps
#include <sstream>


class Timer
{
private:
	bool LStrarted,LPaused; //L means Local
	Uint32 LTimer_Started,LTimer_Paused;
	//For fps
	int countedFrames = 0;
	std::stringstream Stream;
public:
	Timer();
	~Timer();
	void Start_Timer();
	void Stop_Timer();
	void Pause_Timer();
	void Unpause_Timer();
	int Get_Ticks();
	int Get_Time_In_Seconds();
	void Push_Fps(int);
	std::string Get_FPS();
};

