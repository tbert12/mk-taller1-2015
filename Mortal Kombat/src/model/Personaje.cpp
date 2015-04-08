/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad) {
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];
	m_xActual = 0;
	m_yActual = 0;
	m_velocidad = 0;
	estaScrolleando = false;
	_tDeSalto = 0;
	_estaSaltando = -1;
}


std::vector<Sprite*> Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){;
	return spriteActual;
}

void Personaje::AvanzarSprite(){
	if (spriteActual->puedeAvanzar()){
		spriteActual->Advance();
	} else {
		spriteActual = spriteActual->getSpriteSiguiente();
		spriteActual->Reset();
	}
}

int Personaje::getVida(){
	return vida;
}

void Personaje::SetScroll(bool valor){
	estaScrolleando = valor;
}

void Personaje::_cambiarSprite(int accion){
	if(_estaSaltando > 0) return;
	if(_estaSaltando == 0){
		_actualizarY();
	}
	if (sprites[accion] != spriteActual){
		spriteActual = sprites[accion];
		spriteActual->Reset();
	}
}

void Personaje::Inicial(){
	if (_estaSaltando > 0) return;
	m_velocidad = 0;
	if (spriteActual == sprites[SPRITE_SALTO] or
		spriteActual == sprites[SPRITE_SALTO_DIAGONAL_DERECHA] or
		spriteActual == sprites[SPRITE_SALTO_DIAGONAL_IZQUIERDA]){
		this->_cambiarSprite(SPRITE_SALTO_CAIDA);
	} else if (spriteActual == sprites[SPRITE_AGACHADO]){
		this->_cambiarSprite(SPRITE_LEVANTARSE);
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
	if (_estaSaltando > 0) return;
	m_velocidad = VELOCIDAD_ADELANTE;
}

void Personaje::CaminarIzquierda(){
	this->_cambiarSprite(SPRITE_CAMINAR_IZQUIERDA);
	if (estaScrolleando) {
		return;
	}
	if (_estaSaltando > 0) return;
	m_velocidad = VELOCIDAD_ATRAS;
}

void Personaje::Saltar(){
	if (estaScrolleando) {
		return;
	}
	if (m_velocidad){
		if (m_velocidad > 0){
			_SaltarDerecha();
		} else {
			_SaltarIzquierda();
		}
	}
	else{
		_SaltarHorizontal();
	}

}



void Personaje::_SaltarDerecha(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_ANTES_D);
	_estaSaltando = 1;
	m_velocidad = m_velocidad*2.5f;
}

void Personaje::_SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_ANTES_I);
	_estaSaltando = 1;
	m_velocidad = m_velocidad*2.5f;
}

void Personaje::_SaltarHorizontal(){
	this->_cambiarSprite(SPRITE_SALTO_ANTES);
	_estaSaltando = 1;
}

//Funciones Logicas de Salto
void Personaje::_actualizarY(){
	if(m_yActual >= 0){
		m_yActual = _yDeSalto(m_yActual,_tDeSalto);
		_tDeSalto++;
	}
	if(_tDeSalto > 0 and m_yActual < 100 and m_yActual > 3){
		_estaSaltando = 1;
	}
	if(_tDeSalto > 10 and m_yActual < 1){
		m_yActual = 0;
		_tDeSalto = 0;
		_estaSaltando = -1;
		Inicial();
	}
}

int Personaje::_yDeSalto(int currentY, int currentT)
{
	return -4 * currentT * (currentT - 13);
}

void Personaje::Agachar(){
	if (_estaSaltando > 0) return;
	_cambiarSprite(SPRITE_AGACHARSE);
	m_velocidad = 0;
}

void Personaje::Levantarse(){
	if (_estaSaltando > 0) return;
	_cambiarSprite(SPRITE_LEVANTARSE);
	m_velocidad = 0;
}

int Personaje::getX()
{
	m_xActual += m_velocidad;
	return m_xActual + 320;
}

int Personaje::getY()
{
	if(_estaSaltando > 0){
		_actualizarY();
	}
	return m_yActual;
}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida < 0){
		vida = 0;
	}
}

void Personaje::renderizar(){
	spriteActual->render(getX(),480 - getY());
	AvanzarSprite();
}

bool Personaje::IsScrolling(){
	return this->estaScrolleando;
}
bool Personaje::getSentidoDeMovimiento(){
	return m_velocidad > 0;
}

Personaje::~Personaje() {
	//~sprites();
	//~nombre();
	//sprites.~list();
	//nombre.~string();
}

