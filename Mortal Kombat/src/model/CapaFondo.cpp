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
	rect->x = rect->x - ventana->obtenerAncho()/2;//Inicia al medio
	if ( ! m_texture->loadFromFile( ruta ) ) {
		log( "Error al intentar abrir la imagen de la capa.", LOG_ERROR );
		throw CargarImagenException( "No se pudo cargar la imagen de la capa como textura SDL" );
	}
}

void CapaFondo::_actualizarX(){
}

void CapaFondo::Renderizar(){
	m_texture->renderFondo(rect);
}

CapaFondo::~CapaFondo() {
	//auto call ~Capa() <- delete rect;
	delete m_texture;
}
