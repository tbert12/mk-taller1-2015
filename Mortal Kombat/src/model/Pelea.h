/*
 * Pelea.h
 *
 *  Created on: 28/3/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_PELEA_H_
#define SRC_MODEL_PELEA_H_
#include "Tiempo.h"

namespace Pelea {

class Pelea {
public:
	Pelea();
	void Tiempo(Tiempo* tiempo_pelea);
	virtual ~Pelea();
};

} /* namespace Pelea */

#endif /* SRC_MODEL_PELEA_H_ */
