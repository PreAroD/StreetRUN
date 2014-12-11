#pragma once

#include <string>
#include <map>


class LoadTexture
{
private:
	//DATA
	bool Success = true;
	std::map<std::string,SDL_Texture*> Texture_Container;
	std::map<std::string,SDL_Surface*> Surface_Container;
	
	
	//Functions
	void Free_LoadTexture();
	//Functions Surface
	void ImageInit();
	bool CreateSurface(std::string,std::string);
	bool CreateTexture(std::string);
	bool Image_IsInit = false;
	
	//SDL
	SDL_Surface* MainSurface = nullptr;
	SDL_Texture* Temp_Texture_Get = nullptr;
	SDL_Renderer* LocalRender = nullptr;
	static LoadTexture* Load_Texture_Instance;
	
public:
	
	LoadTexture();
	~LoadTexture();
	//Image
	bool PushTexture(std::string Path_To_Surface, std::string Index);
	SDL_Texture* GetTexture(std::string);
	static LoadTexture* Instance();
	int GetImageWidth(std::string);
	int GetImageHeight(std::string);
	SDL_Renderer* InitRenderer(SDL_Renderer*);
	SDL_Renderer* GetRenderer();
};