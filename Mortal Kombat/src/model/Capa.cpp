/*
 *Created by Joni
 * 28/3
 */

#include "Capa.h"

Capa::Capa(float alto, float ancho, int zIndex, float anchoDeFondo, float factorVelocidad, Ventana* ventana) {
	m_alto = alto;
	m_ancho = ancho;
	m_zIndex = zIndex;
	m_anchoDeFondo = anchoDeFondo;
	m_velocidad = (m_ancho/m_anchoDeFondo)*factorVelocidad;
	m_XActual = m_ancho*0.5f;
	m_anchoDeVentana = 8.0f;
}

int Capa::getX()
{
	return m_XActual;
}

void Capa::Mover(bool right){

	if(right > true)
	{
		printf("xActual: %f , mueve:+ %f ",m_XActual,m_velocidad);
		m_XActual += m_velocidad;

	}else{
		printf("xActual: %f , mueve:- %f ",m_XActual,m_velocidad);
		m_XActual -=m_velocidad;
	}
	if( m_XActual <= 0){
		m_XActual = 0;
	}
	if( m_XActual > m_ancho){
		m_XActual =m_ancho;
	}
}


int Capa::getZIndex(){
	return m_zIndex;
}

void Capa::Renderizar()
{

}

