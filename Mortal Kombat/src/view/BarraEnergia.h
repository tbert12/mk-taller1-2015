/*
 * BarraEnergia.h
 *
 *  Created on: 23/4/2015
 *      Author: facu
 */

#include "Ventana.h"
#ifndef SRC_VIEW_BARRAENERGIA_H_
#define SRC_VIEW_BARRAENERGIA_H_

class BarraEnergia {
private:
	int maximo_barra;
	int actual;
	int velocidad_descarga;
	float ancho_logico;
	float alto_logico;
	float ratio_x;
	float ratio_y;
	bool flip;
	Ventana* ventana;
	SDL_Texture* textura_base;
	SDL_Texture* textura_relleno;
	SDL_Rect* rect_base;
	SDL_Rect* rect_relleno;
	bool _loadBase();
	bool _loadRelleno();
	void _calcularRatios();
	void _renderBase();
	void _renderRelleno(int estado);
	void _actualizarActual(int estado);

	//Nombre Texto
	int anchoTexto,altoTexto;
	bool _loadFromRenderedText( std::string textureText);
	void _renderText();
	string textoConstante;
	SDL_Texture* texturaNombreTexto;
	TTF_Font* font;
	SDL_Color textColor;
public:
	void render(int estado);
	BarraEnergia(Ventana* una_ventana,int maximo_barra);
	void setFlip();
	void setNombreBarra(string nombre);
	virtual ~BarraEnergia();
};

#endif /* SRC_VIEW_BARRAENERGIA_H_ */
