/*
 * Pelea.cpp
 *
 *  Created on: 20/5/2015
 *      Author: facu
 */

#include "Pelea.h"

Pelea::Pelea(Ventana* la_ventana,Escenario* un_escenario,int un_tiempo,int modo_de_juego,TextosPelea* textos_Pelea) {
	ModoDeJuego = modo_de_juego;
	escenario = un_escenario;
	textosPelea = textos_Pelea;
	capaPrincipal = escenario->getCapaPrincipal();
	m_personajeUno = capaPrincipal->getPersonajSinFlip();
	m_personajeDos = capaPrincipal->getPersonajConFlip();
	ganador = NULL;
	ventana = la_ventana;
	tiempoRound = un_tiempo;
	NumeroRound = 1;
	ciclos_round_terminado = CICLOS_FINAL_ROUND;
	ciclos_finish_him = CICLOS_FINISH_HIM;
	ciclos_render_texto = CICLOS_TEXTOS;
	GanadorRound = {0,0,0};
	comenzo_round = false;
	fatality = false;
	round_finalizado = false;
	partida_finalizada = false;
	pelea_terminada = false;
	finish_him = false;
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

	if (ModoDeJuego == MODO_JUGADOR_VS_PC)
		cpu = new JugadorCPU(m_personajeDos, m_personajeUno);
	comenzo_round = true;
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
	if (ModoDeJuego == MODO_ENTRENAMIENTO) return false;
	return pelea_terminada;
}

bool Pelea::roundFinalizado(){
	return round_finalizado;
}

bool Pelea::inFinishHim(){
	if (ModoDeJuego == MODO_ENTRENAMIENTO) return finish_him;
	return partida_finalizada and ciclos_finish_him > 0;
}

void Pelea::render(){

	if(!comenzo_round){
		start();
	}

	//verifico el tiempo
	if (ModoDeJuego != MODO_ENTRENAMIENTO){
		tiempo->actualizar();
		//verifico si finalizo el round
		_roundFinalizado();
		if (round_finalizado)
			_terminarRound();
	}

	// Se mueve el jugador CPU.
	if (cpu != NULL && ModoDeJuego == MODO_JUGADOR_VS_PC)
		cpu->realizarMovimiento();

	//actualizo los estados70
	escenario->Update();

	//aca una vez actualizado to do chequeo las colisiones y demas.
	if (!round_finalizado and !partida_finalizada)
		_verificarColisiones();


	//renderizo las capas
	escenario->render();

	_renderEstado();

	//_renderTextos();

	if (partida_finalizada){
		if (ciclos_finish_him >= 0){
			//finiiiisshhhhhhhiimmm;
			_mostrarGanadorPelea();
			ciclos_finish_him--;
		}
		else{
			ciclos_finish_him = CICLOS_FINAL_ROUND;
			ciclos_render_texto = CICLOS_TEXTOS;
			pelea_terminada = true;
		}
	}
	else if(round_finalizado){
		if (ciclos_round_terminado >= 0){
			_mostarGanadorRound();
			ciclos_round_terminado--;
		}
		else{
			if (!_partidaFinalizo()){
				_avanzarRound();
				_resetRound();
			}
		}
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
			personaje->terminarAtaque();
			if(personaje_flipeado->recibirGolpe(accion))
				ventana->vibrar();
			break;
		case COLISION_PERSONAJE_PERSONAJE_CON_FLIP:
			//personaje_flipeado ataca a personaje
			accion = personaje_flipeado->getAccionDeAtaque();
			personaje_flipeado->terminarAtaque();
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
			GanadorRound[NumeroRound -1]  = 1;
		}
		else if (m_personajeUno->getVida() < m_personajeDos->getVida()){
			//gana personaje dos
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
			GanadorRound[NumeroRound -1]  = 2;
		}
		else if (m_personajeDos->getVida() <= 0){
			round_finalizado = true;
			GanadorRound[NumeroRound -1]  = 1;
		}
	}
}

void Pelea::_avanzarRound(){
	NumeroRound++;
}

bool Pelea::ganoCpu(){
	return pelea_terminada and (ganador==m_personajeDos);
}

bool Pelea::_partidaFinalizo(){
	if (NumeroRound == 2){
		//si ya un personaje gano los dos rounds
		if ((GanadorRound[0]  == 1 and GanadorRound[1]  == 1 ) || (GanadorRound[0]  == 2 and GanadorRound[1]  == 2 )){
			partida_finalizada = true;
			finish_him = true;
			if (GanadorRound[0]  == 1){
				ganador = m_personajeUno;
			}else{
				ganador = m_personajeDos;
			}
			return true;
		}
	}else if (NumeroRound >= 3){
		partida_finalizada = true;
		finish_him = true;
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
		return true;
	}
	return false;
}

void Pelea::_terminarRound(){
	Personaje* ganador_ultimo_round;
	Personaje* perdedor_ultimo_round;

	if (GanadorRound[NumeroRound - 1] == 1){
		ganador_ultimo_round = m_personajeUno;
		perdedor_ultimo_round = m_personajeDos;
	}
	else if (GanadorRound[NumeroRound - 1] == 2){
		ganador_ultimo_round = m_personajeDos;
		perdedor_ultimo_round = m_personajeUno;
	}
	else return;

	if (_partidaFinalizo()){
		perdedor_ultimo_round->finishHim();
	}
	else{
		ganador_ultimo_round->victoria();
		perdedor_ultimo_round->morir();
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

void Pelea::_mostrarGanadorPelea(){
	string nombre;
	if (ganador != NULL){
		nombre = ganador->getNombre();
	}
	string texto = "FINISH HIM";// + nombre;
	ventana->mostrarTexto(texto);

}

void Pelea::_resetRound(){
	escenario->reset();
	tiempo->reset();
	ciclos_round_terminado = CICLOS_FINAL_ROUND;
	ciclos_render_texto = CICLOS_FINISH_HIM;
	round_finalizado = false;
	comenzo_round = false;
}

void Pelea::reset(){
	_resetRound();
	finish_him = false;
	partida_finalizada = false;
	pelea_terminada = false;
	fatality = false;
	ciclos_finish_him = CICLOS_FINISH_HIM;
}

void Pelea::setFatality(){
	if (!fatality) fatality = true;
	ciclos_finish_him = CICLOS_FATALITY;
}

void Pelea::setFinishHim(){
	if (ModoDeJuego != MODO_ENTRENAMIENTO) return;
	partida_finalizada = true;
	finish_him = true;
	ciclos_finish_him = CICLOS_FINISH_HIM;
	m_personajeDos->finishHim();
}

Personaje* Pelea::getPersonajeUno(){
	return m_personajeUno;
}

int Pelea::modoDeJuego(){
	return ModoDeJuego;
}

Personaje* Pelea::getPersonajeDos(){
	return m_personajeDos;
}

int Pelea::getModoDeJuego(){
	return ModoDeJuego;
}

Personaje* Pelea::getContrincante(Personaje* un_personaje){
	if (un_personaje == m_personajeUno)
		return m_personajeDos;
	else return m_personajeUno;
}

void Pelea::_renderTextos(){
	if (ciclos_render_texto <=0 or !textosPelea) return;
	if (finish_him){
		textosPelea->renderFinishHim();
		ciclos_render_texto--;
	}
	if (!round_finalizado){
		textosPelea->renderFight();
		ciclos_render_texto--;
	}
	if (fatality){
		textosPelea->renderFatality();
		ciclos_render_texto--;
		if (ciclos_render_texto <= 0)
			pelea_terminada = true;
	}
}

Pelea::~Pelea() {
	reset();
	GanadorRound.clear();
	if(tiempo) delete tiempo;
	if(BarraPersonajeUno) delete BarraPersonajeUno;
	if(BarraPersonajeDos) delete BarraPersonajeDos;
	if(tiempo_pantalla) delete tiempo_pantalla;
	if (cpu) delete cpu;
	textosPelea = NULL;
}

