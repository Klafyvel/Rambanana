/*    Copyright (C) 2013 LEVY-FALK Hugo

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
#include "menu.h"

Item::Item()
{
	subMenu = NULL;
	function =NULL;
	label="";
}

Menu::Menu(std::string title)
{
	m_title = title;
}

void Menu::addItem(callback function, std::string label)
{
	struct Item item;
	item.function = function;
	item.label = label;
	item.subMenu = NULL;
	m_items.push_back(item);
}

void Menu::addSubMenu(Menu *subMenu, std::string label)
{
	struct Item item;
	item.subMenu = subMenu;
	item.function = NULL;
	item.label = label;
	m_items.push_back(item);
}

void Menu::removeItemByLabel(std::string label)
{
	for(int i=0; i<m_items.size(); i++)
	{
		if(m_items[i].label == label)
			Menu::removeItemByActionNumber(i);
	}
}

void Menu::removeItemByActionNumber(int action)
{
    if((action < 0)||(action >= m_items.size()))
        return;
	m_items.erase(m_items.begin() + action);
}

unsigned int Menu::getTextHeight()
{
	return TITLESIZE + (m_items.size()+1) * (LABELSIZE + INTERLIGNE);
}

unsigned int Menu::getMaxTextWidth()
{
	int largest = 0;
	for(int i=0; i<m_items.size(); i++)
	{
		if(m_items[i].label.length() > largest)
			largest = m_items[i].label.size();
	}
	return largest * LABELSIZE * 1.25;
}

sf::Vector2u Menu::getTextSize()
{
	return sf::Vector2u(Menu::getMaxTextWidth() + 2*SPACEONTEXTSIDE,
						Menu::getTextHeight() + SPACEONTEXTTOP + SPACEONTEXTBOTTOM);
}

int Menu::chooseAnActionNumber(sf::RenderWindow &window)
{
	window.setSize(Menu::getTextSize());
	sf::View view(sf::Vector2f(Menu::getMaxTextWidth()/2,Menu::getTextHeight()/2), sf::Vector2f(Menu::getTextSize()));
	window.setView(view);


	int choix = -1;

	int x = -1;
	int y = -1;

	sf::Font titleFont;
	sf::Font itemFont;
	if(!titleFont.loadFromFile("../font/Bananananananana.ttf") || !itemFont.loadFromFile("../font/BATMAN.TTF"))
		return -1;

	sf::Text textTitle;
	textTitle.setFont(titleFont);
	textTitle.setString(m_title);
	textTitle.setCharacterSize(TITLESIZE);
	textTitle.setColor(sf::Color::Yellow);
	textTitle.setPosition(sf::Vector2f(SPACEONTEXTSIDE, SPACEONTEXTTOP));

	std::vector <sf::Text> textItems;

	std::vector <sf::IntRect> rectItems;

	int yText = SPACEONTEXTTOP + TITLESIZE + INTERLIGNE;
 
	for(int i=0; i<=m_items.size(); i++)
	{
		sf::Text text;
		text.setFont(itemFont);
		text.setCharacterSize(LABELSIZE);
		text.setColor(sf::Color::Green);
		text.setPosition(sf::Vector2f(SPACEONTEXTSIDE, yText));

		std::string str;
		if(i<m_items.size())
			str = m_items[i].label;
		else
			str = "Quitter";

		str.insert(0, "[");
		str.append("]");
	
		text.setString(str);

		textItems.push_back(text);

		sf::IntRect rect(SPACEONTEXTSIDE, yText, Menu::getMaxTextWidth()-SPACEONTEXTSIDE, LABELSIZE * 1.5);
		rectItems.push_back(rect);

		yText += LABELSIZE + INTERLIGNE;
	}

	while((choix < 0) && window.isOpen())
    {
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					choix = -1;
					break;
				case sf::Event::MouseButtonPressed:
					x = event.mouseButton.x;
					y = event.mouseButton.y;
					break;
				default:
					break;
			}
		}

		window.clear(sf::Color::Black);

		for(int i=0; i<rectItems.size(); i++)
		{
			window.draw(textItems[i]);
		}
		window.draw(textTitle);

		window.display();

		for(int i=0; i<rectItems.size(); i++)
		{
			if(((x > rectItems[i].left) && (x < (rectItems[i].left + rectItems[i].width)))&&(y > rectItems[i].top && (y < (rectItems[i].top + rectItems[i].height))))
			{
				choix = i;
				x=-1;
				y=-1;
			}
		}
	}
	if(choix==(m_items.size())) // si on choisis de quitter le programme
        return -1;
    else
       return choix;
}

void Menu::doFromActionNumber(int action, sf::RenderWindow &window)
{
    if((action<0)||(action >= m_items.size()))
    {
        return ;
    }
    else
    {
		callback function;
		if(m_items[action].function)
		{
			function = m_items[action].function;
	        function(window);
	    }
	    else if(m_items[action].subMenu)
	    {
	        m_items[action].subMenu->doFromActionNumber(m_items[action].subMenu->chooseAnActionNumber(window), window);
	    }
    }
}
