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

#ifndef H_PERSONNAGE
#define H_PERSONNAGE

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <ctime>
#include "World.h"
#include "defines.h"
class World;

class Personnage
{
public:
	Personnage(sf::Vector2f position, int hitboxWidth, int hitboxHeight, std::string sprites, World *world);
	void draw(sf::RenderWindow &window);
	void move(int direction);
    int collision(int direction);
    void gravity(int direction);
    void corrigeCollision();
	void setAutoScroll(bool state);
private:
	int m_life;
	
	sf::Texture m_texSprites; 
    sf::Sprite m_sprite;
	struct s_state{
        bool jump;
        bool run;
        bool left;
    }m_state;

	struct s_saut {
		double v_y;
		double v_saut;
		double v_gravitation;
	} m_buffJump;
 	 
	sf::IntRect m_hitbox;

	sf::IntRect m_coupe;

    int m_tempsPerso;

	int m_valAffichage; // Numero du sprite à afficher (0~2)
	sf::Clock m_timerAffichage;

    World *m_world;

	bool m_autoScroll;

    int m_energieSaut;
};

#endif
 
