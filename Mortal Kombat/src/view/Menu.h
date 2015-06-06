/*
 * Menu.h
 *
 *  Created on: 1/6/2015
 *      Author: facu
 */

#ifndef SRC_VIEW_MENU_H_
#define SRC_VIEW_MENU_H_

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Ventana.h"
#include "LTexture.h"
#include <stdio.h>

#define RUTA_IMG "data/img/etc/mode.png"
#define RUTA_FONT "data/font/mortalkombat4.ttf"

typedef struct Opcion {
	SDL_Rect posicion;
	SDL_Texture* textura;
	SDL_Rect rect_textura;
	string texto;
	string descripcion;
} Opcion;

class Menu {
public:
	Menu(Ventana* una_ventana);
	void render(int opcion_actual);
	std::vector<Opcion> getOpciones();
	void mostrarError(string error);
	virtual ~Menu();
private:
	float ratio_x;
	float ratio_y;
	int hayError;
	std::vector<Opcion> opciones;
	Ventana* ventana;
	SDL_Rect* imagen;
	SDL_Texture* textura;
	string textoSeleccion;
	string error;
	SDL_Texture* texturaTextoSeleccion;
	TTF_Font* font;
	SDL_Color Color;
	SDL_Color ColorRed;
	SDL_Rect Descripcion;
	SDL_Rect Select;
	SDL_Rect rectError;

	void _loadImage();
	void _crearOpciones();
	void _renderImagen();
	void _renderTexto(int opcion_actual);
	void _renderText(string text, SDL_Color color, SDL_Rect rect);
	void _renderError();
};

#endif /* SRC_VIEW_MENU_H_ */
