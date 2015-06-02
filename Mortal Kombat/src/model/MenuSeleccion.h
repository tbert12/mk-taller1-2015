/*
 * MenuSeleccion.h
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_MENUSELECCION_H_
#define SRC_MODEL_MENUSELECCION_H_
#include "Personaje.h"
#include "Pelea.h"
#include "../view/Ventana.h"
#include "../view/Menu.h"
#include <SDL2/SDL.h>

#define CANT_TOTAL_MODOS 3

class MenuSeleccion {
private:
	Ventana* ventana;
	Menu* menu;
	std::vector<Opcion> opciones;
	std::vector<Personaje*> personajes;
	int ModoDeJuego;
	bool selected;
	void _crearOpciones();
public:
	MenuSeleccion(Ventana* la_ventana,std::vector<Personaje*> los_personajes);
	void izquierda();
	void derecha();
	void arriba();
	void abajo();
	void select();
	bool mousePosition(int x, int y);
	void render();
	bool modeSelected();
	int modoDeJuego();
	virtual ~MenuSeleccion();
};

#endif /* SRC_MODEL_MENUSELECCION_H_ */
