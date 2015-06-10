/*
 * ComboController.cpp
 *
 *  Created on: May 22, 2015
 *      Author: joni
 */

#include "ComboController.h"

ComboController::ComboController (int tiempoMaximo,int cantidadMaximaErrores, vector<Combo*> combosPosibles) {
	maxTime = tiempoMaximo * 1000;
	maxErrors = cantidadMaximaErrores;
	startingTime = SDL_GetTicks();
	ultimoFueCombo = false;

	currentTime = startingTime;
	_combosPosibles = combosPosibles;

	_keys = "";
}

string ComboController::get_stream_teclas(){
	if (ultimoFueCombo)
		return _keysCombo;
	return _keys;
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

bool findRecursiveChar(string s1,char c1,int pos1, char c2, int pos2){
	string sub = s1.substr(pos1);
	int newPosC2 = sub.find(c2);
	return newPosC2 > -1;
}

bool findStringRecursive(string stringBase, string stringToFind, int maxErrors){

	int errores = 0;
	unsigned int encuentros = 1;
	//fprintf(stderr,"%s stringBase\n", stringBase.c_str());
	for(std::string::size_type i = 0; i < stringBase.size(); ++i) {
		if(stringToFind[encuentros] == stringBase[i]){
			encuentros++;
		}else{
			errores++;
		}
		if(errores>maxErrors){
			int nextPosInicial = stringBase.substr(1).find(stringToFind[0]);
			if(nextPosInicial<0 or nextPosInicial >= (int)(stringBase.size() - stringToFind.size())){
				return false;
			}
			return findStringRecursive(stringBase.substr(nextPosInicial+1),stringToFind,maxErrors);
		}
		if(encuentros == stringToFind.size()){

			return true;
		}
	}
	return false;
}

int ComboController::checkFatalities(){
	if(_keys.compare("") == 0){
		return -1;
	}
	int encontrado = -1;
	bool encontre = false;

	string botonesDelCombo;
	for(unsigned int i=0; i < _combosPosibles.size();i++){
		botonesDelCombo = _combosPosibles[i]->m_botones;
		int posicionDelBoton = _keys.find(botonesDelCombo[0]);
		if(posicionDelBoton < 0)
			continue;
		encontre = findStringRecursive(_keys,botonesDelCombo,maxErrors);
		if(encontre){
			encontrado = i;
			break;
		}
	}
	if (encontrado > -1 ){
		_keysCombo =_combosPosibles[encontrado]->m_botones;
		_keys="";
		keyTime.clear();
		ultimoFueCombo = true;
	}
	else ultimoFueCombo = false;
	return encontrado;
}

int ComboController::checkCombos(){
	return _checkCombos(false);
	/*if(_keys.compare("") == 0){
		return -1;
	}
	int encontrado = -1;
	bool encontre = false;

	string botonesDelCombo;
	for(unsigned int i=0; i < _combosPosibles.size();i++){
		botonesDelCombo = _combosPosibles[i]->m_botones;
		int posicionDelBoton = _keys.find(botonesDelCombo[0]);
		if(posicionDelBoton < 0)
			continue;
		encontre = findStringRecursive(_keys,botonesDelCombo,maxErrors);
		if(encontre){
			encontrado = i;
			break;
		}
	}
	if (encontrado > -1 ){
		_keysCombo =_combosPosibles[encontrado]->m_botones;
		_keys="";
		keyTime.clear();
		ultimoFueCombo = true;
	}
	else ultimoFueCombo = false;
	return encontrado;*/
}

int ComboController::_checkCombos(bool fatalities){
	if(_keys.compare("") == 0){
		return -1;
	}
	int encontrado = -1;
	bool encontre = false;

	string botonesDelCombo;
	for(unsigned int i=0; i < _combosPosibles.size();i++){
		if(_combosPosibles[i]->getFatality() != fatalities)
			continue;
		botonesDelCombo = _combosPosibles[i]->m_botones;
		int posicionDelBoton = _keys.find(botonesDelCombo[0]);
		if(posicionDelBoton < 0)
			continue;
		encontre = findStringRecursive(_keys,botonesDelCombo,maxErrors);
		if(encontre){
			encontrado = i;
			break;
		}
	}
	if (encontrado > -1 ){
		_keysCombo =_combosPosibles[encontrado]->m_botones;
		_keys="";
		keyTime.clear();
		ultimoFueCombo = true;
	}
	else ultimoFueCombo = false;
	return encontrado;
}

void ComboController::Update(){
	currentTime = SDL_GetTicks();

	if(_keys.length() == 0){
		return;
	}

	if(currentTime < maxTime)
		return;

	if(currentTime > (keyTime[0]+ maxTime)){
		if(_keys.length() > 1)
			_keys = _keys.substr(1 ,_keys.length() -1);
		else{
			_keys = "";
		}keyTime.erase(keyTime.begin());
	}

	/*
	 *Insertar codigo de update aqui
	 */

}

void ComboController::sePresiono(int key){
	string caracter = std::to_string(key);
	_keys = _keys + caracter.c_str();
	keyTime.push_back(SDL_GetTicks());
}

bool ComboController::combosInString(){
	return ultimoFueCombo;
}

ComboController::~ComboController() {
	maxTime = 0;
	maxErrors = 0;
	startingTime = 0;
	currentTime = 0;
}


