/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"


Personaje::Personaje(std::string nombre_personaje,Sprite Sprites[]) {
	spriteActual = 0;
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	//sprites = std::list<std::string> sprites("data/players/subzero/sprites/initial.png");
	//sprites = "data/players/subzero/sprites/walk.png";
}

Sprite* Personaje::Sprites(){
	return sprites;
}

Sprite Personaje::Sprite(unsigned int accion){
	if (sizeof(sprites)/sizeof(*sprites) <= accion or accion == spriteActual){
		return NULL;
	}
	spriteActual = accion;
	return sprites[accion];
}

int Personaje::Vida(){
	return vida;
}

void Personaje::Saltar(){
	return;
}
void Personaje::Agachar(){}
void Personaje::CaminarDerecha(){}
void Personaje::CaminarIzquierda(){}
void Personaje::SaltarDerecha(){}
void Personaje::SaltarIzquierda(){}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida < 0){
		vida = 0;
	}
}

Personaje::~Personaje() {
	//~sprites();
	//~nombre();
	//sprites.~list();
	//nombre.~string();
}

