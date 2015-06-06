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
	Player1 = rand() % MAX_PLAYER + 1;
	Player2 = rand() % MAX_PLAYER + 1;
	player1Select = false;
	player2Select = false;
	menuPlayers = new MenuSelectPlayer(una_ventana,personajes,ModoDeJuego);
	opciones = menuPlayers->getOpciones();
}

bool SelectPlayer::playersSelected(){
	return player1Select && player2Select;
}

bool SelectPlayer::changeController(){
	return player1Select && !player2Select && (ModoDeJuego != MODO_JUGADOR_VS_JUGADOR);
}

Personaje* SelectPlayer::getPersonajeUno(){
	return personajes[Player1];
}
Personaje* SelectPlayer::getPersonajeDos(){
	return personajes[Player2];
}

void SelectPlayer::render(){
	menuPlayers->render(Player1,Player2);
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
		Player1-= 3;
		if (Player1 < 0)
			Player1 = MAX_PLAYER + Player1;
	}
	else if (jugador == PLAYER_TWO){
		if (player2Select) return;
		Player2-=3;
		if (Player2 < 0)
			Player2 = MAX_PLAYER + Player2;
	}
}
void SelectPlayer::abajo(int jugador){
	if (jugador == PLAYER_ONE){
		if (player1Select) return;
		Player1+= 3;
		if (Player1 > MAX_PLAYER)
			Player1 = Player1 - MAX_PLAYER;
	}
	else if (jugador == PLAYER_TWO){
		if (player2Select) return;
		Player2 += 3;
		if (Player2 > MAX_PLAYER)
			Player2 = Player2 - MAX_PLAYER;
	}
}
void SelectPlayer::select(int jugador){
	if (jugador == PLAYER_ONE){
		player1Select = true;
	}
	else if (jugador == PLAYER_TWO){
		player2Select = true;
	}
}

bool SelectPlayer::mousePosition(int x, int y){
	if (player1Select) return false;
	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		SDL_Rect rect = opciones[i].posicion;
		if (x >= rect.x and x <= (rect.x + rect.w) ){
			if (y >= rect.y and y <= (rect.y + rect.h) ){
				Player1 = i;
				return true;
			}
		}
	}
	return false;
}

SelectPlayer::~SelectPlayer() {
}

