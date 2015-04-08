/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, float velocidad) {
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];
	m_xActual = 0;
	m_yActual = 0;
	m_velocidad = velocidad;
	estaScrolleando = false;
	_tDeSalto = 0;
	_estaSaltando = -1;
}


std::vector<Sprite*> Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){
	Sprite* spriteReturn = spriteActual;
	spriteActual->Advance();
	return spriteReturn;
}

int Personaje::Vida(){
	return vida;
}

void Personaje::SetScroll(bool valor){
	estaScrolleando = valor;
}

void Personaje::_cambiarSprite(int accion){
	printf("Accion: %d\n",accion);
	//Con la logica del salto tengo que mantener Reseteando el SPRITE_SALTO asi no se pasa
	//if(_estaSaltando > 0){
	//	printf("_estaSaltando > 0\n");
	//	_actualizarY();
	//	return;
	//}
	if(_estaSaltando == 0){
		_actualizarY();
	}
	if (sprites[accion] != spriteActual){
		if (!spriteActual->puedeAvanzar()){
			spriteActual = spriteActual->getSpriteSiguiente();
			spriteActual->Reset();
		}
		printf("accion != spriteActual\n");
		spriteActual = sprites[accion];
		spriteActual->Reset();
	} else if (!spriteActual->puedeAvanzar()){
		printf("No puede Avanzar\n");
		spriteActual = spriteActual->getSpriteSiguiente();
		spriteActual->Reset();
	}
}

void Personaje::Inicial(){
	printf("Inicial()\n");
	if (spriteActual == sprites[SPRITE_SALTO]){
		printf("Esta Saltando\n");
		this->_cambiarSprite(SPRITE_SALTO_CAIDA);
	} else {
		this->_cambiarSprite(SPRITE_INICIAL);
	}
}

void Personaje::CaminarDerecha(){
	this->_cambiarSprite(SPRITE_CAMINAR_DERECHA);
	if (estaScrolleando) {
		estaScrolleando = false;
		return;
	}
	m_xActual += m_velocidad;
}

void Personaje::CaminarIzquierda(){
	this->_cambiarSprite(SPRITE_CAMINAR_IZQUIERDA);
	if (estaScrolleando) {
		return;
	}
	m_xActual -= m_velocidad;
}

void Personaje::_actualizarY(){
	if(m_yActual > 0){
		m_yActual = _yDeSalto(m_yActual,_tDeSalto);
		_tDeSalto++;
	}
	if(_tDeSalto > 50 and m_yActual < 20 and m_yActual > 3){
		_estaSaltando = 0;
	}
	if(_tDeSalto > 50 and m_yActual < 3){
		m_yActual = 0;
		_estaSaltando = -1;
	}
}

int Personaje::_yDeSalto(int currentY, int currentT)
{
	return -0.1 * currentT * (currentT-100);
}

void Personaje::Saltar(){
	this->_cambiarSprite(SPRITE_SALTO_ANTES);
	_estaSaltando = 1;

}

void Personaje::SaltarDerecha(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_DERECHA);
	//aca saltar
	if (estaScrolleando) {
		return;
	}
}

void Personaje::SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_IZQUIERDA);
	//aca saltar
	if (estaScrolleando) {
		return;
	}
}


void Personaje::Agachar(){}

int Personaje::getX()
{
	return m_xActual;
}

int Personaje::getY()
{
	return m_yActual;
}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida < 0){
		vida = 0;
	}
}

void Personaje::renderizar(){
	spriteActual->render();
}

Personaje::~Personaje() {
	//~sprites();
	//~nombre();
	//sprites.~list();
	//nombre.~string();
}

