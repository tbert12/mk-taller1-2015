/*
 * Menu.h
 *
 *  Created on: 1/6/2015
 *      Author: facu
 */

#ifndef SRC_VIEW_MENU_H_
#define SRC_VIEW_MENU_H_

#include <string>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include "Ventana.h"
#include "LTexture.h"
#include <stdio.h>

#define RUTA_IMG "data/img/etc/mode.png"
#define RUTA_TTF "data/font/fuente.ttf"

typedef struct Opcion {
	SDL_Rect posicion;
	SDL_Color color;
	string texto;
	string descripcion;
} Opcion;

class Menu {
public:
	Menu(Ventana* una_ventana);
	void render(SDL_Rect* opcion_actual);
	void _loadImage();
	std::vector<Opcion> getOpciones();
	virtual ~Menu();
private:
	float ratio_x;
	float ratio_y;
	std::vector<Opcion> opciones;
	Ventana* ventana;
	SDL_Rect* imagen;
	SDL_Texture* textura;
	string textoSeleccion;
	SDL_Texture* texturaTextoSeleccion;
	TTF_Font* font;
	SDL_Color Color;
	SDL_Color ColorRed;

	void _crearOpciones();
	void _renderImagen();
	void _renderTexto();
};

#endif /* SRC_VIEW_MENU_H_ */
