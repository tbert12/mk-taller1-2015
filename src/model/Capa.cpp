/*
 *Created by Joni
 * 28/3
 */

#include "Capa.h"

Capa::Capa(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana) {
	rect = new Rect_Logico;
	rect->x = ancho*0.5f;
	rect->y = 0;
	rect->w = ancho;
	rect->h = alto;
	m_zIndex = zIndex;
	m_anchoDeFondo = anchoDeFondo;
	m_ancho_ventana = ancho_ventana;
	m_velocidad_a_multiplicar = (ancho-ancho_ventana)/(anchoDeFondo-ancho_ventana);
}

float Capa::getX()
{
	return rect->x;
}

void Capa::Mover(bool right, float factorVelocidad){
	float velocidad = m_velocidad_a_multiplicar * factorVelocidad;
	if(right)
	{
		rect->x += velocidad;

	}else{
		rect->x -=velocidad;
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
void Capa::Update(int scroll,float velocidad){

}

void Capa::reset(){

}

void Capa::Renderizar()
{

}

Capa::~Capa(){
	delete rect;
}
