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
#define ciclos_por_segundo 10

enum {CABEZA,SANGRE_MUCHA,SANGRE_GOTA,SANGRE_CHICA};

class ObjetoDroppable {
public:
	ObjetoDroppable(string nombre, float velocidad, Sprite* un_sprites,bool loopeable);
	void y_piso(float y_piso);
	void lanzar(float pos_x,float pos_y,bool flipeo, bool rebotar, int cantidad=1);
	void reset();
	void renderizar(float x_dist_ventana);
	bool getVida();
	virtual ~ObjetoDroppable();

private:
	string nombre;
	bool vida;
	bool loop;
	bool mRebotar;
	int tiempo;
	int mCantidad;
	float velocidad;
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
