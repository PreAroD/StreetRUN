#pragma once
#include "LoadTexture.h"
#include "Map.h"
#include "Timer.h"
#include <iostream>
#include <map>
using namespace std;
class RoadTrafic
{
private:
	SDL_Rect Car_Position_On_Road[4];
	SDL_Rect Car_Position_On_Image[6];
	map<std::string, SDL_Rect> Car_Pos;
	SDL_Renderer* LocalRenderer;
public:
	RoadTrafic();
	~RoadTrafic();
	int Generate_Random_Number(int,int);
	bool Push_Texture(std::string,std::string);
	SDL_Texture* Get_Texture(std::string);
	void Get_Renderer();
	SDL_Rect Render_Car(std::string,int,int,int,int);
	SDL_Rect Get_Car_Pos();
};

