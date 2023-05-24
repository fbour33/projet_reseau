# Client sur localhost (Client + serveur sur la même machine)

## Compilation et exécution du serveur 

- Compiler le projet avec la commande make 
- Exécuter le serveur avec la commande ./serveur, un aquarium est déjà chargé en mémoire
  
## Execution du client

- Taper la commande ./gradlew run sur un autre terminal


# Client sur une adresse IP (Client + serveur des machines différentes)

- Modifier dans le dossier app la ligne controller-address du fichier affichge.cfg en ajoutant l'adresse IP du réseau auquel vous êtes connecté. 
- Suivre les mêmes étapes de compilation et d'exécution que sur un client en localhost
