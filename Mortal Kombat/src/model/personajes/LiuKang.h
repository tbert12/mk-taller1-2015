/*
 * LiuKang.h
 *
 *  Created on: 7/6/2015
 *      Author: tomi
 */

#ifndef SRC_MODEL_PERSONAJES_LIUKANG_H_
#define SRC_MODEL_PERSONAJES_LIUKANG_H_
#include "../Personaje.h"


namespace std {

class LiuKang : public Personaje{
public:
	LiuKang(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped=false);
	virtual ~LiuKang();

	void poder2();
	void fatality1(Personaje* personajeQueRecibe);

};

} /* namespace std */

#endif /* SRC_MODEL_PERSONAJES_LIUKANG_H_ */
