/*
 * TiempoPartida.cpp
 *
 *  Created on: 6/5/2015
 *      Author: facu
 */

#include "TiempoPartida.h"
#define RUTA_FUENTE "data/font/mortalkombat1.ttf"

TiempoPartida::TiempoPartida(Ventana* una_ventana, Tiempo* un_tiempo) {
	m_tiempo = un_tiempo;
	m_ventana = una_ventana;
	font = TTF_OpenFont(RUTA_FUENTE, (int)(m_ventana->obtenerAlto()*(0.1)*m_ventana->obtenerRatioY() +0.5) );
	if( font == NULL ){
		log("No se pudo cargar la fuente del tiempo",LOG_ERROR);
	}
	m_textura = NULL;
	ancho = 0;
	alto = 0;
	textColor = { 255, 247, 0 };
}

bool TiempoPartida::loadFromRenderedText( std::string textureText){
	//Get rid of preexisting texture
	if( m_textura != NULL ){
		SDL_DestroyTexture( m_textura );
		m_textura = NULL;
	}

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textureText.c_str(), textColor );
	if( textSurface == NULL ){
		log("No se puede crear la textura del tiempo",LOG_ERROR);
	}
	else{

		//Create texture from surface pixels
	SDL_Renderer* renderVentana= m_ventana->getRenderer();
	if (renderVentana==NULL)
		return false;
        m_textura = SDL_CreateTextureFromSurface( renderVentana, textSurface );
		if( m_textura == NULL ){
			log("No se puede crear la textura del tiempo",LOG_ERROR);
		}
		else{
			//Get image dimensions
			ancho = textSurface->w;
			alto = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return m_textura != NULL;
}


void TiempoPartida::render(){
	int numero = m_tiempo->getTiempo();
	loadFromRenderedText(to_string(numero));

	int pos_x = ( (int)(m_ventana->obtenerAncho()*m_ventana->obtenerRatioX() + 0.5) - ancho ) / 2;
	int pos_y =	(int)(m_ventana->obtenerAlto()*(0.03)*m_ventana->obtenerRatioY() + 0.5);

	SDL_Rect renderQuad = { pos_x, pos_y, ancho, alto };

	//Render to screen
	SDL_RenderCopyEx( m_ventana->getRenderer(), m_textura, NULL, &renderQuad, 0.0, NULL,SDL_FLIP_NONE);

}


TiempoPartida::~TiempoPartida() {
	if( m_textura != NULL ){
		SDL_DestroyTexture( m_textura );
		m_textura = NULL;
	}
	if (font)
		TTF_CloseFont( font );
	m_tiempo = NULL;
	m_ventana = NULL;
}

