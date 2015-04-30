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
	m_yPiso = 0;

	m_velocidad = 0;

	m_AltoMundo = 0;
	m_AnchoMundo = 0;

	m_fliped = fliped;

	m_velocidad = velocidad;

	//Es igual a SpriteActual->getAlto();
	maxAlturaDeSalto = 1.20 * getAlto();
	tiempoDeSalto = 0;
	_estaSaltando = -1;

	_estaCubriendose = false;
	_estaAgachado = false;
}


std::vector<Sprite*> Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){;
	return spriteActual;
}

void Personaje::setDimensionesMundo(float h,float w){
	m_AltoMundo = h;
	m_AnchoMundo = w;
}

int Personaje::getVida(){
	return vida;
}

void Personaje::setPosition(float x, float y){
	m_xActual = x;
	m_yActual = y;
	m_yPiso = m_yActual;
}

void Personaje::AvanzarSprite(){
	if ( (_estaAgachado and spriteActual->ultimoFrame() ) or !_estaSaltando){
		if (m_velocidadActual == 0){
			_cambiarSprite(SPRITE_INICIAL);
		} else {
			_cambiarSprite(SPRITE_CAMINAR);
		}
		_estaAgachado = false;
	}
	else if ( (_estaCubriendose) and spriteActual->ultimoFrame() ) {
		if ( !_estaAgachado ) {
			_cambiarSprite(SPRITE_INICIAL);
		} else {
			_cambiarSprite(SPRITE_AGACHAR);
			spriteActual->doLoop(true);
		}
		_estaCubriendose = false;
	}
	if ( _estaSaltando > 0){
		//Salteo en el Aire el impulso del salto diagonal
		if ( (m_velocidadActual > 0 and spriteActual->ultimoFrame()) or
			 (m_velocidadActual < 0 and spriteActual->proxFrameUltimo()) ){
			spriteActual->Advance();
		}
	}

	spriteActual->Advance();
	return;
}

void Personaje::_cambiarSprite(int SpriteAccion){
	if(_estaSaltando > 0) return;

	if (sprites[SpriteAccion] == spriteActual and SpriteAccion != SPRITE_CAMINAR) return;
	printf("CAMBIA DE SPRITE\n");
	spriteActual = sprites[SpriteAccion];
	spriteActual->doLoop(false);
	spriteActual->doReverse(false);

	if (SpriteAccion == SPRITE_CAMINAR or
		SpriteAccion == SPRITE_SALTAR_DIAGONAL){
		bool doReverse;
		if (m_velocidadActual > 0){
			doReverse = m_fliped;
		}
		else if (m_velocidadActual < 0){
			doReverse = !m_fliped;
		}
		if (SpriteAccion == SPRITE_SALTAR_DIAGONAL) spriteActual->Reset();
		spriteActual->doReverse(doReverse);
		return;
	}
	spriteActual->Reset();

}


void Personaje::Inicial(){
	if (_estaSaltando > 0) return;
	this->_cambiarSprite(SPRITE_INICIAL);
}

void Personaje::Frenar(){
	if (_estaSaltando > 0) return;
	m_velocidadActual = 0;
	Inicial();
}

void Personaje::CaminarDerecha(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose) return;
	m_velocidadActual = m_velocidad;
	this->_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::CaminarIzquierda(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose) return;
	m_velocidadActual = - m_velocidad;
	this->_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::Saltar(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose) return;
	if (m_velocidadActual){
		if (m_velocidadActual > 0){
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
	m_velocidadActual = m_velocidad;
}

void Personaje::_SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	m_velocidadActual = - m_velocidad;
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
		spriteActual->doLoop(false);
		return;
	}

	if(tiempoDeSalto == TIEMPOTOTALDESALTO and !m_velocidad){
		tiempoDeSalto = 0;
		_estaSaltando = 0;
		spriteActual->doLoop(false);
		return;
	}
}

float Personaje::_yDeSalto(float currentY, float currentT)
{
	float tiempoDeSalto = TIEMPOTOTALDESALTO;

	//Despeje de la Cuadratica dependiendo del MAX;
	float alturaMax = maxAlturaDeSalto/((tiempoDeSalto*tiempoDeSalto)/4);
	return alturaMax * currentT * (currentT - tiempoDeSalto) + m_yPiso;
}

void Personaje::Agachar(){
	if (_estaSaltando > 0 or  _estaAgachado ) return;

	_cambiarSprite(SPRITE_AGACHAR);
	_estaAgachado = true;
	spriteActual->doLoop(true);

	//Quitar Vida Prueba Barra
	this->QuitarVida(5);

}

void Personaje::Levantarse(){
	if (_estaSaltando > 0 or !_estaAgachado) return;

	spriteActual->doLoop(false);
	spriteActual->doReverse(true);
}

void Personaje::cubrirse() {
	if ( _estaCubriendose or _estaSaltando > 0 ) return;

	if ( _estaAgachado ) {
		_cubrirseAgachado();
	} else {
		_cubrirseParado();
	}
	_estaCubriendose = true;
}

void Personaje::_cubrirseAgachado() {
	// Destrabarlo
	_cambiarSprite(SPRITE_CUBRIRSE_AGACHADO);
	spriteActual->doLoop(true);
}

void Personaje::_cubrirseParado(){
	_cambiarSprite(SPRITE_CUBRIRSE);
	spriteActual->doLoop(true);
}

void Personaje::dejarDeCubrirse() {
	if ( !_estaCubriendose ) return;
	spriteActual->doLoop(true);
	spriteActual->doReverse(true);
	_estaCubriendose = false;
}

void Personaje::pinaBaja() {
	this->Frenar();
	if ( _estaAgachado ) {
		_pinaAgachado();
	}else if ( _estaSaltando > 0 )  {
		_pinaSaltando();
	} else {
		_cambiarSprite(SPRITE_PINA_BAJA);
	}
}

void Personaje::_pinaAgachado() {
	_cambiarSprite(SPRITE_PINA_AGACHADO);
}

void Personaje::pinaAlta() {
	Frenar();
	if ( _estaAgachado ) {
		_gancho();
	} else if ( _estaSaltando > 0 ) {
		_pinaSaltando();
	} else {
		_cambiarSprite(SPRITE_PINA_ALTA);
	}
}

void Personaje::_gancho() {
	//Destrabarlo
	_cambiarSprite(SPRITE_GANCHO);
}

void Personaje::_pinaSaltando() {
	_cambiarSprite(SPRITE_PINA_SALTANDO);
	spriteActual->doReverse(SPRITE_PINA_SALTANDO);
}

void Personaje::patadaBaja() {
	if ( _estaAgachado ) {
		_patadaBajaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_patadaSaltando();
	} else {
		//_cambiarSprite(SPRITE_PATADA_BAJA);
	}
}

void Personaje::_patadaBajaAgachado() {
	//Destrabarlo
	this->_cambiarSprite(SPRITE_PATADA_BAJA_AGACHADO);
}

void Personaje::patadaAlta() {
	if ( _estaAgachado ) {
		_patadaAltaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_patadaSaltando();
	} else if (m_velocidadActual < 0) {
		_patadaCircular();
	} else {
		_cambiarSprite(SPRITE_PATADA_ALTA);
	}
}

void Personaje::_patadaCircular() {
	_cambiarSprite(SPRITE_PATADA_CIRCULAR);
}

void Personaje::_patadaSaltando() {
	if ( tiempoDeSalto >= TIEMPOTOTALDESALTO/2 ){
		_cambiarSprite(SPRITE_PATADA_SALTANDO);
		spriteActual->setLoop(true);
	}
}

void Personaje::_patadaAltaAgachado() {
	//Destrabarlo
	this->_cambiarSprite(SPRITE_PATADA_ALTA_AGACHADO);
}

std::string Personaje::getNombre() {
	return nombre;
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

void Personaje::Update(int velocidadScroll){
	float renderX = m_xActual;
	if(velocidadScroll != 0)
			renderX += velocidadScroll;
		else
			renderX += m_velocidad;

		if (renderX <= (m_AnchoMundo - spriteActual->getAncho()) and renderX >= 0){
			if ( !_estaAgachado ){
				m_xActual += (velocidadScroll!=0? velocidadScroll : m_velocidadActual);
			}
	}
	if(m_xActual > m_AnchoMundo - spriteActual->getAncho()*1.3f)
			m_xActual = m_AnchoMundo - spriteActual->getAncho()*1.3f;
	else if(m_xActual < 0)
			m_xActual = 0;

	if(_estaSaltando > 0){
			_actualizarY();
	}

	else if (_estaSaltando == 0){
		m_yActual = m_yPiso;
		_estaSaltando = -1;
	}

}

void Personaje::renderizar(float x_dist_ventana, float posOtherPlayer){
	m_fliped = posOtherPlayer - getAncho() < m_xActual;
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
	if (m_velocidadActual > 0) return 1;
	else if (m_velocidadActual < 0) return -1;
	return 0;
}

float Personaje::getVelocidadDerecha(){
	return m_velocidad;
}
float Personaje::getVelocidadIzquierda(){
	return -m_velocidad;
}

Personaje::~Personaje() {
	spriteActual = NULL;
	for (size_t i=0; i < sprites.size() ; i++){
		delete sprites[i];
	}
}


