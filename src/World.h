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
#ifndef H_WORLD
#define H_WORLD

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include "personnage.h"

class World
{
public:
	World(std::string file, SDL_Renderer* renderer);
	int typeBloc(int x, int y); // Pour détecter les collisions
	void affiche(SDL_Renderer* renderer);
	void scroll(int mvX);// 0 = vers la gauche 1 = vers la droite
	void upgradeBloc(int x, int y);
	void eraseBloc(int x, int y);
	void getMap(std::vector <std::vector <int>> *receiver); 
	~World();
 
private:
 	int m_debutAffichage;
	std::vector <std::vector <SDL_Rect>> m_blocs;
	SDL_Texture* m_background;
	SDL_Texture* m_texBlocs;
};

#endif
