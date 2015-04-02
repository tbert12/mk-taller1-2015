/*
 *Created by Joni
 * 28/3
 */

#include "Capa.h"

Capa::Capa(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal) {
	// TODO Auto-generated constructor stub
	m_alto = alto;
	m_ancho = ancho;
	m_zIndex = zIndex;
	m_anchoDeFondo = anchoDeFondo;
	m_velocidad = velocidadPrincipal;
	m_XActual = anchoDeFondo *.5f - ancho * .5f;
}

void Capa::Mover(int posX){

	if(posX > m_XActual)
	{
		if( m_XActual+m_ancho >= m_anchoDeFondo)
		{
			m_XActual = m_anchoDeFondo - m_ancho;
			return;
		}
		m_XActual += m_velocidad;
		return;
	}
	if( m_XActual <= 0)
	{
		m_XActual = 0;
		return;
	}
	m_XActual -= m_velocidad;
}



int Capa::getZIndex(){
	return m_zIndex;
}
