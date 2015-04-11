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
	m_ancho_ventana = ancho_ventana;
	_actualizarX();
}

void CapaPrincipal::_actualizarX(){
	//m_XActual = m_Personaje->getX() - m_ancho_ventana/2;

	if (m_XActual < 0) m_XActual = 0;
	if (m_XActual > m_ancho) m_XActual = m_ancho;
	if (rect->x < 0) rect->x = 0;
	if (rect->x > rect->w) rect->x = rect->w;
}

void CapaPrincipal::Renderizar()
{
	_actualizarX();
	m_Personaje->renderizar();
}

int CapaPrincipal::Scrollear(){

	if (m_Personaje->getX() <= (getX() + m_ancho_ventana*0.05f)){
		printf("ESTA SCROLLEANDO IZQUIERDA\n");
		return -1;
	}
	if (m_Personaje->getX() >= (getX() + m_ancho_ventana*0.85f)){
		printf("ESTA SCROLLEANDO Derecha\n");
		return 1;
	}
	//printf("NoScrollea\n");
	printf("xPers:%f , x:%f , ancho:%f \n",m_Personaje->getX(),getX(),rect->w);
	if(getX() == 0 and (m_Personaje->getSentidoDeMovimiento() < 0))return 0;
	if(getX() == rect->w and (m_Personaje->getSentidoDeMovimiento() > 0)) return 0;
	if ((m_Personaje->getX() <= (getX() + m_ancho_ventana*0.1f)) and (m_Personaje->getSentidoDeMovimiento() < 0)) return -1;
	if ((m_Personaje->getX() >= (getX() + m_ancho_ventana*0.4f)) and (m_Personaje->getSentidoDeMovimiento() > 0) ) return 1;
	return 0;
}

/*
void CapaPrincipal::Mover(bool right){
	printf("\n\n\nMUCHAA CAAAACAAA\n\n\n");
	if(right)
	{
		printf("xActual: %f , mueve:+ %f ",rect->x,m_velocidad);
		rect->x += m_Personaje->getVelocidadDerecha();

	}else{
		printf("xActual: %f , mueve:- %f ",rect->x,m_velocidad);
		rect->x -= m_Personaje->getVelocidadIzquierda();
	}
	if( rect->x < 0){
		rect->x = 0;
	}
	if( rect->x > rect->w - m_ancho_ventana){
		rect->x = rect->w - m_ancho_ventana;
	}
}
*/

CapaPrincipal::~CapaPrincipal() {
	// TODO Auto-generated destructor stub
}

