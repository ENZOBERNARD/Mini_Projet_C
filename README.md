# Mini_Projet_C

Le but de ce projet est de créer un jeu à l'aide de raylib. Ce jeu comporte plusieurs points communs avec Geometry Dash https://play.google.com/store/apps/details?id=com.robtopx.geometryjump&hl=fr&gl=US
Il s'agit d'un jeu 2D où un carré avance (sans arrêt) de gauche à droite et le but est de sauter au bon moment afin d'éviter les différents obstacles.

Un seul objectif : Finir tous les niveaux !!

# Commandes: 

Sauter  [Barre Espace]
Pause [Entrée]

# Caractéristiques

Niveau :
Il existe actuellement 2 niveaux. Les niveaux peuvent facilement être créé grâce à la fonction generateLevel().
Les collisisons avec les obstacles fonctionnent bien : Lorsque le joueur rentre dans un obstacle, il perd. Et lorsque le joueur est sur un obstacle cela n'est pas considéré comme game over, mais comme une plateforme.

Customisation et couleur :
Il y a possibilité de changer la couleur du joueur. Chaque niveaux possèdent ses propres couleurs, afin qu'ils aient chacuns un "univers" différent.

Barre de progression :
Une barre de progression est diponible lors de la partie et lorsque le joueur perd, il peut voir son avancée dans le niveau.

# Perpectives d'améliorations

Niveau: 
On peut tout d'abord ajouter et créer plusieurs niveaux, avec de plus belles couleurs et des diffultés différentes selon les niveaux.

Customisation :
Ajouter des textures au jeu afin qu'il soit plus beau ainsi que des animations, comme par exmemple lors d'un game over ou le lancement d'un niveau.

Jouabilité :
Optimiser le temps de saut, la hauteur.
Optimiser aussi la vitesse des obstacles.
Ajout de niveaux 


# Fichiers du projet

L'ensemble du code source se trouve dans le fichier main.c qui utilise geo.h (qui utilise raylib.h).

# Vidéo de présentation

Une courte vidéo est disponible dans le projet : enzo-bernard.mp4 afin d'expliquer le but et le fonctionnement du projet.



Enzo BERNARD


