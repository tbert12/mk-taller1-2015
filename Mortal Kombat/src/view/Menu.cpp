/*
 * Menu.cpp
 *
 *  Created on: 1/6/2015
 *      Author: facu
 */

#include "Menu.h"

Menu::Menu(Ventana* una_ventana) {

	ventana = una_ventana;
	imagen = new SDL_Rect;
	textura = NULL;
	_loadImage();
	_crearOpciones();

	//Texto
	font = TTF_OpenFont(RUTA_TTF, (int)(ventana->obtenerAlto()*(0.10)*ventana->obtenerRatioY() +0.5) );
	if( font == NULL ){
		log("No se pudo cargar la fuente del tiempo",LOG_ERROR);
	}
	else{
		texturaTextoSeleccion = NULL;
		textoSeleccion = "Seleccionar modo de juego";
		Color = { 255, 247, 0 };
		ColorRed = { 255, 0, 0 };
	}
}

void Menu::_crearOpciones(){
	Opcion opcion1 = {SDL_Rect {0,0,0,0},SDL_Color { 255, 247, 0 },string("Player vs Player"),string("Player vs Player")};
	opciones.push_back(opcion1);
	Opcion opcion2 = {SDL_Rect {0,0,0,0},SDL_Color { 255, 247, 0 },string("Player vs CPU"),string("Player vs CPU")};
	opciones.push_back(opcion2);
	Opcion opcion3 = {SDL_Rect {0,0,0,0},SDL_Color { 255, 247, 0 },string("Practica"),string("Practica")};
	opciones.push_back(opcion3);
}

void Menu::_loadImage(){
	SDL_Texture* nuevaTexture = NULL;

	//Cargar imagen desde ruta
	SDL_Surface* loadedSurface = IMG_Load( RUTA_IMG );
	if( loadedSurface == NULL ){
		log( string("No se puede cargar imagen %s! SDL_image Error:") + RUTA_IMG,LOG_ERROR);
		return;
	}
	else{
		//Color de Imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Crear textura desde Surface por pixer
		nuevaTexture = SDL_CreateTextureFromSurface( ventana->getRenderer(), loadedSurface );
		if( nuevaTexture == NULL ){
			log( string("No se puede crear textura desde: ") + RUTA_IMG,LOG_ERROR);
			return;
		}
		else{
			//Dimensiones de imagen
			imagen->x = 0;
			imagen->y = 0;
			imagen->w = loadedSurface->w;
			imagen->h = loadedSurface->h;
		}

		//Liberar la imagen cargada
		SDL_FreeSurface( loadedSurface );
	}
	//ratios
	ratio_x = imagen->w/ventana->obtenerAncho();
	ratio_y = imagen->h/ventana->obtenerAlto();

	//Success
	textura = nuevaTexture;
	log("Se cargo correctamente la textura de la imagen del menu inicial",LOG_DEBUG);
}

std::vector<Opcion> Menu::getOpciones(){
	return opciones;
}

void Menu::_renderImagen(){
	SDL_Rect camera = { 0,0, ventana->getAnchoPx(), ventana->getAltoPx()};
	SDL_Rect clip = {0,0,ventana->getAnchoPx(), ventana->getAltoPx()};
	SDL_RenderCopy( ventana->getRenderer(), textura, &clip, &camera);
}

void Menu::_renderTexto(){
	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		//opciones[i];
	}

}

void Menu::render(SDL_Rect* opcion_actual){
	_renderImagen();
	_renderTexto();
}

Menu::~Menu() {
	if( textura != NULL ){
		SDL_DestroyTexture( textura );
		textura = NULL;
	}
	delete imagen;
	if( texturaTextoSeleccion!= NULL ){
		SDL_DestroyTexture( texturaTextoSeleccion);
		texturaTextoSeleccion = NULL;
	}
	if (font)
		TTF_CloseFont( font );

	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		//delete opciones[i];
	}
	opciones.clear();

	ventana = NULL;
}

