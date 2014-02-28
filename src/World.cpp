#include "World.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "personnage.h"
#include "defines.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


Bloc::Bloc()
{
    m_rect = sf::IntRect(0,0,0,0);
    m_sprite = sf::Sprite();
}
void Bloc::setRect(sf::IntRect rect)
{
    m_rect = rect;
}
void Bloc::setSprite(sf::Sprite sprite)
{
    std::cout << "Définition de sprite" << std::endl;
    m_sprite = sprite;
}
sf::IntRect &Bloc::getRect()
{
    return m_rect;
}
sf::Sprite &Bloc::getSprite()
{
    return m_sprite;
}
World::World(const World &world) 
{
    m_debutAffichage = world.m_debutAffichage;
    m_blocs = world.m_blocs;
    m_background = world.m_background;
    m_texBlocs = world.m_texBlocs;
}
    
World::World(std::string file)
{
	std::ifstream lvl(file.c_str(), std::ios::in);
	if(!lvl)
	{
		std::cout << "Impossible de charger le fichier niveau" << std::endl;
		return;
	}
	char c;

	std::string background;
	int w, h;
	lvl >> background >> w >> h;

    sf::Image imageBack;
    sf::Image imageBloc;
	if(!imageBack.loadFromFile(background))
    {
        std::cerr << "Image non chargée. (" << background << ")"<<std::endl;
        return;
    }
    if(!imageBloc.loadFromFile("../sprites/SpritesBloc.bmp"))
    {
        std::cerr << "Image non chargée. (" << "../sprites/SpritesBloc.bmp" << ")" <<std::endl;
        return;
    }
    imageBloc.createMaskFromColor(sf::Color(0,38,255));
    m_background.loadFromImage(imageBack);
    m_texBlocs.loadFromImage(imageBloc);

	lvl.get(c);

	for(int i=0; i<h; i++)
	{
		std::vector <Bloc> v;
		for(int j=0; j<w; j++)
		{
			Bloc bloc;
			v.push_back(bloc);
		}
		m_blocs.push_back(v);
	}

	for(int i=0; i<h; i++)
	{
		for(int j=0; j<w; j++)
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
                sf::IntRect rect(foo * BLOC, 0, BLOC, BLOC);
				m_blocs[i][j].setRect(rect);
			}
		}
		
		while(c!='\n')
		{
			lvl.get(c);
		}
	}	
	
    World::updateBloc();

	m_debutAffichage = 0;	
}
void World::draw(sf::RenderWindow &window)
{
	for(int i=0; i<m_blocs.size(); i++)
	{
		for(int j=0; j<m_blocs[i].size(); j++)
		{
			window.draw(m_blocs[i][j].getSprite());
		}
	}
}
/*
void World::scroll(int mvX)
{
	if((mvX & GAUCHE)&&(m_debutAffichage <=-5))
		m_debutAffichage += 5;
	if(mvX & DROITE)
		m_debutAffichage -= 5;
}*/
int World::typeBloc(sf::Vector2f pos)
{
	return (m_blocs[pos.y/BLOC][(pos.x-m_debutAffichage)/BLOC].getRect().left) / BLOC;
}
/*
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
void World::getMap(std::vector <std::vector <int>> *receiver)
{
	receiver->resize(m_blocs.size());
	for(int i=0; i<receiver->size(); i++)
		(*receiver)[i].resize(m_blocs[i].size());
	for(int i=0; i<m_blocs.size(); i++)
	{
		for(int j=0; j<m_blocs[i].size(); j++)
		{
			(*receiver)[i][j] = m_blocs[i][j].x / BLOC;
		}
	}
}*/
void World::updateBloc()
{
    for(int i=0; i<m_blocs.size(); i++)
    {
        for(int j=0; j<m_blocs[i].size(); j++)
        {
            sf::Sprite sprite;
            sprite.setPosition(sf::Vector2f(j*BLOC,i*BLOC));
            sprite.setTexture(m_texBlocs);
            sprite.setTextureRect(m_blocs[i][j].getRect());
            m_blocs[i][j].setSprite(sprite);
        }
    }
}

