Liu francois
Rechercher le plus court chemin entre deux points d'un réseau (par exemple ferroviaire) décrit par un fichier texte.

Comment compiler votre projet.
avoir le fichier liste_chemin.txt dans le meme dossier.
le fichier doit avoir a chaque ligne le nom du point de depart {espace} nom du point d'arriver {espace} le cout entre ces 2 points
gcc chemin.c

Comment exécuter votre projet. 
On voit les points possibles, le programme nous demande le point de debut et le point d'arriver.
Le programme vas ensuite faire le plus court chemin entre ces 2 points et nous l'afficher avec son cout.

Les fonctions/aspects de votre projet (essayez d'être exhaustif mais bref) en indiquant ce qui ne fonctionne pas bien. 
afficher permet d'afficher le chemin.
nb_ligne permet de compter le nombre de ligne dans le fichier.
cree_liste permet de recupperer les points et le cout dans le ficher.
nb_sommet permet d'avoir la liste des points et le nombre.
Dijkstra permet de calculer le plus court chemin.
