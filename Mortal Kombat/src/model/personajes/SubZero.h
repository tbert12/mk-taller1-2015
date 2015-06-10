/*
 * SubZero.h
 *
 *  Created on: 8/6/2015
 *      Author: tomi
 */

#ifndef SRC_MODEL_PERSONAJES_SUBZERO_H_
#define SRC_MODEL_PERSONAJES_SUBZERO_H_
#include "../Personaje.h"


namespace std {

class SubZero : public Personaje{
private:

	bool _estaHaciendoPoder;

	bool _estaHaciendoFatality;
	bool _pararDeRetrocederFatality1;

	bool _updatePropio();
	void _updatePoder2();
	void _updateFatality1();

	int _getaccionPropia();

	void _resetPropio();
public:
	SubZero(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped=false);
	virtual ~SubZero();

	void terminarAtaque();

	void poder2();
	void fatality1(Personaje* personajeQueRecibe);

};

} /* namespace std */

#endif /* SRC_MODEL_PERSONAJES_SUBZERO_H_ */
