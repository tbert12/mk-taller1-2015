/*
 * Combo.h
 *
 *  Created on: May 23, 2015
 *      Author: joni
 */

#ifndef COMBO_H_
#define COMBO_H_

#include <vector>


namespace std {

class Combo {

public:

	Combo(vector<int> botones);
	virtual ~Combo();

	vector<int> m_botones;
};

} /* namespace std */

#endif /* COMBO_H_ */
