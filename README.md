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

Exécutable Windows
------------------
Le Makefile permet de générer un exécutable windows depuis GNU/Linux.
Pour cela il vous faut la [version mingw](http://www.sfml-dev.org/download/sfml/2.1/index-fr.php) de la SFML. Décompressez-la dans `/home/votrenom/SFML-2.1-win` ou modifiez le Makefile. 

Il vous faut également mingw. Sous Ubuntu :
```console
$ sudo apt-get install mingw32-runtime
```
Vous pouvez ensuite générer directement une archive ZIP contenant l'exécutable, les dll etc...
```console
$ make winarchive
```

Vous pouvez également générer uniquement l'exécutable (les dlls de SFML seront néanmoins copiées à côté de l'exécutable). Il faut pour cela mettre la variable `WINEX` du Makefile à "yes". Puis:
```console
$ make
```
Notez que si la variable `RUNAPP` est à "yes", le Makefile tentera de lancer l'exécutable avec wine.

Dépendances
-----------
cJSON -> http://sourceforge.net/projects/cjson/ par Dave Gamble.

SFML2 -> http://sfml-dev.org/ par Laurent Gomila

Bananananananana -> http://www.dafont.com/fr/bananananananana.font par Beth Nott

Federico -> http://www.dafont.com/fr/federico.font?l[]=10&l[]=1 par woodcuter
