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
	ModoDeJuego = MODO_JUGADOR_VS_PC;
	cantComandos = 1;
}

void MenuSeleccion::setCantidadComandos(int cantidad){
	cantComandos = cantidad;
}

void MenuSeleccion::render(){
	menu->render(ModoDeJuego);
}

void MenuSeleccion::select(){
	if (cantComandos < 2 and ModoDeJuego == MODO_JUGADOR_VS_JUGADOR){
		menu->mostrarError("No hay Joystick");
		return;
	}
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
	if (ModoDeJuego == 0)
		ModoDeJuego = 2;
	else ModoDeJuego--;
}

void MenuSeleccion::derecha(){
	if (ModoDeJuego == 2)
		ModoDeJuego = 0;
	else ModoDeJuego++;
}

MenuSeleccion::~MenuSeleccion() {
	delete menu;
	ModoDeJuego = MODO_JUGADOR_VS_PC;
	ventana = NULL;
}

