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

#include <errno.h>

#include <dirent.h>

#ifndef WIN32
	#include <sys/types.h>
#endif

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "cJSON.h"

#include "menu.h"
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
	World(std::string file, sf::RenderWindow *window);
	World();
	void create(std::string file, sf::RenderWindow *window);
	int typeBloc(sf::Vector2f pos);
    void draw();
	void scroll(int direction);
	void upgradeBloc(sf::Vector2f pos);
	void eraseBloc(sf::Vector2f pos);
	void setBlocType(sf::Vector2f pos, int type); 
	std::string getJSONMap();
    sf::Vector2f getCharacterPos();
    void updateBloc();
	bool initialized();
	void parseJSON(std::string json);
	std::string getFileName();
	void setCharPos(sf::Vector2f pos);

	static std::string getAFileName(sf::RenderWindow &window);

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
	sf::RenderWindow *m_window;
	std::string m_lvlPath;
};

#endif
