/*
 * CapaFondo.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: root
 */

#include "CapaFondo.h"


CapaFondo::CapaFondo(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal,
		std::string ruta, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal) //call superclass constructor
{
	m_texture = ventana->crearTextura();
	m_texture->loadFromFile(ruta);
	m_clip = new SDL_Rect();
	m_ventana_ancho = ventana->obtenerAncho();
	m_clip->h = alto;
	m_clip->w = ancho;//ventana->obtenerAncho();
	m_clip->x = getX(); //La mitad de la capa al centro de la ventana
	m_clip->y = 0;
}

void CapaFondo::Mover(bool right)
{
	Capa::Mover(right);
	m_clip->x = this->getX();
}

void CapaFondo::Renderizar(){
	m_texture->renderFondo(m_clip);
}

CapaFondo::~CapaFondo() {

}

