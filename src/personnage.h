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

#include "defines.h"

/* Contient la classe générique pour créer un personnage */
class Personnage
{
public:
	Personnage(int x, int y, int hitboxHeight, int hitboxWidth, char sprites[]);
	void affiche(SDL_Renderer* render);
	void avance(int direction); // voir description m_state 

private:
	int m_pointsDeVie;
	
	SDL_Texture m_sprites;
	
	int m_state; /* Varie entre 0 et 7:
	
	saute | cour | vaADroite || state
		0		|		0	 |		0			 || 0
		0		|		0	 |		1			 || 1
		0		|		1	 |		0			 || 2
		0		|		1	 |		1			 || 3
		1		|		0	 |		0			 || 4
		1		|		0	 |		1			 || 5
		1		|		1	 |		0			 || 6
		1		|		1	 |		1			 || 7
*/		
	
	SDL_Rect m_hitbox;

};

#endif
