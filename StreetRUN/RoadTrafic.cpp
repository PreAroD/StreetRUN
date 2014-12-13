#include "stdafx.h"
#include "RoadTrafic.h"

//Making this in string_texture_index, because i don't know hot to initilize the array in the constructur itself
RoadTrafic::RoadTrafic()
{
	FirstCars[0] = true;
	FirstCars[1] = true;
	Loop = 0;
	Car_Position_On_Road[0] = { 50, -400, 150, 300 };
	Car_Position_On_Road[1] = { 300, -400, 150, 300 };
	Car_Position_On_Road[2] = { 550, -900, 150, 300 };
	Car_Position_On_Road[3] = { 800, -2000, 150, 300 };

	//Car position in PNG
	Car_Position_On_Image[0] = { 0, 0, 144, 290 };
	Car_Position_On_Image[1] = { 0, 0, 150, 338 };
	Car_Position_On_Image[2] = { 0, 0, 150, 308 };
	Car_Position_On_Image[3] = { 0, 0, 150, 300 };
	Car_Position_On_Image[4] = { 0, 0, 150, 313 };
	Car_Position_On_Image[5] = { 0, 0, 150, 309 };	

	//Initialize the array this way, because VS13 not supporting C++11 fully -_-
	String_Texture_Index[0] = "Zero_Car";
	String_Texture_Index[1] = "First_Car";
	String_Texture_Index[2] = "Second_Car";
	String_Texture_Index[3] = "Third_Car";
	String_Texture_Index[4] = "Fourth_Car";
	String_Texture_Index[5] = "Fifth_Car";
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

void RoadTrafic::Get_Renderer()
{
	LocalRenderer = LoadTexture::Instance()->GetRenderer();
}

bool RoadTrafic::Push_Texture(std::string Path,std::string Index)
{
	return LoadTexture::Instance()->PushTexture(Path, Index);
}


SDL_Texture* RoadTrafic::Get_Texture(std::string Texture_Index)
{
	return LoadTexture::Instance()->GetTexture(Texture_Index);
}


SDL_Rect RoadTrafic::Render_Car(SDL_Texture* LocalCarType,int Car_Index,int Position_On_Road,int Speed,int MainCar_Position)
{
	Get_Renderer();
	//? To fix the speed
	if (FirstCars[0] == true)
	{
		for (int Temp = 0; Temp < 4; Temp++)
		{
			CarSpeed[Temp] = Generate_Random_Number(1, 20);
		}
		FirstCars[0] = false;
	}
	//? To fix the car type spawn
	if (FirstCars[1] == true)
	{
		 
		Get_CarType[Loop] = LocalCarType;
		if (Loop == 3)
		{
			Loop = 0;
			FirstCars[1] = false;
		}
	}
	
	if (Car_Position_On_Road[Position_On_Road].y >= 1024)
	{
		Car_Position_On_Road[Position_On_Road].y = -Generate_Random_Number(400, 1500);
		CarSpeed[Position_On_Road] = Generate_Random_Number(1, 20);
		Get_CarType[Position_On_Road] = LocalCarType;
	}

	Car_Position_On_Road[Position_On_Road].y += CarSpeed[Position_On_Road];
	
	SDL_QueryTexture(Get_CarType[Position_On_Road], NULL, NULL, &CarWidth, &CarHeight);
	Car_Position_On_Road[Position_On_Road].h = CarHeight;
	Car_Position_On_Image[Car_Index].h = CarHeight;
	Car_Position_On_Road[Position_On_Road].w = CarWidth;
	Car_Position_On_Image[Car_Index].w = CarWidth;
	if (Position_On_Road <= 3)
		if (SDL_RenderCopy(LocalRenderer, Get_CarType[Position_On_Road], &Car_Position_On_Image[Car_Index], &Car_Position_On_Road[Position_On_Road]) == -1)
				cerr << "Some shit happened\n" << SDL_GetError() << endl;
	Loop++;
	return Car_Position_On_Road[Position_On_Road];
}



