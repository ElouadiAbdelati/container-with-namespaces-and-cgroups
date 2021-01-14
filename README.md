# irisi-container


                       //**************************************************************
                                //     EL OUADI Abdelati & KHADIM Meriem
                               //                    IRISI2
                      //*****************************************************************
                      
   
                            // Création d’un conteneur ia les Namespaces et les Cgroups
## Introduction
  Un conteneur Linux est un processus ou un ensemble de processus isolés du reste du système.
  
  
 ## Installation
 Vous devez installer un outil Cgroup avant
     ```bash
    sudo apt-get install libcgroup1 cgroup-tools
     ```
 
afin de créer ce conteneur,veuillez exécuter le fichier clone existant dans le même répertoire avec les privilèges root via la commande suivante: 
       ```bash
    sudo ./clone
```
 L'exécution de cette commande vous allez etre rédiger à un nouveau shell bash exécuter dans un espace de noms vraiement isolé , dont le root directory est le répertoire Host,il appartient à deux cgroups:
  -le premier cgroupe limite la mémoire qui va etre utilisée par l'espace de noms
  -le deuxieme limite nombre de PIds à utiliser,càd il limite le nombre de processus à exécuter.
  
   Pour tester ces limitations,veuillez exécuter la commande ci-dessous :
   
       ```bash
       ./testForMomery
    ```
   
       ```bash
       ./testForpids
    ```
    
