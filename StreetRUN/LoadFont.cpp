#include "stdafx.h"
#include "LoadFont.h"


LoadFont::LoadFont()
{
}


LoadFont::~LoadFont()
{
}

LoadFont* LoadFont::Load_Font_Instance = nullptr;

void LoadFont::FontInit()
{
	Instance();
	if (TTF_Init() == -1)
		std::cerr << "Could not init TTF! " << TTF_GetError() << std::endl;
}

void LoadFont::Free_LoadFont()
{
	Font_IsInit = false;
	Surface_Container.clear();
	Texture_Container.clear();
	Font = nullptr;
	TTF_Quit();
}

//Load the font
bool LoadFont::SetFont(const std::string Path_To_Font, int Font_Size)
{
	//Init the font
	if (Font_IsInit == false)
	{
		FontInit();
		Font_IsInit = true;
	}
	//END FOT INIT
	Font = TTF_OpenFont(Path_To_Font.c_str(), Font_Size);
	if (Font == NULL)
	{
		std::cerr << "Could not open font " << TTF_GetError() << std::endl;
		Success = false;
	}
	return Success;
}

//Create surface from the text with the color
bool LoadFont::CreateSurfaceText(const std::string Text, SDL_Color Text_Color, std::string TextIndex)
{

	Surface_Container[TextIndex] = TTF_RenderText_Solid(Font, Text.c_str(), Text_Color);
	if (Surface_Container[TextIndex] == NULL)
	{
		std::cerr << "Could not load font surface because of SDL_Error: \n " << TTF_GetError() << std::endl;
		Success = false;
	}
	return Success;
}

//Create the text texture
bool LoadFont::CreateTextureText(std::string TextIndex)
{

	Texture_Container[TextIndex] = SDL_CreateTextureFromSurface(LocalRender, Surface_Container[TextIndex]);
	if (Texture_Container[TextIndex] == NULL)
	{
		std::cerr << "Could not create texture from surface! because of SDL_Error: \n " << TTF_GetError << std::endl;
		Success = false;
	}
	return Success;
}

//Push the text to the container
bool LoadFont::PushText(std::string Text, SDL_Color Text_Color, std::string Index)
{
		if (!CreateSurfaceText(Text, Text_Color, Index))
		{
			std::cerr << "Could not make surface from the font!" << std::endl;
			Success = false;
		}
		else
		{
			if (!CreateTextureText(Index))
			{
				std::cerr << "Could not create texture from font surface!" << std::endl;
			}
		}
	return Success;
}

//Get the text by the index
SDL_Texture* LoadFont::GetText(std::string Index)
{
	SDL_Texture* Temp_Texture = Texture_Container[Index];
	if (Temp_Texture == NULL)
	{
		std::cerr << "Could not return Text Texture, because its NULL" << std::endl;
		return NULL;
	}
	return Texture_Container[Index];
}


//Get the max width of the text
int LoadFont::GetTextWidth(std::string Index)
{
	SDL_Surface* Temp_Surface = Surface_Container[Index];
	if (Temp_Surface == NULL)
		std::cerr << "Could not take the width from the font surface" << std::endl;
	return Temp_Surface->w;
}

//Get the max height of the text
int LoadFont::GetTextHeight(std::string Index)
{
	SDL_Surface* Temp_Surface = Surface_Container[Index];
	if (Temp_Surface == NULL)
		std::cerr << "Could not take the height from the font surface" << std::endl;
	return Temp_Surface->h;
}

//Get renderer from the main renderer
SDL_Renderer* LoadFont::InitRenderer(SDL_Renderer* Render)
{
	LocalRender = Render;
	if (LocalRender == NULL)
	{
		std::cerr << "ERROR! Could not import MainRender to LocalRender" << std::endl;
	}
	return LocalRender;
}

LoadFont* LoadFont::Instance()
{
	if (Load_Font_Instance == nullptr)
	{
		Load_Font_Instance = new LoadFont;
		return Load_Font_Instance;
	}
	else
	{
		return Load_Font_Instance;
	}
}

SDL_Renderer* LoadFont::GetRenderer()
{
	return LocalRender;
}
