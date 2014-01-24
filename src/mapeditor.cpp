#include <iostream>

#include <SDL2/SDL.h>

#include "World.h"
#include "SDLFunc.h"
#include "defines.h"
#include "menu.h"

#include "mapeditor.h"



int main(int argc, char* argv[])
{
	lvl* world;

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
	Menu_newItem(&itemBack, setBack, "Modifier le fond");
	Menu_newItem(&itemEdit, edit, "Editer la map");
	Menu_newItem(&itemWrite, write, "Sauvegarder la map");

	Menu_addItem(&menu, &itemCreate);
	Menu_addItem(&menu, &itemLoad);
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
            if(!Menu_do(&menu, action, world))
            {
                printf("Erreur lors du lancement d'une action.\n");
            }
        }
    }

    return 0;
}


void create(lvl* world)
{
	std::string chemin
	cout << "Indiquez le chemin (relatif) du fichier.";
	cin >> chemin;
	world->background = chemin;
	world->h=0;
	world->w=0;
}
void load(lvl* world)
{
	std::string chemin
	cout << "Indiquez le chemin (relatif) du fichier.";
	cin >> chemin;

	char c;

	std::ifstream fic(chemin, std::ios::in);
	if(!fic)
		return;
	
	fic >> world->background >> world->w >> world->h;

	lvl.get(c);

	for(int i=0; i<world->w; i++)
	{
		std::vector <int> v;
		for(int j=0; j<world->h; j++)
		{
			int foo;
			lvl.get(c);
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
			v.push_back(foo);
		}
		world->blocs.push_back(v);
	}
		
			
}
void edit(lvl* world){}
void setSize(lvl* world){}
void setBack(lvl* world){}
void write(lvl* world){}
