/*
 * MenuSeleccion.cpp
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#include "MenuSeleccion.h"

MenuSeleccion::MenuSeleccion(Ventana* la_ventana,std::vector<Personaje*> los_personajes) {
	personajes = los_personajes;
	ventana = la_ventana;
	selected = false;
	menu = new Menu(ventana);
	opciones = menu->getOpciones();
	//SI hay un joystick o mas JUGADOR VS JUGADOR.
	if (SDL_NumJoysticks() >= 1)
		ModoDeJuego = MODO_JUGADOR_VS_JUGADOR;
	else
		ModoDeJuego = MODO_JUGADOR_VS_PC;
}

void MenuSeleccion::render(){
	//menu->render();
}

void MenuSeleccion::select(){
	selected = true;
}

int MenuSeleccion::modoDeJuego(){
	return ModoDeJuego;
}

bool MenuSeleccion::modeSelected(){
	return selected;
}

bool MenuSeleccion::mousePosition(int x, int y){
	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		SDL_Rect rect = opciones[i].posicion;
		if (x >= rect.x and x <= (rect.x + rect.w) ){
			if (y >= rect.y and y <= (rect.y + rect.h) ){
				ModoDeJuego = i;
				return true;
			}
		}
	}
	return false;
}

void MenuSeleccion::arriba(){

}

void MenuSeleccion::abajo(){

}

void MenuSeleccion::izquierda(){

}

void MenuSeleccion::derecha(){

}

MenuSeleccion::~MenuSeleccion() {
	delete menu;
	ModoDeJuego = MODO_JUGADOR_VS_PC;
	ventana = NULL;
}

