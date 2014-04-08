//Doit être modifié pour SFML [28/02/2014]

#include <iostream>


#include "World.h"
#include "defines.h"
#include "menu.h"

#include "mapeditor.h"



void mapeditor(sf::RenderWindow &window)
{
   //Window
    window.create(sf::VideoMode::getDesktopMode(), "Rambanana !", sf::Style::Fullscreen);
	window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);

	Menu menu("Map Editor");

	menu.addItem(&create, "Nouveau][niveau");
	menu.addItem(&load, "Charger][niveau");
	menu.addItem(&setBack, "Changer][fond");
	menu.addItem(&edit, "Editer][niveau");
	menu.addItem(&write, "Enregistrer");
	int choix = 0;

	while(window.isOpen() && choix >= 0)
	{
		choix = menu.chooseAnActionNumber(window);
		if(choix >= 0)
			menu.doFromActionNumber(choix, window);
	}

}

void create(sf::RenderWindow &window)
{
    /*
	std::string chemin;
	std::cout << "Chemin actuel :" << world->chemin << std::endl;
	std::cout << "Indiquez le chemin (relatif) du fichier: ";
	std::cin >> chemin;
	world->chemin = chemin;
	(*world).background = chemin;
	(*world).h=0;
	(*world).w=0;*/
}
void load(sf::RenderWindow &window)
{
    /*
	std::string chemin;
	std::cout << "Chemin actuel :" << world->chemin << std::endl;
	std::cout << "Indiquez le chemin (relatif) du fichier: ";
	std::cin >> chemin;
	world->chemin = chemin;

	char c;

	std::ifstream fic(chemin, std::ios::in);
	if(!fic)
		return;

	fic >> world->background >> world->w >> world->h;

	fic.get(c);

	for(int i=0; i<world->w; i++)
	{
		std::vector <int> v;
		for(int j=0; j<world->h; j++)
		{
			bool isEndl = false;
			int foo;
			fic.get(c);
			switch(c)
			{

				case '0':
					foo = 0;
					break;
				case '1':
					foo = 1;
					break;
				case '2':
					foo = 2;
					break;
				case '3':
					foo = 3;
					break;
				case '4':
					foo = 4;
					break;
				case '5':
					foo = 5;
					break;
				case '6':
					foo = 6;
					break;
				default:
					isEndl = true;
					break;
			}
			if(!isEndl)
				v.push_back(foo);
			else
			{
				isEndl = false;
			}
		}
		while(c!='\n')
			fic.get(c);
		world->blocs.push_back(v);
	}
	fic.close();*/
}
void edit(sf::RenderWindow &window)
{
/*
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return;
	SDL_Window *fen = SDL_CreateWindow("Editor", 0, 0, TAILLE_X, TAILLE_Y, SDL_WINDOW_SHOWN);
	if(fen == nullptr)
		return;
	SDL_Renderer *renderer = SDL_CreateRenderer(fen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if(renderer == nullptr)
		return;

	World map(world->chemin, renderer);

	SDL_Event e;

	bool quit = false;

	while(!quit)
	{
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT)
			{
				write(world);
				quit = true;
			}
			if(e.type == SDL_MOUSEBUTTONDOWN)
			{
				if(e.button.button == SDL_BUTTON_LEFT)
					map.upgradeBloc(e.button.x, e.button.y);
				if(e.button.button == SDL_BUTTON_RIGHT)
					map.eraseBloc(e.button.x, e.button.y);
			}
			if(e.type == SDL_KEYDOWN)
			{
				if(e.key.keysym.sym == SDLK_RIGHT)
					map.scroll(0);
				if(e.key.keysym.sym == SDLK_LEFT)
					map.scroll(1);
				if(e.key.keysym.sym == SDLK_RETURN)
				{
					map.getMap(&world->blocs);
					write(world);
					quit = true;
				}
			}
		}
		SDL_RenderClear(renderer);
		map.affiche(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fen);
	SDL_Quit();*/
}
/*
void setSize(lvl* world)
{
	std::cout << "Taille actuelle :" << world->w << "x" << world->h << std::endl;
	std::cout << "Indiquez la nouvelle largeur (en blocs): ";
	std::cin >> world->w;
	std::cout << "Indiquez la nouvelle hauteur (en blocs): ";
	std::cin >> world->h;
	int oldW = world->blocs.size();
	if(oldW < world->w)
	{
		for(int i=0; i<oldW; i++)
		{
			int oldH = world->blocs[i].size();
			for(int j=oldH; j<world->h; j++)
			{
				world->blocs[i].push_back(0);
			}
		}
		for(int i=oldW; i<world->w; i++)
		{
			std::vector <int> row;
			for(int j=0; j<world->h; j++)
			{
				row.push_back(0);
			}
			world->blocs.push_back(row);
		}
	}
	if(oldW > world->w)
	{
		for(int i=oldW-1; i>=world->w; i--)
		{
			world->blocs.pop_back();
		}
	}
}*/
void setBack(sf::RenderWindow &window)
{
    /*
	std::cout << "Chemin actuel :" << world->background << std::endl;
	std::cout << "Indiquez le chemin (relatif) du background: ";
	std::cin >> world->background;*/
}
void write(sf::RenderWindow &window)
{
    /*
	std::ofstream fic(world->chemin, std::ios::out | std::ios::trunc);
	if(!fic)
		return;
	if((world->background == "")||(world->h == 0)||(world->w == 0))
		return;
	fic << world->background << std::endl << world->w << " " << world->h << std::endl;
	for(int i=0; i<world->w; i++)
	{
		for(int j=0; j<world->h; j++)
		{
			fic << world->blocs[i][j];
		}
		fic << std::endl;
	}
	fic.close();
	*/
}
