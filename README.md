
# TIPE : Comment garder un musée

### Ce travail de recherche est effectué dans un cadre scolaire  

On s'interesse dans ce projet au problème soulevé par V.Klee en 1973. On suppose un musée et on se demande combien de gardes immobiles sont nécessaires afin de le surveiller. On prendra ainsi des polygones simples, donc la forme peut être quelconque. Pour cela on utilise des polygones générés aléatoirement, les exemples seront donc tous sur des polygones distincts.




**On se limite dans un premier temps à la dimension deux, on estime que chaque étage est clairement distinct des autres, on considère ainsi que si les gardes sont capables de voir tout le sol de l'étage qu'ils sont capables de l'observer en entier.**

### On utilise 2 algorithmes afin de générer les polygones, dont voici une brève description ainsi qu'une comparaison : dans les deux cas on commence par générer $N$ points de coordonnées aléatoires

1. Découpe en hemisphère et tri des points
    - On commence par découper le polygone en 2 hémisphère en créant un segment entre le point le plus à gauche et celui le plus à droite.
    - On tri les points au dessus et en dessous de la ligne par coordonnée $x$ croissante
    - On peut ensuite relier les points d'en haut et d'en bas chacun dans l'ordre du tri pour obtenir un polygone dont les sommets sont les points générés.
    

[//]: # (Preuve de correction à mettre ici ?)

![image](./src/resources/example_hemispheres.png)

- Cet méthode a pour avantage d'être très simple à implémenter et a une complexité en $O(n\log n)$ cependant au delà de $20$ côtés les polygones ont tous une forme semblable, une sorte de peigne vers le haut et le bas, c'est ce qui nous a motivé à voir une deuxième approche pour construire les polygones. 

2. Parcours de Graham et grignottage
    - On commence par cherche l'eveloppe convexe du nuage de points
    - On prend ensuite un point intérieur avec lequel on brise l'enveloppe convexe obtenu, celà ne crée pas de segments séquents par convexité de l'enveloppe.
    - La forme obtenu n'étant plus convexe, pour chaque  point on cherche le segment le plus proche et on découpe ce segment en deux pour inclure le point en question dans les sommets. 
    > Sur l'exemple ci dessus, on pourrait obtenir le même résultat qu'avec l'autre méthode.