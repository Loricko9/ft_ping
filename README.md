# Ft_ping

[![fr](https://img.shields.io/badge/Langue-fr-blue)](README.fr.md)

$$\color{darkgreen}{{\Huge \mathbf {100/100 ✅}}}$$

## The goal

Reproduce the simple `ping` (inetutils-2.0) command with socket

We also need to handle 2 options :
- `-v`
- `-?`

## Execution

This project contain a `Makefile`.
It compile each file in `src/` directory and it produce a executable
The executable must be executed as follow :
````sh
./ft_ping [options] addresses
````
You can put either ip addresses (`172.217.20.163`) or DNS addresses (`google.fr`).
You can also put more than one address in the command and the program will test each addresses.
