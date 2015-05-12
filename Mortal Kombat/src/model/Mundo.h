/*
 * Mundo.h
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#ifndef SRC_MODEL_MUNDO_H_
#define SRC_MODEL_MUNDO_H_


#include "Tiempo.h"
#include "../view/LTexture.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "CapaFondo.h"
#include "Personaje.h"
#include "ObjetoArrojable.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"
#include "../view/Ventana.h"
#include "../view/BarraEnergia.h"
#include "../view/TiempoPartida.h"
#include <vector>
#include <algorithm>
#include "logging.h"


class Mundo {
private:
	float ancho_mundo;
	float alto_mundo;
	std::vector<Capa*> capas;
	CapaPrincipal* capaPrincipal;
	std::vector<Personaje*> personajes;
	Tiempo* tiempo;
	TiempoPartida* tiempo_pantalla;
	Ventana* ventana;
	int personajes_z_index;
	bool empezar;
	void start();
	int _verificarScroll();
	void _verificarColisiones();
	void _crearBarras();
	void _crearTiempo();
	void _renderEstado();
	BarraEnergia* BarraJugador1;
	BarraEnergia* BarraJugador2;
public:
	Mundo(float AnchoMundo,float AltoMundo);
	bool addPersonaje(Personaje* un_personaje);
	Personaje* getPersonaje(int indice = 0);
	void addCapa(Capa* unaCapa);
	void addCapaPrincipal(CapaPrincipal* capa_principal,int index);
	Capa* getCapa(int indice = 0);
	void setTiempo(Tiempo* unTiempo);
	void setVentana(Ventana* unaVentana);
	Ventana* getVentana();
	void render();
	virtual ~Mundo();
	bool mostrarImagen(string ruta);
};

#endif /* SRC_MODEL_MUNDO_H_ */
