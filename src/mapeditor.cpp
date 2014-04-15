//Doit être modifié pour SFML [28/02/2014]

#include <iostream>


#include "World.h"
#include "defines.h"
#include "menu.h"
#include "SFML_io.h"

#include "mapeditor.h"

void mapeditor(sf::RenderWindow& window, World& world)
{
	mainloop(window, world);
}

void mainloop(sf::RenderWindow &window, World& world)
{
   //Window
    window.create(sf::VideoMode::getDesktopMode(), "Rambanana !" );
	window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);

	Menu menu("Map Editor");

	menu.addItem(&(create), "Nouveau][niveau");
	menu.addItem(&(load), "Charger][niveau");
	menu.addItem(&(setBack), "Changer][fond");
	menu.addItem(&(edit), "Editer][niveau");
	menu.addItem(&(write), "Enregistrer");
	int choix = 0;

	while(window.isOpen() && choix >= 0)
	{
		choix = menu.chooseAnActionNumber(window);
		if(choix >= 0)
			menu.doFromActionNumber(choix, window, world);
	}

}

void create(sf::RenderWindow &window, World& world)
{

}
void load(sf::RenderWindow &window, World& world)
{
    window.create(sf::VideoMode::getDesktopMode(), "Rambanana !" );
	window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);
	world = World(World::getAFileName(window), &window);
}
void edit(sf::RenderWindow &window, World& world)
{
    window.create(sf::VideoMode::getDesktopMode(), "Rambanana !" );
	window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);
	if(!world.initialized())
    {
        std::cerr << "world non-initialisé." << std::endl;
        load(window, world);
    }

	int typeBloc = 1;

	bool quit = false;
	while(!quit && window.isOpen())
	{
	    //std::cout<< "boucle event" << std::endl;
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					switch(event.key.code)
					{
						case sf::Keyboard::E:
							quit=true;
							break;
						case sf::Keyboard::Left:
							world.scroll(GAUCHE);
							break;
						case sf::Keyboard::Right:
							world.scroll(DROITE);
							break;
						case sf::Keyboard::Up:
							world.scroll(HAUT);
							break;
						case sf::Keyboard::Down:
							world.scroll(BAS);
							break;
                        case sf::Keyboard::Numpad1:
							typeBloc = 1;
							break;
                        case sf::Keyboard::Numpad2:
							typeBloc = 2;
							break;
                        case sf::Keyboard::Numpad3:
							typeBloc = 3;
							break;
                        case sf::Keyboard::Numpad4:
							typeBloc = 4;
							break;
                        case sf::Keyboard::Numpad5:
							typeBloc = 5;
							break;
                        case sf::Keyboard::Numpad6:
							typeBloc = 6;
							break;
							
						default:
                            break;
					} 
					break;
                default:
                    break;

			}
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
				world.setBlocType(window.mapPixelToCoords(sf::Mouse::getPosition(window)), typeBloc);
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
				world.eraseBloc(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}
		window.clear(sf::Color::Black);
		world.updateBloc();
		world.draw();
        	    //std::cout<< "boucle event" << std::endl;

		window.display();
	}
}

void setBack(sf::RenderWindow &window, World& world)
{
}
void write(sf::RenderWindow &window, World& world)
{
}
