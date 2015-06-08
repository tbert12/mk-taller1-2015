/*
 * FightText.h
 *
 *  Created on: 8/6/2015
 *      Author: buby
 */

#ifndef SRC_VIEW_FIGHTTEXT_H_
#define SRC_VIEW_FIGHTTEXT_H_

#include <SDL2/SDL_ttf.h>
#include <string>
#include "Ventana.h"

class FightText {

private:
	std::string texto;
	float duracion;
	int ancho;
	int alto;
	Ventana* m_ventana;
	SDL_Texture* m_textura;
	TTF_Font *font;
	SDL_Color textColor;
	bool loadFromRenderedText(std::string textureText);

public:
	FightText(Ventana* ventana, std::string texto, float duracion);
	virtual ~FightText();
	void render();
};

#endif /* SRC_VIEW_FIGHTTEXT_H_ */
