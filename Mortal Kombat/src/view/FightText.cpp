/*
 * FightText.cpp
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#include "FightText.h"

#define RUTA_FUENTE "data/font/mortalkombat5.ttf"

using namespace std;

FightText::FightText(Ventana* una_ventana, string un_texto, float tiempo_duracion) {
	texto = un_texto;
	duracion = tiempo_duracion;
	m_ventana = una_ventana;
	font = TTF_OpenFont(RUTA_FUENTE, (int)(m_ventana->obtenerAlto()*(0.5)*m_ventana->obtenerRatioY() + 0.8) );
	if( font == NULL ){
		log("No se pudo cargar la fuente del tiempo",LOG_ERROR);
	}
	m_textura = NULL;
	ancho = 0;
	alto = 0;
	textColor = { 207, 23, 29 };
}

bool FightText::loadFromRenderedText(string textureText){
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

void FightText::render(){

	loadFromRenderedText(texto);

	int pos_x = ( (int)(m_ventana->obtenerAncho()*m_ventana->obtenerRatioX() + 0.5) - ancho ) / 2;
	int pos_y =	( (int)(m_ventana->obtenerAlto()*m_ventana->obtenerRatioY() + 0.5) - alto) / 2;

	SDL_Rect renderQuad = { pos_x, pos_y, ancho, alto };

	//Render to screen
	SDL_RenderCopyEx( m_ventana->getRenderer(), m_textura, NULL, &renderQuad, 0.0, NULL,SDL_FLIP_NONE);

}


FightText::~FightText() {
	// TODO Auto-generated destructor stub
}

