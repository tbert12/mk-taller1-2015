/*
 * CapaFondo.h
 *
 *  Created on: Apr 3, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPAFONDO_H_
#define SRC_MODEL_CAPAFONDO_H_

#include "Capa.h"
#include "../view/LTexture.h"
#include "../view/Ventana.h"
#include <string>
#include <SDL2/SDL.h>


class CapaFondo: public Capa {

private:
	LTexture* m_texture;
	SDL_Rect* m_clip;

public:
	CapaFondo(int alto, int ancho, int zIndex, int anchoDeFondo, float velocidadPrincipal,
			std::string ruta, Ventana* ventana);
	virtual void Mover(bool right);
	virtual void Renderizar();
	virtual ~CapaFondo();
};

#endif /* SRC_MODEL_CAPAFONDO_H_ */
