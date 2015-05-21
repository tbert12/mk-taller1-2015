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
#include "../model/CargarImagenException.h"
#include <stdexcept>
#include <exception>


class CapaFondo: public Capa {

private:
	LTexture* m_texture;
	void _actualizarX();


public:
	CapaFondo(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal,std::string ruta, Ventana* ventana);
	//virtual void Mover(bool right);
	virtual void Renderizar();
	virtual void Update(int scroll);
	virtual void reset();
	virtual ~CapaFondo();
};

#endif /* SRC_MODEL_CAPAFONDO_H_ */
