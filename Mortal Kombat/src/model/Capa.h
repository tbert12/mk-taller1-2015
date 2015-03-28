/*
 * Capa.h
 *
 *  Created on: Mar 26, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPA_H_
#define SRC_MODEL_CAPA_H_

class Capa {
public:
	int getZIndex();
	void Actualizar();
	void Mover(int y_pos, int velocidad);
};

#endif /* SRC_MODEL_CAPA_H_ */
