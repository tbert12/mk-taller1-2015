/*
 * JoystickControl.cpp
 *
 *  Created on: 28/4/2015
 *      Author: facu
 */

#include "JoystickControl.h"

JoystickControl::JoystickControl(SDL_Event* e,int id_joystick,Personaje* un_personaje,map<string, int>* mapa_comandos,ComboController* comboCon,Pelea* una_pelea) {
	personaje = un_personaje;
	pelea = una_pelea;
	if (personaje)
		combosPosibles = personaje->getCombos();
	comboController = NULL;
	comboController = comboCon;
	evento = e;
	pausa = false;
	returnMenu = false;
	comandos = mapa_comandos;
	_Init(id_joystick);
	_verificarMapaComandos();
}

bool JoystickControl::pause(){
	return pausa;
}

bool JoystickControl::goToMenu(){
	return returnMenu;
}

void JoystickControl::_verificarMapaComandos(){
	bool mapa_correcto = false;

	if (comandos != NULL && joystick != NULL){
		mapa_correcto = true;
		for (std::map<string,int>::const_iterator it=comandos->begin(); it!=comandos->end(); ++it){
			//si supera la cantidad de botones del joystick
			if(it->second >= SDL_JoystickNumButtons(joystick))
				mapa_correcto = false;
		}
	}
	//si no es correcto hago uno propio
	if(!mapa_correcto){
		log("Los botones del joystick especificados en el Json no son correctos, se crean unos por defecto",LOG_WARNING);
		std::map<std::string, int>* mapita = new std::map<std::string,int>;
		mapita->operator[](PINA_BAJA) = JOY_X;
		mapita->operator[](PATADA_BAJA) = JOY_CIRCULO;
		mapita->operator[](PINA_ALTA) = JOY_CUADRADO;
		mapita->operator[](PATADA_ALTA) = JOY_TRIANGULO;
		mapita->operator[](CUBRIRSE)= JOY_R1;
		comandos = mapita;
	}
}

void JoystickControl::_Init(int id){
	joystick =	NULL;
	joystickHaptic = NULL;
	if(SDL_NumJoysticks() < id +1) log("No se puede abrir el joystick",LOG_ERROR);
	else joystick = SDL_JoystickOpen( id );
	if( joystick == NULL ) log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
	else{
		log("Joystick cargado correctamente",LOG_DEBUG);
		//joystickHaptic = SDL_HapticOpenFromJoystick( joystick );
		if( joystickHaptic == NULL ){
			log(string("El Joystick no soporta haptics! SDL Error:" + string(SDL_GetError())),LOG_WARNING);
		}
		else{
			//Get initialize rumble
			if( SDL_HapticRumbleInit( joystickHaptic ) < 0 ){
				log(string("Unable to initialize rumble! SDL Error:" + string(SDL_GetError())),LOG_WARNING);
			}
		}
	}
}

void JoystickControl::JoyPressed(){

	if(evento->type == SDL_JOYAXISMOTION){
		//X axis motion
		if( evento->jaxis.axis == 0 ){
			//Left of dead zone
			if( evento->jaxis.value < -JOYSTICK_DEAD_ZONE ){
				personaje->CaminarIzquierda();
				if (comboController){
					int accion;
					if (!personaje->getFlipState())
						accion = IZQUIERDA;
					else accion = DERECHA;
					comboController->sePresiono(accion);
				}
			}
			//Right of dead zone
			else if( evento->jaxis.value > JOYSTICK_DEAD_ZONE ){
				personaje->CaminarDerecha();
				if (comboController){
					int accion;
					if (!personaje->getFlipState())
						accion = DERECHA;
					else accion = IZQUIERDA;
					comboController->sePresiono(accion);
				}
			}else{
				//NO SE
			}
		}
		//Y axis motion
		else if( evento->jaxis.axis == 1 ){
			//arriba
			if( evento->jaxis.value < -JOYSTICK_DEAD_ZONE ){
				personaje->Saltar();
				if (comboController)
					comboController->sePresiono(ARRIBA);
			}
			//abajo
			else if( evento->jaxis.value > JOYSTICK_DEAD_ZONE){
				personaje->Agachar();
				if (comboController)
					comboController->sePresiono(ABAJO);
			}
			else{
				//NADA
			}
		}
	}
	//Boton
	else if (evento->type == SDL_JOYBUTTONDOWN){
		int boton = evento->jbutton.button;
		if (boton == comandos->operator[](RESET)){
			if (pelea->modoDeJuego() == MODO_ENTRENAMIENTO)
				pelea->reset();
				return;
		}
		else if (boton == comandos->operator[](MENU)){
			returnMenu = true;
			return;
		}
		else if (boton == comandos->operator[](PINA_BAJA) ){
			personaje->pinaBaja();
			if (comboController)
				comboController->sePresiono(PINABAJA);
		}
		else if( boton == comandos->operator [](PINA_ALTA)){
			personaje->pinaAlta();
			if (comboController)
				comboController->sePresiono(PINAALTA);
			if (SDL_JoystickGetAxis(joystick,1) > JOYSTICK_DEAD_ZONE )
				if (joystickHaptic != NULL)
					SDL_HapticRumblePlay( joystickHaptic, 0.75, 700 );
		}
		else if ( boton == comandos->operator [](PATADA_BAJA)){
			personaje->patadaBaja();
			if (comboController)
				comboController->sePresiono(PATADABAJA);
		}
		else if ( boton == comandos->operator [](PATADA_ALTA)){
			personaje->patadaAlta();
			if (comboController)
				comboController->sePresiono(PATADAALTA);
		}
		else if ( boton == comandos->operator [](CUBRIRSE)){
			if (comboController)
			comboController->sePresiono(CUBRIR);
		}
		else if ( boton == JOY_START){
			pausa = !pausa;
		}
	}

	if(comboController){
		int combo_a_realizar =  comboController->checkCombos();
		if (combo_a_realizar >= 0){
			switch (combo_a_realizar){
				case PODER1:
					personaje->poder1();
					break;
				case PODER2:
					personaje->poder2();
					break;
			}
		}
		if (pelea->inFinishHim()){
			int fatality_a_realizar =  comboController->checkFatalities();
			switch (fatality_a_realizar){
				case FATALITY1:
					personaje->fatality1(pelea->getContrincante(personaje));
					pelea->setFatality();
					break;
			}
		}
	}
}
void JoystickControl::JoyState(){
	if (comboController)
		comboController->Update();

	Sint16 x_mov = SDL_JoystickGetAxis(joystick,0);
	Sint16 y_mov = SDL_JoystickGetAxis(joystick,1);
	int sentido_personaje = personaje->getSentidoDeMovimiento();

	//frena si no se esta manteniendo para un lado el analogico
	if ( ( sentido_personaje > 0 && x_mov < JOYSTICK_DEAD_ZONE ) || (sentido_personaje < 0 && x_mov > -JOYSTICK_DEAD_ZONE)  )
		personaje->Frenar();

	//salta si mantiene para arriba el analogico
	if ((y_mov < -JOYSTICK_DEAD_ZONE)){
		personaje->Saltar();
	}

	//se levanta si no esta manteniendo para abajo el analogico
	if (!(y_mov > JOYSTICK_DEAD_ZONE))
		personaje->Levantarse();

	//se deja de cubrir si no esta apretado
	switch ( SDL_JoystickGetButton(joystick,comandos->operator [](CUBRIRSE)) ){
		case BUTTON_PRESSED:
			personaje->cubrirse();
			break;
		case BUTTON_UNPRESSED:
			personaje->dejarDeCubrirse();
			break;
	}
}

JoystickControl::~JoystickControl() {
	personaje = NULL;
	pelea = NULL;
	if (joystick != NULL && SDL_JoystickGetAttached(joystick)){
		SDL_JoystickClose( joystick );
		joystick = NULL;
	}
	if (joystickHaptic != NULL){
		SDL_HapticClose(joystickHaptic);
		joystickHaptic = NULL;
	}
}

