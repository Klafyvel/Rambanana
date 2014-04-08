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
/*World::World(const World &world) 
{
    m_debutAffichage = world.m_debutAffichage;
    m_blocs = world.m_blocs;
    m_background = world.m_background;
    m_texBlocs = world.m_texBlocs;
}*/
    
World::World(std::string file,  sf::RenderWindow *window)
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

	World::parseJSON(lvl);

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

	m_window = window;

	m_initialized = true;
}
void World::draw(sf::RenderWindow &window)
{
	window.draw(m_background);
	for(unsigned int i=0; i<m_blocs.size(); i++)
	{
		for(unsigned int j=0; j<m_blocs[i].size(); j++)
		{
			window.draw(m_blocs[i][j].getSprite());
		}
	}
}

void World::scroll(int direction)
{
	sf::View view = m_window->getView();
	sf::Vector2f mv;
	if(direction & GAUCHE)
		mv = sf::Vector2f(-1.1 * PAS_DEPLACEMENT_X, 0);
	if(direction & DROITE)
		mv = sf::Vector2f(1.1 * PAS_DEPLACEMENT_X, 0);
	if(direction & HAUT)
		mv = sf::Vector2f(0, -1.1 *  PAS_DEPLACEMENT_Y);
	if(direction & BAS)
		mv = sf::Vector2f(0,1.1 * PAS_DEPLACEMENT_Y);
	view.move(mv.x, mv.y);
	m_window->setView(view);
	
	m_background.move(mv);
}
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
    for(unsigned int i=0; i<m_blocs.size(); i++)
    {
        for(unsigned int j=0; j<m_blocs[i].size(); j++)
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
sf::Vector2f World::getCharacterPos()
{
	return m_posInitPers;
}
void World::parseJSON(std::string json)
{
	cJSON * root = cJSON_Parse(json.c_str());
	if(!root)
	{
		std::cout << "[Parseur de JSON]Erreur : Impossible de transformer la chaîne reçu en cJSON." << std::endl << "Before [" << cJSON_GetErrorPtr() << "]" << std::endl;
		std::cout << cJSON_Print(root) << std::endl;
		return;
	}

	m_lvlName = cJSON_GetObjectItem(root, "name")->valuestring;
	m_cheminBackground = cJSON_GetObjectItem(root, "background")->valuestring;
	m_cheminTexBlocs = cJSON_GetObjectItem(root, "block_text")->valuestring;
	
	cJSON * h = cJSON_GetObjectItem(root, "blocks");
	for(int i=0; i<cJSON_GetArraySize(h); i++)
	{
		cJSON * w = cJSON_GetArrayItem(h, i);
		std::vector <Bloc> v;
		for(int j=0; j<cJSON_GetArraySize(w); j++)
		{
			Bloc bloc;
			sf::IntRect rect(cJSON_GetArrayItem(w, j)->valueint * BLOC, 0, BLOC, BLOC);
			bloc.setRect(rect);
			v.push_back(bloc);
		}
		m_blocs.push_back(v);
	}

	/*TODO:Add ennemys to the game ;)*/

	m_posInitPers = sf::Vector2f(cJSON_GetObjectItem(cJSON_GetObjectItem(root, "character"), "init_left")->valueint * BLOC,
								 cJSON_GetObjectItem(cJSON_GetObjectItem(root, "character"), "init_top")->valueint * BLOC);
}
