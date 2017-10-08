/*
 * Color.h
 *
 *  Created on: 28/4/2015
 *      Author: buby
 */

#ifndef SRC_MODEL_COLOR_H_
#define SRC_MODEL_COLOR_H_

#include <math.h>
#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>


using namespace std;


void RGBaHSV(Uint8 r, Uint8 g, Uint8 b, float *h, float *s, float *v);
void HSVaRGB(float h, float s, float v, Uint8* r, Uint8* g, Uint8* b);

void desplazarHue(float* h, float desplazamiento);


#endif /* SRC_MODEL_COLOR_H_ */
