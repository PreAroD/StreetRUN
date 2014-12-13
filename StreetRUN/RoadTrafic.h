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
	SDL_Renderer* LocalRenderer;
	bool FirstCars[2];
	int CarSpeed[4];
	SDL_Texture* Get_CarType[4];
	int Loop = 0;
	std::string String_Texture_Index[6];
	//For correct car spawn, because there is something bad with sdl_rect
	int CarWidth, CarHeight;
public:
	RoadTrafic();
	~RoadTrafic();
	int Generate_Random_Number(int,int);
	bool Push_Texture(std::string,std::string);
	SDL_Texture* Get_Texture(std::string);
	void Get_Renderer();
	SDL_Rect Render_Car(SDL_Texture*,int,int,int,int);
};

