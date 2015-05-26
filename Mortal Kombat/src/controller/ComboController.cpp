/*
 * ComboController.cpp
 *
 *  Created on: May 22, 2015
 *      Author: joni
 */

#include "ComboController.h"

ComboController::ComboController (int tiempoMaximo,int distanciaMaxima, vector<Combo*> combosPosibles) {
	// TODO Auto-generated constructor stub
	maxTime = tiempoMaximo * 1000;
	fprintf(stderr,"%s \n",_keys.c_str());
	maxLength = distanciaMaxima;
	startingTime = SDL_GetTicks();

	currentTime = startingTime;
	lastTime = 0;
	_combosPosibles = combosPosibles;

	_keys = "";
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

int ComboController::checkCombos(){
	if(_keys.compare(""))
		return 1;

	return 0;
}

bool ComboController::checkPosibleCombo(){
	if(_keys.compare(""))
		return false;
	string botonesDelCombo;
	for(unsigned int i=0; i < _combosPosibles.size();i++){
		botonesDelCombo = _combosPosibles[i]->m_botones;
		int valorFind = 0;
		/*for(unsigned int j = 0; j < botonesDelCombo.size(); j++){
			int item = botonesDelCombo[j];

		}*/
	}
	return false;
}

void ComboController::Update(){
	currentTime = SDL_GetTicks();

	//fprintf(stderr,"curr/last %i  \n",currentTime/maxLength );
	/*fprintf(stderr,"curr %i  \n",currentTime);
	fprintf(stderr,"last %i  \n",lastTime);*/

	if(_keys.length() > 10){
		_keys = _keys.substr(_keys.length() - 11,10);
	}
	if(currentTime > (lastTime+ maxTime/maxLength)){
		if(_keys.length() > 2)
			_keys = _keys.substr(1 ,_keys.length() -2);
		lastTime = currentTime ;
	}
	fprintf(stderr,"keys %s  \n",_keys.c_str());

	/*
	 *Insertar codigo de update aqui
	 */

}

void ComboController::sePresiono(int key){
	string caracter = std::to_string(key-'a');
	_keys = _keys + caracter.c_str();
	//fprintf(stderr,"keys %s\n",_keys.c_str());
}

ComboController::~ComboController() {
	// TODO Auto-generated destructor stub
}


