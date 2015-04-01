/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

//Constants
#define SPRITE_PARADO 0;
#define SPRITE_CAMINAR 1;
#define SPRITE_SALTO 2;
#define SPRITE_SALTO_DIAGONAL 3;
#define SPRITE_PUNCHING 4;
#define SPRITE_KICKING 5;

Personaje::Personaje(std::string nombre_personaje,Sprite** Sprites) {
	spriteActual = 0;
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	//sprites = std::list<std::string> sprites("data/players/subzero/sprites/initial.png");
	//sprites = "data/players/subzero/sprites/walk.png";
}

Sprite** Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){
	return sprites[spriteActual];
}

int Personaje::Vida(){
	return vida;
}

void Personaje::_cambiarSprite(unsigned int accion){
	if (accion != spriteActual){
		spriteActual = accion;
	}
}

void Personaje::Inicial(){
	this->_cambiarSprite(0);
}

void Personaje::Saltar(){
	return;
}
void Personaje::Agachar(){}

void Personaje::CaminarDerecha(){
	this->_cambiarSprite(1);
}

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

