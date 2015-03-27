/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje) {
	nombre = nombre_personaje;
	vida = 100;
	//COMO ES UN SOLO JUGADOR EN ESTE TP LO HARCODEAMOS, LUEGO LO LEVANTAMOS CON JSON
	//sprites = std::list<std::string> sprites("data/players/subzero/sprites/initial.png");
	sprites = "data/players/subzero/sprites/walk.png";
}

//std::list<std::string> Personaje::Sprites(){
std::string Personaje::Sprites(){
	return sprites;
}

std::string Personaje::Sprite(unsigned int accion){
	//std::string sprite = "";
	//if (sprite.size() > accion){
	//    std::list::iterator_it = sprite.begin();
	//    std::advance(sprite, accion);
	//}
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
	//~sprites();
	//~nombre();
	//sprites.~list();
	//nombre.~string();
}

