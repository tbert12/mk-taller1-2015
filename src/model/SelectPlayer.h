/*
 * SelectPlayer.h
 *
 *  Created on: 4/6/2015
 *      Author: facu
 */

#ifndef SRC_MODEL_SELECTPLAYER_H_
#define SRC_MODEL_SELECTPLAYER_H_
#include "Personaje.h"
#include "Pelea.h"
#include "SoundMenu.h"
#include "../view/MenuSelectPlayer.h"
#include "../view/Ventana.h"
#include "../view/TextBox.h"

enum Players {PLAYER_ONE, PLAYER_TWO};
#define CICLOS_EN_VICTORIA 20

class SelectPlayer {
public:
	SelectPlayer(Ventana* una_ventana,int modo_de_juego,std::vector<Personaje*> personajes,SoundMenu* un_sound);
	void izquierda(int jugador);
	void derecha(int jugador);
	void arriba(int jugador);
	void abajo(int jugador);
	void select(int jugador);
	bool mousePosition(int x, int y, int jugador);
	void render();
	bool playersSelected();
	bool changeController();
	bool changeControllerTextBox();
	bool changeMouseController();
	bool textBox();
	Personaje* getPersonajeUno();
	Personaje* getPersonajeDos();
	TextBox* getTextBox();
	bool textBoxEnter(int jugador);
	bool textBoxButtonMouse(int x,int y);
	bool mouseinTextBox(int x , int y);
	virtual ~SelectPlayer();
private:
	MenuSelectPlayer* menuPlayers;
	std::vector<Personaje*> personajes;
	std::vector<Opcion_Personaje*> opciones;
	SoundMenu* sound;
	int ModoDeJuego;
	int Player1;
	int Player2;
	int ciclosDelay;
	SDL_Rect NameJug1;
	SDL_Rect NameJug2;
	bool player1Select;
	bool player2Select;
	bool textBoxPlayer1;
	bool textBoxPlayer2;
	TextBox* text_Box_1;
	TextBox* text_Box_2;
};

#endif /* SRC_MODEL_SELECTPLAYER_H_ */
