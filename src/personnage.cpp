#include "personnage.h"

Personnage::Personnage(int x, int y, int hitboxHeight, int hitboxWidth, std::string sprites, SDL_Renderer *render)
{
	m_pointsDeVie = 100;

	m_hitbox.x = x;
	m_hitbox.y = y;
	m_hitbox.h = hitboxHeight;
	m_hitbox.w = hitboxWidth;

	m_sprites = loadTextureAlpha(sprites, render, 0, 38, 255);

	m_state = 0;

	m_rectAffichage.x = x - TAILLE_PERSO_X/2 + hitboxWidth/2;
	m_rectAffichage.y = y - TAILLE_PERSO_Y/2 + hitboxHeight/2;

	m_rectAffichage.w = (int)(TAILLE_PERSO_X * 2);
	m_rectAffichage.h = (int)(TAILLE_PERSO_Y * 2);

	m_coupe.x = 0;
	m_coupe.y = 0;
	m_coupe.w = TAILLE_PERSO_X;
	m_coupe.h = TAILLE_PERSO_Y;

	m_valAffichage = 0;

	m_timerAffichage = SDL_GetTicks();

}

void Personnage::affiche(SDL_Renderer* render)
{
	m_coupe.y = m_state * TAILLE_PERSO_Y;
	m_coupe.x = m_valAffichage * TAILLE_PERSO_X;

	if(SDL_GetTicks() - m_timerAffichage >= TEMPS_PERSO)
	{
		m_timerAffichage = SDL_GetTicks();
		m_valAffichage ++;
		if(m_valAffichage > 2)
			m_valAffichage = 0;
	}
	renderTexture(m_sprites, render, m_rectAffichage, &m_coupe); 
}
