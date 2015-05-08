/*
 * Color.cpp
 *
 *  Created on: 28/4/2015
 *      Author: buby
 */

#include "Color.h"

using namespace std;


void RGBaHSV(Uint8 r, Uint8 g, Uint8 b, float* h, float* s, float* v) {

	float max_rgb = fmax(r, fmax(g, b));
	float min_rgb = fmin(r, fmin(g, b));

	float chroma = max_rgb - min_rgb;
	*v = max_rgb;
	if ( *v != 0 ) {
		*s = chroma / (*v);
	} else *s = 0;

	float hue;
	if ( chroma != 0 ) {
		if (max_rgb == r) hue = (g-b)/chroma;
		else if (max_rgb == g) hue = ( (b-r)/chroma ) + 2;
		else if (max_rgb == b) hue = ( (r-g)/chroma ) + 4;
		*h = hue*60;
		if (*h < 0)
			*h += 360;
	} else *h = 0;	// indefinido
}

void HSVaRGB(float h, float s, float v, Uint8* r, Uint8* g, Uint8* b) {

	int i;
	float f, p, q, t;


	if( s == 0 ) {
		// acromatico (gris)
		*r = *g = *b = v;
		return;
	}


	h /= 60;			// sector 0 a 5
	i = floor( h );
	f = h - i;
	p = v * ( 1 - (s) );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}
}

void desplazarHue(float* h, float desplazamiento) {
	(*h) += desplazamiento;
	*h = fmod(*h, 360);
	if ( (*h) < 0 ) {
		(*h) = fabs((*h));
		(*h) = 360 - (*h);
	}
}
