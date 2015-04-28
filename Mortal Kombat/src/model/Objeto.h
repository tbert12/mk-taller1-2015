/*
 * Objeto.h
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_OBJETO_H_
#define SRC_MODEL_OBJETO_H_

#include <string>
#include "../view/Sprite.h"

class Objeto {
private:
	std::string nombre;
	bool vida;
	float m_xActual;
	float m_yActual;
	float m_velocidad;
	std::vector<Sprite*> sprites;
	float m_AltoMundo;
	float m_AnchoMundo;

public:
	Objeto();
	bool lanzar(float pos_x,float pos_y);
	void renderizar(float x_dist_ventana, float posOtherPlayer);
	virtual ~Objeto();
};

#endif /* SRC_MODEL_OBJETO_H_ */
