/*    Copyright (C) 2014 LEVY-FALK Hugo

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/
#ifndef H_MENU
#define H_MENU

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "color.h"

#include "mapeditor.h"

#define SPACEONTEXTSIDE 10
#define SPACEONTEXTTOP 10
#define SPACEONTEXTBOTTOM 10

#define TITLESIZE 150
#define LABELSIZE 75
#define INTERLIGNE 10

typedef void (*callback)(sf::RenderWindow &window);

class Menu;

struct Item {
	Item();
	Menu* subMenu; 
	callback function;
	std::string label;
};

class Menu
{
public:
	Menu(std::string title);
	void addItem(callback function, std::string label);
	void addSubMenu(Menu *subMenu, std::string label);
	void removeItemByLabel(std::string label);
	void removeItemByActionNumber(int action);
	void doFromActionNumber(int action, sf::RenderWindow &window);
	int chooseAnActionNumber(sf::RenderWindow &window);
	sf::Vector2u getTextSize();
	unsigned int getMaxTextWidth();
	unsigned int getTextHeight();
private:
    std::vector <struct Item> m_items;
    std::string m_title;
	/*bool isASubMenu;*/
};


#endif
