/*    Copyright (C) 2014 LEBY-FALK Hugo

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
#ifndef H_MENU
#define H_MENU

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"

#include "mapeditor.h"

#define MAX_ITEM 10
#define MAX_LABEL_LONG 20

typedef void (*callback)(lvl *world);

typedef struct Item Item;
typedef struct Menu Menu;
struct Item
{
    Item* suivant;
    Menu* sousMenu;
    callback fonction;
    char label[MAX_LABEL_LONG];
};

struct Menu
{
    int nombreItem;
    Item* premier;
    char titre[100];
};

int Menu_newItem(Item* item, callback fonction, const char nom[]);
int Menu_newItemSubMenu(Item* item, Menu* subMenu, const char nom[]);

int Menu_new(Menu* menu, char titre[]);
int Menu_addItem(Menu* menu, Item* item);
int Menu_removeItemByLabel(Menu* menu, const char nom[]);
int Menu_removeItemById(Menu* menu, int id);
int Menu_do(Menu* menu, int action, lvl* world);
int Menu_choose(Menu* menu);

int Menu_setSubMenu(Item* item, Menu* subMenu);

long inputLong(void);
int lire(char *chaine, int longueur);


#endif
