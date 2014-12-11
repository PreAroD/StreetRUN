#pragma once

#include "LoadFont.h"

class Text
{
public:
	Text();
	~Text();
	void SetFont(std::string,int);
	//Text then Index then Color
	void SetText(std::string,std::string,SDL_Color);
	SDL_Texture* GetText(std::string);
	void Render_Text(std::string Index,int PosX,int PosY);


};

