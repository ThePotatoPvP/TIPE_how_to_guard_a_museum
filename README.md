
# TIPE : Comment garder un musée

### Ce travail de recherche est effectué dans un cadre scolaire  

On s'interesse dans ce projet au problème soulevé par V.Klee en 1973. On suppose un musée, combien de gardes immobiles sont nécessaires afin de surveiller la moindre partie du musée. On prendra ainsi des polygones symples, donc la forme peut être quelconque. Pour cela on utilise des polygones générés aléatoirement, les exemples seront donc tous sur des polygones distincts.




**On se limite dans un premier temps à la dimension deux, on estime que chaque étage est clairement distinct des autres, on considère ainsi que si les gardes sont capables de voir tout le sol de l'étage qu'ils sont capables de l'observer en entier.**

### On utilise 2 algorithmes afin de générer les polygones, dont voici une brève description ainsi qu'une comparaison : dans les deux cas on commence par générer $N$ points de coordonnées aléatoires

1. Découpe en hemisphère et tri des points
    - On commence par découper le polygone en 2 hémisphère en créant un segment entre le point le plus à gauche et celui le plus à droite.
    - On tri les points au dessus et en dessous de la ligne par coordonnée $x$ croissante
    - On peut ensuite relier les points dans l'ordre en haut et en bas pour obtenir un polygone dont les sommets sont les points générés.

2. Parcours de Graham et grignottage


![image](./ressources/example_polygons_basic_shape.png)