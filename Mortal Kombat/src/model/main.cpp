/*
 * main.cpp
 *
 *  Created on: 26/3/2015
 *      Author: tomi
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../view/Mundo.h"
#include "../controller/KeyboardControl.h"
#include "Personaje.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main( int argc, char* args[] )
{
	//Creo el Personaje
	Personaje luchador = Personaje("Sub Zero");

	//Creo el Controlador
	KeyboardControl control = KeyboardControl(&luchador);

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
					control.KeyPressed(e);
				}

				printf("%i\n",frame);
				Refresh(frame,SCREEN_WIDTH,SCREEN_HEIGHT);

				//Ir al siguiente estado
				++frame;

				//Ciclo de animacion
				if( frame >= 9 ){
					frame = 0;
				}

				//Sleep(Microsegundos)
				usleep(100000);

			}
		}
	}

	//Free resources and close SDL
	close_window();

	return 0;
}


