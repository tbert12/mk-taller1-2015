/*
 * main.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>

#include "../view/Mundo.h"
#include "Personaje.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//Creo el Personaje
	Personaje luchador = Personaje("Sub Zero");
	//Iniciar SDL y crear ventana
	if( !create_window(SCREEN_WIDTH,SCREEN_HEIGHT) ) {
		printf( "Error al inicializar!\n" );
	} else {
		//Load media
		if( !loadMedia( luchador.Sprite(0) ) ){
			printf( "Error al cargar media!\n" );
		} else {
			//flag para el Loop Principal
			bool quit = false;

			//Manejador de evento
			SDL_Event e;

			//Current animation frame
			int frame = 0;

			//While Principal
			while( !quit ){
				//Eventos
				while( SDL_PollEvent( &e ) != 0 ){
					//Usuario presiona [X]
					if( e.type == SDL_QUIT ){
						quit = true;
					}
				}

				//Limpiar pantalla
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Renderizar estado actual
				SDL_Rect* currentClip = &gSpriteClips[ frame / 9 ];
				gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

				//Actualizar pantalla
				SDL_RenderPresent( gRenderer );

				//Ir al siguiente estado
				++frame;

				//Ciclo de animacion
				if( frame / 9 >= ANIMATION_IMAGES ){
					frame = 0;
				}
			}
		}
	}

	//Free resources and close SDL
	close_window();

	return 0;
}


