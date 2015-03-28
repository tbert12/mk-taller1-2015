/*
 * CapaPrincipal.h
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#ifndef SRC_MODEL_CAPAPRINCIPAL_H_
#define SRC_MODEL_CAPAPRINCIPAL_H_

#include "Capa.h"
#include "Personaje.h"

class CapaPrincipal: public Capa {

public:
	CapaPrincipal(Personaje* personaje);
	virtual ~CapaPrincipal();

private:
	Personaje* m_Personaje;
};


#endif /* SRC_MODEL_CAPAPRINCIPAL_H_ */
