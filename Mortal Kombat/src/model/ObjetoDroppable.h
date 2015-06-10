/*
 * ObjetoDroppable.h
 *
 *  Created on: 9/6/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_OBJETODROPPABLE_H_
#define SRC_MODEL_OBJETODROPPABLE_H_

#include <string>
#include "../view/Sprite.h"
#define VELOCIDAD_OBJETO_DEFAULT 5
#define G 10
#define ciclos_por_segundo 40

enum {SANGRE, CABEZA};

class ObjetoDroppable {
public:
	ObjetoDroppable(Sprite* un_sprites,float y_piso,bool loopeable);
	void lanzar(float pos_x,float pos_y,bool flipeo);
	void renderizar(float x_dist_ventana);
	bool getVida();
	virtual ~ObjetoDroppable();

private:
	bool vida;
	bool loop;
	int tiempo;
	float m_yPiso;
	float m_xActual;
	float m_yActual;
	float m_xInicial;
	float m_yInicial;
	float m_velocidad_x;
	float m_velocidad_y;
	int contadorPorWhile;
	Sprite* sprite;
	bool flip;
	void _avanzarSprite();
	void _terminar();
	void _Update();
	void _render(float x_dist_ventana);
	void _verificarTiempo();
};

#endif /* SRC_MODEL_OBJETODROPPABLE_H_ */
