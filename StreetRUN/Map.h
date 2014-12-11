#pragma once

#include "LoadTexture.h"
#include <sstream>
class Map
{
private:
	int RoadSpeed;
	std::stringstream Stream;
public:
	Map();
	~Map();

	SDL_Renderer* GetRender();
	bool Push_Texture(std::string, std::string);
	SDL_Texture* GetMap(std::string);
	void Render(std::string, int, int);
	void HandleEvents(SDL_Event*);
	void MoveTheMap();
	std::string GetRoadSpeed_For_Text();
	int GetRoadSpeed();
};

