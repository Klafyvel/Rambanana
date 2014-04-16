#ifndef H_GAME
#define H_GAME

#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "World.h"
#include "defines.h"
#include "personnage.h"
#include "menu.h"
class World;
void game(sf::RenderWindow &window, World& world);
#endif
