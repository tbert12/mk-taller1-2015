/*
 * Personaje.h
 *
 *  Created on: 26/3/2015
 *      Author: Facu
 */

#ifndef SRC_MODEL_PERSONAJE_H_
#define SRC_MODEL_PERSONAJE_H_

class Personaje {
	std::string nombre;
	int vida;
	std::list<char*> sprites;

public:
	Personaje(char* nombre_personaje);
	std::list<char*> Sprites();
	int Vida();
	void QuitarVida(int valor);
	virtual ~Personaje();
};

#endif /* SRC_MODEL_PERSONAJE_H_ */
