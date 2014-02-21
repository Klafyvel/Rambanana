/*    Copyright (C) 2014 LEVY-FALK Hugo

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#ifndef H_PERSONNAGE
#define H_PERSONNAGE

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <ctime>

#include "defines.h"
#include "World.h" 
#include "SDLFunc.h"
class World;
// Contient la classe générique pour créer un personnage 
class Personnage
{
public:
	Personnage(int x, int y, int hitboxHeight, int hitboxWidth, std::string sprites, SDL_Renderer *render, World* world);
	void affiche(SDL_Renderer* render);
	void move(int direction); // voir description m_state
    int collision(int direction);
    void gravite(int direction);
private:
	int m_pointsDeVie;
	
	SDL_Texture* m_sprites; 
	struct s_state{
        bool saute;
        bool cour;
        bool vaAGauche;
    }m_state;
 	
	SDL_Rect m_hitbox;

	SDL_Rect m_rectAffichage;

	SDL_Rect m_coupe;

    int m_tempsPerso;

	int m_valAffichage; // Numero du sprite à afficher (0~2)
	Uint32 m_timerAffichage;

    World* m_world;

    int m_energieSaut;
};

#endif

