/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

class Personaje {
	char* nombre;
	int vida;

public:
	Personaje(char* nombre_personaje);
	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
