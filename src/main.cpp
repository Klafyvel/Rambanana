/* Copyright (C) 2014 LEVY-FALK Hugo

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
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "World.h"
#include "defines.h"
#include "personnage.h"
#include "game.h"
#include "menu.h"

void test(sf::RenderWindow &window)
{
	std::cout << "Coucou !" << std::endl;
}


int main(int argc, char* argv[])
{

    //Window
    sf::RenderWindow window(sf::VideoMode(TAILLE_X, TAILLE_Y), "Rambanana !");

	window.setVerticalSyncEnabled(true);

	Menu menu("Rambanana !");

	menu.addItem(&game, "Jouer");
	menu.addItem(&test, "Testeuuuu");
	
	while(window.isOpen())
	{
		int choix = menu.chooseAnActionNumber(window);
		menu.doFromActionNumber(choix, window);
	}

	return 0;
}
