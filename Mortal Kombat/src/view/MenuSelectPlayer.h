/*
 * MenuSelectPlayer.h
 *
 *  Created on: 5/6/2015
 *      Author: facu
 */

#ifndef SRC_VIEW_MENUSELECTPLAYER_H_
#define SRC_VIEW_MENUSELECTPLAYER_H_
#define MAX_PLAYER 11

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "Ventana.h"
#include "TextBox.h"
#include "../model/Personaje.h"
#include "../model/Pelea.h"

#define RUTA_FONDO "data/img/etc/MenuSelection.png"
#define RUTA_RECT_1 "data/img/etc/1.png"
#define RUTA_RECT_2 "data/img/etc/2.png"
#define RUTA_RECT_CPU "data/img/etc/cpu.png"

typedef struct Opcion_Personaje {
	SDL_Rect posicion;
	Personaje* personaje;
} Opcion_Personaje;

class MenuSelectPlayer {
public:
	MenuSelectPlayer(Ventana* ventana,std::vector<Personaje*> personajes, int modo_de_juego);
	void render(int opcion_actual1, int opcion_actual2,TextBox* textbox1,TextBox* textbox2);
	std::vector<Opcion_Personaje*> getOpciones();
	SDL_Rect getRectName1();
	SDL_Rect getRectName2();
	virtual ~MenuSelectPlayer();
private:
	Ventana* ventana;
	int ModoDeJuego;
	float ratio_x;
	float ratio_y;
	std::vector<Opcion_Personaje*> opciones;
	std::vector<Personaje*> personajes;
	SDL_Rect* imagen;
	SDL_Rect* rect_1;
	SDL_Rect* rect_2;
	SDL_Rect NameJug1;
	SDL_Rect NameJug2;
	SDL_Texture* textura_imagen;
	SDL_Texture* textura_1;
	SDL_Texture* textura_2;
	//TTF_Font* font;
	//SDL_Color Color;
	//SDL_Color ColorRed;
	SDL_Rect personaje_1;
	SDL_Rect personaje_2;

	SDL_Texture* _loadImage(SDL_Rect* rect, string ruta);
	void _crearOpciones();
	void _renderImagen();
	void _renderFaces();
	void _renderFace(Opcion_Personaje* opcion);
	void _renderSeleccion(int opcion_actual1,int opcion_actual2);
	void _renderTexto(int opcion_actual);
	void _renderText(string text, SDL_Color color, SDL_Rect rect);
};
#endif /* SRC_VIEW_MENUSELECTPLAYER_H_ */
