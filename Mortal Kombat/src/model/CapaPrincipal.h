/*
 * CapaPrincipal.h
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPAPRINCIPAL_H_
#define SRC_MODEL_CAPAPRINCIPAL_H_

#include "Capa.h"
#include "Personaje.h"
#include <SDL2/SDL.h>

class CapaPrincipal: public Capa {

public:
<<<<<<< HEAD
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo, float velocidadPrincipal, Personaje* personaje, Ventana* ventana);
	bool Scrollear();
=======
	CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personaje);
	int Scrollear(); //0 no scrollea , 1 para la derecha -1 para la izquierda!
>>>>>>> 85bd7a198744ff541d20009763ef9ffefbdd3060
	virtual ~CapaPrincipal();
	virtual void Renderizar();

private:
	Personaje* m_Personaje;
	float m_ancho_ventana;
	void _actualizarX();
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
