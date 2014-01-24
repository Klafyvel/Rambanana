/*    Copyright (C) 2013 LEVY-FALK Hugo

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/
#include "menu.h"

int Menu_new(Menu* menu, char titre[]) // Fonction pour initialiser le menu.
{
    menu->nombreItem = 0; // Il n'y a pas encore d'items...
    menu->premier = NULL; // Il n'y a pas non plus de premier item du coup :o)
    if(strlen(titre) <= 100) // Si le titre donné n'est pas trop grand...
    {
        strcpy(menu->titre, titre); // ... on l'afecte comme titre.
    }
    else // sinon on crée une erreur
    {
        return 0;
    }

	return 1;
}

int Menu_addItem(Menu* menu, Item* item) // Fonction pour ajouter un item à un menu.
{
    if(menu->nombreItem==0) // si c'est le premier item
    {
        menu->premier = item;
    }
    else
    {
        Item* buffer = NULL;
        buffer=menu->premier; // On fait pointer un buffer sur le premier élément de menu.
        if(buffer == NULL)
            return 0;
        while(buffer->suivant) // Tant qu'on est pas au dernier élément...
        {
            buffer = buffer->suivant; // ...on passe à l'item suivant.
        }
        buffer->suivant = item; // On affecte notre item comme dernier élément du menu.
    }
	menu->nombreItem ++; // On incrémente aussi le nombre d'items.

	return 1;
}

int Menu_removeItemByLabel(Menu* menu, const char nom[]) // Fonction pour enlever un item d'un menu à partir de son nom.
{
	Item* item = menu->premier; // Un buffer pour parcourir les items.
	while(strcmp(item->suivant->label, nom)) // On parcour les items.
	{
		item = item->suivant;
	}
	item->suivant = item->suivant->suivant; // On "recable" le tout !

	return 1;
}

int Menu_removeItemById(Menu* menu, int id) // Fonction pour détruire un item à partir de son id.
{
    if((id < 0)||(id >= menu->nombreItem)) // Si l'id ne correspond pas...
    {
        return 0; // ...On crée une erreur.
    }
    else // Sinon l'id correspond.
    {

        int i; // On crée un buffer.
	Item* item = menu->premier; // Et un deuxième buffer !
        for(i = 1; i<id; i++) // On va jusqu'à l'item qui précède celui que l'on souhaite retirer.
		{
			item = item->suivant;
		}
		item->suivant = item->suivant->suivant; // Et on "recâble" !
        menu->nombreItem --; // Enfin, on décrémente le nombre d'items
    }
	return 1;
}

void Menu_free(Menu* menu) // Fonction pour détruire tout les items du tableau.
{
    int buffer;
    for(buffer = 0; buffer < menu->nombreItem; buffer ++)
    {
        Menu_removeItemById(menu, buffer);
    }
}


int Menu_choose(Menu* menu) // Fonction pour choisir une id
{
    long choix = 0; // Le choix de l'utilisateur
    while((choix <= 0) || (choix > menu->nombreItem+1))
    {
		clrscr();
        int buffer; // un buffer
		Item* item = menu->premier; // le premier item de la liste
        printf("-------- %s --------\n", menu->titre); // On affiche le titre.
        for(buffer = 0; buffer < menu->nombreItem; buffer++)
        {
            printf("%d- %s\n", buffer+1, item->label); // On affiche les différents choix.
	    item = item->suivant;
        }
        printf("%d- Quitter\n", menu->nombreItem + 1);
        choix = inputLong(); // On récupère l'entrée utilisateur.
    }
	clrscr();
    if(choix==(menu->nombreItem + 1)) // si on choisis de quitter le programme
    {
        return -1;
    }
    else
    {
        return (int)(choix - 1);
    }
}

int lire(char *chaine, int longueur) //extrait du cour sur le C
{
    char *positionEntree = NULL;

    // On lit le texte saisi au clavier
    if (fgets(chaine, longueur, stdin) != NULL)  // Pas d'erreur de saisie ?
    {
        positionEntree = strchr(chaine, '\n'); // On recherche l'"Entrée"
        if (positionEntree != NULL) // Si on a trouvé le retour à la ligne
        {
            *positionEntree = '\0'; // On remplace ce caractère par \0
        }
        return 1; // On renvoie 1 si la fonction s'est déroulée sans erreur
    }
    else
    {
        return 0; // On renvoie 0 s'il y a eu une erreur
    }
}

long inputLong() //extrait du cour sur le C
{
    char nombreTexte[100] = {0}; // 100 cases devraient suffire

    if (lire(nombreTexte, 100))
    {
        // Si lecture du texte ok, convertir le nombre en long et le retourner
        return strtol(nombreTexte, NULL, 10);
    }
    else
    {
        // Si problème de lecture, renvoyer 0
        return 0;
    }
}

int Menu_do(Menu* menu, int action, lvl* world)
{
    if((action<0)||(action >= menu->nombreItem))
    {
        return 0;
    }
    else
    {
    callback fonction;
	int i;
	Item* item = menu->premier;
	for(i=0; i<action; i++)
	{
	    item = item->suivant;
	}
	if(item->fonction)
	{
        fonction = item->fonction;
        fonction(world);
    }
    else if(item->sousMenu)
    {
        Menu_do(item->sousMenu, Menu_choose(item->sousMenu), world);
    }
    }
    return 1;
}

int Menu_newItem(Item* item, callback fonction, const char nom[])
{
    item->fonction = fonction;
    strcpy(item->label, nom);
    item->suivant=NULL;
    item->sousMenu=NULL;

    return 1;
}
int Menu_newItemSubMenu(Item* item, Menu* subMenu, const char nom[])
{
    item->fonction = NULL;
    item->sousMenu = subMenu;
    strcpy(item->label, nom);
    item->suivant = NULL;
    return 1;
}


