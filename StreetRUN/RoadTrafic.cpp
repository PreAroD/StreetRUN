#include "stdafx.h"
#include "RoadTrafic.h"


RoadTrafic::RoadTrafic()
{
	FirstCars = true;
	Car_Position_On_Road[0] = { 50, -400, 150, 314 };
	Car_Position_On_Road[1] = { 300, -400, 150, 314 };
	Car_Position_On_Road[2] = { 550, -900, 150, 314 };
	Car_Position_On_Road[3] = { 800, -2000, 150, 314 };

	Car_Position_On_Image[0] = { 0, 0, 150, 300 };
	Car_Position_On_Image[1] = { 0, 0, 150, 338 };
	Car_Position_On_Image[2] = { 0, 0, 150, 308 };
	Car_Position_On_Image[3] = { 0, 0, 150, 300 };
	Car_Position_On_Image[4] = { 0, 0, 150, 313 };
	Car_Position_On_Image[5] = { 0, 0, 150, 309 };	
	Car_Pos["Zero_Car"] = Car_Position_On_Image[0];
	Car_Pos["First_Car"] = Car_Position_On_Image[1];
	Car_Pos["Second_Car"] = Car_Position_On_Image[2];
	Car_Pos["Third_Car"] = Car_Position_On_Image[3];
	Car_Pos["Fourth_Car"] = Car_Position_On_Image[4];
	Car_Pos["Fifth_Car"] = Car_Position_On_Image[5];

}

RoadTrafic::~RoadTrafic()
{

}
int RoadTrafic::Generate_Random_Number(int Low_Num,int High_Num)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(Low_Num, High_Num);

    return dis(gen);

}

bool RoadTrafic::Push_Texture(std::string Path,std::string Index)
{
	return LoadTexture::Instance()->PushTexture(Path, Index);
}


SDL_Texture* RoadTrafic::Get_Texture(std::string Texture_Index)
{
	return LoadTexture::Instance()->GetTexture(Texture_Index);
}


SDL_Rect RoadTrafic::Render_Car(std::string Texture_Index,int Position,int Speed,int Show_Interval,int MainCar_Position)
{
	Get_Renderer();
	//! To fix the speed
	if (FirstCars == true)
	{
		for (int Temp = 0; Temp < 4; Temp++)
		{
			CarSpeed[Temp] = Generate_Random_Number(1, 20);
		}
		FirstCars = false;
	}
	
	if (Car_Position_On_Road[Position].y >= 1024)
	{
		Car_Position_On_Road[Position].y = -Generate_Random_Number(400,1500);
		CarSpeed[Position] = Generate_Random_Number(1, 20);
	}

	Car_Position_On_Road[Position].y += CarSpeed[Position];

	if (Position <= 3)
			if (SDL_RenderCopy(LocalRenderer, Get_Texture(Texture_Index), &Car_Pos[Texture_Index], &Car_Position_On_Road[Position]) == -1)
				cerr << "Some shit happened\n" << SDL_GetError() << endl;
	return Car_Position_On_Road[Position];
}

void RoadTrafic::Get_Renderer()
{
	LocalRenderer = LoadTexture::Instance()->GetRenderer();
}

