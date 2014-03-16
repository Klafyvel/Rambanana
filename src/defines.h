#ifndef H_DEFINE
#define H_DEFINE

#define BLOC 26

#define TAILLE_X BLOC * 30
#define TAILLE_Y BLOC * 25

#define TAILLE_PERSO_X 26
#define TAILLE_PERSO_Y 38

#define AGRANDISSEMENT_PERSO 2

#define TAILLE_PERSO_AFFICHE_X AGRANDISSEMENT_PERSO * TAILLE_PERSO_X
#define TAILLE_PERSO_AFFICHE_Y AGRANDISSEMENT_PERSO * TAILLE_PERSO_Y

#define TAILLE_HITBOX_PERSO_X AGRANDISSEMENT_PERSO * 20
#define TAILLE_HITBOX_PERSO_Y TAILLE_PERSO_AFFICHE_Y


#define TEMPS_PERSO  200
#define TEMPS_PERSO_RUN 150

#define RANG_SAUT 4
#define RANG_COUR 2
#define RANG_IMMOBILE 0

#define IMAGES_PAR_MOUVEMENT 3

#define IMMOBILE 1
#define DROITE 2
#define GAUCHE 4
#define COUR 8
#define SAUTE 16
#define HAUT 32
#define BAS 64

#define PAS_DEPLACEMENT_X 5
#define PAS_DEPLACEMENT_Y 10

#define ENERGIE_SAUT 10000


#endif
