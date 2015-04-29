/*
 * Color.cpp
 *
 *  Created on: 28/4/2015
 *      Author: buby
 */

#include "Color.h"

using namespace std;


void RGBaHSV(Uint8 r, Uint8 g, Uint8 b, float* h, float* s, float* v) {

	// Primero transformo los valores RGB a floats del rango [0,1].
	float r1, g1, b1;
	r1 = r / 255.0;
	g1 = g / 255.0;
	b1 = b / 255.0;

	float max_rgb = fmax(r1, fmax(g1, b1));
	float min_rgb = fmin(r1, fmin(g1, b1));

	float chroma = max_rgb - min_rgb;
	*v = max_rgb;
	if ( *v != 0 ) {
		*s = chroma / (*v);
	} else *s = 0;

	float hue;
	if ( chroma != 0 ) {
		if (max_rgb == r1) hue = (g1-b1)/chroma;
		else if (max_rgb == g1) hue = ( (b1-r1)/chroma ) + 2;
		else if (max_rgb == b1) hue = ( (r1-g1)/chroma ) + 4;
		*h = hue*60;
		if (*h < 0)
			*h += 360;
	} else *h = 0;	// indefinido
}

void HSVaRGB(float h, float s, float v, Uint8* r, Uint8* g, Uint8* b) {

	// Para transformar los valores RGB al rango de [0,255].
	float r1, g1, b1;

	int i;
	float f, p, q, t;

	if( s == 0 ) {
		// acromatico (gris)
		r1 = g1 = b1 = v;
		*r = (Uint8) r1*255;
		*g = (Uint8) g1*255;
		*b = (Uint8) b1*255;
		return;
	}

	h /= 60;			// sector 0 a 5
	i = floor( h );
	f = h - i;
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			r1 = v;
			g1 = t;
			b1 = p;
			break;
		case 1:
			r1 = q;
			g1 = v;
			b1 = p;
			break;
		case 2:
			r1 = p;
			g1 = v;
			b1 = t;
			break;
		case 3:
			r1 = p;
			g1 = q;
			b1 = v;
			break;
		case 4:
			r1 = t;
			g1 = p;
			b1 = v;
			break;
		default:		// case 5:
			r1 = v;
			g1 = p;
			b1 = q;
			break;
	}
	*r = (Uint8) r1*255;
	*g = (Uint8) g1*255;
	*b = (Uint8) b1*255;
}

void desplazarHue(float* h, float desplazamiento) {
	*h += desplazamiento;
	*h = fmod(*h, 360);
	if ( *h < 0 ) {
		*h = 360 - (*h);
	}
}
