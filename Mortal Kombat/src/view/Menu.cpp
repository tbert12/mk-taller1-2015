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
	hayError = 0;

	//Texto
	font = TTF_OpenFont(RUTA_FONT, (int)(ventana->obtenerAlto()*(0.08)*ventana->obtenerRatioY() +0.5) );
	if( font == NULL ){
		log("No se pudo cargar la fuente del tiempo",LOG_ERROR);
	}
	else{
		texturaTextoSeleccion = NULL;
		textoSeleccion = "Seleccionar modo de juego";
		Color = { 255, 247, 0 };
		ColorRed = { 255, 0, 0 };
	}

	_loadImage();
	_crearOpciones();
}

void Menu::_crearOpciones(){

	int ancho = int(99*ventana->obtenerRatioX() + 0.5);
	int alto = int(120*ventana->obtenerRatioY() + 0.5);
	int y = int(51*ventana->obtenerRatioY() + 0.5);

	Descripcion = {int(22*ventana->obtenerRatioX() + 0.5),int(206*ventana->obtenerRatioY() + 0.5),int(356*ventana->obtenerRatioX() + 0.5),int(102*ventana->obtenerRatioY() + 0.5)};
	rectError = {int(22*ventana->obtenerRatioX() + 0.5),int(206*ventana->obtenerRatioY() + 0.5),int(356*ventana->obtenerRatioX() + 0.5),int(50*ventana->obtenerRatioY() + 0.5)};

	Opcion* opcion1 = new Opcion;
	opcion1->posicion = SDL_Rect {int(20*ventana->obtenerRatioX() + 0.5),y,ancho,alto};
	opcion1->texto = string("Player\n  vs \nPlayer");
	opcion1->descripcion =  string("Player vs Player");
	opcion1->textura = NULL;
	opciones.push_back(*opcion1);

	Opcion* opcion2 = new Opcion;
	opcion2->posicion = SDL_Rect {int(150*ventana->obtenerRatioX() + 0.5),y,ancho,alto};
	opcion2->texto = string("Player\n  vs\n CPU");
	opcion2->descripcion =  string("Player vs CPU");
	opcion2->textura = NULL;
	opciones.push_back(*opcion2);

	Opcion* opcion3 = new Opcion;
	opcion3->posicion = SDL_Rect {int(280*ventana->obtenerRatioX() + 0.5),y,ancho,alto};
	opcion3->texto = string("Training");
	opcion3->descripcion =  string("Entrenamiento");
	opcion3->textura = NULL;
	opciones.push_back(*opcion3);
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
	SDL_RenderCopy( ventana->getRenderer(), textura, NULL, NULL);
}

void Menu::_renderTexto(int opcion_actual){

	for (unsigned int i = 0; i < opciones.size(); i++){

		if ((int)i == opcion_actual){
			_renderText(opciones[i].texto,ColorRed,opciones[i].posicion);
			_renderText(opciones[i].descripcion,Color,Descripcion);
		}
		else
			_renderText(opciones[i].texto,Color,opciones[i].posicion);
	}

	//cuadrado rojo del seleccionado
	SDL_SetRenderDrawColor(ventana->getRenderer(), 255, 0, 0, 255);
	SDL_Rect rect = opciones[opcion_actual].posicion;
	rect.x -= 15;
	rect.y -= 12;
	rect.w += 2*15 + 2;
	rect.h += 2*12 ;
	SDL_RenderDrawRect(ventana->getRenderer(), &rect);

}

void Menu::render(int opcion_actual){
	ventana->clear();

	_renderImagen();
	_renderTexto(opcion_actual);
	_renderError();
	ventana->Refresh();
}
void Menu::_renderText(string text, SDL_Color color, SDL_Rect rect){
	SDL_Texture* textura;
	int ancho,alto;
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Blended_Wrapped( font, text.c_str(), color, rect.w);
	if( textSurface == NULL ){
		log("No se puede crear la textura de la descripion del menu",LOG_ERROR);
		return;
	}
	else{
		//Create texture from surface pixels
		textura = SDL_CreateTextureFromSurface( ventana->getRenderer(), textSurface );
		if( textura == NULL ){
			log("No se puede crear la textura de la descriptcion del menu",LOG_ERROR);
			return;
		}
		else{
			//Get image dimensions
			ancho = textSurface->w;
			alto = textSurface->h;
		}
		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	SDL_Rect renderQuad = {rect.x + rect.w/2 - ancho/2,rect.y + rect.h/2 - alto/2,ancho,alto};
	if ( rect.w == ancho)
		renderQuad.x = renderQuad.x + rect.w/2 - ancho*0.4 ;

	SDL_RenderCopy( ventana->getRenderer(), textura, NULL, &renderQuad);
	SDL_DestroyTexture( textura );

}

void Menu::_renderError(){
	if (hayError <= 0) return;
	_renderText(error,ColorRed,rectError);
	hayError--;
}

void Menu::mostrarError(string un_error){
	error = un_error;
	hayError = 50;
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
		if( opciones[i].textura != NULL ){
			SDL_DestroyTexture( opciones[i].textura );
			opciones[i].textura = NULL;
			free(&opciones[i]);
		}
	}
	opciones.clear();

	ventana = NULL;
}

