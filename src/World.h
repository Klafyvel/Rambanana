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

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "libjson.h"

#include "personnage.h"

class Bloc
{
public:
    Bloc();
    void setRect(sf::IntRect rect);
    void setSprite(sf::Sprite sprite);
    sf::IntRect &getRect();
    sf::Sprite &getSprite();
private:
    sf::IntRect m_rect;
    sf::Sprite m_sprite;
};

class Personnage;
class World
{
public:
	World(std::string file = "");
    World(const World &world);
	int typeBloc(sf::Vector2f pos);
    void draw(sf::RenderWindow &window);
	void scroll(int direction);
	void upgradeBloc(sf::Vector2f pos);
	void eraseBloc(sf::Vector2f pos);
	void getMap(std::vector <std::vector <int> > *receiver);
    sf::Vector2f getCaracterPos();
    void updateBloc();
	bool initialized();
	void parseJSON(const JSONNode & n);
 
private:
	bool m_initialized;
 	int m_debutAffichage;
	std::vector <std::vector <Bloc> > m_blocs;
	sf::Texture m_texBackground;
	sf::Sprite m_background;
	sf::Texture  m_texBlocs;
	sf::Vector2f m_posInitPers;
	std::string m_lvlName;
	std::string m_cheminBackground;
	std::string m_cheminTexBlocs;
};
#endif
