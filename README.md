  **KHADIM Meriem & EL OUADI Abdelati IRISI2**
# CRÉATION D'UN CONTENEUR VIA LES ESPACES DE NOMS ET LES CGROUPS

**Notre objectif dans ce projet est d’exécuter un shell bash dans un environnement système isolé(conteneur),à l'aide des espaces de noms et les cgroups,tout en limitant la mémoire et aussi le nombre des processus qui pourraient être exécutés par le conteneur.**

## Préparation de l'environnement du nouveau conteneur

Pour se faire,veuillez ouvrir un terminal dans le répertoire  (Iirisi-container),puis exécuter la commande suivante :
 ```bash
        ./newRoot.sh
 ``` 
 Celle-ci va vous créer un nouveau root ,à savoir le répertoire Host,tout en créant dedans tout les libraries nécessaire pour exécuter des commandes dans le shell bash.
 
##Création du conteneur

Dans le même terminal veuillez exécuter la commande suivante avec le privilège root:
 ```bash
       $ sudo ./clone
 ``` 
L'exécution de cette commande vous allez être redirigés à un nouveau shell bash exécuté dans un espace de noms vraiement isolé , dont le root directory est le répertoire Host,il appartient à deux cgroups:
  -le premier cgroupe limite la mémoire qui va etre utilisée par l'espace de noms
  -le deuxième limite nombre de PIds à utiliser,càd il limite le nombre de processus à exécuter.
  
## Tester la limitation des ressources utilisées par le conteneur
### Mémoire
Pour le faire,veuillez exécuter la commande ci-dessous dans le nouveau shell bash:
 ```bash
      $ ./testForMem
 ```    
### Nombre de processus à exécuter
 ```bash
      $ ./testForPids
 ``` 

