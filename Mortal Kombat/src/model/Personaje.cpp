/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad, bool fliped) {
	nombre = nombre_personaje;
	vida = 100;

	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];


	m_xActual = 0;
	m_yActual = 0;

	m_xInicial = 0;
	m_yInicial = 0;

	m_velocidad = 0;

	m_AltoMundo = 0;
	m_AnchoMundo = 0;

	m_fliped = fliped;

	velocidadAdelante = velocidad;
	velocidadAtras = -velocidad;

	//Es igual a SpriteActual->getAlto();
	maxAlturaDeSalto = 1.10*getAlto();

	tiempoDeSalto = 0;
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

float Personaje::getVida(){
	return vida;
}

void Personaje::setPosition(float x, float y){
	m_xActual = x;
	m_xInicial = x;
	m_yActual = y;
	m_yInicial = m_yActual;
}

void Personaje::AvanzarSprite(){
	if ( (_estaAgachado() and spriteActual->ultimoFrame() ) or !_estaSaltando){
		if (m_velocidad == 0){
			_cambiarSprite(SPRITE_INICIAL);
		} else {
			_cambiarSprite(SPRITE_CAMINAR);
		}

	}
	spriteActual->Advance();
	return;
}

void Personaje::_cambiarSprite(int SpriteAccion){
	if(_estaSaltando > 0) return;

	if (sprites[SpriteAccion] == spriteActual) return;

	spriteActual = sprites[SpriteAccion];
	spriteActual->doLoop(false);
	spriteActual->doReverse(false);

	if (SpriteAccion == SPRITE_CAMINAR or
		SpriteAccion == SPRITE_SALTAR_DIAGONAL){

		bool doReverse;
		if (m_velocidad > 0){
			doReverse = m_fliped;
		}
		else if (m_velocidad < 0){
			doReverse = !m_fliped;
		}
		spriteActual->doReverse(doReverse);
		return;
	}
	spriteActual->Reset();

}

void Personaje::Inicial(){
	if (_estaSaltando > 0) return;
	this->_cambiarSprite(SPRITE_INICIAL);
	m_velocidad = 0;
}

void Personaje::Frenar(){
	if (_estaSaltando > 0) return;
	m_velocidad = 0;
}

void Personaje::CaminarDerecha(){
	if (_estaSaltando > 0) return;
	m_velocidad = velocidadAdelante;
	this->_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::CaminarIzquierda(){
	if (_estaSaltando > 0) return;
	m_velocidad = velocidadAtras;
	this->_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::Saltar(){
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
	this->_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	m_velocidad = velocidadAdelante;
}

void Personaje::_SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	m_velocidad = -velocidadAdelante;
}

void Personaje::_SaltarHorizontal(){
	this->_cambiarSprite(SPRITE_SALTAR);
	spriteActual->doLoop(true);
	_estaSaltando = 1;
}

//Funciones Logicas de Salto
void Personaje::_actualizarY(){
	//Si esta Saltanto va actualizando
	if(_estaSaltando > 0){
		m_yActual = _yDeSalto(m_yActual,tiempoDeSalto);
		tiempoDeSalto++;
	}

	//Cuando esta llegando al piso, vuelvo a las condiciones iniciales
	if(tiempoDeSalto > TIEMPOTOTALDESALTO){
		tiempoDeSalto = 0;
		_estaSaltando = 0;
		if (m_velocidad) {
			//Voy al tercero para visualizar la caida
			_cambiarSprite(SPRITE_SALTAR);
			spriteActual->Advance();
			spriteActual->Advance();
		}
		m_velocidad = 0;
		spriteActual->doLoop(false);
		return;
	}

	if(tiempoDeSalto == TIEMPOTOTALDESALTO and !m_velocidad){
		tiempoDeSalto = 0;
		_estaSaltando = 0;
		m_velocidad = 0;
		spriteActual->doLoop(false);
		return;
	}
}

float Personaje::_yDeSalto(float currentY, float currentT)
{
	float tiempoDeSalto = TIEMPOTOTALDESALTO;

	//Despeje de la Cuadratica dependiendo del MAX;
	float alturaMax = maxAlturaDeSalto/((tiempoDeSalto*tiempoDeSalto)/4);
	return alturaMax * currentT * (currentT - tiempoDeSalto) + m_yInicial;
}

void Personaje::Agachar(){
	if (_estaAgachado()) return;
	if (_estaSaltando > 0) return;
	_cambiarSprite(SPRITE_AGACHAR);
	spriteActual->doLoop(true);
}

void Personaje::Levantarse(){
	if (_estaSaltando > 0) return;
	//Destrabarlo
	spriteActual->doLoop(false);
	//Reproducir levantarse
	spriteActual->doReverse(true);
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

bool Personaje::_estaAgachado(){
	return (spriteActual == sprites[SPRITE_AGACHAR]);
}

void Personaje::Update(){
	float renderX = m_xActual + m_velocidad;
	if (renderX <= (m_AnchoMundo - spriteActual->getAncho()) and renderX >= 0){
		if ( !_estaAgachado() ) m_xActual += m_velocidad;
	}
	if(_estaSaltando > 0){
			_actualizarY();
	}
	else if (_estaSaltando == 0){
		m_yActual = m_yInicial;
		_estaSaltando = -1;
	}
}

void Personaje::renderizar(float x_dist_ventana){
	Update();
	spriteActual->render(m_xActual-x_dist_ventana,m_yActual,m_fliped);
	AvanzarSprite();

}

bool Personaje::enMovimiento(){
	return (m_velocidad != 0);
}

float Personaje::getAncho(){
	return spriteActual->getAncho();
}

float Personaje::getAlto(){
	return spriteActual->getAlto();
}

int Personaje::getSentidoDeMovimiento(){
	if (m_velocidad > 0) return 1;
	else if (m_velocidad < 0) return -1;
	return 0;
}

float Personaje::getVelocidadDerecha(){
	return velocidadAdelante;
}
float Personaje::getVelocidadIzquierda(){
	return velocidadAtras;
}

Personaje::~Personaje() {
	spriteActual = NULL;
	for (size_t i=0; i < sprites.size() ; i++){
		delete sprites[i];
	}
}


