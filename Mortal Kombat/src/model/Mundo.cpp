/*
 * Mundo.cpp
 *
 *  Created on: Apr 6, 2015
 *      Author: seba
 */

#include "Mundo.h"

Mundo::Mundo(float ancho,float alto) {
	ancho_mundo = ancho;
	alto_mundo = alto;
	tiempo = NULL;
	ventana = NULL;
	personajes_z_index = 0;
	BarraJugador1 = NULL;
	BarraJugador2 = NULL;
	capaPrincipal = NULL;
	tiempo_pantalla = NULL;
	empezar = false;
	partida_finalizada = false;
}

void Mundo::start(){
	if (tiempo != NULL)
		tiempo->start();
}

bool Mundo::addPersonaje(Personaje* un_personaje){
	personajes.push_back(un_personaje);
	return true;
}
Personaje* Mundo::getPersonaje(int indice){
	if ((size_t)indice <= personajes.size()){
		return personajes[indice];
	}
	return NULL;
}

void Mundo::addCapa(Capa* una_capa) {
	capas.push_back(una_capa);
}

void Mundo::addCapaPrincipal( CapaPrincipal* capa_principal, int index ) {

	if ( index > (int)capas.size() ) {
		this->addCapa(capa_principal);
		personajes_z_index = capas.size()-1;
	} else {
		capas.insert(capas.begin()+index, capa_principal);
		personajes_z_index = index;
	}
	capaPrincipal = capa_principal;
}

Capa* Mundo::getCapa(int indice){
	if ((size_t)indice <= capas.size()){
		return capas[indice];
	}
	return NULL;
}
void Mundo::setTiempo(Tiempo* unTiempo){
	tiempo = unTiempo;
}
void Mundo::setVentana(Ventana* unaVentana){
	ventana = unaVentana;
	_crearBarras();
	_crearTiempo();
}

void Mundo::_crearTiempo(){
	if (ventana == NULL || tiempo == NULL) return;
	tiempo_pantalla = new TiempoPartida(ventana,tiempo);
}

void Mundo::_crearBarras(){
	if (ventana == NULL) return;
	BarraJugador1 = new BarraEnergia(ventana,100);
	BarraJugador2 = new BarraEnergia(ventana,100);
	BarraJugador2->setFlip();
}
Ventana* Mundo::getVentana(){
	return ventana;
}

int Mundo::_verificarScroll(){
	return capaPrincipal->Scrollear();
}

bool Mundo::mostrarImagen(string ruta){
	if(!ventana->mostrarImagen(ruta)){
		log("No se pudo mostrar la imagen",LOG_ERROR);
		return false;
	}
	log("Se muestra imagen de inicio",LOG_DEBUG);
	return true;
}

void Mundo::_renderEstado(){
	if (BarraJugador1 != NULL)
		BarraJugador1->render(personajes[0]->getVida());
	if (BarraJugador2 != NULL)
		BarraJugador2->render(personajes[1]->getVida());
	if (tiempo_pantalla != NULL)
		tiempo_pantalla->render();
}

void Mundo::render(){
	if(!empezar){
		start();
		empezar = true;
	}
	//limpio pantalla
	ventana->clear();

	//verifico el tiempo
	tiempo->actualizar();
	if (tiempo->tiempoTerminado()){
		//se termino el tiempo
	}

	if(capaPrincipal->getPersonajConFlip()->getVida() <= 0){
		log("Partida finalizada, GANADOR: " + capaPrincipal->getPersonajSinFlip()->getNombre(),LOG_DEBUG);
		partida_finalizada = true;
		//_mostrar_ganador(capaPrincipal->getPersonajConFlip()->getNombre());
		return;
	}
	else if (capaPrincipal->getPersonajSinFlip()->getVida() <= 0){
		log("Partida finalizada, GANADOR: " + capaPrincipal->getPersonajConFlip()->getNombre(),LOG_DEBUG);
		partida_finalizada = true;
		//_mostrar_ganador(capaPrincipal->getPersonajConFlip()->getNombre());
		return;
	}

	//verifico scroll
	int scroll = _verificarScroll();

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

	//actualizo el estado de la pantalla
	_renderEstado();

	//actualizo pantalla -> SDL_RenderPresent( Renderer );
	ventana->Refresh();
}

void Mundo::_verificarColisiones(){
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

void Mundo::_mostrar_ganador(string nombre){
	string texto = "Ganador \n" + nombre;
	ventana->mostrarTexto(texto);
	usleep(3000);
}

Mundo::~Mundo() {
	//fijar si hay que liberar cada uno de los contenidos de los vectores
	for (unsigned int i = 0 ; i < capas.size() ; i++){
	      delete capas[i];
	}
	capas.clear();
	for (unsigned int i = 0 ; i < personajes.size() ; i++){
		delete personajes[i];
	}
	personajes.clear();

	if(tiempo) delete tiempo;
	if(BarraJugador1) delete BarraJugador1;
	if(BarraJugador2) delete BarraJugador2;
	if(tiempo_pantalla) delete tiempo_pantalla;

	if(ventana) delete ventana; //Siempre eliminarlo Ultimo (Hace SDL_Quit)
}

