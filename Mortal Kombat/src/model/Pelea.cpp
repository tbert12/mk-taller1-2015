/*
 * Pelea.cpp
 *
 *  Created on: 20/5/2015
 *      Author: facu
 */

#include "Pelea.h"

Pelea::Pelea(Ventana* la_ventana,Personaje* personaje1,Personaje* personaje2,int un_tiempo,std::vector<Capa*> las_capas,CapaPrincipal* capa_principal) {
	personaje_uno = personaje1;
	personaje_dos = personaje2;
	capas = las_capas;
	capaPrincipal = capa_principal;
	ventana = la_ventana;
	tiempoRound = un_tiempo;
	NumeroRound = 1;
	comenzo_pelea = false;
	round_finalizado = false;
	tiempo = new Tiempo(tiempoRound);
	_crearEstado();
}

void Pelea::_crearEstado(){
	if (ventana == NULL) return;
	BarraPersonajeUno = new BarraEnergia(ventana,personaje_uno->getVida());
	BarraPersonajeDos = new BarraEnergia(ventana,personaje_dos->getVida());
	BarraPersonajeDos->setFlip();
	if (tiempo)
		tiempo_pantalla = new TiempoPartida(ventana,tiempo);
}

void Pelea::start(){
	if (tiempo != NULL)
		tiempo->start();
}

void Pelea::_renderEstado(){
	if (BarraPersonajeUno != NULL)
		BarraPersonajeUno->render(personaje_uno->getVida());
	if (BarraPersonajeDos != NULL)
		BarraPersonajeDos->render(personaje_dos->getVida());
	if (tiempo_pantalla != NULL)
		tiempo_pantalla->render();
}

void Pelea::render(){
	if(!comenzo_pelea){
		start();
		comenzo_pelea = true;
	}

	//verifico el tiempo
	tiempo->actualizar();
	if (tiempo->tiempoTerminado()){
		//se termino el tiempo
	}

	//verifico Ganador
	if(personaje_uno->getVida() <= 0){
		log("Partida finalizada, GANADOR: " + personaje_dos->getNombre(),LOG_DEBUG);
		round_finalizado = true;
		//_mostrar_ganador(capaPrincipal->getPersonajSinFlip()->getNombre());
		return;
	}
	else if (personaje_dos->getVida() <= 0){
		log("Partida finalizada, GANADOR: " + personaje_uno->getNombre(),LOG_DEBUG);
		round_finalizado = true;
		//_mostrar_ganador(capaPrincipal->getPersonajConFlip()->getNombre());
		return;
	}

	//verifico scroll
	int scroll = capaPrincipal->Scrollear(); //capaPrincipal->Scrollear();

	//actualizo los estados
	for (unsigned int i = 0 ; i <= capas.size() -1 ; i++){
		capas[i]->Update(scroll);
	}


	//aca una vez actualizado to do chequeo las colisiones y demas.
	_verificarColisiones();

	//renderizo las capas
	for (unsigned int i = 0 ; i <= capas.size() -1 ; i++){
		capas[i]->Renderizar();
	}

}

void Pelea::_verificarColisiones(){
	int resultado = capaPrincipal->CheckearColisiones();

	if (resultado == COLISION_NO_COLISION ) return;

	int accion;
	Personaje* personaje = capaPrincipal->getPersonajSinFlip();
	Personaje* personaje_flipeado = capaPrincipal->getPersonajConFlip();

	/*COLISION CAPA PRINCIPAL*/
	switch (resultado){
		case COLISION_PERSONAJE_PERSONAJE_SIN_FLIP:
			//personaje ataca a personaje_flipeado
			accion = personaje->getAccionDeAtaque();
			if(personaje_flipeado->recibirGolpe(accion))
				ventana->vibrar();
			break;
		case COLISION_PERSONAJE_PERSONAJE_CON_FLIP:
			//personaje_flipeado ataca a personaje
			accion = personaje_flipeado->getAccionDeAtaque();
			if(personaje->recibirGolpe(accion))
				ventana->vibrar();
			break;
		case COLISION_PERSONAJE_OBJETO_SIN_FLIP:
			//objeto de personaje choco a personaje_flipeado
			if(personaje_flipeado->recibirGolpe(GOLPE_DE_PODER,personaje->getPoderActivo()->getDanio()))
				ventana->vibrar();
			personaje->getPoderActivo()->destruir();
			break;
		case COLISION_PERSONAJE_OBJETO_CON_FLIP:
			//objeto de personaje_flipeado choco a personaje
			if(personaje->recibirGolpe(GOLPE_DE_PODER,personaje_flipeado->getPoderActivo()->getDanio()))
				ventana->vibrar();
			personaje_flipeado->getPoderActivo()->destruir();
			break;
		case COLISION_OBJETO_OBJETO:
			//chocan los dos objetos
			personaje_flipeado->getPoderActivo()->destruir();
			personaje->getPoderActivo()->destruir();
			break;
		default:
			break;
	}
}

Pelea::~Pelea() {
	if(tiempo) delete tiempo;
	if(BarraPersonajeUno) delete BarraPersonajeUno;
	if(BarraPersonajeDos) delete BarraPersonajeDos;
	if(tiempo_pantalla) delete tiempo_pantalla;

}

