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
	m_Personaje = personajeUno;
	m_PersonajeDos = personajeDos;
	personajeUno->setDimensionesMundo(alto,ancho);
	personajeDos->setDimensionesMundo(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_Personaje->getVelocidadDerecha();
	m_velocidad_izquierda = m_Personaje->getVelocidadIzquierda();
	m_PersonajeQueScrollea = 0;
}

CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, vector<Personaje*> personajes)
:Capa(alto,ancho,zIndex, anchoDeFondo,ancho_ventana,velocidadPrincipal) //call superclass constructorPersonaje* personajeUno
{
	m_Personaje = personajes[0];
	m_PersonajeDos = personajes[1];
	personajes[0]->setDimensionesMundo(alto,ancho);
	personajes[1]->setDimensionesMundo(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_Personaje->getVelocidadDerecha();
	m_velocidad_izquierda = m_Personaje->getVelocidadIzquierda();
	m_PersonajeQueScrollea = 0;
	rectAtaqueAnterior1 = m_Personaje->rectanguloAtaque();
	rectAtaqueAnterior2 = m_PersonajeDos->rectanguloAtaque();
}

void CapaPrincipal::_actualizarX(){
	if (rect->x < 0) rect->x = 0;
	if (rect->x > rect->w) rect->x = rect->w;
}

void CapaPrincipal::Update(int scroll){
	if (scroll > 0)this->Mover(true);
	else if (scroll < 0) this->Mover(false);
	this->_actualizarX();
	Personaje* personaje;
	Personaje* personajeFlippeado;

	this->_CheckearColisiones();

	if(m_Personaje->getFlipState()){
		personaje = m_PersonajeDos;
		personajeFlippeado = m_Personaje;
	}
	else{
		personajeFlippeado = m_PersonajeDos;
		personaje = m_Personaje;
	}
	if(personaje->getX() > personajeFlippeado->getX() ){
		personaje->setFlip(true);
		personajeFlippeado->setFlip(false);
	}

	if(m_PersonajeQueScrollea==2){
		if (m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f)) {
			m_Personaje->Update(m_PersonajeDos->getVelocidadIzquierda());
		}else if (m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f) ){
			m_Personaje->Update(m_PersonajeDos->getVelocidadDerecha());
		}
		m_Personaje->Update(scroll>0? m_PersonajeDos->getVelocidadDerecha() : m_PersonajeDos->getVelocidadIzquierda());
	}else
		m_Personaje->Update(0);

	if(m_PersonajeDos){
		if(m_PersonajeQueScrollea==1){
			if (m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f)) {
				m_PersonajeDos->Update(m_Personaje->getVelocidadIzquierda());
			}else if (m_PersonajeDos->getX() <= (getX() + m_ancho_ventana*0.02f) ){
				m_PersonajeDos->Update(m_Personaje->getVelocidadDerecha());
			}
			else
				m_PersonajeDos->Update(0);
		}else{
			m_PersonajeDos->Update(0);
		}
	}

}

void CapaPrincipal::_CheckearColisiones(){

	Rect_Logico* rectAtaque1 = m_Personaje->rectanguloAtaque();
	Rect_Logico* rectDefensa1 = m_Personaje->rectanguloDefensa();

	Rect_Logico* rectAtaque2 = m_PersonajeDos->rectanguloAtaque();
	Rect_Logico* rectDefensa2 = m_PersonajeDos->rectanguloDefensa();

	//printf("actual: %f, anterior: %f, defensa: %f\n",rectAtaque1->x + rectAtaque1->w ,rectAtaqueAnterior1->x + rectAtaqueAnterior1->w,rectDefensa2->x );

	if(rectAtaque1->x + rectAtaque1->w >= rectDefensa2->x and rectAtaqueAnterior1->x + rectAtaqueAnterior1->w < rectDefensa2->x  )
		printf("hubo colision\n");

	rectAtaqueAnterior1 = rectAtaque1;
	rectAtaqueAnterior2 = rectAtaque2;
}

void CapaPrincipal::Renderizar()
{
	m_Personaje->renderizar(getX(), m_PersonajeDos->getX());
	if(m_PersonajeDos){
		m_PersonajeDos->renderizar(getX(), m_Personaje->getX());
	}
}

int CapaPrincipal::Scrollear(){
	if(getX() == 0 and (m_Personaje->getSentidoDeMovimiento() < 0))return this->CheckSegundoJugador(0);
	if(getX() == rect->w and (m_Personaje->getSentidoDeMovimiento() > 0)) return this->CheckSegundoJugador(0);
	if ((m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f)) and (m_Personaje->getSentidoDeMovimiento() < 0)) return this->CheckSegundoJugador(-1);
	if ((m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f)) and (m_Personaje->getSentidoDeMovimiento() > 0) ) return this->CheckSegundoJugador(1);
	return this->CheckSegundoJugador(0);
}

int CapaPrincipal::CheckSegundoJugador(int estadoJugador1){
	if(!m_PersonajeDos){
		if(estadoJugador1 == 1)
			m_PersonajeQueScrollea = 1;
		return estadoJugador1;
	}


	switch (estadoJugador1) {
		case 1:
			if ((m_PersonajeDos->getX() <= (getX() + m_ancho_ventana*0.02f))){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			m_PersonajeQueScrollea = 1;
			return 1;
			break;
		case -1:
			if ((m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f))){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			m_PersonajeQueScrollea = 1;
			return -1;
			break;
		default:
			if(getX() == 0 and (m_PersonajeDos->getSentidoDeMovimiento() < 0))return this->_NadieScrollea();
			if(getX() == rect->w and (m_PersonajeDos->getSentidoDeMovimiento() > 0)) return this->_NadieScrollea();
			if ((m_PersonajeDos->getX() <= (getX() + m_ancho_ventana*0.02f)) and (m_PersonajeDos->getSentidoDeMovimiento() < 0)){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			if ((m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f)) and (m_PersonajeDos->getSentidoDeMovimiento() > 0) ){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			return this->_NadieScrollea();
			break;
	}
}

int CapaPrincipal::_NadieScrollea(){
	m_PersonajeQueScrollea = 0;
	return 0;
}

CapaPrincipal::~CapaPrincipal() {
	m_velocidad_derecha = 0;
	m_velocidad_izquierda = 0;
	m_Personaje = NULL;
	if(m_PersonajeDos)
		m_PersonajeDos = NULL;
}
