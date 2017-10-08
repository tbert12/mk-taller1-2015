/*
 * CapaFondo.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: root
 */

#include "CapaFondo.h"


CapaFondo::CapaFondo(float alto, float ancho, int zIndex, float anchoDeFondo,
		std::string ruta, Ventana* ventana)
:Capa(alto,ancho,zIndex, anchoDeFondo,ventana->obtenerAncho()) //call superclass constructor
{
	m_texture = ventana->crearTextura();
	rect->x = rect->x - ventana->obtenerAncho()/2;//Inicia al medio
	if ( ! m_texture->loadFromFile( ruta ) ) {
		log( "Error al intentar abrir la imagen de la capa.", LOG_ERROR );
		throw CargarImagenException( "No se pudo cargar la imagen de la capa como textura SDL" );
	}
}

void CapaFondo::_actualizarX(){
}

void CapaFondo::Update(int scroll, float velocidad){
	if (scroll > 0)this->Mover(true,velocidad);
	else if (scroll < 0) this->Mover(false,velocidad);
}

void CapaFondo::Renderizar(){
	m_texture->renderFondo(rect);
}

void CapaFondo::reset(){
	rect->x = rect->w*0.5f - m_ancho_ventana/2;
	rect->y = 0;
}

CapaFondo::~CapaFondo() {
	//auto call ~Capa() <- delete rect;
	delete m_texture;
}
