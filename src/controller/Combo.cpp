/*
 * Combo.cpp
 *
 *  Created on: May 23, 2015
 *      Author: joni
 */

#include "Combo.h"

namespace std {

Combo::Combo(string botones, bool esFatality) {
	// TODO Auto-generated constructor stub
	m_botones = botones;
	_esFatality = esFatality;
}

bool Combo::getFatality(){
	return _esFatality;
}

Combo::~Combo() {
	// TODO Auto-generated destructor stub
}

} /* namespace std */
