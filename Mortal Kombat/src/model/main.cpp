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
#include <unistd.h> //usleep
#include <vector>
#include "logging.h"

#include <algorithm>    // std::reverse (Tranfuguiada para que camine para atras)

#include "../view/Ventana.h"
#include "../controller/KeyboardControl.h"
#include "Personaje.h"


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

std::vector<Sprite*> CargaDePrueba(){
	std::vector<Frame*> framesInitial(9);
	std::vector<Frame*> framesCaminar(9);
	int wInitial = 72,wCaminar = 68;
	for (int i=0;i<9;i++){
		framesInitial[i] = new Frame(wInitial*i,0,133,wInitial);
		framesCaminar[i] = new Frame(wCaminar*i,0,133,wCaminar);
	}
	std::vector<Frame*> framesCaminarAtras (framesCaminar);
	std::reverse(framesCaminarAtras.begin(),framesCaminarAtras.end());


	std::string rutaInitial = "data/players/subzero/sprites/initial.png";
	std::string rutaCaminar = "data/players/subzero/sprites/walk.png";
	std::string rutaCaminarAtras = "data/players/subzero/sprites/walk.png";
	Sprite* Initial = new Sprite(rutaInitial,framesInitial,getRenderer());
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar,getRenderer());
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras,getRenderer());
	std::vector<Sprite*> sprites(3);
	sprites[0] = Initial;
	sprites[1] = Caminar;
	sprites[2] = CaminarAtras;
	return sprites;
}


int main( int argc, char* args[] )
{

	Ventana* ventana = new Ventana(SCREEN_WIDTH,SCREEN_HEIGHT);

	// Marco inicio de un nuevo run en el .log
	prepararLog();

	Ventana ventana = new Ventana(SCREEN_WIDTH,SCREEN_HEIGHT);

	//Iniciar SDL y crear ventana
<<<<<<< HEAD
	//if( !ventana->create_window(SCREEN_WIDTH,SCREEN_HEIGHT) ) {
	if(!ventana.create_window(SCREEN_WIDTH,SCREEN_HEIGHT)){
=======
	if( !ventana->create_window() ) {
>>>>>>> 678a75332f497bede532db1bd680ff416f19d19b
		printf( "Error al inicializar!\n" );
	} else {

		//Creo el Personaje
		Personaje luchador = Personaje("Sub Zero",CargaDePrueba());

		std::string rutaFondoAncho = "data/Fondos/largo.png";
		std::string rutaFondo2 = "data/Fondos/atras.png";

		CapaFondo capaFondo = CapaFondo(SCREEN_HEIGHT,SCREEN_WIDTH, 0, 1068, 10,rutaFondoAncho,ventana.getRenderer(),ventana);
		CapaFondo capaAtras = CapaFondo(SCREEN_HEIGHT,SCREEN_WIDTH, 1, 1068, 10,rutaFondo2,ventana.getRenderer(),ventana);

		//Creo el Controlador
		KeyboardControl control = KeyboardControl(&luchador);

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

<<<<<<< HEAD
			ventana.Refresh(luchador.getSpriteActual(),SCREEN_WIDTH,SCREEN_HEIGHT);
			ventana.Refresh(luchador.getSpriteActual(),SCREEN_WIDTH,SCREEN_HEIGHT);
=======
			ventana->Refresh(luchador.getSpriteActual());
>>>>>>> 678a75332f497bede532db1bd680ff416f19d19b

			//FrameGuia
			++frame;

			//Sleep(Microsegundos)
			usleep(15000);
		}
	}

	//Free resources and close SDL
<<<<<<< HEAD
	ventana.close_window();
=======
	ventana->close_window();
>>>>>>> 678a75332f497bede532db1bd680ff416f19d19b

	return 0;
}


