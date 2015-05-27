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

bool findRecursive(string s1,char c1,int pos1, char c2, int pos2){
	string sub = s1.substr(pos1);
	int newPosC2 = sub.find(c2);
	return newPosC2 > -1;
}

bool ComboController::checkPosibleCombo(){

	if(_keys.compare("") == 0){
		return false;
	}

	string botonesDelCombo;

	bool hayPosibilidadDeCombo = false;
	for(unsigned int i=0; i < _combosPosibles.size();i++){
		botonesDelCombo = _combosPosibles[i]->m_botones;
		vector<int> valorFind(botonesDelCombo.length());
		for(unsigned int j = 0; j < botonesDelCombo.size(); j++){
			char item = botonesDelCombo[j];
			valorFind[j]=_keys.find(item);
		}
		bool hayPosibilidad = true;
		if(valorFind[0] < 0){
			hayPosibilidad=false;
		}else{
			for(unsigned int j = 0; j < valorFind.size() -1; j++){
				if(j > 0){
					if( (valorFind[j] <0 and valorFind[j+1] >0) or valorFind[j-1] < 0  or (valorFind[j] > valorFind[j+1] and not((valorFind[j] < 0 and valorFind[j+1] < 0) or ((valorFind[j] > valorFind[j+1]) and valorFind[j+1] == -1))) ){
						if(not(valorFind[j] > valorFind[j+1])){
							hayPosibilidad=false;
							break;
						}
						if(not(findRecursive(_keys,botonesDelCombo[j+1], valorFind[j], botonesDelCombo[j], valorFind[j+1]))){
							hayPosibilidad=false;
							break;
						}
					}
				}
			}
		}
		hayPosibilidadDeCombo = hayPosibilidadDeCombo or hayPosibilidad;
		fprintf(stderr,"hay posibilidad %i  \n",hayPosibilidadDeCombo);
	}
	//fprintf(stderr,"hay posibilidad %i  \n",hayPosibilidadDeCombo);
	return hayPosibilidadDeCombo;
}

void ComboController::Update(){
	currentTime = SDL_GetTicks();

	if(_keys.compare("") > 0){
		fprintf(stderr,"keys %s  \n",_keys.c_str());
	}

	if(currentTime < maxTime)
		return;

	if(currentTime > (lastTime+ maxTime/maxLength)){
		if(_keys.length() > 1)
			_keys = _keys.substr(1 ,_keys.length() -1);
		else
			_keys = "";
		lastTime = currentTime ;
	}

	/*
	 *Insertar codigo de update aqui
	 */

}

void ComboController::sePresiono(int key){
	string caracter = std::to_string(key);
	_keys = _keys + caracter.c_str();
}

ComboController::~ComboController() {
	// TODO Auto-generated destructor stub
}


