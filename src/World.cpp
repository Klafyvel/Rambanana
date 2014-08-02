#include "World.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
World::World()
{
    m_initialized = false;
}

World::World(std::string file,  sf::RenderWindow *window)
{
    World::create(file, window);
}
void World::create(std::string file, sf::RenderWindow *window)
{
    m_initialized = false;

    m_lvlPath = file;

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
void World::draw()
{
    m_window->draw(m_background);
    for(unsigned int i=0; i<m_blocs.size(); i++)
    {
		for(unsigned int j=0; j<m_blocs[i].size(); j++)
		{
			m_window->draw(m_blocs[i][j].getSprite());
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
bool World::isInMap(sf::Vector2f pos)
{
    return pos.x/BLOC >= 0 && pos.x/BLOC < m_blocs[pos.y/BLOC].size() && pos.y/BLOC >= 0 && pos.y/BLOC < m_blocs.size();
}
int World::typeBloc(sf::Vector2f pos)
{
    if(World::isInMap(pos))
	    return (m_blocs[pos.y/BLOC][(pos.x-m_debutAffichage)/BLOC].getRect().left) / BLOC;
    else
        return 0;
}

void World::upgradeBloc(sf::Vector2f pos)
{
    if(World::typeBloc(pos) == NB_BLOC)
        World::eraseBloc(pos);
	else
    {
        sf::IntRect rect = m_blocs[pos.y/BLOC][pos.x/BLOC].getRect();
        rect.left += BLOC;
		m_blocs[pos.y/BLOC][pos.x/BLOC].setRect(rect);
    }
}
void World::eraseBloc(sf::Vector2f pos)
{
    sf::IntRect rect = m_blocs[pos.y/BLOC][pos.x/BLOC].getRect();
    rect.left = 0;
    m_blocs[pos.y/BLOC][pos.x/BLOC].setRect(rect);
}

std::string World::getJSONMap()
{
    cJSON* root;
	cJSON* pers;
    root = cJSON_CreateObject();
	pers = cJSON_CreateObject();

	cJSON_AddItemToObject(root, "name", cJSON_CreateString(m_lvlName.c_str()));

    cJSON_AddItemToObject(root, "background", cJSON_CreateString(m_cheminBackground.c_str()));
    cJSON_AddItemToObject(root, "block_text", cJSON_CreateString(m_cheminTexBlocs.c_str()));

	cJSON_AddItemToObject(pers, "init_left", cJSON_CreateNumber(m_posInitPers.x));
	cJSON_AddItemToObject(pers, "init_top", cJSON_CreateNumber(m_posInitPers.y));
	cJSON_AddItemToObject(root, "character", pers);

	
	cJSON* map;
	map = cJSON_CreateArray();
	for(unsigned int i=0; i<m_blocs.size(); i++)
	{
		cJSON* foo;
		cJSON_AddItemToArray(map, foo=cJSON_CreateArray());
		for(unsigned int j=0; j<m_blocs[i].size(); j++)
		{
			cJSON_AddItemToArray(foo, cJSON_CreateNumber(m_blocs[i][j].getRect().left / BLOC));
		}
	}
	cJSON_AddItemToObject(root, "blocks", map);
	
    /* TODO: finish the register */
	char* out_str;
	out_str = cJSON_Print(root);
	std::string returned = out_str;
	free(out_str);
	return returned;
}
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

std::string World::getAFileName(sf::RenderWindow &window)
{
	std::string returned;

    window.create(sf::VideoMode::getDesktopMode(), "Rambanana !" );
	window.setFramerateLimit(30);

    sf::View view(sf::FloatRect(0, 0, TAILLE_X, TAILLE_Y));

    window.setView(view);

	Menu menu("Sélectionnez un fichier");

	DIR* dir = nullptr;
	dir = opendir("../lvl");
	if(dir == nullptr)
		perror("");
	else
	{
		std::vector <std::string> files;
		struct dirent* file = nullptr;


		while((file=readdir(dir)) != nullptr)
		{
				menu.addItem(nullptr, file->d_name);
				files.push_back(file->d_name);
				std::cout << file->d_name << std::endl;
		}
		closedir(dir);
		int choose = menu.chooseAnActionNumber(window);
		if(choose > 0)
			returned = files[choose];
	}
	return "../lvl/" + returned;
}
void World::setBlocType(sf::Vector2f pos, int type)
{
	if(type <= NB_BLOC)
	{
		sf::IntRect rect = m_blocs[pos.y/BLOC][pos.x/BLOC].getRect();
		rect.left = type * BLOC;
		m_blocs[pos.y/BLOC][pos.x/BLOC].setRect(rect);
	}
}
std::string World::getFileName()
{
    return m_lvlPath;
}
void World::setCharPos(sf::Vector2f pos)
{
    m_posInitPers.x = (int)(pos.x / BLOC);
    m_posInitPers.y = (int)(pos.y / BLOC);
}
