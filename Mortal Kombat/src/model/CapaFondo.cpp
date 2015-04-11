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

void CapaFondo::Renderizar(){
	m_texture->renderFondo(rect);
}

CapaFondo::~CapaFondo() {
	return;
}
