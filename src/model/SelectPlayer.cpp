/*
 * SelectPlayer.cpp
 *
 *  Created on: 4/6/2015
 *      Author: facu
 */

#include "SelectPlayer.h"

SelectPlayer::SelectPlayer(Ventana* una_ventana,int modo_de_juego,std::vector<Personaje*> los_personajes,SoundMenu* un_sound) {
	ModoDeJuego = modo_de_juego;
	sound = un_sound;
	personajes = los_personajes;
	Player1 = rand() % MAX_PLAYER + 1;
	Player2 = rand() % MAX_PLAYER + 1;
	while (Player1 == Player2)
		Player2 = rand() % MAX_PLAYER + 1;
	player1Select = false;
	player2Select = false;
	textBoxPlayer1 = false;
	textBoxPlayer2 = false;
	menuPlayers = new MenuSelectPlayer(una_ventana,personajes,ModoDeJuego);
	NameJug1 = menuPlayers->getRectName1();
	NameJug2 = menuPlayers->getRectName2();
	text_Box_1 = new TextBox(NameJug1,una_ventana);
	text_Box_2 = new TextBox(NameJug2,una_ventana);
	opciones = menuPlayers->getOpciones();
	ciclosDelay = CICLOS_EN_VICTORIA;
}

bool SelectPlayer::playersSelected(){
	return (player1Select and player2Select and (ciclosDelay <= 0) and !textBoxPlayer1 and !textBoxPlayer2);
}

TextBox* SelectPlayer::getTextBox(){
	if (textBoxPlayer1)
		return text_Box_1;
	else if (textBoxPlayer2)
		return text_Box_2;
	else return NULL;
}

bool SelectPlayer::changeController(){
	if (ModoDeJuego == MODO_JUGADOR_VS_JUGADOR){
		return false;
	}
	else
		return player1Select && !player2Select;
}

bool SelectPlayer::changeMouseController(){
	return player1Select && !player2Select;
}

bool SelectPlayer::changeControllerTextBox(){
	return !textBoxPlayer1 and textBoxPlayer2;
}

Personaje* SelectPlayer::getPersonajeUno(){
	personajes[Player1]->reset();
	return personajes[Player1];
}
Personaje* SelectPlayer::getPersonajeDos(){
	personajes[Player2]->reset();
	return personajes[Player2];
}

void SelectPlayer::render(){
	if (!textBoxPlayer1)
		text_Box_1->setText(personajes[Player1]->getNombre());
	if (!textBoxPlayer2)
		text_Box_2->setText(personajes[Player2]->getNombre());
	menuPlayers->render(Player1,Player2,player1Select,player2Select,text_Box_1,text_Box_2);
	if (player1Select and player2Select and !textBoxPlayer1 and !textBoxPlayer2){
		ciclosDelay--;
	}
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
	sound->play(MOVE);
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
	sound->play(MOVE);
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
	sound->play(MOVE);
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
	sound->play(MOVE);
}
void SelectPlayer::select(int jugador){
	if (jugador == PLAYER_ONE){
		player1Select = true;
		textBoxPlayer1 = true;
		ciclosDelay = CICLOS_EN_VICTORIA;
		text_Box_1->focus(true);
		opciones[Player1]->personaje->victoria();
		sound->play(SELECT);
	}
	else if (jugador == PLAYER_TWO){
		player2Select = true;
		textBoxPlayer2 = true;
		ciclosDelay = CICLOS_EN_VICTORIA;
		text_Box_2->focus(true);
		//ACA if player1selected return
		opciones[Player2]->personaje->victoria();
		sound->play(SELECT);
	}
}

bool SelectPlayer::mousePosition(int x, int y, int jugador){

	if (player1Select and jugador == PLAYER_ONE) return false;
	if (player2Select and jugador == PLAYER_TWO) return false;

	for (unsigned int i = 0 ; i < opciones.size() ; i++){
		SDL_Rect rect = opciones[i]->posicion;
		if (x >= rect.x and x <= (rect.x + rect.w) ){
			if (y >= rect.y and y <= (rect.y + rect.h) ){
				if (jugador == PLAYER_ONE){
					if(Player1 != (int)i){
						Player1 = i;
						sound->play(MOVE);
					}
				}
				else if (jugador == PLAYER_TWO){
					if (Player2 != (int)i){
						Player2 = i;
						sound->play(MOVE);
					}
				}
				return true;
			}
		}
	}
	return false;
}

bool SelectPlayer::mouseinTextBox(int x, int y){
	if (x >= NameJug1.x and x <= (NameJug1.x + NameJug1.w) ){
		if (y >= NameJug1.y and y <= (NameJug1.y + NameJug1.h) ){
			sound->play(MOVE);
			return true;
		}
	}

	if (x >= NameJug2.x and x <= (NameJug2.x + NameJug2.w) ){
		if (y >= NameJug2.y and y <= (NameJug2.y + NameJug2.h) ){
			sound->play(MOVE);
			return true;
		}
	}

	return false;
}
/*
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
*/
bool SelectPlayer::textBox(){
	return textBoxPlayer1 || textBoxPlayer2;
}

bool SelectPlayer::textBoxEnter(int jugador){
	if (ModoDeJuego != MODO_JUGADOR_VS_JUGADOR)
		jugador = textBoxPlayer1 ?PLAYER_ONE: PLAYER_TWO;
	if (textBoxPlayer1 and jugador == PLAYER_ONE){
		personajes[Player1]->setNombre(text_Box_1->getText());
		text_Box_1->focus(false);
		textBoxPlayer1 = false;
		return true;
		sound->play(SELECT);
	}
	if (textBoxPlayer2 and jugador == PLAYER_TWO){
		personajes[Player2]->setNombre(text_Box_2->getText());
		text_Box_2->focus(false);
		textBoxPlayer2 = false;
		return true;
		sound->play(SELECT);
	}
	return false;
}

bool SelectPlayer::textBoxButtonMouse(int x,int y){
	if (textBoxPlayer1){
		if (x >= NameJug1.x and x <= (NameJug1.x + NameJug1.w) ){
			if (y >= NameJug1.y and y <= (NameJug1.y + NameJug1.h) ){
				personajes[Player1]->setNombre(text_Box_1->getText());
				text_Box_1->focus(false);
				textBoxPlayer1 = false;
				sound->play(SELECT);
				return true;
			}
		}
	}
	if (textBoxPlayer2){
		if (x >= NameJug2.x and x <= (NameJug2.x + NameJug2.w) ){
			if (y >= NameJug2.y and y <= (NameJug2.y + NameJug2.h) ){
				personajes[Player2]->setNombre(text_Box_2->getText());
				text_Box_2->focus(false);
				textBoxPlayer2 = false;
				sound->play(SELECT);
				return true;
			}
		}
	}
	return false;
}

SelectPlayer::~SelectPlayer() {
	delete text_Box_1;
	delete text_Box_2;
	delete menuPlayers;
}

