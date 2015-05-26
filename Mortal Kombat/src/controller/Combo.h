/*
 * Combo.h
 *
 *  Created on: May 23, 2015
 *      Author: joni
 */

#ifndef COMBO_H_
#define COMBO_H_

#include <string>


namespace std {

class Combo {

public:

	Combo(string botones);
	virtual ~Combo();

	string m_botones;
};

} /* namespace std */

#endif /* COMBO_H_ */
