#include "personnage.h"

Personnage::Personnage(int x, int y, int hitboxHeight, int hitboxWidth, std::string sprites, SDL_Renderer *render, World* world)
{
	m_pointsDeVie = 100;

	m_hitbox.x = x + (TAILLE_PERSO_AFFICHE_X - hitboxWidth)/2;
	m_hitbox.y = y + (TAILLE_PERSO_AFFICHE_Y - hitboxHeight)/2;
	m_hitbox.h = hitboxHeight;
	m_hitbox.w = hitboxWidth;

	m_sprites = loadTextureAlpha(sprites, render, 0, 38, 255);


	m_state.saute=false;
	m_state.cour=false;
	m_state.vaAGauche=false;
	
    m_rectAffichage.x = x;
	m_rectAffichage.y = y;

	m_rectAffichage.w = TAILLE_PERSO_AFFICHE_X;
	m_rectAffichage.h = TAILLE_PERSO_AFFICHE_Y;

	m_coupe.x = 0;
	m_coupe.y = 0;
	m_coupe.w = TAILLE_PERSO_X;
	m_coupe.h = TAILLE_PERSO_Y;

	m_valAffichage = 0;

	m_timerAffichage = SDL_GetTicks();

    m_tempsPerso = 200;

    m_world = world;

    m_energieSaut = ENERGIE_SAUT;

}
 
void Personnage::affiche(SDL_Renderer* render)
{
    if(m_state.saute)
	    m_coupe.y = RANG_SAUT * TAILLE_PERSO_Y;
    else if(m_state.cour)
        m_coupe.y = RANG_COUR * TAILLE_PERSO_Y;
    else
        m_coupe.y = RANG_IMMOBILE * TAILLE_PERSO_Y;

	if(SDL_GetTicks() - m_timerAffichage >= m_tempsPerso)
	{
		m_timerAffichage = SDL_GetTicks();
		m_valAffichage ++;
		if(m_valAffichage > IMAGES_PAR_MOUVEMENT - 1)
			m_valAffichage = 0;
	}
    if(m_state.vaAGauche)
        m_coupe.y += TAILLE_PERSO_Y;
	m_coupe.x = m_valAffichage * TAILLE_PERSO_X;


	renderTexture(m_sprites, render, m_rectAffichage, &m_coupe); 
}
void Personnage::move(int direction)
{

    if(direction & IMMOBILE)
    {
        m_state.cour=false;
        m_state.saute=false;
    }
    if(direction & DROITE)
        m_state.vaAGauche=false;
    if(direction & GAUCHE)
        m_state.vaAGauche=true;
    if(direction & COUR)
    {
        m_state.cour=true;
        m_state.saute=false;
    }
    if(direction & SAUTE)
    {
        m_state.cour=false;
        m_state.saute=true;
    }
    if((direction & HAUT)&&(m_energieSaut > 0))
    {
        m_hitbox.y -= PAS_DEPLACEMENT_Y;
        m_energieSaut --;
    }
    if(direction & BAS)
            m_hitbox.y += PAS_DEPLACEMENT_Y;

    if(m_state.cour || m_state.saute)
    {
        m_tempsPerso=100;
        if((m_state.cour && m_state.vaAGauche) && !Personnage::collision(GAUCHE))
            m_hitbox.x -= PAS_DEPLACEMENT_X;
        if((m_state.cour && !m_state.vaAGauche) && !Personnage::collision(DROITE))
            m_hitbox.x += PAS_DEPLACEMENT_X;
        if(m_state.saute && m_state.vaAGauche)
            Personnage::move(HAUT | GAUCHE | COUR);
        if(m_state.saute && !m_state.vaAGauche)
            Personnage::move(HAUT | DROITE | COUR);
    }
    else
        m_tempsPerso=200;

    m_rectAffichage.x = m_hitbox.x - ((TAILLE_PERSO_AFFICHE_X - m_hitbox.w)/2);
    m_rectAffichage.y = m_hitbox.y - ((TAILLE_PERSO_AFFICHE_Y - m_hitbox.h)/2);  
}
int Personnage::collision(int direction)
{
    if((direction & GAUCHE) && ((m_world->typeBloc(m_rectAffichage.x - PAS_DEPLACEMENT_X, m_rectAffichage.y))||m_world->typeBloc(m_rectAffichage.x - PAS_DEPLACEMENT_X, m_rectAffichage.y + m_rectAffichage.h - 1)))
        return 1;
    if((direction & DROITE) && m_world->typeBloc(m_rectAffichage.x + m_rectAffichage.w + PAS_DEPLACEMENT_X, m_rectAffichage.y))
        return 1;
    if((direction & HAUT) && m_world->typeBloc(m_rectAffichage.x, m_rectAffichage.y - PAS_DEPLACEMENT_Y))
        return 1;
    if((direction & BAS) && m_world->typeBloc(m_rectAffichage.x, m_rectAffichage.y + m_rectAffichage.h +PAS_DEPLACEMENT_Y - 1))
        return 1;
    return 0;
}
void Personnage::gravite(int direction)
{
    if(!Personnage::collision(direction))
        Personnage::move(direction);
}

