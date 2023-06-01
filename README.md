
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


# Plan de présentation

I -
> - présentation du problème global
> - approche théorique (complexité)

1. On commence par montrer que le problème est dans NP

    - On commence par remarquer qu'une solution est un ensemble de sommets du polygone et est donc bien de taille polynomiale. Montrons maintenant que la vérification se fait en temps polynomial.

    - <b>Lemme</b> : Si un garde voit les deux extrémités d'un segment alors il voit l'entièreté du segment. Ce résultat s'obtient du fait qu'un triangle est convexe.

    - Le calcul de la zone visible par un garde donné se fait en temps polinômial et forme des polygones, on peut ensuite construire l'union toujours en temps polynomial puis vérifier l'égalité entre le polygone obtenu et celui de départ. On a ainsi bien que le problème est dans NP.


2. Montrons ensuite que le problème est NP-Complet

    - On va ici montrer que le problème 3-SAT se réduit à notre problème. Pour cela on commence par considérer une clause de 3-SAT de la forme $(x_1\lor x_2\lor x_3)$ avec les $x_i$ des litéraux.

    ![image](./src/resources/VGSP_schemas.png)

    - En limitant le nombre de gardes maximum on a bien que chaque clause doit être vraie pour que le schéma de clause soit couvert par les gardes. On peut ainsi placer les  clauses côte à côte en autorisant 3 gardes par clause, si le placement des gardes en retour contient assez peu de gardes alors la formule est vérifiable. Reste à s'assurer qu'une même variable a bien la même valuation dans chaque clause. On construit alors la structure ci-dessous pour chaque variable

    ![image](./src/resources/UNICITY_valuate.png)

    - En alignant correctement les clauses et en ajoutant des creux comme $x$ et $x'$ pour chaque occurence de la variable. On a alors un polygone tel que si toutes les occurences de la variable ont la même valeur alors tous les creux d'une colonnes sont observés et tous ceux de l'autre non, on place donc un garde sur l'un des points rouges.

    - En limitant le nombre de gardes au triple du nombre de clause plus le nombre de variables distinctes on a bien que le polygone est recouvert si et seulement si la formule est satisifable. On a finalement que le problème est dans NP car il se réduit en temps polynomial à 3-SAT.

> - tentative de génération de polygones pour aborder le problème de façon globale -> on y arrive pas

## Sur la génération de polygones

La galerie d'art étant représentée par un polygone il est bon de s'intéresser à leur génération. Plusieurs formes de génération
existent. On peut en faire d'autant de façons que l'esprit humain c'est en trouver. Cette question étant largement trop vaste
pour être intérrogée, on va partir d'une idée de base et la développer:

- L'arborescence à partir d'une structure de base

> - Partir d'un polygone choisi arbitrairement à k côtés.
> - Sur chaque côté choisir aléatoirement si elle doit être "développée"
> - Si il y a developpement: créer un nouveau polygone avec un côté commun au précédent
> - Répéter sur l'entiereté de la structure un nombre aléatoire de fois


_Le problème est que pour une structure de base choisit les figures seront relativement similaire.
On étudierait alors le problème de la galerie d'art sur un ensemble de figures qui se ressemblent._

- Création direct d'un polygone

> - On choisit sur le plan n points
> - On crée son enveloppe convexe par l'algorithme de Graham

On a alors deux ensembles de points, celui de l'enveloppe convexe et les points intérieurs.

> - Pour chaque point intérieur on brise l'enveloppe convexe pour créer deux nouveaux segments dans la figure finale
> - Répéter sans créer de segments qui intersecte la figure

_Il est difficile de savoir à l'avance le nombre de points de la figure convexe et donc de celle finale._


Cependant, on peut étudier une propriété qu'on tout les polygones. C'est le fait d'être triangulisable.
Ainsi en partant d'une structure de base qui est un triangle (donc trois points pris aléatoirement sur le plan) et
en utilisant la technique de l'arborescence on pourrait avoir un bon ensemble de polygone.


Voyons désormais les couts techniques de telles algorithmes.

L'arboresence demande une chose:

   - vérifier à chaque étape que l'ajout d'un point ne brise pas un polygone (côté qui s'intersecte) en O((i)²) où i est l'étape

Ainsi la création est en O(n²) où n est le nombre de sommets de la figure finale.

La création direct avec l'algorithme de Graham demande:

   - trier une liste de points en fonction d'un angle donc en O(n*ln(n))

Ainsi la création est en O(n*ln(n)) où n est le nombre de points choisis au départ (et non le nombre de sommet du polygone final).

On peut alors faire un mélange des deux méthodes, et pour des figures de tailles petites on peut utiliser l'arborescence
et on pour des figures de plus grandes tailles utiliser la création directe.

II -
> -  idée de tester tous les algos sur le mm set de polygones
> - présentations d'idées d'algos cons pour poser des cams -> pas opti
> - recherche d'algos avec des outils au programme (prog dynamique, memoisation, ..)

III -
> - Recherche d'algorithmes optimaux (insérer noms d'algos)
> - Implémentation et recherche duquel est le meilleur sur notre sample de polygones
> - on rajoute n-2 dimension

