//Doit être modifié pour SFML [28/02/2014]
#ifndef H_MAPEDITOR
#define H_MAPEDITOR

#include <iostream>

#include "defines.h"
#include "World.h"

#include "menu.h"

typedef struct lvl lvl;
struct lvl
{
	std::string chemin;
	std::string background;
	int h;
	int w;
	std::vector <std::vector <int> > blocs;
};
void mapeditor(sf::RenderWindow &window);
void create(sf::RenderWindow &window);
void load(sf::RenderWindow &window);
void edit(sf::RenderWindow &window);
void setBack(sf::RenderWindow &window);

void write(sf::RenderWindow &window);

#endif
