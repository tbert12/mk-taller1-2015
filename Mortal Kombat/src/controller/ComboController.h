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

enum Movimientos { ARRIBA, ABAJO, DERECHA, IZQUIERDA, PINAALTA, PINABAJA, PATADAALTA, PATADABAJA,CUBRIR};

class ComboController {
public:

	ComboController(int tiempoMaximo,int cantidadMaximaErrores, std::vector<Combo*> combosPosibles);

	int checkCombos();
	bool checkCombo(Combo* combo);
	vector<bool> checkPosibleCombo();

	void sePresiono(int key);
	void Update();

	string get_stream_teclas();
	virtual ~ComboController();
private:

	std::vector<Combo*> _combosPosibles;

	string _keys;

	unsigned int startingTime = 0;
	unsigned int currentTime;
	std::vector<int> keyTime;

	unsigned int maxTime;
	unsigned int maxErrors;

	int distanciaLevenshtein(string s1,int len_s, string s2, int len_t);

};

#endif /* COMBOCONTROLLER_H_ */
