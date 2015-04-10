/*
 * CapaFondo.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: root
 */

#include "CapaFondo.h"


CapaFondo::CapaFondo(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal,
		std::string ruta, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal,ventana) //call superclass constructor
{
	m_texture = ventana->crearTextura();
	m_texture->loadFromFile(ruta);
	m_clip = new SDL_Rect();
	///m_ventana_ancho = ventana->obtenerAncho();
	m_clip->h = alto;
	m_clip->w = ancho;
	m_clip->x = getX(); //La mitad de la capa al centro de la ventana
	m_clip->y = 0;
}

<<<<<<< HEAD
void CapaFondo::Mover(bool right)
{
	Capa::Mover(right);
=======
void CapaFondo::_actualizarX(){
>>>>>>> 85bd7a198744ff541d20009763ef9ffefbdd3060
	m_clip->x = this->getX();
}
void CapaFondo::Renderizar(){
	_actualizarX();
	m_texture->renderFondo(m_clip);
}

CapaFondo::~CapaFondo() {
	return;
}

