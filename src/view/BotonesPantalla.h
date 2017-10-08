/*
 * BotonesPantalla.h
 *
 *  Created on: 30/5/2015
 *      Author: facu
 */

#ifndef SRC_VIEW_BOTONESPANTALLA_H_
#define SRC_VIEW_BOTONESPANTALLA_H_

#define RUTA_BOTONES "data/font/mortalkombat1.ttf"
#include "Ventana.h"
#include <string>
#include <vector>
#include "../controller/ComboController.h"

class BotonesPantalla {
private:
	Ventana* ventana;
	int anchoTexto,altoTexto;
	string textoConstante;
	SDL_Texture* texturaNombreTexto;
	TTF_Font* font;
	SDL_Color Color;
	SDL_Color ColorRED;
	bool _loadFromRenderedText( std::string textureText,SDL_Color color);
	string _limpiarPorAccion(string botones);
public:
	BotonesPantalla(Ventana* una_ventana);
	void render(std::string botones,bool red);
	virtual ~BotonesPantalla();
};

#endif /* SRC_VIEW_BOTONESPANTALLA_H_ */
