/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personajeUno, Personaje* personajeDos)
:Capa(alto,ancho,zIndex, anchoDeFondo,ancho_ventana,velocidadPrincipal) //call superclass constructorPersonaje* personajeUno
{
	m_PersonajeUno = personajeUno;
	m_PersonajeDos = personajeDos;
	personajeUno->setDimensionesMundo(alto,ancho);
	personajeDos->setDimensionesMundo(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_PersonajeUno->getVelocidadDerecha();
	m_velocidad_izquierda = m_PersonajeUno->getVelocidadIzquierda();
	m_PersonajeQueScrollea = 0;
	rectAtaqueAnterior2 = NULL;
	rectAtaqueAnterior1 = NULL;
	m_personajeConFlip = NULL;
	m_personajeSinFlip = NULL;
	_scroll = 0;
}

CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, vector<Personaje*> personajes)
:Capa(alto,ancho,zIndex, anchoDeFondo,ancho_ventana,velocidadPrincipal) //call superclass constructorPersonaje* personajeUno
{
	m_PersonajeUno = personajes[0];
	m_PersonajeDos = personajes[1];
	personajes[0]->setDimensionesMundo(alto,ancho);
	personajes[1]->setDimensionesMundo(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_PersonajeUno->getVelocidadDerecha();
	m_velocidad_izquierda = m_PersonajeUno->getVelocidadIzquierda();
	m_PersonajeQueScrollea = 0;
	rectAtaqueAnterior1 = m_PersonajeUno->rectanguloAtaque();
	rectAtaqueAnterior2 = m_PersonajeDos->rectanguloAtaque();
	m_personajeSinFlip = m_PersonajeUno;
	m_personajeConFlip = m_PersonajeDos;
	_scroll = 0;
}

void CapaPrincipal::_actualizarX(){
	if (rect->x < 0) rect->x = 0;
	if (rect->x > rect->w) rect->x = rect->w;
}

void CapaPrincipal::Update(int scroll){
	if (scroll > 0)this->Mover(true);
	else if (scroll < 0) this->Mover(false);
	this->_actualizarX();

	_scroll = scroll;
}


int CapaPrincipal::CheckearColisiones(){
	Personaje* personaje;
	Personaje* personajeFlippeado;

	if(m_PersonajeUno->getFlipState()){
		personaje = m_PersonajeDos;
		personajeFlippeado = m_PersonajeUno;
	}else{
		personajeFlippeado = m_PersonajeDos;
		personaje = m_PersonajeUno;
	}

	if(personaje->getX() + personaje->getAncho()*.5f > personajeFlippeado->getX() - personajeFlippeado->getAncho()*.5f){
		personaje->setFlip(true);
		personajeFlippeado->setFlip(false);
	}

	m_personajeSinFlip = personaje;
	m_personajeConFlip = personajeFlippeado;

	this->_ChequearSiSePisan();

	int toReturn = this->_CheckearColisiones(personaje,personajeFlippeado);

	_LateUpdate();

	return toReturn;
}

void CapaPrincipal::_LateUpdate(){
	if(m_PersonajeQueScrollea == this->_getIdDePersonaje(m_personajeConFlip) ){
		if (m_personajeSinFlip->getX() >= (getX() + m_ancho_ventana*0.80f)) {
			m_personajeSinFlip->Update(m_personajeConFlip->getX() + m_personajeConFlip->getVelocidadIzquierda());
		}else if (m_personajeSinFlip->getX() <= (getX() + m_ancho_ventana*0.02f) ){
			m_personajeSinFlip->Update( m_personajeConFlip->getX() + m_personajeConFlip->getVelocidadDerecha());
		}
		m_personajeSinFlip->Update(m_personajeConFlip->getX() + _scroll>0? m_personajeConFlip->getVelocidadDerecha() : m_personajeConFlip->getVelocidadIzquierda());
	}else
		m_personajeSinFlip->Update(m_personajeConFlip->getX());

	if(m_PersonajeQueScrollea == this->_getIdDePersonaje(m_personajeSinFlip)){
		if (m_personajeConFlip->getX() >= (getX() + m_ancho_ventana*0.80f)) {
			m_personajeConFlip->Update(m_personajeSinFlip->getX() + m_personajeSinFlip->getVelocidadIzquierda());
		}else if (m_personajeConFlip->getX() <= (getX() + m_ancho_ventana*0.02f) ){
			m_personajeConFlip->Update(m_personajeSinFlip->getX() + m_personajeSinFlip->getVelocidadDerecha());
		}
		else
			m_personajeConFlip->Update(m_personajeSinFlip->getX());
	}else{
		m_personajeConFlip->Update(m_personajeSinFlip->getX());
	}
}

bool floatIsBetween(float x, float border1, float deltaX){
	return x>=border1 and x<= border1+deltaX;
}

void CapaPrincipal::_ChequearSiSePisan(){

	bool hayAlguienSaltando = false;
	Personaje* personajeSaltando;
	Personaje* personajeEnElSuelo;


	if(m_personajeSinFlip->estaSaltando() and m_personajeConFlip->estaSaltando()){
		hayAlguienSaltando= false;
	}else if(m_personajeSinFlip->estaSaltando()){
		hayAlguienSaltando= true;
		personajeSaltando = m_personajeSinFlip;
		personajeEnElSuelo= m_personajeConFlip;
	}else if(m_personajeConFlip->estaSaltando()){
		hayAlguienSaltando= true;
		personajeSaltando = m_personajeConFlip;
		personajeEnElSuelo= m_personajeSinFlip;
	}

	Rect_Logico* rectDefensa1 = m_personajeSinFlip->rectanguloDefensa();
	Rect_Logico* rectDefensa2 = m_personajeConFlip->rectanguloDefensa();

	bool colisionaDefensaPersonajesX = (floatIsBetween(rectDefensa2->x ,rectDefensa1->x,rectDefensa1->w*1.5f));
	bool sePisanX = (floatIsBetween(rectDefensa2->x ,rectDefensa1->x,rectDefensa1->w));
	//bool colisionaDefensaPersonajesX = false;
	if(colisionaDefensaPersonajesX){
		if(hayAlguienSaltando){
			personajeSaltando->Update(personajeEnElSuelo->getX(),true);//lo hago dos veces para que se mueva el doble
			personajeSaltando->Update(personajeEnElSuelo->getX(),true);//porque el update a algo quito no lo mueve
			return;
		}
		if(m_personajeSinFlip->getSentidoDeMovimiento()>0)
			m_personajeSinFlip->Frenar();
		if(m_personajeConFlip->getSentidoDeMovimiento()<0)
			m_personajeConFlip->Frenar();
		if(sePisanX){
			if(!(rectDefensa1->x+ rectDefensa1->w*.5f >= rectDefensa2->x - rectDefensa2->w*.5f)){
				m_personajeSinFlip->setPositionX(m_personajeSinFlip->getX()+m_personajeSinFlip->getAncho()*.05f);
				m_personajeConFlip->setPositionX(m_personajeConFlip->getX()-m_personajeConFlip->getAncho()*.05f);
			}else{
				m_personajeSinFlip->setPositionX(m_personajeSinFlip->getX()-m_personajeSinFlip->getAncho()*.05f);
				m_personajeConFlip->setPositionX(m_personajeConFlip->getX()+m_personajeConFlip->getAncho()*.05f);
			}
		}
	}
}


int CapaPrincipal::_CheckearColisiones(Personaje* personaje, Personaje* personajeFlippeado){
	Rect_Logico* rectAtaque1 = personaje->rectanguloAtaque();
	Rect_Logico* rectDefensa1 = personaje->rectanguloDefensa();

	Rect_Logico* rectAtaque2 = personajeFlippeado->rectanguloAtaque();
	Rect_Logico* rectDefensa2 = personajeFlippeado->rectanguloDefensa();

	if (rectAtaque1 != NULL ){

		if(!rectAtaqueAnterior1){
			rectAtaqueAnterior1 = rectDefensa1;
		}

		bool antesColisionaX = floatIsBetween(rectDefensa2->x ,rectAtaqueAnterior1->x,rectAtaqueAnterior1->w);
		bool ahoraColisionaX = floatIsBetween(rectDefensa2->x ,rectAtaque1->x,rectAtaque1->w);
		bool antesColisionaY = floatIsBetween(rectDefensa2->y, rectAtaqueAnterior1->y-rectAtaqueAnterior1->h, rectAtaqueAnterior1->h) or floatIsBetween(rectAtaqueAnterior1->y, rectDefensa2->y-rectDefensa2->h, rectDefensa2->h);
		bool ahoraColisionaY = floatIsBetween(rectDefensa2->y, rectAtaque1->y-rectAtaque1->h , rectAtaque1->h) or floatIsBetween(rectAtaque1->y, rectDefensa2->y-rectDefensa2->h , rectDefensa2->h);

		bool posibilidad1 = (ahoraColisionaX and not antesColisionaX)and ( antesColisionaY and ahoraColisionaY );
		bool posibilidad2 = (ahoraColisionaX and antesColisionaX)and ( not antesColisionaY and ahoraColisionaY );
		bool colision = posibilidad1 or posibilidad2;

		if( colision){
			return COLISION_PERSONAJE_PERSONAJE_SIN_FLIP;
		}

	}else if (rectAtaque2 != NULL ){
		if(!rectAtaqueAnterior2){
			rectAtaqueAnterior2 = rectDefensa2;
		}

		bool antesColisionaX = floatIsBetween(rectDefensa1->x + rectDefensa1->w, rectAtaqueAnterior2->x, rectAtaqueAnterior2->w);
		bool ahoraColisionaX = floatIsBetween(rectDefensa1->x  + rectDefensa1->w, rectAtaque2->x , rectAtaque2->w);
		bool antesColisionaY = floatIsBetween(rectDefensa1->y, rectAtaqueAnterior2->y-rectAtaqueAnterior2->h, rectAtaqueAnterior2->h) or floatIsBetween(rectAtaqueAnterior2->y, rectDefensa1->y-rectDefensa1->h, rectDefensa1->h);
		bool ahoraColisionaY = floatIsBetween(rectDefensa1->y, rectAtaque2->y-rectAtaque2->h , rectAtaque2->h) or floatIsBetween(rectAtaque2->y, rectDefensa1->y-rectDefensa1->h , rectDefensa1->h);

		bool posibilidad1 = (ahoraColisionaX and not antesColisionaX)and ( antesColisionaY and ahoraColisionaY );
		bool posibilidad2 = (ahoraColisionaX and antesColisionaX)and ( not antesColisionaY and ahoraColisionaY );
		bool colision = posibilidad1 or posibilidad2;

		if(colision){
			return COLISION_PERSONAJE_PERSONAJE_CON_FLIP;
		}
	}

	rectAtaqueAnterior1 = rectAtaque1;
	rectAtaqueAnterior2 = rectAtaque2;

	ObjetoArrojable* objetoSinFlip = personaje->getPoderActivo();
	ObjetoArrojable* objetoConFlip = personajeFlippeado->getPoderActivo();

	if (objetoSinFlip == NULL and objetoConFlip == NULL )
		return COLISION_NO_COLISION;

	if (objetoSinFlip != NULL and objetoConFlip != NULL ){

		Rect_Logico* rectPoderSinFlip = objetoSinFlip->rectanguloAtaque();
		Rect_Logico* rectPoderConFlip = objetoConFlip->rectanguloAtaque();
		if(rectPoderSinFlip->x>=rectPoderConFlip->x){
			return COLISION_OBJETO_OBJETO;
		}
	}

	if (objetoSinFlip != NULL){
		Rect_Logico* rectPoder = objetoSinFlip->rectanguloAtaque();
		if(rectPoder == NULL){
			return COLISION_NO_COLISION;
		}

		bool colisionaAtaquePersonajeSinFlipX = rectDefensa2->x - rectDefensa2->w < rectPoder->x + objetoSinFlip->getVelocidadX() +rectPoder->w
				and not(rectDefensa2->x < rectPoder->x);

		bool colisionaY = (floatIsBetween(rectDefensa2->y, rectPoder->y-rectPoder->h , rectPoder->h) and floatIsBetween(rectDefensa2->y, rectPoder->y-rectPoder->h, rectPoder->h)) or
				(floatIsBetween(rectPoder->y, rectDefensa2->y-rectDefensa2->h , rectDefensa2->h) and floatIsBetween(rectPoder->y, rectDefensa2->y-rectDefensa2->h, rectDefensa2->h));

		if( colisionaAtaquePersonajeSinFlipX and colisionaY){
			return COLISION_PERSONAJE_OBJETO_SIN_FLIP;
		}
	}

	if (objetoConFlip != NULL ){

		Rect_Logico* rectPoder = objetoConFlip->rectanguloAtaque();

		if(rectPoder == NULL or rectPoder->x + rectPoder->w < rectDefensa1->x )
			return COLISION_NO_COLISION;

		bool colisionaAtaquePersonajeConFlipX = rectDefensa1->x + rectDefensa1->w > rectPoder->x - objetoConFlip->getVelocidadX()
				and	not(rectDefensa1->x > rectPoder->x + rectPoder->w );

		bool colisionaY = (floatIsBetween(rectDefensa1->y, rectPoder->y-rectPoder->h , rectPoder->h) and floatIsBetween(rectDefensa1->y, rectPoder->y-rectPoder->h, rectPoder->h)) or
				(floatIsBetween(rectPoder->y, rectDefensa1->y-rectDefensa1->h , rectDefensa2->h) and floatIsBetween(rectPoder->y, rectDefensa1->y-rectDefensa1->h, rectDefensa1->h));

		if( colisionaAtaquePersonajeConFlipX and colisionaY){
			return COLISION_PERSONAJE_OBJETO_CON_FLIP;
		}
	}
	return COLISION_NO_COLISION;
}

Personaje* CapaPrincipal::getPersonajSinFlip(){
	return m_personajeSinFlip;
}

Personaje* CapaPrincipal::getPersonajConFlip(){
	return m_personajeConFlip;
}


void CapaPrincipal::Renderizar()
{
	m_PersonajeUno->renderizar(getX(), m_PersonajeDos->getX());
	if(m_PersonajeDos){
		m_PersonajeDos->renderizar(getX(), m_PersonajeUno->getX());
	}
}

int CapaPrincipal::Scrollear(){
	if(getX() == 0 and (m_personajeSinFlip->getSentidoDeMovimiento() < 0))return this->CheckSegundoJugador(0);
	if(getX() == (rect->w - m_ancho_ventana) and (m_personajeSinFlip->getSentidoDeMovimiento() > 0)) return this->CheckSegundoJugador(0);
	if ((m_personajeSinFlip->getX() <= (getX() + m_ancho_ventana*0.02f)) and !(m_personajeSinFlip->getSentidoDeMovimiento() < 0)) return this->CheckSegundoJugador(0);
	if ((m_personajeSinFlip->getX() >= (getX() + m_ancho_ventana*0.90f)) and !(m_personajeSinFlip->getSentidoDeMovimiento() > 0) ) return this->CheckSegundoJugador(0);
	if ((m_personajeSinFlip->getX() <= (getX() + m_ancho_ventana*0.02f)) and (m_personajeSinFlip->getSentidoDeMovimiento() < 0)) return this->CheckSegundoJugador(-1);
	if ((m_personajeSinFlip->getX() + m_personajeSinFlip->getAncho() >= (getX() + m_ancho_ventana*0.96f)) and (m_personajeSinFlip->getSentidoDeMovimiento() > 0) ) return this->CheckSegundoJugador(1);
	return this->CheckSegundoJugador(0);
}

int CapaPrincipal::CheckSegundoJugador(int estadoJugador1){
	if(!m_personajeConFlip){
		if(estadoJugador1 == 1)
			m_PersonajeQueScrollea = 1;
		return estadoJugador1;
	}

	switch (estadoJugador1) {
		case 1:
			if ((m_personajeConFlip->getX() <= (getX() + m_ancho_ventana*0.01f))){
				m_personajeSinFlip->setScroll(false);
				m_personajeConFlip->setScroll(false);
				return 0;
			}
			m_PersonajeQueScrollea = _getIdDePersonaje(m_personajeSinFlip);
			return 1;
			break;
		case -1:
			if ((m_personajeConFlip->getX() >= (getX() + m_ancho_ventana*0.98f)) and !(m_personajeConFlip->getSentidoDeMovimiento() < 0) ){
				m_personajeSinFlip->setScroll(false);
				m_personajeConFlip->setScroll(false);
				return 0;
			}
			m_PersonajeQueScrollea = _getIdDePersonaje(m_personajeSinFlip);
			return -1;
			break;
		default:
			if(getX() == 0 and (m_personajeConFlip->getSentidoDeMovimiento() < 0))return this->_NadieScrollea();
			if(getX() == (rect->w-m_ancho_ventana) and (m_personajeConFlip->getSentidoDeMovimiento() > 0) and (m_personajeConFlip->getX() >= (getX() + m_ancho_ventana*0.97f)) ) return this->_NadieScrollea();
			if ((m_personajeConFlip->getX() - m_personajeConFlip->getAncho()<= (getX() + m_ancho_ventana*0.02f)) and (m_personajeConFlip->getSentidoDeMovimiento() < 0)){
				if ((m_personajeSinFlip->getX() >= (getX() + m_ancho_ventana*0.97f))){
					m_personajeSinFlip->setScroll(false);
					m_personajeConFlip->setScroll(false);
					return 0;
				}
				m_PersonajeQueScrollea = _getIdDePersonaje(m_personajeConFlip);
				return -1;
			}
			if ((m_personajeConFlip->getX() >= (getX() + m_ancho_ventana*0.97f)) and (m_personajeConFlip->getSentidoDeMovimiento() > 0) ){
				if ((m_personajeSinFlip->getX() <= (getX() + m_ancho_ventana*0.02f))){
					m_personajeSinFlip->setScroll(false);
					m_personajeConFlip->setScroll(false);
					return 0;
				}
				m_PersonajeQueScrollea = _getIdDePersonaje(m_personajeConFlip);
				return 1;
			}
			return this->_NadieScrollea();
			break;
	}
}

int CapaPrincipal::_getIdDePersonaje(Personaje* personaje_a_ver){
	if(personaje_a_ver == m_PersonajeUno)
		return 1;
	return 2;

}


int CapaPrincipal::_NadieScrollea(){
	m_PersonajeQueScrollea = 0;
	return 0;
}

CapaPrincipal::~CapaPrincipal() {
	m_velocidad_derecha = 0;
	m_velocidad_izquierda = 0;
	m_PersonajeUno = NULL;
	if(m_PersonajeDos)
		m_PersonajeDos = NULL;
}
