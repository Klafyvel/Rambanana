#include "World.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "SDLFunc.h"

#include <SDL2/SDL.h>

World::World(std::string file, SDL_Renderer* renderer)
{
	std::ifstream lvl(file, std::ios::in);
	if(!lvl)
	{
		std::cout << "Impossible de charger le fichier niveau" << std::endl;
		return;
	}
	char c;

	std::string background;
	int w, h;
	lvl >> background >> w >> h;


	for(int i=0; i<=w; i++)
	{
		std::vector <int> v;
		for(int j=0; j<=h; j++)
		{
			v.push_back(0);
		}
		m_blocs.push_back(v);
	}
	

	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			lvl.get(c);
			switch(c)
			{
				case '0':
					m_blocs[i][j] = 0;
					break;
				case '1':
					m_blocs[i][j] = 1;
					break;
				case '2':
					m_blocs[i][j] = 2;
					break;
				case '3':
					m_blocs[i][j] = 3;
					break;
				case '4':
					m_blocs[i][j] = 4;
					break;
				case '5':
					m_blocs[i][j] = 5;
					break;
				default:
					break;
			}
		}
	}	
	
	m_background = loadTexture(background, renderer);
	m_texBlocs = loadTexture("../sprites/SpritesBloc.bmp", renderer);
	
}
World::~World()
{
	SDL_DestroyTexture(m_background);
	SDL_DestroyTexture(m_texBlocs);
}
void World::affiche(SDL_Renderer* renderer)
{
	renderTexture(m_background, renderer, 0, 0);
}
