Bonjour, Voici le déroulé de mon TP1 : 
Question 1 et 2 : Nous affichons le prompt, le message d'accueil, et notre console comprend des fonctions simples :  ![whatever](Capture01.png)
Question 3 : Notre console détecte le mot exit ou un controle D et la console se ferme : ![whatever](Capture02.png)
Question 4 et 5 : Nous modifions le retour de la console de sorte à connaitre le type de sortie, pour tester avec SIGN nous utilisons une autre console pour tuer notre processus fils (qui est modifié pour afficher son PID et ensuite être en attente : ![whatever](Capture3.png)) : 
    Console numéro 1, le processus fils affiche son PID puis s'endort et est tué par la console numéro 2 :  ![whatever](Capture1.png)
    Console numéro 2, elle tue notre signal  :  ![whatever](Capture2.png)

Question 6 : Nous créons une fonction qui découpe l'entrée console (input) pour ensuite analyser les commandes complexes : ![whatever](Capture4.png) ![whatever](Capture6.png)
Question 7 : Nous devons créer des fonctions qui permettent de rediriger l'entrée ou la sortie des fichiers : ![whatever](Capture5.png)
