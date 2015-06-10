/*
 * FightText.h
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#ifndef SRC_VIEW_TEXTOSPELEA_H_
#define SRC_VIEW_TEXTOSPELEA_H_

#include "Sprite.h"

class TextosPelea {

private:
	Sprite* spriteFight = NULL;
	Sprite* spriteFinishHim = NULL;
	Sprite* spriteFatality = NULL;
	bool Fight;
	bool FinishHim;
	bool Fatality;
public:
	TextosPelea();
	void reset();

	void renderFight();
	void renderFinishHim();
	void renderFatality();

	bool fight();

	void setTextoFight(Sprite* spriteTextoFight);
	void setTextoFinishHim(Sprite* spriteTextoFinishHim);
	void setTextoFatality(Sprite* spriteTextoFatality);

	virtual ~TextosPelea();
};

#endif /* SRC_VIEW_TEXTOSPELEA_H_ */
