/*
 * Mundo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#include "Mundo.h"

Mundo::Mundo(Ventana* una_ventana, int tiempo , map<string, int>* mapaComan1,map<string, int>* mapaComan2,int un_tiempoMax,int una_tolerancia){
	ventana = una_ventana;
	tolerancia = una_tolerancia;
	tiempoMax = un_tiempoMax;
	mapa_comandos1 = mapaComan1;
	mapa_comandos2 = mapaComan2;
	escenario_actual = NULL;
	Personaje_uno = NULL;
	Personaje_dos = NULL;
	pelea = NULL;
	textoPelea = NULL;
	tiempo_round = tiempo;
	empezar = false;
	partida_finalizada = false;
	botones_pantalla = NULL;
	ModoDeJuego = MODO_JUGADOR_VS_PC;
	control = NULL;
}

void Mundo::start(){

	Personaje* p_uno = Personaje_uno;
	Personaje* p_dos = Personaje_dos;

	if (p_uno == NULL)
		p_uno = personajes[0];
	if (p_dos == NULL)
		p_dos = personajes[1];

	if (escenarios[0]){
		escenario_actual = escenarios[0];
		escenario_actual->addPersonajes(p_uno,p_dos);
		pelea = new Pelea(ventana,escenario_actual,tiempo_round,ModoDeJuego,textoPelea);
		//Creo el Controlador
		control = new Controller(pelea,mapa_comandos1, mapa_comandos2,tiempoMax,tolerancia);
		if (ModoDeJuego == MODO_ENTRENAMIENTO){
			botones_pantalla = new BotonesPantalla(ventana);
		}
	}
}

void Mundo::setTextoPelea(TextoPelea* un_text){
	textoPelea = un_text;
}

void Mundo::addPersonaje(Personaje* un_personaje){
	personajes.push_back(un_personaje);
}

void Mundo::setPersonajesDeJuego(Personaje* p_uno, Personaje* p_dos){
	Personaje_uno = p_uno;
	Personaje_dos = p_dos;
}

void Mundo::addPersonajes(vector<Personaje*> nuevos_personajes) {
	for (int i = 0; i < (int) nuevos_personajes.size(); i++) {
		personajes.push_back(nuevos_personajes[i]);
	}
}

void Mundo::addEscenario(Escenario* un_escenario){
	escenarios.push_back(un_escenario);
}

void Mundo::addEscenarios(vector<Escenario*> nuevos_escenarios) {
	for (int i = 0; i < (int) nuevos_escenarios.size(); i++) {
		escenarios.push_back(nuevos_escenarios[i]);
	}
}

bool Mundo::Quit(){
	if(control)
		return control->Quit();
	return false;
}

bool Mundo::Fin(){
	if (!empezar)
		return false;
	if(pelea)
		return pelea->peleaFinalizada() || control->goToMenu();
	return false;
}

void Mundo::setModoDeJuego(int modo){
	if (modo == MODO_ENTRENAMIENTO || modo == MODO_JUGADOR_VS_JUGADOR || modo == MODO_JUGADOR_VS_PC )
		ModoDeJuego = modo;
}

std::vector<Personaje*> Mundo::getPersonajes(){
	return personajes;
}


Ventana* Mundo::getVentana(){
	return ventana;
}

bool Mundo::Pausa(){
	if (control)
		return control->pausa();
	return false;
}

void Mundo::render(){
	if(!empezar){
		start();
		empezar = true;
	}

	if( control){
		control->KeyState();
		while( control->PollEvent()){
			control->Pressed();
		}
	}
	if (control->pausa()) return;

	//limpio pantalla
	ventana->clear();
	
	if(pelea->peleaFinalizada()){
		//_mostrar_ganador();
		partida_finalizada = true;
	}

	pelea->render();

	if(ModoDeJuego == MODO_ENTRENAMIENTO){
		botones_pantalla->render(control->get_stream_teclas(),control->checkCombo());
	}


	ventana->Refresh();
}

void Mundo::_mostrar_ganador(string nombre){
	string texto = "Ganador de la partida " + nombre;
	ventana->mostrarTexto(texto);
	usleep(3000000);
}

int Mundo::getSleep(){
	return control->getSleep();
}

void Mundo::reset(){
	escenario_actual = NULL;
	if (pelea){
		pelea->reset();
		delete pelea;
		pelea = NULL;
	}
	if (botones_pantalla){
		delete botones_pantalla;
		botones_pantalla = NULL;
	}
	if (control){
		delete control;
		control = NULL;
	}
	empezar = false;
	partida_finalizada = false;
	ModoDeJuego = MODO_JUGADOR_VS_PC;

}

Mundo::~Mundo() {

	for (unsigned int i = 0 ; i < escenarios.size() ; i++){
	      delete escenarios[i];
	}
	escenarios.clear();

	for (unsigned int i = 0 ; i < personajes.size() ; i++){
		delete personajes[i];
	}
	personajes.clear();

	if (pelea) delete pelea;

	if (control) delete control;

	if (textoPelea) delete textoPelea;

	if(ventana) delete ventana; //Siempre eliminarlo Ultimo (Hace SDL_Quit)
}

