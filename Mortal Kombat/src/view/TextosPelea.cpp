/*
 * FightText.cpp
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#include "TextosPelea.h"

using namespace std;

TextosPelea::TextosPelea() {
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
	int x = 0; //pos x de la ventana en pixels
	int y = 0; //pos y de la ventana en pixels
	spriteFight->renderSpecialText(x,y);
	spriteFight->Advance();
}

void TextosPelea::renderFinishHim() {
	int x = 0; //pos x de la ventana en pixels
	int y = 0; //pos y de la ventana en pixels
	spriteFinishHim->renderSpecialText(x,y);
	spriteFinishHim->Advance();
}

void TextosPelea::renderFatality() {
	int x = 0; //pos x de la ventana en pixels
	int y = 0; //pos y de la ventana en pixels
	spriteFatality->renderSpecialText(x,y);
	spriteFatality->Advance();
}

TextosPelea::~TextosPelea() {
	if (spriteFight) delete spriteFight;
	if (spriteFinishHim) delete spriteFinishHim;
	if (spriteFatality) delete spriteFatality;
}

