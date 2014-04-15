//Doit être modifié pour SFML [28/02/2014]
#ifndef H_MAPEDITOR
#define H_MAPEDITOR

#include <iostream>

#include "defines.h"
#include "World.h"

#include "menu.h"
class World;


typedef struct lvl lvl;
struct lvl
{
	std::string chemin;
	std::string background;
	int h;
	int w;
	std::vector <std::vector <int> > blocs;
};
void mapeditor(sf::RenderWindow &window, World& world);

void mainloop(sf::RenderWindow &window, World& world);
void create(sf::RenderWindow &window, World& world);
void load(sf::RenderWindow &window, World& world);
void edit(sf::RenderWindow &window, World& world);
void setBack(sf::RenderWindow &window, World& world);
void write(sf::RenderWindow &window, World& world);


#endif
