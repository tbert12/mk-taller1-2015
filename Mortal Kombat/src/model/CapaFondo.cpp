/*
 * CapaFondo.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: root
 */

#include "CapaFondo.h"


CapaFondo::CapaFondo(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal,
		std::string ruta, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal) //call superclass constructor
{
	m_texture = new LTexture(ventana->getRenderer());
	m_texture->loadFromFile(ruta);
	m_clip = new SDL_Rect();
	m_clip->h = alto;
	m_clip->w = ventana->obtenerAncho();
	m_clip->x = (ancho - m_clip->w) *5;
	m_clip->y = 0;
}

void CapaFondo::Mover(int posX)
{
	Capa::Mover(posX);
	m_clip->x = this->getX();
}

void CapaFondo::Renderizar(){
	m_texture->render(0,0, m_clip);
}

CapaFondo::~CapaFondo() {

}

