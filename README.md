Bilan du sujet de TP : Création d'un micro-shell
Au cours de ce sujet, j'ai développé mes compétences en programmation système et compris le fonctionnement global d'une console, notamment avec la gestion des processus, de la lecture des entrées et des redirections : 

1. Création d'un shell de base
Tout d'abord, j'ai appris à implémenter un shell basique, ce dernier affichait un message d'accueil et executait des fonctions basiques (date, fortune,...). Il était important de prendre en compte l'attente d'une entrée et la gestion d'une commande non connue.
Il y a aussi eu la gestion des processus entre le fils et le père. Ceci m'a permis de comprendre comment fonctionnent les processus mais aussi le lien entre le père et le fils (notamment lorsqu'il fallait tuer le fils avec un signal extérieur). 

2. Gestion des redirections
L'un des défis majeurs du projet a été la gestion des redirections. J'ai appris à utiliser les appels système open(), dup2() et close() pour rediriger les flux d'entrée et de sortie des commandes vers des fichiers. Par exemple, l'opération > permet de rediriger la sortie d'une commande vers un fichier, et < permet de rediriger l'entrée depuis un fichier.
J'ai également mis en place des fonctions pour gérer ces redirections en veillant à ne pas modifier la logique de traitement des commandes. Cela m'a permis de comprendre l'importance de l'ordre des actions (lecture d'un caractère <> avant la lecture d'un espace), puisque c'est primordiale pour la lecture de commande composée complexe. 

3. Gestion des erreurs et lisibilité du code
Un des points clés de ce projet a été la compréhension du code. J'ai essayé de structurer au maximum mon code en différentes fonctions. Cela m'a permis de clarifier mon code et le rendre le plus lisible possible; notamment lors de la présence d'une erreur, le temps gagné avec un code propre est très important.

