// StreetRUN.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"

int main(int argc, char* argv[])
{
	int Fps = 0;
	bool Do_Quit = false;
	SDL_Event* MainEvent = new SDL_Event;
	Game TheGame;
	if (!TheGame.Init("StreetRUN",1024,900,500,100,SDL_WINDOW_SHOWN))
	{
		std::cerr << "Could not init everything because of SDL_Error: \n" << SDL_GetError() << std::endl;
	}
	else
	{

		//TODO Add some pushTexture functions 
	}
	while (!Do_Quit)
	{
		while (SDL_PollEvent(MainEvent) != 0)
		{
			//For normal Exit
			if (MainEvent->type == SDL_QUIT)
			{
				Do_Quit = true;
			}
			//For Escape Exit
			if (MainEvent->key.keysym.sym == SDLK_ESCAPE)
			{
				Do_Quit = true;
			}
			//The main event handler
			TheGame.Event_Handler(MainEvent);
		}
		TheGame.Update();
		
		SDL_SetRenderDrawColor(TheGame.GetRenderer(), 255, 255, 255, 255);
		SDL_RenderClear(TheGame.GetRenderer());
		TheGame.Render();
		SDL_RenderPresent(TheGame.GetRenderer());
		Fps++;
		TheGame.Push_Fps(Fps);
	}
	TheGame.Quit();

	return 0;
}

