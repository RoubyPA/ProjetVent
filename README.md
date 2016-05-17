# ProjetVent

###### Author :  Rouby Pierre-Antoine
###### Date :    06/05/2016
###### System :  Linux (PC/RASPBERRY)

## 1. Objectif

L’objectif principal du projet est de mesurer, archiver et visualiser la vitesse et la direction du vent.Pour ce faire, nous installerons un anémomètre afin de mesurer la vitesse et la direction du vent que nous récupérerons ensuite à l’aide d’une raspberry pi zero. Cette dernière contiendra un programme permettant la récupération de la vitesse et de la direction du vent, celui-ci permettra également la sauvegarde des données en local (directement sur la mémoire de la raspberry) et de transférer les données via un module GPRS directement sur un serveur de base de données. Un transfert manuel avec une clé usb sera possible : après avoir branché la clé usb sur la raspberry, les données se transféreront dessus. Ensuite, le transfert de données pourra se faire de la clé vers le serveur de données.
Un site web permettra aux utilisateurs de visualiser la vitesse et la direction du vent sur la période voulu. Il sera également possible de comparer deux périodes et/ou deux endroits différents.


###### PS : Se repositories ne comprend que la partie récuperation via usb.

## 2. Compilation

Compilation on GNU/Linux:

>Use **make** commande line.
