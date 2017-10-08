/*
 * FightText.cpp
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#include "TextosPelea.h"

using namespace std;

TextosPelea::TextosPelea() {
	spriteFatality = NULL;
	spriteFight = NULL;
	spriteFinishHim = NULL;
	Fatality = false;
	FinishHim = false;
	Fight = false;
}

void TextosPelea::setTextoFight(Sprite* spriteTextoFight) {
	spriteFight = spriteTextoFight;
}

void TextosPelea::setTextoFinishHim(Sprite* spriteTextoFinishHim) {
	spriteFinishHim = spriteTextoFinishHim;
}

void TextosPelea::setTextoFatality(Sprite* spriteTextoFatality) {
	spriteFatality = spriteTextoFatality;
}

void TextosPelea::renderFight() {
	if (!spriteFight)return;
	spriteFight->renderSpecialText();
	if (!spriteFight->ultimoFrame())
		spriteFight->Advance();
	else{
		if(!Fight) Fight = true;
	}
}

bool TextosPelea::fight(){
	return Fight;
}

void TextosPelea::reset() {
	if (!spriteFight)return;
	spriteFight->hardReset();
	Fight = false;
}

void TextosPelea::renderFinishHim() {
	if (!spriteFinishHim) return;
	spriteFinishHim->renderSpecialText();
	spriteFinishHim->Advance();
}

void TextosPelea::renderFatality() {
	if (!spriteFatality) return;
	spriteFatality->renderSpecialText();
	spriteFatality->Advance();
}

TextosPelea::~TextosPelea() {
	if (spriteFight) delete spriteFight;
	if (spriteFinishHim) delete spriteFinishHim;
	if (spriteFatality) delete spriteFatality;
}

