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

bool Game::InitSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "Could not Init video by SDL_Init_Video, because of SDL_Error: \n" << SDL_GetError() << std::endl;
		Success = false;
	}
	else
	{
		MainWindow = SDL_CreateWindow(Local_WindowName.c_str(), Local_PosX, Local_PosY, Local_WindowWidth, Local_WindowHeight, Local_WindowFlag);
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
			}
		}
	}
	return Success;
}

bool Game::InitTextures()
{
	//Check for errors, if no Errors return true, if there is an error return false!
	
	bool Check_For_Errors[8];
	//Push the cars
	Check_For_Errors[0] = MainCar.Push_Texture("Img/CarSprites.png", "CarSprites");
	Check_For_Errors[1] = MainMap.Push_Texture("Img/road.png", "Map");
	Check_For_Errors[2] = MainTrafic.Push_Texture("Img/0.png", "Zero_Car");
	Check_For_Errors[3] = MainTrafic.Push_Texture("Img/1.png", "First_Car");
	Check_For_Errors[4] = MainTrafic.Push_Texture("Img/2.png", "Second_Car");
	Check_For_Errors[5] = MainTrafic.Push_Texture("Img/3.png", "Third_Car");
	Check_For_Errors[6] = MainTrafic.Push_Texture("Img/4.png", "Fourth_Car");
	Check_For_Errors[7] = MainTrafic.Push_Texture("Img/5.png", "Fifth_Car");
	//Get the cars
	CarType[0] = MainTrafic.Get_Texture("Zero_Car");
	CarType[1] = MainTrafic.Get_Texture("First_Car");
	CarType[2] = MainTrafic.Get_Texture("Second_Car");
	CarType[3] = MainTrafic.Get_Texture("Third_Car");
	CarType[4] = MainTrafic.Get_Texture("Fourth_Car");
	CarType[5] = MainTrafic.Get_Texture("Fifth_Car");

	for (int Check = 0; Check < 8; Check++)
	{
		if (Check_For_Errors[Check] == false)
		{
			return false;
		}
	}
	return true;
}

bool Game::Init(std::string WindowName, int Window_Width, int Window_Height, int PosX, int PosY, Uint32 Window_Flag)
{
	Local_WindowName = WindowName;
	Local_WindowWidth = Window_Width;
	Local_WindowHeight = Window_Height;
	Local_PosX = PosX;
	Local_PosY = PosY;
	Local_WindowFlag = Window_Flag;


	if (!InitSDL())
	{
		std::cerr << "Error in InitSDL function" << std::endl;
		Success = false;
	}
	if (!InitTextures())
	{
		std::cerr << "Error in InitTextures function" << std::endl;
		Success = false;
	}


	for (int a = 0; a <= 3; a++)
		Trafic[a] = new RoadTrafic;

	return Success;
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
		if (MainMap.GetRoadSpeed() != 0)
		{
			MainCar.Move(Temp);
		}
	return true; //TEMP
}

bool Game::Render()
{
	//Render and move the map!
	MainMap.MoveTheMap();
	//Render the car
	
	MainText.Render_Text("Speed", 30, 880); 
	MainText.Render_Text("FPS", 450, 0);
	
	if (MainMap.GetRoadSpeed() != 0)
	{
		for (int a = 0; a <= 3; a++)
		{
			//Temp[a] for collision
			int Generated_Number = MainTrafic.Generate_Random_Number(0, 5);
			Temp[a] = Trafic[a]->Render_Car(CarType[Generated_Number], Generated_Number, a, MainMap.GetRoadSpeed(), MainCar.Get_YPos());
			MainCar.Render("CarSprites");

		}
	}
	
	return true; // TEMP
}

void Game::Calculate_Fps(int Fps)
{
	MainTime.Push_Fps(Fps);
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






