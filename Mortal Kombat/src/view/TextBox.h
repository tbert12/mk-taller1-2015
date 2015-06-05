/*
 * TextBox.h
 *
 *  Created on: 5/6/2015
 *      Author: tomi
 */

#ifndef SRC_VIEW_TEXTBOX_H_
#define SRC_VIEW_TEXTBOX_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../model/logging.h"
#include "Ventana.h"

#define PATH_FONT "data/font/fuente.ttf"
#define SIZE_FONT 28

namespace std {

class TextBox {
private:
	Ventana* mVentana;
	SDL_Texture* mTexture;
	TTF_Font* gFont;
	string mTexto;

	SDL_Color textColor;
	SDL_Color borderColor;
	int dcolor;

	/* Posicion */
	SDL_Rect mDimension;

	int mWidth;
	int mHeight;


	void _loadFromRenderedText(string textureText);
	void _loadFont();

	void _renderText(int x, int y, SDL_Rect* clip);


public:
	TextBox(int x,int y,int h,int w, Ventana* ventana);
	void focus(bool enfocar);
	void render();
	void borrarUltimoChar();
	void appendString( char* frase);
	string getText();
	virtual ~TextBox();

};

} /* namespace std */

#endif /* SRC_VIEW_TEXTBOX_H_ */
