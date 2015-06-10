/*
 * Jax.h
 *
 *  Created on: 10/6/2015
 *      Author: tomi
 */

#ifndef SRC_MODEL_PERSONAJES_JAX_H_
#define SRC_MODEL_PERSONAJES_JAX_H_
#include "../Personaje.h"


namespace std {

class Jax : public Personaje{
private:
	bool _estaHaciendoPoder;
	int duracionPoder;
	void _resetDuracion();
	bool _updatePropio();
	int _getaccionPropia();
	void _resetPropio();

	bool _estaHaciendoFatality;
	Personaje* personajeQueRecibe;

public:
	Jax(string nombre_personaje,vector<Sprite*> Sprites,vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped=false);
	virtual ~Jax();
	void terminarAtaque();

	void poder2();
	void terminarPoder2();
	void fatality1(Personaje* personajeQueRecibe);

};

} /* namespace std */

#endif /* SRC_MODEL_PERSONAJES_JAX_H_ */
