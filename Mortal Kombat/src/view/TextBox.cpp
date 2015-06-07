/*
 * TextBox.cpp
 *
 *  Created on: 5/6/2015
 *      Author: tomi
 */

#include "TextBox.h"


namespace std {

TextBox::TextBox(SDL_Rect rect, Ventana* ventana) {
	/* x,y,w,h correspondientes a la poscion y tamaño del cuadro de texto */
	mVentana = ventana;
	mDimension = rect;
	mTexto = " ";
	textColor = {255,0,0,255};
	borderColor = {0,255,0,255};
	dcolor = 0; /* diferencial color */
	_loadFont();

}

void TextBox::_loadFont(){
	gFont = TTF_OpenFont( PATH_FONT, SIZE_FONT );
	if( gFont == NULL ){
		log( "Error al inicializar Fuente de TextBox: %s" + string( TTF_GetError() ), LOG_ERROR );
	} else {
		log("Font del Textbox Cargada correctamente",LOG_DEBUG);
	}
}
void TextBox::focus(bool enfocar){
	if (enfocar)
		dcolor += 50; //Altena el color del borde para saber que esta enfocado
	else {
		borderColor = {255,0,0,255};
		dcolor = 0;
	}
}

void TextBox::setText(string text){
	mTexto = text;
}


void TextBox::_renderText(int x, int y, SDL_Rect* clip){
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( mVentana->getRenderer(), mTexture, clip, &renderQuad, 0, NULL, SDL_FLIP_NONE );
}

void TextBox::render(){
	//Generar Textura con texto
	if( mTexto != "" ){
		_loadFromRenderedText( mTexto.c_str());
	} else {
		_loadFromRenderedText(" ");
	}

	//Borde Con Focus
	int variacion = borderColor.b + dcolor;
	if (variacion > 255 or variacion < 0) {
		variacion = borderColor.b;
		dcolor = -dcolor;
	}
	borderColor.b = (Uint8)variacion;
	//SDL_SetRenderDrawColor(mVentana->getRenderer(), borderColor.r, borderColor.g, borderColor.b, borderColor.a);

	SDL_SetRenderDrawColor(mVentana->getRenderer(), 255, 0, 0, 255);
	SDL_RenderDrawRect(mVentana->getRenderer(), &mDimension);

	int ancho = mDimension.w;
	int x = mWidth - mDimension.w;
	if ( x < 0){
		x = 0;
		ancho = mWidth;
	}
	SDL_Rect CorteDeString = { x , 0 , ancho, mDimension.h };
	_renderText( mDimension.x, mDimension.y + mHeight * 0.2, &CorteDeString);
}

void TextBox::_loadFromRenderedText( string textureText){
	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( mVentana->getRenderer(), textSurface );
		if( mTexture == NULL )
		{
			log( "No se puede crear textura del texto renderizado! SDL Error: %s" +  string( SDL_GetError() ), LOG_ERROR );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		log( "No se puede crear TextBox! SDL_ttf Error: %s" + string( TTF_GetError() ), LOG_ERROR );
	}
}

void TextBox::borrarUltimoChar(){
	mTexto.pop_back();
}

void TextBox::appendString( char* append){
	mTexto += append;
}

string TextBox::getText(){
	return mTexto;
}


TextBox::~TextBox() {
	TTF_CloseFont( gFont );
}

} /* namespace std */
