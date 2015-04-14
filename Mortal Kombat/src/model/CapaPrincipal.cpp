/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personaje)
:Capa(alto,ancho,zIndex, anchoDeFondo,ancho_ventana,velocidadPrincipal) //call superclass constructor
{
	m_Personaje = personaje;
	personaje->setDimensiones(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_Personaje->getVelocidadDerecha();
	m_velocidad_izquierda = m_Personaje->getVelocidadIzquierda();
	//m_velocidad = m_velocidad_derecha;
}

void CapaPrincipal::_actualizarX(){
	if (rect->x < 0) rect->x = 0;
	if (rect->x > rect->w) rect->x = rect->w;
}

void CapaPrincipal::Renderizar()
{
	_actualizarX();
	m_Personaje->renderizar(getX());
}

int CapaPrincipal::Scrollear(){
	if(getX() == 0 and (m_Personaje->getSentidoDeMovimiento() < 0))return 0;
	if(getX() == rect->w and (m_Personaje->getSentidoDeMovimiento() > 0)) return 0;
	if ((m_Personaje->getX() <= (getX() + m_ancho_ventana*0.05f)) and (m_Personaje->getSentidoDeMovimiento() < 0)) return -1;
	if ((m_Personaje->getX() >= (getX() + m_ancho_ventana*0.85f)) and (m_Personaje->getSentidoDeMovimiento() > 0) ) return 1;
	return 0;
}

CapaPrincipal::~CapaPrincipal() {
	//this->Capa::~Capa();
}
