/*
 * BarraEnergia.cpp
 *
 *  Created on: 23/4/2015
 *      Author: facu
 */

#include "BarraEnergia.h"
#define RUTA_BASE "data/img/estado/barras/energia_vacia.png"
#define RUTA_RELLENO "data/img/estado/barras/energia_llena.png"

BarraEnergia::BarraEnergia(Ventana* una_ventana,int max_barra) {
	ventana = una_ventana;
	maximo_barra = max_barra;
	actual = maximo_barra;
	velocidad_descarga = 1;
	flip = false;
	ancho_logico = (0.35)*ventana->obtenerAncho();
	alto_logico = ventana->obtenerAlto()*(0.05) ;
	rect_base = new SDL_Rect;
	rect_relleno = new SDL_Rect;
	textura_base = NULL;
	textura_relleno = NULL;
	_loadBase();
	_loadRelleno();
}

void BarraEnergia::setFlip(){
	if(flip)flip = false;
	else flip = true;
}

bool BarraEnergia::_loadBase(){
	SDL_Texture* nuevaTexture = NULL;

		//Cargar imagen desde ruta
		SDL_Surface* loadedSurface = IMG_Load( RUTA_BASE );
		if( loadedSurface == NULL )
		{
			log( string("No se puede cargar imagen %s! SDL_image Error: %s\n", RUTA_BASE),LOG_ERROR);
			return false;
		}
		else
		{
			//Color de Imagen
			SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

			//Crear textura desde Surface por pixer
			nuevaTexture = SDL_CreateTextureFromSurface( ventana->getRenderer(), loadedSurface );
			if( nuevaTexture == NULL )
			{
				log( string("No se puede crear textura desde %s!", RUTA_BASE),LOG_ERROR);
				return false;
			}
			else
			{
				//Dimensiones de imagen
				rect_base->x = 0;
				rect_base->y = 0;
				rect_base->w = loadedSurface->w;
				rect_base->h = loadedSurface->h;
			}

			//Liberar la imagen cargada
			SDL_FreeSurface( loadedSurface );
		}

		//Success
		textura_base = nuevaTexture;
		log("Se cargo correctamente la textura base de la barra de energia");
		_calcularRatios();
		return true;

}
void BarraEnergia::_calcularRatios(){
	ratio_x = rect_base->w/ancho_logico;
	ratio_y = rect_base->h/alto_logico;
}

bool BarraEnergia::_loadRelleno(){
	SDL_Texture* nuevaTexture = NULL;

		//Cargar imagen desde ruta
		SDL_Surface* loadedSurface = IMG_Load( RUTA_RELLENO );
		if( loadedSurface == NULL )
		{
			log( string("No se puede cargar imagen %s! SDL_image Error: %s\n", RUTA_RELLENO),LOG_ERROR);
			return false;
		}
		else
		{
			//Color de Imagen
			SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

			//Crear textura desde Surface por pixer
			nuevaTexture = SDL_CreateTextureFromSurface( ventana->getRenderer(), loadedSurface );
			if( nuevaTexture == NULL )
			{
				log( string("No se puede crear textura desde %s!", RUTA_RELLENO),LOG_ERROR);
				return false;
			}
			else
			{
				//Dimensiones de imagen
				rect_relleno->x = 0;
				rect_relleno->y = 0;
				rect_relleno->w = loadedSurface->w;
				rect_relleno->h = loadedSurface->h;
			}

			//Liberar la imagen cargada
			SDL_FreeSurface( loadedSurface );
		}

		//Success
		textura_relleno = nuevaTexture;
		log("Se cargo correctamente la textura relleno de la barra de energia");
		return true;

}

void BarraEnergia::_renderBase(){

	int pos_x;
	int pos_y = (int)(ventana->obtenerAlto()*(0.03)*ventana->obtenerRatioY() + 0.5);

	if (!flip){ //esta en la izquierda
		pos_x = (int)(ventana->obtenerAncho()*(0.02)*ventana->obtenerRatioX() + 0.5);
	}
	else{ //esta en la derecha
		float dist_borde= (ventana->obtenerAncho()*(0.02)*ventana->obtenerRatioX());

		pos_x = (int)((ventana->obtenerAncho() - dist_borde - ancho_logico)*ventana->obtenerRatioX() +0.5);
	}

	SDL_Rect Object = { pos_x,pos_y, (int)(ancho_logico*ventana->obtenerRatioX() +0.5), (int)(alto_logico*ventana->obtenerRatioY() + 0.5)};

	//Renderizar a la pantalla
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if(flip) flipType = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx( ventana->getRenderer(), textura_base, rect_base, &Object,  0 , 0, flipType);

}

void BarraEnergia::_actualizarActual(int estado){
	if(actual == estado) return;
	actual -= velocidad_descarga;
	if(actual < 0) actual = 0;
}

void BarraEnergia::_renderRelleno(int estado){

	_actualizarActual(estado);

	int pos_x;
	int pos_y = (int)(ventana->obtenerAlto()*(0.03)*ventana->obtenerRatioY() + 0.5);

	if (!flip){ //esta en la izquierda
		pos_x = (int)(ventana->obtenerAncho()*(0.02)*ventana->obtenerRatioX() + 0.5);
	}
	else{ //esta en la derecha
		float dist_borde= (ventana->obtenerAncho()*(0.02)*ventana->obtenerRatioX());

		pos_x = (int)((ventana->obtenerAncho() - dist_borde - ancho_logico)*ventana->obtenerRatioX() +0.5);

	}

	SDL_Rect Object = { pos_x,pos_y, actual*(int)(ancho_logico*ventana->obtenerRatioX() +0.5)/100, (int)(alto_logico*ventana->obtenerRatioY() + 0.5)};
	SDL_Rect clip;
	clip.x = rect_relleno->x;
	clip.y = rect_relleno->y;
	//clip.w = (actual*rect_relleno->w)/100;
	clip.w = rect_relleno->w;
	clip.h = rect_relleno->h;
	//Renderizar a la pantalla
	SDL_RendererFlip flipType = SDL_FLIP_NONE;
	if(flip) flipType = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx( ventana->getRenderer(), textura_relleno, &clip, &Object,  0 , 0, flipType);
}

void BarraEnergia::render(int estado){
	if (textura_base == NULL or textura_relleno == NULL){
		if (textura_base == NULL )printf("BASE es null\n");
		if (textura_relleno == NULL )printf("rellleno es null\n");
		log("No se puede renderizar la barra de energia",LOG_ERROR);
		return;
	}
	_renderBase();
	_renderRelleno(estado);
}

BarraEnergia::~BarraEnergia() {
	if( textura_base != NULL ){
		SDL_DestroyTexture( textura_base );
		textura_base = NULL;
	}
	delete rect_base;
	if( textura_relleno != NULL ){
		SDL_DestroyTexture( textura_relleno );
		textura_relleno = NULL;
	}
	delete rect_relleno;
	ventana = NULL;
}

