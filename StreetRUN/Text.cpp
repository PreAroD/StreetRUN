#include "stdafx.h"
#include "Text.h"


Text::Text()
{
}


Text::~Text()
{
}

void Text::SetFont(std::string Path, int Size)
{
	LoadFont::Instance()->SetFont(Path, Size);
}

void Text::SetText(std::string The_Text, std::string Index, SDL_Color Text_Color)
{
	LoadFont::Instance()->PushText(The_Text, Text_Color, Index);
}

SDL_Texture* Text::GetText(std::string Index)
{
	return LoadFont::Instance()->GetText(Index);
}

void Text::Render_Text(std::string Index, int PosX, int PosY)
{
	SDL_Rect Src;
	SDL_Rect Dest;
	//Source
	Src.h = LoadFont::Instance()->GetTextHeight(Index);
	Src.w = LoadFont::Instance()->GetTextWidth(Index);
	Src.x = 0;
	Src.y = 0;
	//Destination
	Dest.h = LoadFont::Instance()->GetTextHeight(Index);
	Dest.w = LoadFont::Instance()->GetTextWidth(Index);
	Dest.x = PosX;
	Dest.y = PosY;
	SDL_RenderCopy(LoadFont::Instance()->GetRenderer(), GetText(Index), &Src, &Dest);
}
