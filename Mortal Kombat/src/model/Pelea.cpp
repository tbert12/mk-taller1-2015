/*
 * Pelea.cpp
 *
 *  Created on: 20/5/2015
 *      Author: facu
 */

#include "Pelea.h"

Pelea::Pelea(Ventana* la_ventana,Escenario* un_escenario,int un_tiempo,int modo_de_juego) {
	ModoDeJuego = modo_de_juego;
	escenario = un_escenario;
	capaPrincipal = escenario->getCapaPrincipal();
	m_personajeUno = capaPrincipal->getPersonajSinFlip();
	m_personajeDos = capaPrincipal->getPersonajConFlip();
	ganador = NULL;
	//capas = escenario->getCapas();
	ventana = la_ventana;
	tiempoRound = un_tiempo;
	NumeroRound = 1;
	ciclos_round_terminado = CICLOS_FINAL_ROUND;
	GanadorRound = {0,0,0};
	comenzo_round = false;
	round_finalizado = false;
	partida_finalizada = false;
	tiempo = new Tiempo(tiempoRound);
	_crearEstado();
}

void Pelea::_crearEstado(){
	if (ventana == NULL) return;
	BarraPersonajeUno = new BarraEnergia(ventana,m_personajeUno->getVida(),m_personajeUno->getNombre());
	BarraPersonajeDos = new BarraEnergia(ventana,m_personajeDos->getVida(),m_personajeDos->getNombre());
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
		BarraPersonajeUno->render(m_personajeUno->getVida());
	if (BarraPersonajeDos != NULL)
		BarraPersonajeDos->render(m_personajeDos->getVida());
	if (tiempo_pantalla != NULL)
		tiempo_pantalla->render();
}

bool Pelea::peleaFinalizada(){
	return partida_finalizada;
}

void Pelea::render(){
	if (partida_finalizada)
		return;

	if(!comenzo_round){
		start();
		comenzo_round = true;
	}

	//verifico el tiempo
	if (ModoDeJuego != MODO_ENTRENAMIENTO){
		tiempo->actualizar();
		//verifico si finalizo el round
		_roundFinalizado();


		if (round_finalizado){
			if (ciclos_round_terminado > 0){
				ciclos_round_terminado--;
			}
			else{
				_partidaFinalizada();
				ciclos_round_terminado = CICLOS_FINAL_ROUND;
				if(!partida_finalizada)
					_resetRound();
			}
		}
	}

	//actualizo los estados
	escenario->Update();

	//aca una vez actualizado to do chequeo las colisiones y demas.
	_verificarColisiones();

	//renderizo las capas
	escenario->render();

	_renderEstado();

	if(round_finalizado && ciclos_round_terminado > 0)
		_mostarGanadorRound();
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

void Pelea::_roundFinalizado(){

	//se termino el tiempo, gana el de mayor vida
	if(tiempo->tiempoTerminado()){
		round_finalizado = true;
		if(m_personajeUno->getVida() > m_personajeDos->getVida()){
			//gana personaje uno
			log("Round finalizado, GANADOR: " + m_personajeUno->getNombre(),LOG_DEBUG);
			m_personajeUno->victoria();
			GanadorRound[NumeroRound -1]  = 1;
		}
		else if (m_personajeUno->getVida() < m_personajeDos->getVida()){
			//gana personaje dos
			log("Round finalizado, GANADOR: " + m_personajeDos->getNombre(),LOG_DEBUG);
			m_personajeDos->victoria();
			GanadorRound[NumeroRound -1]  = 2;
		}
		else{
			//empatan ?
			GanadorRound[NumeroRound -1]  = 0;
		}
	}

	//el tiempo no termino
	else{
		//verifico si hay ganador por agotarse vida
		if(m_personajeUno->getVida() <= 0){
			round_finalizado = true;
			log("Round finalizado, GANADOR: " + m_personajeDos->getNombre(),LOG_DEBUG);
			m_personajeDos->victoria();
			GanadorRound[NumeroRound -1]  = 2;
		}
		else if (m_personajeDos->getVida() <= 0){
			round_finalizado = true;
			log("Round finalizado, GANADOR: " + m_personajeUno->getNombre(),LOG_DEBUG);
			m_personajeUno->victoria();
			GanadorRound[NumeroRound -1]  = 1;
		}
	}
}
void Pelea::_partidaFinalizada(){
	if (NumeroRound == 2){
		//si ya un personaje gano los dos rounds
		if ((GanadorRound[0]  == 1 and GanadorRound[1]  == 1 ) || (GanadorRound[0]  == 2 and GanadorRound[1]  == 2 )){
			partida_finalizada = true;
			if (GanadorRound[0]  == 1){
				ganador = m_personajeUno;
			}else{
				ganador = m_personajeDos;
			}
		}
		else{
			NumeroRound++;
		}
	}else if (NumeroRound >= 3){
		partida_finalizada = true;
		//si hay 3 round el que gano el ultimo es el ganador
		if (GanadorRound[NumeroRound - 1] == 1){
			ganador = m_personajeUno;
		}
		else if (GanadorRound[NumeroRound - 1] == 2){
			ganador = m_personajeDos;
		}
		else{ //empate gana el que gano el primer round?
			if (GanadorRound[0] == 1){
			ganador = m_personajeUno;
			}
			else if (GanadorRound[0] == 2){
				ganador = m_personajeDos;
			}
		}
	}
	else{
		NumeroRound++;
	}
}

void Pelea::_mostarGanadorRound(){
	string nombre;
	if (GanadorRound[NumeroRound - 1] == 1){
		nombre = m_personajeUno->getNombre();
	}
	else if (GanadorRound[NumeroRound - 1] == 2){
		nombre = m_personajeDos->getNombre();
	}
	string texto = "Ganador Round: " + to_string(NumeroRound) + " " + nombre;
	ventana->mostrarTexto(texto);
}

void Pelea::_resetRound(){
	//reseteo todos las capas y personajes
	escenario->reset();
	tiempo->reset();
	round_finalizado = false;
	comenzo_round = false;
}

void Pelea::reset(){
	_resetRound();
}

Personaje* Pelea::getPersonajeUno(){
	return m_personajeUno;
}

Personaje* Pelea::getPersonajeDos(){
	return m_personajeDos;
}

int Pelea::getModoDeJuego(){
	return ModoDeJuego;
}

Pelea::~Pelea() {

	GanadorRound.clear();
	if(tiempo) delete tiempo;
	if(BarraPersonajeUno) delete BarraPersonajeUno;
	if(BarraPersonajeDos) delete BarraPersonajeDos;
	if(tiempo_pantalla) delete tiempo_pantalla;

}

