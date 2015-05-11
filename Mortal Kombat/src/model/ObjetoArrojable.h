/*
 * ObjetoArrojable.h
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_OBJETOARROJABLE_H_
#define SRC_MODEL_OBJETOARROJABLE_H_
#define VELOCIDAD_DEFAULT 10;

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
	Sprite* sprite;
	float m_AltoMundo;
	float m_AnchoMundo;
	bool flip;
	bool m_destruir;
	void _avanzarSprite();
	void _terminar();
	void _Update();
	void _render(float x_dist_ventana);

public:
	ObjetoArrojable(string un_nombre,float velocidad,Sprite* un_sprites);
	bool lanzar(float pos_x,float pos_y,bool flipeo);
	void renderizar(float x_dist_ventana);
	void setDimensionesMundo(float alto,float ancho);
	bool getVida();
	void destruir();
	float getPosX();
	Rect_Logico* rectanguloAtaque();
	Rect_Logico* nextRectAtaque();
	void update();
	virtual ~ObjetoArrojable();
};

#endif /* SRC_MODEL_OBJETOARROJABLE_H_ */
