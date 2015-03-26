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

//Constants
#define SPRITE_PARADO = 0;
#define SPRITE_CAMINAR = 1;
#define SPRITE_SALTO = 2;
#define SPRITE_SALTO_DIAGONAL = 3;
#define SPRITE_PUNCHING = 4;
#define SPRITE_KICKING = 5;


Personaje::Personaje(char* nombre_personaje) {
	nombre = std::string(nombre_personaje);
	vida = 100;
	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	sprites = sprites("../../data/players/subzero/sprites/initial.png");
}

std::list<char*> Personaje::Sprites(){
	return sprites;
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

