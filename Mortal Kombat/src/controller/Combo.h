/*
 * Combo.h
 *
 *  Created on: May 23, 2015
 *      Author: joni
 */

#ifndef COMBO_H_
#define COMBO_H_

#include <string>

enum Combos { PODER1, PODER2, FATALITY1 };

namespace std {

class Combo {

private:
	bool _esFatality;

public:

	Combo(string botones, bool fatality = false);
	virtual ~Combo();

	string m_botones;

	bool getFatality();
};

} /* namespace std */

#endif /* COMBO_H_ */
