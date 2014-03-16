#include "personnage.h"
#include "World.h"

Personnage::Personnage(sf::Vector2f position, int hitboxWidth, int hitboxHeight, std::string sprites, World *world)
{
	
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
	m_timerMove.restart();

    m_tempsPerso = TEMPS_PERSO;

    m_energieSaut = ENERGIE_SAUT;

}
void Personnage::draw(sf::RenderWindow &window)
{ 
    if(m_state.jump)
	    m_coupe.top = RANG_SAUT * TAILLE_PERSO_Y;
    else if(m_state.run)
        m_coupe.top = RANG_COUR * TAILLE_PERSO_Y;
    else
        m_coupe.top = RANG_IMMOBILE * TAILLE_PERSO_Y;

	if(m_timerAffichage.getElapsedTime() >= sf::milliseconds(m_tempsPerso))
	{
		m_timerAffichage.restart();
		m_valAffichage ++;
		if(m_valAffichage > IMAGES_PAR_MOUVEMENT - 1)
			m_valAffichage = 0;
	}
    if(m_state.left)
        m_coupe.top += TAILLE_PERSO_Y;
	m_coupe.left = m_valAffichage * TAILLE_PERSO_X;
    m_sprite.setTextureRect(m_coupe);
    window.draw(m_sprite);
}
void Personnage::move(int direction)
{
    if(direction & IMMOBILE)
    {
        m_state.run=false;
        m_state.jump=false;
    }
    if(direction & DROITE)
        m_state.left=false;
    if(direction & GAUCHE)
        m_state.left=true;
    if(direction & COUR)
    {
        m_state.run=true;
        m_state.jump=false;
    }
    if(direction & SAUTE)
    {
        m_state.run=false;
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
        if(m_state.jump && m_state.left)
            Personnage::move(HAUT | GAUCHE | COUR);
        if(m_state.jump && !m_state.left)
            Personnage::move(HAUT | DROITE | COUR);
    }
    else
        m_tempsPerso=TEMPS_PERSO;

    m_sprite.setPosition(sf::Vector2f(m_hitbox.left - ((TAILLE_PERSO_AFFICHE_X - m_hitbox.width)/2), m_hitbox.top - ((TAILLE_PERSO_AFFICHE_Y - m_hitbox.height)/2)));
/*
	std::cout << "Personnage: " << std::endl;
	std::cout << "\t m_sprite.left = " << m_sprite.getPosition().x << std::endl;
	std::cout << "\t m_sprite.top = " << m_sprite.getPosition().y << std::endl;
	std::cout << "\t m_hitbox.left = " << m_hitbox.left << std::endl;
	std::cout << "\t m_hitbox.top = " << m_hitbox.top << std::endl;
*/
}
int Personnage::collision(int direction)
{
	bool collision = false;
    if((direction & GAUCHE) && ((m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top)))||m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top + m_hitbox.height -1))))
		collision = true;
    if((direction & DROITE) && ((m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width, m_hitbox.top))) || m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width , m_hitbox.top + m_hitbox.height - 1))))
		collision = true;
    if((direction & HAUT) && m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top)))
		collision = true;
    if((direction & BAS) && (m_world->typeBloc(sf::Vector2f(m_hitbox.left, m_hitbox.top + m_hitbox.height + PAS_DEPLACEMENT_Y - 1)) || m_world->typeBloc(sf::Vector2f(m_hitbox.left + m_hitbox.width, m_hitbox.top + m_hitbox.height + PAS_DEPLACEMENT_Y -1))))
		collision = true;
    if(collision)
		return 1;
	return 0;
}
void Personnage::gravity(int direction)
{
    if(!Personnage::collision(direction))
        Personnage::move(direction);
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

