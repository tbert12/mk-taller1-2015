/*
 * MenuSeleccion.h
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_MENUSELECCION_H_
#define SRC_MODEL_MENUSELECCION_H_
#include "Pelea.h"
#include "../view/Ventana.h"
#include "../view/Menu.h"
#include "SoundMenu.h"
#include <SDL2/SDL.h>

class MenuSeleccion {
private:
	Ventana* ventana;
	Menu* menu;
	std::vector<Opcion*> opciones;
	int ModoDeJuego;
	SoundMenu* sound;
	int cantComandos;
	bool selected;
	void _crearOpciones();
public:
	MenuSeleccion(Ventana* la_ventana, SoundMenu* un_sound);
	void izquierda();
	void derecha();
	void arriba();
	void abajo();
	void select();
	bool mousePosition(int x, int y);
	void render();
	bool modeSelected();
	int modoDeJuego();
	void setCantidadComandos(int cantidad);
	virtual ~MenuSeleccion();
};

#endif /* SRC_MODEL_MENUSELECCION_H_ */
