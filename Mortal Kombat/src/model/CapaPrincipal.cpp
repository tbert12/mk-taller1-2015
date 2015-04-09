/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal, Personaje* personaje, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal, ventana) //call superclass constructor
{
	m_Personaje = personaje;
}

void CapaPrincipal::Renderizar()
{
	if( Scrollear())
	{
		m_Personaje->SetScroll(true);
		Mover(m_Personaje->getSentidoDeMovimiento());
	}
	m_Personaje->renderizar(getX());
}

bool CapaPrincipal::Scrollear(){
	return m_Personaje->getX() >= m_ancho* 0.9f || m_Personaje->getX() <= m_ancho* 0.1f;
}

CapaPrincipal::~CapaPrincipal() {
	// TODO Auto-generated destructor stub
}

