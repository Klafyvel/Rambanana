/*    Copyright (C) 2014 LEVY-FALK Hugo

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <string>

#include "SDLFunc.h"
#include "defines.h"
#include "personnage.h"
#include "World.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window *fen = SDL_CreateWindow("Rambanana !", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (fen == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		return 1;
	}

	Personnage Rambanana(0, 0, 38, 26, "../sprites/SpritesRambanana.bmp", renderer);

	World world("../lvl/1.lvl", renderer);

	SDL_Event e;

	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				quit = true;
			if(e.type == SDL_KEYDOWN)
				quit = true;
			if(e.type == SDL_MOUSEBUTTONDOWN)
				quit = true;
		}
		SDL_RenderClear(renderer);
		world.affiche(renderer);
		Rambanana.affiche(renderer);
		SDL_RenderPresent(renderer);

	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fen);
	SDL_Quit();
	return 0;
}
