/*
 * SelectPlayer.cpp
 *
 *  Created on: 4/6/2015
 *      Author: facu
 */

#include "SelectPlayer.h"

SelectPlayer::SelectPlayer(Ventana* una_ventana,int modo_de_juego,std::vector<Personaje*> los_personajes) {
	ModoDeJuego = modo_de_juego;
	personajes = los_personajes;
	_verificarPersonajes();
	Player1 = rand() % MAX_PLAYER + 1;
	Player2 = rand() % MAX_PLAYER + 1;
	player1Select = false;
	player2Select = false;
	textBoxPlayer1 = false;
	textBoxPlayer2 = false;
	menuPlayers = new MenuSelectPlayer(una_ventana,personajes_12,ModoDeJuego);
	NameJug1 = menuPlayers->getRectName1();
	NameJug2 = menuPlayers->getRectName2();
	text_Box_1 = new TextBox(NameJug1,una_ventana);
	text_Box_2 = new TextBox(NameJug2,una_ventana);
	opciones = menuPlayers->getOpciones();
}

bool SelectPlayer::playersSelected(){
	return player1Select && player2Select;
}

TextBox* SelectPlayer::getTextBox(){
	if (textBoxPlayer1)
		return text_Box_1;
	else if (textBoxPlayer2)
		return text_Box_2;
	else return NULL;
}

bool SelectPlayer::changeController(){
	if (ModoDeJuego == MODO_JUGADOR_VS_JUGADOR)
		return false;
	else
		return player1Select && !player2Select;
}

Personaje* SelectPlayer::getPersonajeUno(){
	personajes_12[Player1]->reset();
	return personajes_12[Player1];
}
Personaje* SelectPlayer::getPersonajeDos(){
	personajes_12[Player2]->reset();
	return personajes_12[Player2];
}

void SelectPlayer::render(){
	menuPlayers->render(Player1,Player2);
	if (!textBoxPlayer1)
		text_Box_1->setText(personajes_12[Player1]->getNombre());
	if (!textBoxPlayer2)
		text_Box_2->setText(personajes_12[Player2]->getNombre());
	text_Box_1->render();
	text_Box_2->render();
}

void SelectPlayer::izquierda(int jugador){
	if (jugador == PLAYER_ONE){
		if (player1Select) return;
		Player1--;
		if (Player1 < 0)
			Player1 = MAX_PLAYER;
	}
	else if (jugador == PLAYER_TWO){
		if (player2Select) return;
		Player2--;
		if (Player2 < 0)
			Player2 = MAX_PLAYER;
	}
}
void SelectPlayer::derecha(int jugador){
	if (jugador == PLAYER_ONE){
		if (player1Select) return;
		Player1++;
		if (Player1 > MAX_PLAYER)
			Player1 = 0;
	}
	else if (jugador == PLAYER_TWO){
		if (player2Select) return;
		Player2++;
		if (Player2 > MAX_PLAYER)
			Player2 = 0;
	}
}
void SelectPlayer::arriba(int jugador){
	if (jugador == PLAYER_ONE){
		if (player1Select) return;
		Player1-= 4;
		if (Player1 < 0)
			Player1 = MAX_PLAYER + Player1;
	}
	else if (jugador == PLAYER_TWO){
		if (player2Select) return;
		Player2-=4;
		if (Player2 < 0)
			Player2 = MAX_PLAYER + Player2;
	}
}
void SelectPlayer::abajo(int jugador){
	if (jugador == PLAYER_ONE){
		if (player1Select) return;
		Player1+= 4;
		if (Player1 > MAX_PLAYER)
			Player1 = Player1 - MAX_PLAYER;
	}
	else if (jugador == PLAYER_TWO){
		if (player2Select) return;
		Player2 += 4;
		if (Player2 > MAX_PLAYER)
			Player2 = Player2 - MAX_PLAYER;
	}
}
void SelectPlayer::select(int jugador){
	if (jugador == PLAYER_ONE){
		player1Select = true;
		opciones[Player1].personaje->victoria();
	}
	else if (jugador == PLAYER_TWO){
		player2Select = true;
		opciones[Player2].personaje->victoria();
	}
}

bool SelectPlayer::mousePosition(int x, int y, int jugador){
	if (player1Select and player2Select) return false;
	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		SDL_Rect rect = opciones[i].posicion;
		if (x >= rect.x and x <= (rect.x + rect.w) ){
			if (y >= rect.y and y <= (rect.y + rect.h) ){
				if (jugador == PLAYER_ONE)
					Player1 = i;
				else if (jugador == PLAYER_TWO)
					Player2 = i;
				return true;
			}
		}
	}
	return false;
}

bool SelectPlayer::mouseinTextBox(int x, int y){
	if (x >= NameJug1.x and x <= (NameJug1.x + NameJug1.w) ){
		if (y >= NameJug1.y and y <= (NameJug1.y + NameJug1.h) ){
			textBoxPlayer1 = true;
			textBoxPlayer2 = false;
			return true;
		}
	}

	if (x >= NameJug2.x and x <= (NameJug2.x + NameJug2.w) ){
		if (y >= NameJug2.y and y <= (NameJug2.y + NameJug2.h) ){
			textBoxPlayer2 = true;
			textBoxPlayer1 = false;
			return true;
		}
	}

	if (textBoxPlayer1) textBoxPlayer1 = false;
	if (textBoxPlayer2) textBoxPlayer2 = false;

	return false;
}

void SelectPlayer::_verificarPersonajes(){
	unsigned int cant_real = personajes.size();
	bool copy = false;
	unsigned int contador = 0;
	for(unsigned int i = 0; i <= MAX_PLAYER; i++){
		if (copy)
			personajes_12.push_back(personajes[contador]->copy());
		else
			personajes_12.push_back(personajes[contador]);
		contador++;
		if (contador >= cant_real){
			contador = 0;
			if (!copy)
				copy = true;
		}
	}
}

bool SelectPlayer::textBox(){
	return textBoxPlayer1 || textBoxPlayer2;
}

void SelectPlayer::textBoxEnter(){

	if (textBoxPlayer1){
		//personajes_12[Player1]->setNombre(text_Box_1->getText());
		textBoxPlayer1 = false;
	}
	if (textBoxPlayer2){
		//personajes_12[Player2]->setNombre(text_Box_2->getText());
		textBoxPlayer2 = false;
	}
}

SelectPlayer::~SelectPlayer() {
	personajes_12.clear();
	delete text_Box_1;
	delete text_Box_2;
}

