/*
 * ControlModo.cpp
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#include "ControlModo.h"

ControlModo::ControlModo(MenuSeleccion* un_menu) {
	menu = un_menu;
	keystate = SDL_GetKeyboardState(NULL);
	quit = false;
	joystick = NULL;
	joystick2 = NULL;
	if(SDL_NumJoysticks() > 1){
		joystick = SDL_JoystickOpen(0);
		if( joystick == NULL )
			log(string("No se puede leer el joystick 1! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
		else
			log("Joystick 1 cargado correctamente",LOG_DEBUG);
		joystick2 = SDL_JoystickOpen(1);
		if( joystick2 == NULL )
			log(string("No se puede leer el joystick 2! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
		else
			log("Joystick 2 cargado correctamente",LOG_DEBUG);
	}
	else if(SDL_NumJoysticks() == 1){
		joystick = SDL_JoystickOpen(0);
		if( joystick == NULL )
			log(string("No se puede leer el joystick 1! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
		else
			log("Joystick 1 cargado correctamente",LOG_DEBUG);
	}
	menu->setCantidadComandos(SDL_NumJoysticks()+ 1);
}

bool ControlModo::PollEvent(){
	SDL_JoystickUpdate();
	return (SDL_PollEvent( &evento ) != 0);
}

void ControlModo::Pressed(){
	if(evento.type == SDL_QUIT){
		quit = true;
		return;
	}
	//teclado
	else if (evento.type == SDL_KEYDOWN){
		switch( evento.key.keysym.sym ){
			case  SDLK_UP:
				menu->arriba();
				break;
			case SDLK_DOWN:
				menu->abajo();
				break;
			case SDLK_LEFT:
				menu->izquierda();
				break;
			case SDLK_RIGHT:
				menu->derecha();
				break;
			case SDLK_a:
				menu->select();
				break;
			case SDLK_s:
				menu->select();
				break;
			case SDLK_RETURN:
				menu->select();
				break;
			case SDLK_SPACE:
				menu->select();
				break;
			case SDLK_d:
				menu->select();
				break;
		}
	}
	//mouse
	else if (evento.type == SDL_MOUSEMOTION || evento.type == SDL_MOUSEBUTTONDOWN ){
		int x, y;
		SDL_GetMouseState( &x, &y );
		switch( evento.type ){
			case SDL_MOUSEMOTION:
				//Get mouse position
				menu->mousePosition(x,y);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (menu->mousePosition(x,y) and evento.button.button == SDL_BUTTON_LEFT )
					menu->select();
				break;
		}
	}
	//Joystick
	else if(evento.type == SDL_JOYAXISMOTION){
		//X axis motion
		if( evento.jaxis.axis == 0 ){
			//Left of dead zone
			if( evento.jaxis.value < -JOYSTICK_DEAD_ZONE ){
				menu->izquierda();
			}
			//Right of dead zone
			else if( evento.jaxis.value > JOYSTICK_DEAD_ZONE ){
				menu->derecha();
			}
			else{
				//NO SE
			}
		}
		//Y axis motion
		else if( evento.jaxis.axis == 1){
			//arriba
			if( evento.jaxis.value < -JOYSTICK_DEAD_ZONE ){
				menu->arriba();
			}
			//abajo
			else if( evento.jaxis.value > JOYSTICK_DEAD_ZONE){
				menu->abajo();
			}
			else{
				//NADA
			}
		}
	}
	//flechas
	else if (evento.type == SDL_JOYHATMOTION){

		switch (evento.jhat.value){
			case SDL_HAT_UP :
				menu->arriba();
				break;
			case SDL_HAT_DOWN:
				menu->abajo();
				break;
			case SDL_HAT_LEFT:
				menu->izquierda();
				break;
			case SDL_HAT_RIGHT:
				menu->derecha();
				break;
		}
	}
	//Boton
	else if (evento.type == SDL_JOYBUTTONDOWN){
		//con cualquier boton se selecciona
		menu->select();
	}
}

bool ControlModo::Quit(){
	return quit;
}

ControlModo::~ControlModo() {
	keystate = NULL;
	if (joystick != NULL && SDL_JoystickGetAttached(joystick)){
		SDL_JoystickClose( joystick );
		joystick = NULL;
	}
	if (joystick2 != NULL && SDL_JoystickGetAttached(joystick2)){
		SDL_JoystickClose( joystick2 );
		joystick2 = NULL;
	}
	menu = NULL;
}

