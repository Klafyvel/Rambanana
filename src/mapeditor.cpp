#include <iostream>

#include <SDL2/SDL.h>

#include "World.h"
#include "SDLFunc.h"
#include "defines.h"
#include "menu.h"

#include "mapeditor.h"



int main(int argc, char* argv[])
{
	lvl world;
 
	Menu menu;
	Menu_new(&menu, "Préparation de la map");

	Item itemCreate;
	Item itemLoad;
	Item itemSize;
	Item itemBack;
	Item itemEdit;
	Item itemWrite;

	
	Menu_newItem(&itemCreate, create, "Créer une map");
	Menu_newItem(&itemLoad, load, "Charger une map");
	Menu_newItem(&itemSize, setSize, "Changer la taille de la map");
	Menu_newItem(&itemBack, setBack, "Modifier le fond");
	Menu_newItem(&itemEdit, edit, "Editer la map");
	Menu_newItem(&itemWrite, write, "Sauvegarder la map");

	Menu_addItem(&menu, &itemCreate);
	Menu_addItem(&menu, &itemLoad);
	Menu_addItem(&menu, &itemSize);
	Menu_addItem(&menu, &itemBack);
	Menu_addItem(&menu, &itemEdit);
	Menu_addItem(&menu, &itemWrite);

    while(1)
    {
        int action = Menu_choose(&menu);

        if(action == -1)
        {
            break;
        }
        else
        {
            if(!Menu_do(&menu, action, &world))
            {
                printf("Erreur lors du lancement d'une action.\n");
            }
        }
    }

    return 0;
}

void create(lvl* world)
{
	std::string chemin;
	std::cout << "Chemin actuel :" << world->chemin << std::endl;
	std::cout << "Indiquez le chemin (relatif) du fichier: ";
	std::cin >> chemin;
	world->chemin = chemin;
	(*world).background = chemin;
	(*world).h=0;
	(*world).w=0;
}
void load(lvl* world)
{/*
	for(int i=0; i<world->h; i++)
	{
		world->blocs.pop_back();
	}*/

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
	fic.close();
}
void edit(lvl* world)
{
	write(world);

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
			}
		}
		SDL_RenderClear(renderer);
		map.affiche(renderer);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fen);
	SDL_Quit();
}
void setSize(lvl* world)
{
	std::cout << "Taille actuelle :" << world->w << "x" << world->h << std::endl;
	std::cout << "Indiquez la nouvelle largeur (en blocs): ";
	std::cin >> world->w;
	std::cout << "Indiquez la nouvelle hauteur (en blocs): ";
	std::cin >> world->h;
	for(int i=0; i<world->w; i++)
	{
		std::vector <int> v;
		for(int j=0; j<world->h; j++)
		{
			v.push_back(0);
		}
		world->blocs.push_back(v);
	}
}
void setBack(lvl* world)
{
	std::cout << "Chemin actuel :" << world->background << std::endl;
	std::cout << "Indiquez le chemin (relatif) du background: ";
	std::cin >> world->background;
}
void write(lvl* world)
{
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
}
