# Ft_ping

[![en](https://img.shields.io/badge/Language-en-red)](README.md)

<p style="color: darkgreen;font-weight: 800;font-size:xxx-large;text-align:center;">100/100 ✅</p>

## The goal

Reproduire trés simplement la commande `ping` (inetutils-2.0) avec des socket

Nous devons gérer 2 options :
- `-v`
- `-?`
  
##### Ce programme doit utiliser des sockets brutes donc vous devez avoir les droits administrateur !

## Execution

Ce projet contient un `Makefile`.
Il compile tous les fichier présent dans `src/` et produit un exécutable.
Le programme doit être lancer comme suit :
````sh
sudo ./ft_ping [options] addresses
````

<span style="color: red;font-weight: 800;font-size:large;">⚠⚠ Vous devez avoir les droits administrateur pour executer le programme ⚠⚠</span>

Vous pouvez mettre soit des adresses ip (`172.217.20.163`), soit des adresses DNS (`google.fr`).
Vous pouvez également mettre plus d'une adresse dans la commande et le programme testera chaque adresses.