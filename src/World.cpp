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
	m_initialized = false;

	std::ifstream ficLvl(file.c_str(), std::ios::in);
	if(!ficLvl)
	{
		std::cout << "Impossible de charger le fichier niveau" << std::endl;
		return;
	}
	std::string lvl;
	while(!ficLvl.eof())
	{
		char c;
		ficLvl.get(c);
		lvl+=c;
	}

	JSONNode n = libjson::parse(lvl);

	World::parseJSON(n);

    sf::Image imageBack;
    sf::Image imageBloc;
	if(!imageBack.loadFromFile(m_cheminBackground))
    {
        std::cerr << "Image non chargée. (" << m_cheminBackground << ")"<<std::endl;
        return;
    }
    if(!imageBloc.loadFromFile(m_cheminTexBlocs))
    {
        std::cerr << "Image non chargée. (" << m_cheminTexBlocs << ")" <<std::endl;
        return;
    }
    imageBloc.createMaskFromColor(sf::Color(0,38,255));
    m_texBackground.loadFromImage(imageBack);
    m_texBlocs.loadFromImage(imageBloc);

	m_background.setPosition(sf::Vector2f(0,0));
	m_background.setTexture(m_texBackground);

    World::updateBloc();

	m_debutAffichage = 0;
	m_initialized = true;
}
void World::draw(sf::RenderWindow &window)
{
	window.draw(m_background);
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
bool World::initialized()
{
	return m_initialized;
}
sf::Vector2f World::getCaracterPos()
{
	return m_posInitPers;
}
void World::parseJSON(const JSONNode & n)
{
    JSONNode::const_iterator i = n.begin();
	while (i != n.end()){
		std::string node_name = i->name();
		if(node_name == "name")
			m_lvlName = i->as_string();
		if(node_name == "background")
			m_cheminBackground = i->as_string();
		if(node_name == "block_text")
			m_cheminTexBlocs = i->as_string();
		if(node_name == "blocks") {
			for(int foo=0; foo<m_blocs.size(); foo++)
			{
				m_blocs.pop_back();
			}
			JSONNode arrayH = i->as_array();
			JSONNode::const_iterator j = arrayH.begin();
			while(j != arrayH.end())
			{
				std::vector <Bloc> v;
				JSONNode arrayW = j->as_array();
				JSONNode::const_iterator k = arrayW.begin();
				while(k != arrayW.end())
				{
					Bloc bloc;
					sf::IntRect rect(/*k->as_int() **/ BLOC, 0, BLOC, BLOC);
					bloc.setRect(rect);
					v.push_back(bloc);
					k++;
				}
				m_blocs.push_back(v);
				j++;
			}
		}
		if(node_name == "ennemys")
			//TODO: add ennemys to the game ;P
		if(node_name == "character") {
			JSONNode character = i->as_node();
			JSONNode::const_iterator j = character.begin();
			int x=0;
			int y=0;
			while(j!=character.end())
			{
				if(j->name()=="init_left")
					x = 30/*j->as_int()*/;
				if(j->name()=="init_top")
					y = 30/*j->as_int()*/;
				j++;
			}
			m_posInitPers = sf::Vector2f(x,y);
		}
		i++;
	}
}
