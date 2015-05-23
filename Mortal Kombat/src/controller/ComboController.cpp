/*
 * ComboController.cpp
 *
 *  Created on: May 22, 2015
 *      Author: joni
 */

#include "ComboController.h"

ComboController::ComboController (int tiempoMaximo,int distanciaMaxima, vector<Combo*> combosPosibles) {
	// TODO Auto-generated constructor stub
	maxTime = tiempoMaximo;
	maxLength = distanciaMaxima;
	startingTime = SDL_GetTicks();
	lastTime = SDL_GetTicks();
	currentTime = SDL_GetTicks();
	_combosPosibles = combosPosibles;
}


int ComboController::distanciaLevenshtein(string s1,int len_s, string s2, int len_t){
	  /* base case: empty strings */
	if (len_s == 0) return len_t;
	if (len_t == 0) return len_s;

	/* test if last characters of the strings match */
	int cost= 0;
	if (!(s1[len_s-1] == s2[len_t-1]))
		cost = 1;

	/* return minimum of delete char from s, delete char from t, and delete char from both */
	return std::min(distanciaLevenshtein(s1, len_s - 1, s2, len_t    ) + 1,
					std::min(distanciaLevenshtein(s1, len_s    , s2, len_t - 1) + 1,
							distanciaLevenshtein(s1, len_s - 1, s2, len_t - 1) + cost)
				);
}

bool ComboController::checkCombo(Combo* combo){
	if(_keys.empty())
		return 1;

	return 0;
}

bool ComboController::checkPosibleCombo(){
	if(_keys.empty())
		return false;
	vector<int> botonesDelCombo;
	for(unsigned int i=0; i < _combosPosibles.size();i++){
		botonesDelCombo = _combosPosibles[i]->m_botones;
		vector<int> vectorValorPosiciones;
		int valorFind = 0;
		for(unsigned int j = 0; j < botonesDelCombo.size(); j++){
			int item = botonesDelCombo[j];
			valorFind =std::find(_keys.begin(), _keys.end(), item);
			if(item!=_keys.end()){

			}
		}
	}
	return false;
}

void ComboController::Update(){
	currentTime = SDL_GetTicks();
	if(currentTime / lastTime > currentTime / maxTime){
		_keys.erase(_keys.begin());
		lastTime = currentTime ;
	}
	/*
	 *Insertar codigo de update aqui
	 */

}

void ComboController::sePresiono(int key){
	_keys.push_back(key);
}

ComboController::~ComboController() {
	// TODO Auto-generated destructor stub
}


