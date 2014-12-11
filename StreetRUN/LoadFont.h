#pragma once
#include <map>
class LoadFont
{
private:
	//Data
	bool Success = true;
	std::map<std::string, SDL_Texture*> Texture_Container;
	std::map<std::string, SDL_Surface*> Surface_Container;
	//Functions Font
	void Free_LoadFont();
	void FontInit();
	
	bool CreateSurfaceText(std::string, SDL_Color, std::string);//Create Surface Text 3
	bool CreateTextureText(std::string); //Create Texture

	SDL_Renderer* LocalRender = nullptr;
	bool Font_IsInit = false;
	int FontWidth, FontHeight;
	TTF_Font* Font = nullptr;
	static LoadFont* Load_Font_Instance;

public:
	LoadFont();
	~LoadFont();

		bool PushText(std::string Text, SDL_Color Text_Color, std::string Index);
		bool SetFont(std::string, int);
		SDL_Texture* GetText(std::string); //Main Function
		static LoadFont* Instance();
		int GetTextWidth(std::string);
		int GetTextHeight(std::string);
		SDL_Renderer* GetRenderer();
		SDL_Renderer* InitRenderer(SDL_Renderer*);
	};

