/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


CapaPrincipal::CapaPrincipal(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal, Personaje* personaje)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal) //call superclass constructor
{
	m_Personaje = personaje;
}

void CapaPrincipal::Renderizar()
{
	if( Scrollear())
	{
		Mover(m_Personaje->getSentidoDeMovimiento());
		return;
	}
	m_Personaje->renderizar();
}

bool CapaPrincipal::Scrollear(){
	int x = m_Personaje->getX();
	return m_Personaje->getX() >= m_ancho* 0.9f || m_Personaje->getX() <= m_ancho* 0.1f;
}

CapaPrincipal::~CapaPrincipal() {
	// TODO Auto-generated destructor stub
}

