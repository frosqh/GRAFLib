Arborescence, descriptif des fichiers & utilisation :
- GRAFLib
   +- BIN
   +- LIB
   +- OBJ
   +- SRC
   |  +- libflow
   |     +- max_flow.c
   |     +- max_flow.h
   |  +- libgraph
   |     +- graph.c
   |     +- graph.h
   |  +- liblist
   |     +- list.c
   |     +- list.h
   |  +- main.c
   |  +- menu.h
   +- makefile
   +- ReadMe.txt

Le dossier BIN contient l'executable (graf).
Le dossier LIB contient les librairies (libflow, libgraph, liblist).
Le dossier OBJ contient l'édition de lien de l'executable et des librairies.
Le dossier SRC contient le code répartie en sous-dossiers pour les librairies, avec le source et le header respectif,
puis le source main et son header menu.h.
Le makefile est localisé en racine de GRAFLib tout comme ce fichier.

Pour compiler le programme :
cd GRAFLib
make

Pour executer le programme :
cd GRAFLib/BIN
./graf
Puis suivre les instructions du menu.