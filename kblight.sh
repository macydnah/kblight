#!/bin/bash

# Definiendo variables
#
kbd_backlight_path=/sys/devices/platform/sony-laptop/kbd_backlight
kbd_backlight_value=$(cat $kbd_backlight_path)
argumento=${1:--auto}

# Declarando y definiendo funciones
#
auto () {
if [ $kbd_backlight_value == 1 ] ;

    then echo 0 > $kbd_backlight_path ;

	elif [ $kbd_backlight_value == 0 ] \
	 ||  [ $kbd_backlight_value == 2 ] ;

	    then echo 1 > $kbd_backlight_path ;
fi }

on () {
if [ $kbd_backlight_value == 0 ] \
|| [ $kbd_backlight_value == 1 ] ;

    then echo 2 > $kbd_backlight_path ;
fi }

off () {
if [ $kbd_backlight_value == 1 ] \
|| [ $kbd_backlight_value == 2 ] ;

    then echo 0 > $kbd_backlight_path ;
fi }

# El mero mero
# main () {
if [ $argumento = -auto ] ; then auto ;

	elif [ $argumento = -on ] ; then on ;

	elif [ $argumento = -off ] ; then off ;

    else echo "Argumento Invalido" ;
fi
# }
