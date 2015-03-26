/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <list>


Personaje::Personaje(std::string nombre_personaje) {
	nombre = nombre_personaje;
	vida = 100;
	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	sprites = sprites("../../data/players/subzero/sprites/initial.png");
}

std::list<std::string> Personaje::Sprites(){
	return sprites;
}

std::string Personaje::Sprite(int accion){
	std::string sprite = "";
	if (sprite.size() > accion)
	{
	    std::list<std::string>::iterator it = sprite.begin();
	    std::advance(sprite, accion);
	}
	return sprite;
}

int Personaje::Vida(){
	return vida;
}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida < 0){
		vida = 0;
	}
}

Personaje::~Personaje() {
	sprites.~list();
	nombre.~string();
}

