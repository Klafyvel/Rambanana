Rambanana
=========

Description
-----------
Rambanana est un jeu de plateforme où vous incarnez une banane !

Téléchargement et compilation
-----------------------------

*Attention !*  Le chemin vers la SFML spécifié dans le Makefile correspond à une installation de SFML non standard (voir [l'option 2](http://sfml-dev.org/tutorials/2.1/start-linux-fr.php#installer-sfml) du tutoriel officiel). Il faudra donc adapter les variables `LIB` et `INCLUDE` du Makefile.

cJSON est fourni avec Rambanana.

Ensuite il suffit de cloner Rambanana :
```console
$ git clone https://github.com/Klafyvel/Rambanana.git
```

De se rendre dans le répertoire ainsi créé :
```console
$ cd Rambanana
```

Et de compiler :
```console
$ make
```

Par défaut, le programme sera lançé à la fin de la compilation et la compilation réalisée en mode release. Vous pouvez modifier ce comportement en modifiant les variables `DEBUG` et `RUNAPP`.

Dépendances
-----------
cJSON -> http://sourceforge.net/projects/cjson/ par Dave Gamble.

SFML2 -> http://sfml-dev.org/ par Laurent Gomila

Bananananananana -> http://www.dafont.com/fr/bananananananana.font par Beth Nott

Federico -> http://www.dafont.com/fr/federico.font?l[]=10&l[]=1 par woodcuter
