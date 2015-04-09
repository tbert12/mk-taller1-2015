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
	m_texture = ventana->crearTextura();
	m_texture->loadFromFile(ruta);
	m_clip = new SDL_Rect();
	m_clip->h = alto;
	m_clip->w = ancho;
	m_clip->x = ancho/2 - (ventana->obtenerAncho())/2; //La mitad de la capa al centro de la ventana
	m_clip->y = 0;
}

void CapaFondo::Mover(int posX)
{
	Capa::Mover(posX);
	m_clip->x = this->getX();
}

void CapaFondo::Renderizar(){
	m_texture->render(0.0f,0.0f,m_clip);
}

CapaFondo::~CapaFondo() {

}

