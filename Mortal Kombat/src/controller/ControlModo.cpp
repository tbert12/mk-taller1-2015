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
		else if( evento.jaxis.axis == 1 ){
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
	menu = NULL;
}

