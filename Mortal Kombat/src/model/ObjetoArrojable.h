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
	float m_velocidad_x;
	float m_velocidad_y;
	std::vector<Sprite*> sprites;
	float m_AltoMundo;
	float m_AnchoMundo;
	int sprite_actual;
	bool flip;

	void _Update();
	void _render(float x_dist_ventana);

public:
	ObjetoArrojable(string un_nombre,float velocidad,std::vector<Sprite*> unos_sprites);
	bool lanzar(float pos_x,float pos_y,bool flipeo);
	void renderizar(float x_dist_ventana);
	void setDimensionesMundo(float alto,float ancho);
	bool getVida();
	void destruir();
	float getPosX();
	virtual ~ObjetoArrojable();
};

#endif /* SRC_MODEL_OBJETOARROJABLE_H_ */
