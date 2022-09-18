#!/bin/sh

#Esto es lo minimo que se ocupa para compilar para un microcontrolador AVR en linux

sudo apt update
sudo apt install avr-libc avra gcc-avr binutils

#Lo que sigue es extra
sudo apt install make
