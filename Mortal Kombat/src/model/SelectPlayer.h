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
#include "../view/MenuSelectPlayer.h"
#include "../view/Ventana.h"

enum Players {PLAYER_ONE, PLAYER_TWO};

class SelectPlayer {
public:
	SelectPlayer(Ventana* una_ventana,int modo_de_juego,std::vector<Personaje*> personajes);
	void izquierda(int jugador);
	void derecha(int jugador);
	void arriba(int jugador);
	void abajo(int jugador);
	void select(int jugador);
	bool mousePosition(int x, int y, int jugador);
	void render();
	bool playersSelected();
	bool changeController();
	Personaje* getPersonajeUno();
	Personaje* getPersonajeDos();
	virtual ~SelectPlayer();
private:
	MenuSelectPlayer* menuPlayers;
	std::vector<Personaje*> personajes;
	std::vector<Personaje*> personajes_12;
	std::vector<Opcion_Personaje> opciones;
	int ModoDeJuego;
	int Player1;
	int Player2;
	bool player1Select;
	bool player2Select;
	void _verificarPersonajes();
};

#endif /* SRC_MODEL_SELECTPLAYER_H_ */
