# TP2_synthese compte rendu :

Ce TP m'a permis d'acquérir différentes connaissances : 
Premièrement il fallait lancer le serveur que l'on a télécharger, cela m'a permis de mieux comprendre le fonctionnement de la VM et le partage des fichiers entre ma VM et mon ordinateur. On a donc : 
![whatever](tp22.png)

Puis j'ai améliorer ma compréhension sur la manière de récupérer et de valider des arguments en ligne de commande dans un programme C. On fait ici attention à ce que le programme appel exactement 3 arguments (le nom de l'executable ne compte pas), on aura donc argv[1], argv[2], et argv[3].

Par la suite j'ai compris l'utilisation de getaddrinfo qui permet de convertir le nom de l’hôte (argv[1] et le port [argv2] (69) en une structure d’adresse réseau utilisable par le programme.
On peut donc par la suite afficher notre localhost 

![whatever](tp23.png)

Il faut ensuite crée une socket UDP permettant d'établir une communication réseau entre le client TFTP et le serveur TFTP, via nos paramètres de getaddrinfo sans oublier de gérer les erreurs si la création échoue.
J'ai toujours un peu de mal avec la création des sockets mais je pense avoir compris la création dans ce cas la. 

Puis, on veut construire un message TFTP de type “Read Request” (RRQ) en suivant la spécification du protocole dans la RFC 1350 : et on retient que on peut utiliser sprintf pour écrire dans un buffer, et qu'on envoi note socket avec sendto 
J'ai ensuite affiché l'envoi de ce message dans wireshark. 
![whatever](tp21.png)


Ensuite, j'ai essayé de m'occuper de la réception, j'ai fais beaucoup de code différent mais je n'ai pas réussir à atteindre le port et à l'afficher dans wireshark.

En conclusion, j'ai eu beaucoup de mal à avancer sur ce TP, et j'ai rencontrer de nombreux problèmes avec la VM qui m'ont fait perdre du temps. 
