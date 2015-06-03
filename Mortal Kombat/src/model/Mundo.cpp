/*
 * Mundo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#include "Mundo.h"

Mundo::Mundo(Ventana* una_ventana, int tiempo , map<string, int>* mapaComan1,map<string, int>* mapaComan2){
	ventana = una_ventana;
	mapa_comandos1 = mapaComan1;
	mapa_comandos2 = mapaComan2;
	escenario_actual = NULL;
	pelea = NULL;
	tiempo_round = tiempo;
	empezar = false;
	partida_finalizada = false;
	ModoDeJuego = MODO_JUGADOR_VS_PC;
	botones_pantalla = NULL;
	control = NULL;
	combo = NULL;
}

void Mundo::start(){
	Personaje* p_uno = personajes[0];
	Personaje* p_dos = personajes[1];

	if (escenarios[0]){
		escenario_actual = escenarios[0];
		escenario_actual->addPersonajes(p_uno,p_dos);
		vector<Combo*> vect;
		combo = new ComboController(10, 10 ,vect);
		//Creo el Controlador
		switch(ModoDeJuego){
			case MODO_JUGADOR_VS_JUGADOR:
				control = new Controller(p_uno,p_dos,mapa_comandos1, mapa_comandos2,combo);
				break;
			case MODO_JUGADOR_VS_PC:
				control = new Controller(p_uno,NULL,mapa_comandos1,mapa_comandos2,combo);
				break;
			case MODO_ENTRENAMIENTO:
				control = new Controller(p_uno,NULL,mapa_comandos1,mapa_comandos2,combo);
				botones_pantalla = new BotonesPantalla(ventana);
				break;
		}
		pelea = new Pelea(ventana,escenario_actual,tiempo_round,ModoDeJuego);
	}
}

void Mundo::addPersonaje(Personaje* un_personaje){
	personajes.push_back(un_personaje);
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

	if( control && combo){
		control->KeyState();
		combo->Update();
		//combo->checkCombos();
		while( control->PollEvent()){
			control->Pressed();
		}
	}

	//limpio pantalla
	ventana->clear();
	
	if(pelea->peleaFinalizada()){
		printf("PATIDA FINALIZADA\n");
		partida_finalizada = true;
	}

	pelea->render();

	if(ModoDeJuego == MODO_ENTRENAMIENTO && combo)
		botones_pantalla->render(combo->get_stream_teclas(),false);

	//actualizo pantalla -> SDL_RenderPresent( Renderer );
	ventana->Refresh();
}

void Mundo::_mostrar_ganador(string nombre){
	string texto = "Ganador \n" + nombre;
	ventana->mostrarTexto(texto);
	usleep(3000000);
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

	if (combo) delete combo;

	if (control) delete control;

	if(ventana) delete ventana; //Siempre eliminarlo Ultimo (Hace SDL_Quit)
}

