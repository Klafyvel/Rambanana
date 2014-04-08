#include "personnage.h"
#include "World.h"

Personnage::Personnage(sf::Vector2f position, int hitboxWidth, int hitboxHeight, std::string sprites, World *world)
{
	m_autoScroll = false;

    m_world = world;
    m_life = 100;

	m_hitbox.left = position.x + (TAILLE_PERSO_AFFICHE_X - hitboxWidth)/2;
	m_hitbox.top = position.y + (TAILLE_PERSO_AFFICHE_Y - hitboxHeight)/2;
	m_hitbox.height = hitboxHeight;
	m_hitbox.width = hitboxWidth;

    sf::Image imageTexSprites;
    if (!imageTexSprites.loadFromFile(sprites))
	    return;
    imageTexSprites.createMaskFromColor(sf::Color(0,38,255));

    m_texSprites.loadFromImage(imageTexSprites);

    m_sprite.setTexture(m_texSprites);
	m_sprite.setScale(AGRANDISSEMENT_PERSO, AGRANDISSEMENT_PERSO);
	m_sprite.setOrigin(sf::Vector2f(0,0));

	m_state.jump=false;
	m_state.run=false;
	m_state.left=false;


	m_coupe.left = 0;
	m_coupe.top = 0;
	m_coupe.width = TAILLE_PERSO_X;
	m_coupe.height = TAILLE_PERSO_Y;

	m_valAffichage = 0;

	m_timerAffichage.restart();

    m_tempsPerso = TEMPS_PERSO;

    m_energieSaut = ENERGIE_SAUT;

	m_buffJump.v_y = 0;
	m_buffJump.v_saut = -PAS_DEPLACEMENT_Y;
	m_buffJump.v_gravitation = 0.2;

}
void Personnage::draw(sf::RenderWindow &window)
{
    if(m_state.jump)
	    m_coupe.top = RANG_SAUT * TAILLE_PERSO_Y;
    else if(m_state.run)
        m_coupe.top = RANG_COUR * TAILLE_PERSO_Y;
    else
        m_coupe.top = RANG_IMMOBILE * TAILLE_PERSO_Y;

	if((m_timerAffichage.getElapsedTime() >= sf::milliseconds(m_tempsPerso)) && !m_state.jump)
	{
		m_timerAffichage.restart();
		m_valAffichage ++;
		if(m_valAffichage > IMAGES_PAR_MOUVEMENT - 1)
			m_valAffichage = 0;
	}
	else if(m_state.jump && m_buffJump.v_y <=0)
		m_valAffichage = 0;
	else if(m_state.jump && m_buffJump.v_y > 0)
		m_valAffichage = 1;
    if(m_state.left)
        m_coupe.top += TAILLE_PERSO_Y;
	m_coupe.left = m_valAffichage * TAILLE_PERSO_X;
    m_sprite.setTextureRect(m_coupe);
    window.draw(m_sprite);
	if(m_autoScroll)
	{
		sf::Vector2i pos1 = window.mapCoordsToPixel(sf::Vector2f(m_hitbox.left, m_hitbox.top));
		sf::Vector2i pos2 = window.mapCoordsToPixel(sf::Vector2f(m_hitbox.left + m_hitbox.width, m_hitbox.top + m_hitbox.height));
		if(pos1.x<(window.getSize().x - SCROLL_BOX_W)/2)
			m_world->scroll(GAUCHE);
		else if(pos2.x >(window.getSize().x + SCROLL_BOX_W)/2)
			m_world->scroll(DROITE);
		if(pos1.y <(window.getSize().y - SCROLL_BOX_H)/2)
			m_world->scroll(HAUT);
		else if(pos2.y > (window.getSize().y + SCROLL_BOX_H)/2)
			m_world->scroll(BAS);
	}
}
void Personnage::move(int direction)
{
    if(direction & IMMOBILE)
    {
        m_state.run=false;
		if(Personnage::collision(BAS))
			m_state.jump=false;
    }
    if(direction & DROITE)
        m_state.left=false;
    if(direction & GAUCHE)
        m_state.left=true;
    if(direction & COUR)
    {
        m_state.run=true;
    }
	else
	{
		m_state.run=false;
	}
    if(direction & SAUTE)
    {
        m_state.jump=true;
    }
    if((direction & HAUT)&&(m_energieSaut > 0))
    {
        m_hitbox.top -= PAS_DEPLACEMENT_Y;
        m_energieSaut --;
    }
    if(direction & BAS)
            m_hitbox.top += PAS_DEPLACEMENT_Y;

    if(m_state.run || m_state.jump)
    {
        m_tempsPerso=TEMPS_PERSO_RUN;
        if((m_state.run && m_state.left) && !Personnage::collision(GAUCHE))
            m_hitbox.left -= PAS_DEPLACEMENT_X;
        if((m_state.run && !m_state.left) && !Personnage::collision(DROITE))
            m_hitbox.left += PAS_DEPLACEMENT_X;
        if(m_state.jump && ((m_buffJump.v_y <= 0 && !Personnage::collision(HAUT))||(m_buffJump.v_y > 0 && !Personnage::collision(BAS))))
        {
			if(m_buffJump.v_y == 0)
			{
				m_buffJump.v_y = m_buffJump.v_saut;
			}

			m_buffJump.v_y += m_buffJump.v_gravitation;
			m_hitbox.top += m_buffJump.v_y;
		}
		else if(m_buffJump.v_y <= 0 && Personnage::collision(HAUT))
		{
			m_buffJump.v_y *= -1;
			m_hitbox.top += m_buffJump.v_y;
		}
    }
    else
        m_tempsPerso=TEMPS_PERSO;

    m_sprite.setPosition(sf::Vector2f(m_hitbox.left - ((TAILLE_PERSO_AFFICHE_X - m_hitbox.width)/2), m_hitbox.top - ((TAILLE_PERSO_AFFICHE_Y - m_hitbox.height)/2)));

}
int Personnage::collision(int direction)
{
	bool collision = false;
	int borneH = 0;
	if(m_state.jump)
		borneH = m_hitbox.height - m_buffJump.v_y;
	else
		borneH = m_hitbox.height - PAS_DEPLACEMENT_Y;
    if(direction & GAUCHE)
	{
		for(int i = 0; i<borneH; i++)
		{
			if(m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top + i)))
				collision = true;
		}
	}
    if(direction & DROITE)
	{
		for(int i=0; i<borneH; i++)
		{
			if(m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width, m_hitbox.top + i)))
				collision = true;
		}
	}
    if(direction & HAUT)
	{
		if (((m_world->typeBloc(sf::Vector2f(m_hitbox.left + PAS_DEPLACEMENT_X, m_hitbox.top)))|| m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width - PAS_DEPLACEMENT_X - 1, m_hitbox.top))))
		{
			collision = true;
			/*m_buffJump.v_y = 0;
			m_state.jump = false;*/
		}
	}
    if((direction & BAS))
	{
		if (((m_world->typeBloc(sf::Vector2f(m_hitbox.left + PAS_DEPLACEMENT_X, m_hitbox.top + m_hitbox.height)))|| m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width - PAS_DEPLACEMENT_X, m_hitbox.top + m_hitbox.height))))
		{
			collision = true;
			m_buffJump.v_y = 0;
			m_state.jump = false;
		}
	}
    if(collision)
		return 1;
	return 0;
}
void Personnage::gravity(int direction)
{
    if(!Personnage::collision(BAS) && !m_state.jump)
    {
        m_buffJump.v_y=m_buffJump.v_gravitation;
        m_state.jump=true;
    }
}
void Personnage::corrigeCollision()
{
    if(!(m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top)) || m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width, m_hitbox.top)) || m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top + m_hitbox.height -1)) || m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width, m_hitbox.top + m_hitbox.height -1))))
            return;

/*
    if((direction & GAUCHE) && ((m_world->typeBloc(m_rectAffichage.x - PAS_DEPLACEMENT_X, m_rectAffichage.y))||m_world->typeBloc(m_rectAffichage.x - PAS_DEPLACEMENT_X, m_rectAffichage.y + m_rectAffichage.h - 1)))
        return 1;
    if((direction & DROITE) && m_world->typeBloc(m_rectAffichage.x + m_rectAffichage.w + PAS_DEPLACEMENT_X, m_rectAffichage.y))
        return 1;
    if((direction & HAUT) && m_world->typeBloc(m_rectAffichage.x, m_rectAffichage.y - PAS_DEPLACEMENT_Y))
        return 1;
    if((direction & BAS) && m_world->typeBloc(m_rectAffichage.x, m_rectAffichage.y + m_rectAffichage.h +PAS_DEPLACEMENT_Y - 1))
        return 1;
    return 0;
*/}//to be modified
void Personnage::setAutoScroll(bool state)
{
	m_autoScroll = state;
}
