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
#include "mapeditor.h"

void test(sf::RenderWindow &window)
{
	window.setSize(sf::Vector2u(20,20));
	std::cout << "Work in progress..." << std::endl;
}


int main()
{

    //Window
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Rambanana !" );

	window.setVerticalSyncEnabled(true);

	Menu menu("Rambanana !");

	menu.addItem(&game, "Jouer");
	menu.addItem(&mapeditor, "Map][editor");
	int choix = 0;

	World world;

	while(window.isOpen() && choix >= 0)
	{
		choix = menu.chooseAnActionNumber(window);
		if(choix >= 0)
			menu.doFromActionNumber(choix, window, world);
	}

	window.~RenderWindow();
	return 0;
}
