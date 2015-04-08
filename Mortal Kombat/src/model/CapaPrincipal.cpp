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
<<<<<<< HEAD
		printf("Is Scrolling \n");
		m_Personaje->SetScroll(true);
=======
>>>>>>> 8e4a72c2d00d10bb4b6c63c8b414a43d83ea2744
		Mover(m_Personaje->getSentidoDeMovimiento());
	}
	m_Personaje->renderizar();
}

bool CapaPrincipal::Scrollear(){
<<<<<<< HEAD
=======
	int x = m_Personaje->getX();
>>>>>>> 8e4a72c2d00d10bb4b6c63c8b414a43d83ea2744
	return m_Personaje->getX() >= m_ancho* 0.9f || m_Personaje->getX() <= m_ancho* 0.1f;
}

CapaPrincipal::~CapaPrincipal() {
	// TODO Auto-generated destructor stub
}

