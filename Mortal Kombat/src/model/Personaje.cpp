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
#define SPRITE_CAMINAR_ATRAS 2;
#define SPRITE_SALTO 3;
#define SPRITE_SALTO_DIAGONAL 4;
#define SPRITE_PUNCHING 5;
#define SPRITE_KICKING 6;

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites) {
	spriteActual = 0;
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	m_xActual = 0;
	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	//sprites = std::list<std::string> sprites("data/players/subzero/sprites/initial.png");
	//sprites = "data/players/subzero/sprites/walk.png";
}

std::vector<Sprite*> Personaje::getSprites(){
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
		sprites[spriteActual]->Reset();
	}
}

void Personaje::Inicial(){
	this->_cambiarSprite(0);
}

void Personaje::Saltar(){}

void Personaje::Agachar(){}

void Personaje::CaminarDerecha(){
	this->_cambiarSprite(1);
}

void Personaje::CaminarIzquierda(){
	this->_cambiarSprite(2);
}

void Personaje::SaltarDerecha(){}

void Personaje::SaltarIzquierda(){}
int Personaje::getX()
{
	return m_xActual;
}

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

