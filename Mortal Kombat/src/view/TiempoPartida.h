/*
 * TiempoPartida.h
 *
 *  Created on: 6/5/2015
 *      Author: facu
 */

#ifndef SRC_VIEW_TIEMPOPARTIDA_H_
#define SRC_VIEW_TIEMPOPARTIDA_H_
#include <SDL2/SDL_ttf.h>
#include <string>
#include "Ventana.h"
#include "../model/Tiempo.h"

class TiempoPartida {
private:
	int ancho;
	int alto;
	Ventana* m_ventana;
	Tiempo* m_tiempo;
	SDL_Texture* m_textura;
	TTF_Font *font;
	SDL_Color textColor;
	bool loadFromRenderedText( std::string textureText);

public:
	TiempoPartida(Ventana* una_ventana, Tiempo* un_tiempo);
	void render();
	virtual ~TiempoPartida();
};

#endif /* SRC_VIEW_TIEMPOPARTIDA_H_ */
