#pragma once
#include "Car.h"
#include "Map.h"
#include "Text.h"
#include "RoadTrafic.h"
#include "Timer.h"
class Game
{
private:

	SDL_Window* MainWindow = nullptr;

	SDL_Renderer* MainRenderer = nullptr;
	bool Success = true;
	Car MainCar;
	Map MainMap;
	Text MainText;
	RoadTrafic MainTrafic,*Trafic[4];
	Timer MainTime;
	SDL_Rect Temp[4];
public:
	Game();
	~Game();

	SDL_Renderer* GetRenderer();

	bool Init(std::string WindowName,int Window_Width,int Window_Height,int PosX,int PosY,Uint32 Window_Flag);
	void Push_All_Textures();
	void Push_Fps(int);
	void Event_Handler(SDL_Event*);
	bool Update();
	bool Render();
	void Quit();
};

