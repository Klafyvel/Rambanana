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
#include <string>

#include "World.h"
#include "defines.h"
#include "personnage.h"

int main(int argc, char* argv[])
{
    //Window
    sf::RenderWindow window(sf::VideoMode(TAILLE_X, TAILLE_Y), "Rambanana !");

    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);

	World world("../lvl/1.lvl.json");
	if(!world.initialized())
	{
		std::cerr << "Erreur lors de la création de l'objet World" << std::endl;
		return 1;
	}

    Personnage Rambanana(sf::Vector2f(50,50), TAILLE_HITBOX_PERSO_X, TAILLE_HITBOX_PERSO_Y, "../sprites/SpritesRambanana.bmp", &world);


while(window.isOpen())
{
        bool moving = false;
        sf::Event event;
        while(window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
				case sf::Event::MouseButtonPressed:
					std::cout << world.typeBloc(sf::Vector2f(event.mouseButton.x, event.mouseButton.y)) << std::endl;
					break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::A:
                            view.zoom(0.5);
                            window.setView(view);
                            break;
                        case sf::Keyboard::Z:
                            view.zoom(2);
                            window.setView(view);
                            break;
                        case sf::Keyboard::Q:
                            view.move(sf::Vector2f(-5,0));
                            window.setView(view);
							break;
                        case sf::Keyboard::Left:
                            moving = true;
							Rambanana.move(COUR | GAUCHE);
                            break;
                        case sf::Keyboard::S:
                            view.move(sf::Vector2f(5,0));
                            window.setView(view);
							break;
                        case sf::Keyboard::Right:
                            moving = true;
							Rambanana.move(COUR | DROITE);
                            break;/*
case sf::Keyboard::Left:
moving = true;
Rambanana.move(SAUTE);
break;*/
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        if(!moving)
        {
            Rambanana.move(IMMOBILE);
        }
        Rambanana.gravity(BAS);

        window.clear(sf::Color::Black);
        world.draw(window);
Rambanana.draw(window);

        window.display();


}

return 0;
}
