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
	int x = 0; //pos x de la ventana en pixels
	int y = 0; //pos y de la ventana en pixels
	sprite->renderSpecialText(x,y);
	sprite->Advance();
}

TextoPelea::~TextoPelea() {
	delete sprite;
}

