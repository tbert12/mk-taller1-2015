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
	m_xInicial = 0;
	m_yInicial = 0;
	m_velocidad = 0;
	velocidadAdelante = velocidad;
	velocidadAtras = -velocidad/2;
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

void Personaje::setDimensiones(float h,float w){
	m_AltoMundo = h;
	m_AnchoMundo = w;
}

void Personaje::setPosition(float x, float y){
	m_xActual = x;
	m_xInicial = x;
	m_yActual = y;
	m_yInicial = m_yActual;
}

void Personaje::AvanzarSprite(){
	if (spriteActual->puedeAvanzar()){
		spriteActual->Advance();
	} else {
		spriteActual = spriteActual->getSpriteSiguiente();
		spriteActual->Reset();
	}
}

float Personaje::getVida(){
	return vida;
}

void Personaje::SetScroll(bool valor){
	estaScrolleando = valor;
}

void Personaje::_cambiarSprite(int accion){
	if(_estaSaltando > 0) return;
	if (sprites[accion] != spriteActual){
		spriteActual = sprites[accion];
		spriteActual->Reset();
	}
}

void Personaje::Inicial(){
	if (_estaSaltando > 0) return;

	if (spriteActual == sprites[SPRITE_SALTO] or
		spriteActual == sprites[SPRITE_SALTO_DIAGONAL_DERECHA] or
		spriteActual == sprites[SPRITE_SALTO_DIAGONAL_IZQUIERDA]){
		this->_cambiarSprite(SPRITE_SALTO_CAIDA);
		return;
	} else if (spriteActual == sprites[SPRITE_AGACHADO]){
		this->_cambiarSprite(SPRITE_LEVANTARSE);
	} else {
		this->_cambiarSprite(SPRITE_INICIAL);
		m_velocidad = 0;
	}
}

void Personaje::Frenar(){
	if (_estaSaltando > 0) return;
	m_velocidad = 0;
}

void Personaje::CaminarDerecha(){
	this->_cambiarSprite(SPRITE_CAMINAR_DERECHA);
	if (estaScrolleando) {
		estaScrolleando = false;
		return;
	}
	if (_estaSaltando > 0) return;
	m_velocidad = velocidadAdelante;
}

void Personaje::CaminarIzquierda(){
	this->_cambiarSprite(SPRITE_CAMINAR_IZQUIERDA);
	if (estaScrolleando) {
		return;
	}
	if (_estaSaltando > 0) return;
	m_velocidad = velocidadAtras;
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
	m_velocidad = velocidadAdelante*0.5f;
}

void Personaje::_SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTO_DIAGONAL_ANTES_I);
	_estaSaltando = 1;
	m_velocidad = -velocidadAdelante*0.5f;
}

void Personaje::_SaltarHorizontal(){
	this->_cambiarSprite(SPRITE_SALTO_ANTES);
	_estaSaltando = 1;
}

//Funciones Logicas de Salto
void Personaje::_actualizarY(){
	//Si esta Saltanto va actualizando
	if(_estaSaltando > 0){
		m_yActual = _yDeSalto(m_yActual,_tDeSalto);
		_tDeSalto++;
	}
	//Cuando esta llegando al piso, vuelvo a las condiciones iniciales
	if(_tDeSalto > 10 and m_yActual < m_yInicial + 20){
		m_yActual = m_yInicial;
		_tDeSalto = 0;
		_estaSaltando = -1;
		Inicial();
	}
}

float Personaje::_yDeSalto(float currentY, float currentT)
{
	float alturaMax = 3; //Mas Grande -> mas Alto
	float tiempoDeSalto = 10; //Mas grande -> mas tiempo en volver al suelo
	return alturaMax * currentT * (currentT - tiempoDeSalto) + m_yInicial;
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

float Personaje::getX()
{
	return m_xActual;
}

float Personaje::getY()
{

	return m_yActual;
}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida < 0){
		vida = 0;
	}
}

void Personaje::renderizar(float ancho){
	float renderX = m_xActual + m_velocidad;
	if (renderX <= m_AnchoMundo or renderX >= 0){
		m_xActual += m_velocidad;
	}
	if(_estaSaltando > 0){
			_actualizarY();
	}
	spriteActual->render(m_xActual- ancho,m_yActual);
	AvanzarSprite();
}

bool Personaje::IsScrolling(){
	return this->estaScrolleando;
}
bool Personaje::getSentidoDeMovimiento(){
	return m_velocidad > 0;
}

Personaje::~Personaje() {
	spriteActual = NULL;
	for (size_t i=0; i < sprites.size() ; i++){
		sprites[i]->~Sprite();
	}
}

