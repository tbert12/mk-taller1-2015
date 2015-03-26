/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Personaje::Personaje(char* nombre_personaje) {
	nombre = malloc(sizeof(char*));
	memcpy(nombre,nombre_personaje,sizeof(nombre));
	vida = 100;
}

Personaje::~Personaje() {
	free(Nombre);
}

