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

	SDL_Window *fen = SDL_CreateWindow("Rambanana !", 0, 0, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
	if (fen == nullptr){
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Renderer *renderer = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr){
		logSDLError(std::cout, "CreateRenderer");
		return 1;
	}


	World world("../lvl/1.lvl", renderer);
 
	Personnage Rambanana(26, 26 * 18 - (int)(TAILLE_PERSO_Y * 2), 30, 25, "../sprites/SpritesRambanana.bmp", renderer, &world); 
	
    SDL_Event e;

	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
				quit = true;
			if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				std::cout << world.typeBloc(e.button.x, e.button.y) << std::endl;
			}
			if(e.type == SDL_KEYDOWN)
			{
				switch(e.key.keysym.sym)
				{
					case SDLK_LEFT:
						Rambanana.move(COUR | GAUCHE);
						break;
					case SDLK_RIGHT:
						Rambanana.move(COUR | DROITE);
						break;
                    case SDLK_UP:
                        Rambanana.move(HAUT);
                        break;
                    case SDLK_DOWN:
                        Rambanana.move(BAS);
                        break;
                    case SDLK_q:
                        world.scroll(GAUCHE);
                        break;
                    case SDLK_d:
                        world.scroll(DROITE);
                        break;
                    case SDLK_SPACE:
                        Rambanana.move(SAUTE);
                        break;
					default:
						break;
				}
			}
            else
            {
                Rambanana.move(IMMOBILE);
            }

		}
        Rambanana.gravite(BAS);
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
