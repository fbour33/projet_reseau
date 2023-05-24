# Projet de Réseau

## Arborescence de fichiers

- app/ : Dossier du code de l'afficheur 
    - app/logCLient.txt : Fichier de log du client
    - app/affichage.cfg : Fichier de config. de l'afficheur
- build/ : Fichier objet du controller (après compilation)
- controller/ : Dossier du code du serveur
- aquarium.load : Fichier de paramètre de l'aquarium
- controller.cfg : Fichier de config. du controller
- log.txt : Fichier de log du serveur

## Compilation du projet

- Compiler le serveur avec la commande make 
- Mettre en place gradle avec ./gradlew
  
## Execution du projet

- ./gradlew run pour le client
- ./server pour le serveur

## Exemple de commande client:

- addFish ClownFish_1 at 70x30,10x3, RandomWaypoint
- startFish ClownFish_1 
- status

### Console utilisateur

- La console utilisateur du serveurse trouve sur le terminal qui la lancé
- La console utilisateur du client se trouve en cliquant sur "Aquarium Menu" -> Open console

## Client et serveur distant

- Modifier dans le dossier app la ligne controller-address du fichier affichge.cfg en ajoutant l'adresse IP du serveur.
- Suivre les mêmes étapes de compilation et d'exécution que sur un client en localhost
