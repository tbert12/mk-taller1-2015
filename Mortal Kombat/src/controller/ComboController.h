/*
 * ComboController.h
 *
 *  Created on: May 22, 2015
 *      Author: joni
 */

#ifndef COMBOCONTROLLER_H_
#define COMBOCONTROLLER_H_

#include <math.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
#include <map>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "Combo.h"


using namespace std;

enum Movimientros { ARRIBA, ABAJO, ADELANTE, ATRAS, PINAALTA, PINABAJA, PATADAALTA, PATADABAJA};

class ComboController {
public:

	ComboController(int tiempoMaximo,int distanciaMaxima, std::vector<Combo*> combosPosibles);

	int checkCombos();
	bool checkPosibleCombo();

	void sePresiono(int key);
	void Update();

	virtual ~ComboController();
private:

	std::vector<Combo*> _combosPosibles;
	std::map<int, int> mapaMovimientos;
	string _keys;
	unsigned int startingTime = 0;
	unsigned int currentTime;
	unsigned int lastTime;

	unsigned int maxTime;
	unsigned int maxLength;

	int distanciaLevenshtein(string s1,int len_s, string s2, int len_t);

};

#endif /* COMBOCONTROLLER_H_ */
