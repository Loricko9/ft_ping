# Ft_ping

[![en](https://img.shields.io/badge/Language-en-red)](README.md)

$$\color{darkgreen}{{\Huge \mathbf {100/100 ✅}}}$$

## The goal

Reproduire trés simplement la commande `ping` (inetutils-2.0) avec des socket

Nous devons gérer 2 options :
- `-v`
- `-?`

## Execution

Ce projet contient un `Makefile`.
Il compile tous les fichier présent dans `src/` et produit un exécutable.
Le programme doit être lancer comme suit :
````sh
./ft_ping [options] addresses
````
Vous pouvez mettre soit des adresses ip (`172.217.20.163`), soit des adresses DNS (`google.fr`).
Vous pouvez également mettre plus d'une adresse dans la commande et le programme testera chaque adresses.