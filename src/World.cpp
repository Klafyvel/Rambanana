#include "World.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "SDLFunc.h"
#include "defines.h"

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

	lvl.get(c);

	for(int i=0; i<w; i++)
	{
		std::vector <SDL_Rect> v;
		for(int j=0; j<h; j++)
		{
			SDL_Rect rect;
			initRect(&rect);
			v.push_back(rect);
		}
		m_blocs.push_back(v);
	}

	for(int i=0; i<w; i++)
	{
		for(int j=0; j<h; j++)
		{
			lvl.get(c);
			int foo;				
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
					break;
			}
			if(c!='\n')
			{
				m_blocs[i][j].w = BLOC;
				m_blocs[i][j].h = BLOC;

				m_blocs[i][j].x = foo * BLOC;
				m_blocs[i][j].y = 0;
			}
		}
		
		while(c!='\n')
		{
			lvl.get(c);	
		}
	}	
	
	m_background = loadTexture(background, renderer);
	m_texBlocs = loadTextureAlpha("../sprites/SpritesBloc.bmp", renderer, 0, 38, 255);

	m_debutAffichage = 0;	
}
World::~World()
{
	SDL_DestroyTexture(m_background);
	SDL_DestroyTexture(m_texBlocs);
}
void World::affiche(SDL_Renderer* renderer)
{
	renderTexture(m_background, renderer, 0, 0, 520, 520);

	for(unsigned int i=0; i<m_blocs.size(); i++)
	{
		for(unsigned int j=0; j<m_blocs[i].size(); j++)
		{
			renderTexture(m_texBlocs, renderer, j * BLOC + m_debutAffichage, i * BLOC, &m_blocs[i][j]);
		}
	}
}
void World::scroll(int mvX)
{
	if(mvX)
		m_debutAffichage += 5;
	else
		m_debutAffichage -= 5;
}
int World::typeBloc(int x, int y)
{
	return (m_blocs[y/BLOC][(x-m_debutAffichage)/BLOC].x) / BLOC;
}
void World::upgradeBloc(int x, int y)
{
	if(this->typeBloc(x, y) == 6)
	{
		m_blocs[y/BLOC][(x-m_debutAffichage)/BLOC].x = 0;
	}
	else
	{
		m_blocs[y/BLOC][(x-m_debutAffichage)/BLOC].x += 26;
	}
}
void World::eraseBloc(int x, int y)
{
	m_blocs[y/BLOC][(x-m_debutAffichage)/BLOC].x = 0;
}
