/*
 * FightText.cpp
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#include "TextoPelea.h"

#define RUTA_FUENTE "data/font/mortalkombat5.ttf"

using namespace std;

TextoPelea::TextoPelea(Sprite* el_sprite) {
	sprite = el_sprite;
}

void TextoPelea::render() {
	//sprite->renderTexto();
	sprite->Advance();
}

TextoPelea::~TextoPelea() {
	// TODO Auto-generated destructor stub
}

