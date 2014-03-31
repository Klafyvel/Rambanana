#include "game.h"
void game(sf::RenderWindow &window)
{
	window.setSize(sf::Vector2u(TAILLE_X, TAILLE_Y));
	window.setFramerateLimit(30);
	
    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);

	World world("../lvl/1.lvl", &window);
	if(!world.initialized())
	{
		std::cerr << "Erreur lors de la création de l'objet World" << std::endl;
		return ;
	}

    Personnage Rambanana(world.getCharacterPos(), TAILLE_HITBOX_PERSO_X, TAILLE_HITBOX_PERSO_Y, "../sprites/SpritesRambanana.bmp", &world);
	Rambanana.setAutoScroll(true);
	bool quit = false;

	while(window.isOpen() && !quit)
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
                            break;
						case sf::Keyboard::E:
							quit = true;
							break;
						case sf::Keyboard::Space:
							moving = true;
							Rambanana.move(SAUTE);
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

}
