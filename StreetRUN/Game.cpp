#include "stdafx.h"
#include "Game.h"



Game::Game()
{
	MainTime.Start_Timer(); 
	for (int a = 0; a < 4; a++)
		Temp[a] = { 0, 0, 0, 0 };
}


Game::~Game()
{
}


SDL_Renderer* Game::GetRenderer()
{
	return MainRenderer;
}


bool Game::Init(std::string WindowName, int Window_Width, int Window_Height, int PosX, int PosY, Uint32 Window_Flag)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Could not Init video by SDL_Init_Video, because of SDL_Error: \n" << SDL_GetError() << std::endl;
		Success = false;
	}
	else
	{
		MainWindow = SDL_CreateWindow(WindowName.c_str(), PosX, PosY, Window_Width, Window_Height, Window_Flag);
		if (MainWindow == NULL)
		{
			std::cerr << "Could not Create MainWindow, because of SDL_Error: \n" << SDL_GetError() << std::endl;
			Success = false;
		}
		else
		{
			MainRenderer = SDL_CreateRenderer(MainWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (MainRenderer == NULL)
			{
				std::cerr << "Could not Create MainRenderer, because of SDL_Error: \n" << SDL_GetError() << std::endl;
				Success = false;
			}
			else
			{
				LoadTexture::Instance()->InitRenderer(MainRenderer);
				LoadFont::Instance()->InitRenderer(MainRenderer);
				MainText.SetFont("TTF/Font.ttf", 16);
				Push_All_Textures();
				for (int a = 0; a <= 3; a++)
					Trafic[a] = new RoadTrafic;
			}
		}
	}
	return Success;
}


void Game::Push_All_Textures()
{
	MainCar.Push_Texture("Img/CarSprites.png", "CarSprites");
	MainMap.Push_Texture("Img/road.png", "Map"); 
	MainTrafic.Push_Texture("Img/111.png", "Zero_Car");
	MainTrafic.Push_Texture("Img/1.png", "First_Car");
	MainTrafic.Push_Texture("Img/2.png", "Second_Car");
	MainTrafic.Push_Texture("Img/3.png", "Third_Car");
	MainTrafic.Push_Texture("Img/4.png", "Fourth_Car");
	MainTrafic.Push_Texture("Img/5.png", "Fifth_Car");
}

void Game::Event_Handler(SDL_Event* EventType)
{
	MainCar.HandleEvents(EventType);
	MainMap.HandleEvents(EventType);
}


bool Game::Update()
{
	//This text updates the speed so don't move it to static push
	SDL_Color Text_Color = { 255, 255, 255, 255 };
	MainText.SetText(MainMap.GetRoadSpeed_For_Text(), "Speed", Text_Color);	
	MainText.SetText(MainTime.Get_FPS(), "FPS", Text_Color);
	for (int a = 0; a < 4;a++)
	MainCar.Move(Temp);
	return true; //TEMP
}

bool Game::Render()
{
	//Render and move the map!
	MainMap.MoveTheMap();
	//Render the car
	
	MainText.Render_Text("Speed", 30, 880); 
	MainText.Render_Text("FPS", 0, 0);
	for (int a = 0; a <= 3; a++)
	{
		Temp[a] = Trafic[a]->Render_Car("Zero_Car", a, MainMap.GetRoadSpeed(), 0,MainCar.Car_YPos());
		MainCar.Render("CarSprites");
		
	}

	return true; // TEMP
}

void Game::Quit()
{
	SDL_DestroyWindow(MainWindow);
	SDL_RenderClear(MainRenderer);
	MainWindow = nullptr;
	MainRenderer = nullptr;
	SDL_Quit();
	exit(0);
}

void Game::Push_Fps(int Fps)
{
	MainTime.Push_Fps(Fps);
}


