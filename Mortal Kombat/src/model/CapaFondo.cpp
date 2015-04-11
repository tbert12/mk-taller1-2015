/*
 * CapaFondo.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: root
 */

#include "CapaFondo.h"


CapaFondo::CapaFondo(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal,
		std::string ruta, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,ventana->obtenerAncho(),velocidadPrincipal) //call superclass constructor
{
	m_texture = ventana->crearTextura();
	m_texture->loadFromFile(ruta);
	rect->x = rect->x - ventana->obtenerAncho()/2;//Inicia al medio
}

void CapaFondo::_actualizarX(){
}
/*
void CapaFondo::Mover(bool right){
	if(right)
	{
		printf("xActual: %f , mueve:+ %f ",rect->x,m_velocidad);
		rect->x += m_velocidad;

	}else{
		printf("xActual: %f , mueve:- %f ",rect->x,m_velocidad);
		rect->x -=m_velocidad;
	}
	if( rect->x < 0){
		rect->x = 0;
	}
	if( rect->x > rect->w - m_ancho_ventana){
		rect->x = rect->w - m_ancho_ventana;
	}
}
*/

void CapaFondo::Renderizar(){
	//_actualizarX();
	printf("CAPA:%f x:%f \n",rect->w,rect->x);
	m_texture->renderFondo(rect);
}

CapaFondo::~CapaFondo() {
	return;
}

