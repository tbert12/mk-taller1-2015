/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


CapaPrincipal::CapaPrincipal(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal, Personaje* personaje)
:Capa(alto,ancho,zIndex, anchoDeFondo,velocidadPrincipal) //call superclass constructor
{
	m_Personaje = personaje;
}

void CapaPrincipal::Renderizar()
{

	if( Scrollear())
	{
		m_Personaje->SetScroll(true);
	}
	Sprite* spriteActual =m_Personaje->getSpriteActual();
	SDL_Rect* clip = spriteActual->getFrame();
	LTexture* textura = spriteActual->getSpriteSheetTexture();
	textura->render(m_Personaje->getX(), m_Personaje->getY(),clip);

	//m_Texture->render(0,0, Ventana.obtenerClip());
	/*
	std::list<Renderizable*>::iterator it ;

	for(it=m_listaDeRenderizables.begin(); it!=m_listaDeRenderizables.end(); it++)
	{
		Renderizable* elemento = dynamic_cast<Renderizable*>(*it); // compile error
		elemento->Renderizar();
	}
	*/
}

bool CapaPrincipal::Scrollear(){
	return m_Personaje->getX() >= m_ancho* 0.9f || m_Personaje->getX() <= m_ancho* 0.1f;
}

CapaPrincipal::~CapaPrincipal() {
	// TODO Auto-generated destructor stub
}

