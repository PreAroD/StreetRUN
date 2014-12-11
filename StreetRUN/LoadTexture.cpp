#include "stdafx.h"
#include "LoadTexture.h"



//Texture
LoadTexture::LoadTexture() : LocalRender(nullptr)
{
	
}


LoadTexture::~LoadTexture()
{
	Free_LoadTexture();
}
//End Texture




LoadTexture* LoadTexture::Load_Texture_Instance = nullptr;

void LoadTexture::ImageInit()
{
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		std::cerr << "SDL_image could not initialize! SDL_image Error: \n" << IMG_GetError() << std::endl;
	}
	else
	{
		std::cout << "Init PNG was Successful!" << std::endl;
	}
}


void LoadTexture::Free_LoadTexture()
{
	SDL_DestroyTexture(Temp_Texture_Get);
	SDL_FreeSurface(MainSurface);
	Temp_Texture_Get = nullptr;
	MainSurface = nullptr;
	IMG_Quit();
}

//Don't delete Checks if everything is good
SDL_Renderer* LoadTexture::InitRenderer(SDL_Renderer* Render)
{
	LocalRender = Render;
	if (LocalRender == NULL)
	{
		std::cerr << "ERROR! Could not import MainRender to LocalRender" << std::endl;
	}
	return LocalRender;
}
SDL_Renderer* LoadTexture::GetRenderer()
{
	return LocalRender;
}

//Work with Surface!
bool LoadTexture::CreateSurface(std::string Surface_Path,std::string Surface_Index)
{
	
	Surface_Container[Surface_Index] = (IMG_Load(Surface_Path.c_str()));
	if (Surface_Container[Surface_Index] == NULL)
	{
		std::cerr << "Could not load surface! because of SDL_Error: \n " << SDL_GetError() << std::endl;
		Success = false;
	}
	else
	{
		 SDL_SetColorKey(Surface_Container[Surface_Index], SDL_TRUE, SDL_MapRGB(Surface_Container[Surface_Index]->format, 255, 0, 255));
	}
	return Success;
}

//Work With Textures
bool LoadTexture::CreateTexture(std::string Index)
{
	Texture_Container[Index] = SDL_CreateTextureFromSurface(LocalRender, Surface_Container[Index]);
	if (Texture_Container[Index] == NULL)
	{
		std::cerr << "Failed to Create Texture From Surface! Because of SDL_Error: \n" << SDL_GetError() << std::endl;
		Success = false;
	}
	return Success;
}

//Main Function for pushing textures to the containers
bool LoadTexture::PushTexture(std::string Path_To_Surface, std::string Index)
{
	if (Image_IsInit == false)
	{
		ImageInit();
		Image_IsInit = true;
	}
	if (!CreateSurface(Path_To_Surface, Index))
	{
		std::cerr << "Failed to GetSurface!" << std::endl;
		Success = false;
	}
	else
	{
		if (!CreateTexture(Index))
		{
			std::cerr << "Failed to CreateTexture!" << std::endl;
			Success = false;
		}
	}
	return Success;
}
//End work with Textures

//Function for getting the texture from the container
SDL_Texture* LoadTexture::GetTexture(std::string Texture_Index)
{
	Temp_Texture_Get = Texture_Container[Texture_Index];
	if (Temp_Texture_Get == NULL)
	{
		std::cerr << "Could not Get_Texture with Index " << Texture_Index << std::endl;
		return NULL;
	}
	else
	{
		return Temp_Texture_Get;
	}
}

//Get the width of the image
int LoadTexture::GetImageWidth(std::string index)
{
	if (Surface_Container[index] == NULL)
	{
		std::cerr << "Could not take the width from the image surface" << std::endl;
		return NULL;
	}
	else
	{
		return Surface_Container[index]->w;
	}
}

//Get the height of the image
int LoadTexture::GetImageHeight(std::string index)
{
	if (Surface_Container[index] == NULL)
	{
		std::cerr << "Could not take the width from the image surface" << std::endl;
		return NULL;
	}
	else
	{
		return Surface_Container[index]->h;
	}
}

//Make the instance for all classes
LoadTexture* LoadTexture::Instance()
{
	if (Load_Texture_Instance == nullptr)
	{
		Load_Texture_Instance = new LoadTexture;
		return Load_Texture_Instance;
	}
	else
	{
		return Load_Texture_Instance;
	}
}





