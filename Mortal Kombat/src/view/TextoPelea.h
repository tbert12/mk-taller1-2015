/*
 * FightText.h
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#ifndef SRC_VIEW_TEXTOPELEA_H_
#define SRC_VIEW_TEXTOPELEA_H_

#include "Sprite.h"

class TextoPelea {

private:
	Sprite* sprite;
public:
	TextoPelea(Sprite* sprite);
	void render();
	virtual ~TextoPelea();
};

#endif /* SRC_VIEW_TEXTOPELEA_H_ */
