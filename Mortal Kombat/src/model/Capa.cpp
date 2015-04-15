/*
 *Created by Joni
 * 28/3
 */

#include "Capa.h"

Capa::Capa(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float factorVelocidad) {
	rect = new Rect_Logico;
	rect->x = ancho*0.5f;
	rect->y = 0;
	rect->w = ancho;
	rect->h = alto;
	m_zIndex = zIndex;
	m_anchoDeFondo = anchoDeFondo;
	m_ancho_ventana = ancho_ventana;
	m_velocidad = (ancho-ancho_ventana)/(anchoDeFondo-ancho_ventana) *factorVelocidad;
}

float Capa::getX()
{
	return rect->x;
}

void Capa::Mover(bool right){
	if(right)
	{
		rect->x += m_velocidad;

	}else{
		rect->x -=m_velocidad;
	}
	if( rect->x > rect->w - m_ancho_ventana){
		rect->x = rect->w - m_ancho_ventana;
	}
	if( rect->x < 0){
		rect->x = 0;
	}
}


int Capa::getZIndex(){
	return m_zIndex;
}

void Capa::Renderizar()
{

}

Capa::~Capa(){
	delete rect;
}
