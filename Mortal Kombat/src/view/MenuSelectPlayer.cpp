/*
 * MenuSelectPlayer.cpp
 *
 *  Created on: 5/6/2015
 *      Author: facu
 */

#include "MenuSelectPlayer.h"

MenuSelectPlayer::MenuSelectPlayer(Ventana* una_ventana,std::vector<Personaje*> los_personajes,int modo_de_juego) {
	ventana = una_ventana;
	personajes = los_personajes;
	ModoDeJuego = modo_de_juego;
	imagen = new SDL_Rect;
	rect_1 = new SDL_Rect;
	rect_2 = new SDL_Rect;
	textura_imagen = NULL;
	textura_1 = NULL;
	textura_2 = NULL;

	/* //Texto
	font = TTF_OpenFont(RUTA_FONT, (int)(ventana->obtenerAlto()*(0.08)*ratio_y +0.5) );
	if( font == NULL ){
		log("No se pudo cargar la fuente del tiempo",LOG_ERROR);
	}
	else{
		texturaTextoSeleccion = NULL;
		textoSeleccion = "Seleccionar modo de juego";
		Color = { 255, 247, 0 };
		ColorRed = { 255, 0, 0 };
	}
	*/

	textura_1 = _loadImage(rect_1,RUTA_RECT_1);
	if (ModoDeJuego == MODO_JUGADOR_VS_JUGADOR)
		textura_2 =_loadImage(rect_2,RUTA_RECT_2);
	else
		textura_2 = _loadImage(rect_2,RUTA_RECT_CPU);
	textura_imagen = _loadImage(imagen,RUTA_FONDO);

	ratio_x = ventana->getAnchoPx()/imagen->w;
	ratio_y = ventana->getAltoPx()/imagen->h;

	_crearOpciones();
}


void MenuSelectPlayer::_crearOpciones(){

	int ancho = int(74*ratio_x + 0.5);
	int alto = int(93*ratio_y + 0.5);
	int y_fila_1 = int(85*ratio_y + 0.5);
	int y_fila_2 = int(197*ratio_y + 0.5);
	int y_fila_3 = int(307*ratio_y + 0.5);

	Opcion_Personaje* opcion1 = new Opcion_Personaje;
	opcion1->posicion = SDL_Rect {int(101*ratio_x + 0.5),y_fila_1,ancho,alto};
	opcion1->personaje = personajes[0];
	opciones.push_back(*opcion1);

	Opcion_Personaje* opcion2 = new Opcion_Personaje;
	opcion2->posicion = SDL_Rect {int(192*ratio_x + 0.5),y_fila_1,ancho,alto};
	opcion2->personaje = personajes[1];
	opciones.push_back(*opcion2);

	Opcion_Personaje* opcion3 = new Opcion_Personaje;
	opcion3->posicion = SDL_Rect {int(372*ratio_x + 0.5),y_fila_1,ancho,alto};
	opcion3->personaje = personajes[2];
	opciones.push_back(*opcion3);

	Opcion_Personaje* opcion4 = new Opcion_Personaje;
	opcion4->posicion = SDL_Rect {int(463*ratio_x + 0.5),y_fila_1,ancho,alto};
	opcion4->personaje = personajes[3];
	opciones.push_back(*opcion4);

	Opcion_Personaje* opcion5 = new Opcion_Personaje;
	opcion5->posicion = SDL_Rect {int(100*ratio_x + 0.5),y_fila_2,ancho,alto};
	opcion5->personaje = personajes[4];
	opciones.push_back(*opcion5);

	Opcion_Personaje* opcion6 = new Opcion_Personaje;
	opcion6->posicion = SDL_Rect {int(191*ratio_x + 0.5),y_fila_2,ancho,alto};
	opcion6->personaje = personajes[5];
	opciones.push_back(*opcion6);

	Opcion_Personaje* opcion7 = new Opcion_Personaje;
	opcion7->posicion = SDL_Rect {int(282*ratio_x + 0.5),y_fila_2,ancho,alto};
	opcion7->personaje = personajes[6];
	opciones.push_back(*opcion7);

	Opcion_Personaje* opcion8 = new Opcion_Personaje;
	opcion8->posicion = SDL_Rect {int(372*ratio_x + 0.5),y_fila_2,ancho,alto};
	opcion8->personaje = personajes[7];
	opciones.push_back(*opcion8);

	Opcion_Personaje* opcion9 = new Opcion_Personaje;
	opcion9->posicion = SDL_Rect {int(463*ratio_x + 0.5),y_fila_2,ancho,alto};
	opcion9->personaje = personajes[8];
	opciones.push_back(*opcion9);

	Opcion_Personaje* opcion10 = new Opcion_Personaje;
	opcion10->posicion = SDL_Rect {int(191*ratio_x + 0.5),y_fila_3,ancho,alto};
	opcion10->personaje = personajes[9];
	opciones.push_back(*opcion10);

	Opcion_Personaje* opcion11 = new Opcion_Personaje;
	opcion11->posicion = SDL_Rect {int(282*ratio_x + 0.5),y_fila_3,ancho,alto};
	opcion11->personaje = personajes[10];
	opciones.push_back(*opcion11);

	Opcion_Personaje* opcion12 = new Opcion_Personaje;
	opcion12->posicion = SDL_Rect {int(372*ratio_x + 0.5),y_fila_3,ancho,alto};
	opcion12->personaje = personajes[11];
	opciones.push_back(*opcion12);
}

SDL_Texture* MenuSelectPlayer::_loadImage(SDL_Rect* rect, string ruta){
	SDL_Texture* nuevaTexture = NULL;

	//Cargar imagen desde ruta
	SDL_Surface* loadedSurface = IMG_Load( ruta.c_str() );
	if( loadedSurface == NULL ){
		log( string("No se puede cargar imagen %s! SDL_image Error:") + ruta,LOG_ERROR);
		return NULL;
	}
	else{
		//Color de Imagen
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Crear textura desde Surface por pixer
		nuevaTexture = SDL_CreateTextureFromSurface( ventana->getRenderer(), loadedSurface );
		if( nuevaTexture == NULL ){
			log( string("No se puede crear textura desde: ") + ruta,LOG_ERROR);
			return NULL;
		}
		else{
			//Dimensiones de imagen
			rect->x = 0;
			rect->y = 0;
			rect->w = loadedSurface->w;
			rect->h = loadedSurface->h;
		}

		//Liberar la imagen cargada
		SDL_FreeSurface( loadedSurface );
	}
	//Success
	return nuevaTexture;
	log("Se cargo correctamente la textura de la imagen del menu inicial",LOG_DEBUG);
}

void MenuSelectPlayer::render(int opcion_actual1,int opcion_actual2){
	ventana->clear();

	_renderImagen();
	_renderSeleccion(opcion_actual1,opcion_actual2);
	//_renderTexto(opcion_actual);

	ventana->Refresh();

	usleep(80000);
}

void MenuSelectPlayer::_renderImagen(){
	SDL_RenderCopy( ventana->getRenderer(), textura_imagen, NULL, NULL);
}

void MenuSelectPlayer::_renderSeleccion(int opcion_actual1,int opcion_actual2){
	SDL_RenderCopy( ventana->getRenderer(), textura_2, NULL, &opciones[opcion_actual2].posicion);
	SDL_RenderCopy( ventana->getRenderer(), textura_1, NULL, &opciones[opcion_actual1].posicion);

	if (opciones[opcion_actual1].personaje != NULL){
		opciones[0].personaje->setFlip(false);
		opciones[0].personaje->setPosition(20*ratio_x,300*ratio_y);
		opciones[0].personaje->renderizar(0,0);
	}
	if (opciones[opcion_actual2].personaje != NULL){
		opciones[1].personaje->setFlip(true);
		opciones[1].personaje->setPosition(372*ratio_x,300*ratio_y);
		opciones[1].personaje->renderizar(0,0);
	}
}

std::vector<Opcion_Personaje> MenuSelectPlayer::getOpciones(){
	return opciones;
}

MenuSelectPlayer::~MenuSelectPlayer() {
	if (textura_imagen)
		SDL_DestroyTexture( textura_imagen );
	delete imagen;
	if (textura_1)
		SDL_DestroyTexture( textura_1 );
	delete rect_1;
	if (textura_2)
		SDL_DestroyTexture( textura_2 );
	delete rect_2;
	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		delete &opciones[i];
	}
	opciones.clear();

	ventana = NULL;
}

