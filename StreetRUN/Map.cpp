#include "stdafx.h"
#include "Map.h"


Map::Map()
{
}


Map::~Map()
{
}

void Map::Push_Texture(std::string Path, std::string Index)
{
	LoadTexture::Instance()->PushTexture(Path, Index);
}


SDL_Texture* Map::GetMap(std::string Index)
{
	return LoadTexture::Instance()->GetTexture(Index);
}

SDL_Renderer* Map::GetRender()
{
	return LoadTexture::Instance()->GetRenderer();
}

void Map::Render(std::string Index, int PosX, int PosY)
{
	SDL_Rect src;
	src.h = 1024;
	src.w = 1024;
	src.x = 0;
	src.y = 0;

	SDL_Rect dest;
	dest.h = 1024;
	dest.w = 1020;
	dest.x = PosX;
	dest.y = PosY;

	SDL_RenderCopy(GetRender(), LoadTexture::Instance()->GetTexture(Index), &src, &dest);
}

void Map::HandleEvents(SDL_Event* LocalEvent)
{
	switch (LocalEvent->key.keysym.sym)
		{
		case SDLK_q:
			if (RoadSpeed!=0)
			RoadSpeed--;
			break;
		case SDLK_e:
			RoadSpeed++;
			break;
		}
}

void Map::MoveTheMap()
{
	//Static always 0 at functions
	static int ScrollOffSet;
	ScrollOffSet += RoadSpeed;
	if (ScrollOffSet > LoadTexture::Instance()->GetImageHeight("Map"))
	{
		ScrollOffSet = 0;
		std::cout << "ScrollOffSet = " << ScrollOffSet << std::endl << "-LoadTexture::Instance()->GetImageHeight() = " << 
			-LoadTexture::Instance()->GetImageHeight("Map") << std::endl;
	}
	//For first image
	std::cout << ScrollOffSet << std::endl;
	Render("Map",0,ScrollOffSet);
	//For the next image
	Render("Map", 0, ScrollOffSet - LoadTexture:: Instance()->GetImageHeight("Map"));
}

std::string Map::GetRoadSpeed_For_Text()
{
	
	Stream.str("");
	Stream << "Скорость = " << RoadSpeed << " Km/h";
	return Stream.str().c_str();
}

int Map::GetRoadSpeed()
{
	return RoadSpeed;
}
