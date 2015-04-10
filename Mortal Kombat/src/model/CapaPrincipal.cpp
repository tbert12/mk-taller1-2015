/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


<<<<<<< HEAD
CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal, Personaje* personaje, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal, ventana) //call superclass constructor
=======
CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personaje)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal) //call superclass constructor
>>>>>>> 85bd7a198744ff541d20009763ef9ffefbdd3060
{
	m_Personaje = personaje;
	personaje->setDimensiones(alto,ancho);
	m_ancho_ventana = ancho_ventana;
	_actualizarX();
}

void CapaPrincipal::_actualizarX(){
	m_XActual = m_Personaje->getX() - m_ancho_ventana/2;
	if (m_XActual < 0) m_XActual = 0;
	if (m_XActual > m_ancho) m_XActual = m_ancho;
}

void CapaPrincipal::Renderizar()
{
	_actualizarX();
	m_Personaje->renderizar(getX());
}

int CapaPrincipal::Scrollear(){
	if (m_Personaje->getX() <= (getX() + m_ancho_ventana*0.1f)) return -1;
	if (m_Personaje->getX() >= (getX() + m_ancho_ventana*0.9f)) return 1;
	return 0;
}

CapaPrincipal::~CapaPrincipal() {
	// TODO Auto-generated destructor stub
}
