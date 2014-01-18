#include "personnage.h"

Personnage::Personnage(int x, int y, int hitboxHeight, int hitboxWidth, char sprites[], SDL_Renderer* render)
{
	m_pointsDeVie = 100;

	m_hitbox.x = x
	m_hitbox.y = y
	m_hitbox.h = hitboxHeight;
	m_hitbox.w = hitboxWidth;

	m_sprites = loadTexture(&sprites, renderer);

	m_state = 1;
}


