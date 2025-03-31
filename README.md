# Ft_ping

[![fr](https://img.shields.io/badge/Langue-fr-blue)](README.fr.md)

<p style="color: darkgreen;font-weight: 800;font-size:xxx-large;text-align:center;">100/100 ✅</p>


## The goal

Reproduce the simple `ping` (inetutils-2.0) command with socket

We also need to handle 2 options :
- `-v`
- `-?`

##### This program need to use raw socket to send ICMP Packet so you must have root right !

## Execution

This project contain a `Makefile`.
It compile each file in `src/` directory and it produce a executable
The executable must be executed as follow :
````sh
sudo ./ft_ping [options] addresses
````

<span style="color: red;font-weight: 800;font-size:large;">⚠⚠ You need to have root right to run the program ⚠⚠</span>

You can put either ip addresses (`172.217.20.163`) or DNS addresses (`google.fr`).
You can also put more than one address in the command and the program will test each addresses.
