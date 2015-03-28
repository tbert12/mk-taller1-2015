/*
 *Created by Joni
 * 28/3
 */

#include "Capa.h"

Capa::Capa(int alto, int ancho, int zIndex, int anchoDeFondo, int velocidadPrincipal) {
	// TODO Auto-generated constructor stub
	m_alto = alto;
	m_ancho = ancho;
	m_zIndex = zIndex;
	m_velocidad = ancho/anchoDeFondo * velocidadPrincipal;
	m_XActual = anchoDeFondo *.5f - ancho * .5f;
}


void Capa::Mover(int posX){
	if(posX > m_XActual)
		m_XActual += m_velocidad;
	m_XActual -= m_velocidad;
}

int Capa::getZIndex(){
	return m_zIndex;
}
