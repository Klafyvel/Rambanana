#include "game.h"
void game(sf::RenderWindow &window, World& world)
{
	window.create(sf::VideoMode::getDesktopMode(), "Rambanana !" );
	window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0, 0, window.getSize().x, window.getSize().y));

    window.setView(view);

	World map(World::getAFileName(window), &window);
	if(!map.initialized())
	{
		std::cerr << "Erreur lors de la création de l'objet World" << std::endl;
		return ;
	}

    Personnage Rambanana(map.getCharacterPos(), TAILLE_HITBOX_PERSO_X, TAILLE_HITBOX_PERSO_Y, "../sprites/SpritesRambanana.bmp", &map);
	Rambanana.setAutoScroll(true);
	bool quit = false;

	while(window.isOpen() && !quit)
	{
        bool moving = false;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			Rambanana.move(COUR | GAUCHE);
			moving = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			Rambanana.move(COUR | DROITE);
			moving = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Rambanana.move(SAUTE);
			moving = true;
		}


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
							quit = true;
							break;
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
        map.draw();
		Rambanana.draw(window);

        window.display();


}

}
