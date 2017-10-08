/*
 * BotonesPantalla.cpp
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#include "BotonesPantalla.h"

BotonesPantalla::BotonesPantalla(Ventana* una_ventana) {
	ventana = una_ventana;
	font = NULL;
	font = TTF_OpenFont(RUTA_BOTONES, (int)(ventana->obtenerAlto()*(0.07)*ventana->obtenerRatioY() +0.5) );
	if( font == NULL ){
		log("No se pudo cargar la fuente para los combos",LOG_ERROR);
	}
	texturaNombreTexto = NULL;
	textoConstante = "ERROR";
	anchoTexto = 0;
	altoTexto = 0;
	Color = { 255, 247, 0 };
	ColorRED = { 255, 0 , 0 };
}

bool BotonesPantalla::_loadFromRenderedText( std::string textureText,SDL_Color un_color){
	//Get rid of preexisting texture
	if( texturaNombreTexto != NULL ){
		SDL_DestroyTexture( texturaNombreTexto );
		texturaNombreTexto = NULL;
	}


	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( font, textureText.c_str(), un_color , ventana->getAnchoPx());
	if( textSurface == NULL ){
		log("No se puede crear la textura del tiempo",LOG_ERROR);
	}
	else{
		//Create texture from surface pixels
		texturaNombreTexto = SDL_CreateTextureFromSurface( ventana->getRenderer(), textSurface );
		if( texturaNombreTexto == NULL ){
			log("No se puede crear la textura del tiempo",LOG_ERROR);
		}
		else{
			//Get image dimensions
			anchoTexto = textSurface->w;
			altoTexto = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}

	//Return success
	return texturaNombreTexto != NULL;
}

void BotonesPantalla::render(std::string botones,bool red){
	string texto = _limpiarPorAccion(botones);

	int pos_x = (int)(ventana->obtenerAncho()*(0.5)*ventana->obtenerRatioX() + 0.5) - anchoTexto/2;
	int pos_y = (int)(ventana->obtenerAlto()*(0.25)*ventana->obtenerRatioY() + 0.5);
	SDL_Rect renderQuad = { pos_x, pos_y, anchoTexto, altoTexto };


	//SOMBRA
	SDL_Rect pos_sombra = {renderQuad.x - 3,renderQuad.y + 1,renderQuad.w,renderQuad.h};
	SDL_Color colorSombra = {0,0,0,255};
	_loadFromRenderedText(texto,colorSombra);

	SDL_RenderCopyEx( ventana->getRenderer(), texturaNombreTexto, NULL, &pos_sombra, 0.0, NULL,SDL_FLIP_NONE);

	_loadFromRenderedText(texto,red? ColorRED:Color);
	//Render to screen
	SDL_RenderCopyEx( ventana->getRenderer(), texturaNombreTexto, NULL, &renderQuad, 0.0, NULL,SDL_FLIP_NONE);

}

string BotonesPantalla::_limpiarPorAccion(string botones){
	string texto = "";
	for (unsigned int i = 0; i < botones.size(); i++){
		int boton = botones[i] - 48;
		switch(boton){
			case ARRIBA:
				texto += "U";
				break;
			case ABAJO:
				texto += "D";
				break;
			case IZQUIERDA:
				texto += "B";
				break;
			case DERECHA:
				texto += "F";
				break;
			case PINAALTA:
				texto += "HP";
				break;
			case PINABAJA:
				texto += "LP";
				break;
			case PATADAALTA:
				texto += "HK";
				break;
			case PATADABAJA:
				texto += "LK";
				break;
			case CUBRIR:
				texto += "C";
				break;
		}
		if (i < botones.size() -1)
			texto += " | ";
	}
	return texto;
}

BotonesPantalla::~BotonesPantalla() {
	if( texturaNombreTexto != NULL ){
		SDL_DestroyTexture( texturaNombreTexto);
		texturaNombreTexto = NULL;
	}
	if (font)
		TTF_CloseFont( font );
	ventana = NULL;
}

