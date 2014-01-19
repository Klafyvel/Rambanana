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
#include <SDL2/SDL.h>

typedef struct Bloc Bloc;
struct Bloc
{
	SDL_Texture image;
	int type;
};

class World
{
public:
	World(std::string file);
	bool isInAFullBlock(int x, int y); // Pour détecter les collisions

private:
	Bloc m_blocs[];
	SDL_Texture m_background;
};

#endif
