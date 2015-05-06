/*
 * ObjetoArrojable.h
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_OBJETOARROJABLE_H_
#define SRC_MODEL_OBJETOARROJABLE_H_

#include <string>
#include "../view/Sprite.h"

class ObjetoArrojable {
private:
	std::string nombre;
	bool vida;
	float m_xActual;
	float m_yActual;
	float m_velocidad;
	std::vector<Sprite*> sprites;
	float m_AltoMundo;
	float m_AnchoMundo;

	void _Update();

public:
	ObjetoArrojable(string un_nombre,float velocidad,std::vector<Sprite*> unos_sprites);
	bool lanzar(float pos_x,float pos_y);
	void renderizar(float x_dist_ventana, float posOtherPlayer);
	void setDimensionesMundo(float alto,float ancho);
	bool getVida();
	virtual ~ObjetoArrojable();
};

#endif /* SRC_MODEL_OBJETOARROJABLE_H_ */
