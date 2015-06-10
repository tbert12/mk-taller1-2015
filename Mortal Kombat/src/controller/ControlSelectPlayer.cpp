/*
 * ControlSelectPlayer.cpp
 *
 *  Created on: 5/6/2015
 *      Author: facu
 */

#include "ControlSelectPlayer.h"

ControlSelectPlayer::ControlSelectPlayer(SelectPlayer* select, bool dos_jugadores) {
	menuPlayers = select;
	keystate = SDL_GetKeyboardState(NULL);
	quit = false;
	textBoxOpen = false;
	joystick1 = NULL;
	joystick2 = NULL;
	if(SDL_NumJoysticks() > 1){
		joystick1 = SDL_JoystickOpen(0);
		if( joystick1 == NULL )
			log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
		else
			log("Joystick cargado correctamente",LOG_DEBUG);
		if (dos_jugadores){
			joystick2 = SDL_JoystickOpen(1);
			if( joystick2 == NULL )
				log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
			else
				log("Joystick cargado correctamente",LOG_DEBUG);
		}
	}
	else if(SDL_NumJoysticks() == 1){
		joystick1 = SDL_JoystickOpen(0);
		if( joystick1 == NULL )
			log(string("No se puede leer el joystick! SDL Error:" + string(SDL_GetError())),LOG_ERROR);
		else
			log("Joystick cargado correctamente",LOG_DEBUG);
	}
}

void ControlSelectPlayer::Pressed(){
	if(evento.type == SDL_QUIT){
		quit = true;
		return;
	}
	//textBox
	else if (textBoxOpen){
		_textBoxPressed();
	}
	//teclado
	else if (evento.type == SDL_KEYDOWN){

		int player = menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE;
		if (SDL_NumJoysticks() < 2 and SDL_NumJoysticks() != 0) player = PLAYER_TWO;
		switch( evento.key.keysym.sym ){
			case  SDLK_UP:
				menuPlayers->arriba(player);
				break;
			case SDLK_DOWN:
				menuPlayers->abajo(player);
				break;
			case SDLK_LEFT:
				menuPlayers->izquierda(player);
				break;
			case SDLK_RIGHT:
				menuPlayers->derecha(player);
				break;
			case SDLK_a:
				menuPlayers->select(player);
				openTextBox();
				break;
			case SDLK_s:
				menuPlayers->select(player);
				openTextBox();
				break;
			case SDLK_RETURN:
				menuPlayers->select(player);
				openTextBox();
				break;
			case SDLK_SPACE:
				menuPlayers->select(player);
				openTextBox();
				break;
			case SDLK_d:
				menuPlayers->select(player);
				openTextBox();
				break;
		}
	}
	//mouse
	else if (evento.type == SDL_MOUSEMOTION || evento.type == SDL_MOUSEBUTTONDOWN ){
		int x, y;
		SDL_GetMouseState( &x, &y );
		switch( evento.type ){
			case SDL_MOUSEMOTION:
				//Get mouse position
				menuPlayers->mousePosition(x,y,menuPlayers->changeMouseController()? PLAYER_TWO:PLAYER_ONE);
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (menuPlayers->mousePosition(x,y,menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE) and evento.button.button == SDL_BUTTON_LEFT ){
					menuPlayers->select(menuPlayers->changeMouseController()? PLAYER_TWO:PLAYER_ONE);
					openTextBox();
				}
				break;
		}
	}
	//Joystick
	else if(evento.type == SDL_JOYAXISMOTION){
		//X axis motion
		if( evento.jaxis.axis == 0 ){
			//Left of dead zone
			if( evento.jaxis.value < -JOYSTICK_DEAD_ZONE ){
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->izquierda(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->izquierda(PLAYER_TWO);
			}
			//Right of dead zone
			else if( evento.jaxis.value > JOYSTICK_DEAD_ZONE ){
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->derecha(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->derecha(PLAYER_TWO);
			}
			else{
				//NO SE
			}
		}
		//Y axis motion
		else if( evento.jaxis.axis == 1){
			//arriba
			if( evento.jaxis.value < -JOYSTICK_DEAD_ZONE ){
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->arriba(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->arriba(PLAYER_TWO);
			}
			//abajo
			else if( evento.jaxis.value > JOYSTICK_DEAD_ZONE){
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->abajo(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->abajo(PLAYER_TWO);
			}
			else{
				//NADA
			}
		}
	}
	else if (evento.type == SDL_JOYHATMOTION){

		switch (evento.jhat.value){
			case SDL_HAT_UP :
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->arriba(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->arriba(PLAYER_TWO);
				break;
			case SDL_HAT_DOWN:
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->abajo(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->abajo(PLAYER_TWO);
				break;
			case SDL_HAT_LEFT:
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->izquierda(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->izquierda(PLAYER_TWO);
				break;
			case SDL_HAT_RIGHT:
				if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1))
					menuPlayers->derecha(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
				else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2))
					menuPlayers->derecha(PLAYER_TWO);
				break;
		}
	}
	//Boton
	else if (evento.type == SDL_JOYBUTTONDOWN){
		//con cualquier boton se selecciona
		if (evento.jaxis.which == SDL_JoystickInstanceID(joystick1)){
			menuPlayers->select(menuPlayers->changeController()? PLAYER_TWO:PLAYER_ONE);
			openTextBox();
		}
		else if (evento.jaxis.which == SDL_JoystickInstanceID(joystick2)){
			menuPlayers->select(PLAYER_TWO);
			openTextBox();
		}
	}
}

bool ControlSelectPlayer::Quit(){
	return quit;
}

bool ControlSelectPlayer::PollEvent(){
	SDL_JoystickUpdate();
	return (SDL_PollEvent( &evento ) != 0);
}

void ControlSelectPlayer::openTextBox(){
	SDL_StartTextInput();
	textBoxOpen = true;
}

void ControlSelectPlayer::closeTextBox(){
	SDL_StopTextInput();
	textBoxOpen = false;
}

void ControlSelectPlayer::_textBoxPressed(){
	TextBox* textBox = menuPlayers->getTextBox();
	string inputText = textBox->getText();

	if( evento.type == SDL_KEYDOWN ){
		//Handle backspace
		if( evento.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
		{
			//lop off character
			textBox->borrarUltimoChar();
		}
		//Quit
		else if(evento.key.keysym.sym == SDLK_RETURN){
			if(menuPlayers->textBoxEnter(menuPlayers->changeControllerTextBox()? PLAYER_TWO:PLAYER_ONE))
				closeTextBox();
		}
		//Handle copy
		else if( evento.key.keysym.sym == SDLK_c && (SDL_GetModState() & KMOD_CTRL) )
		{
			SDL_SetClipboardText( inputText.c_str() );
		}


		//Handle paste
		else if( evento.key.keysym.sym == SDLK_v && (SDL_GetModState() & KMOD_CTRL) )
		{
			/* inputText += SDL_GetClipboardText();*/
			textBox->appendString( SDL_GetClipboardText() );
		}
	}
	else if (evento.type == SDL_JOYBUTTONDOWN ){
		if(menuPlayers->textBoxEnter((evento.jaxis.which == SDL_JoystickInstanceID(joystick1))? PLAYER_ONE:PLAYER_TWO))
			closeTextBox();
	}
	//mouse
	else if (evento.type == SDL_MOUSEBUTTONDOWN){
		int x, y;
		SDL_GetMouseState( &x, &y );
		if (menuPlayers->mouseinTextBox(x,y)){
			if(menuPlayers->textBoxButtonMouse(x,y))
				closeTextBox();
		}
	}
	else if( evento.type == SDL_TEXTINPUT )
	{
		//No se detecta copy and paste
		char firstChar = evento.text.text[ 0 ];
		bool hayCopyPaste = ( firstChar == 'c' or firstChar == 'C' ) and ( firstChar == 'v' or firstChar == 'V' ) and (SDL_GetModState() & KMOD_CTRL);
		bool espaciosSinNada = (inputText == "" and firstChar == ' ');
		if( !(hayCopyPaste or espaciosSinNada) ){
				//Append character
				textBox->appendString( evento.text.text );
		}
	}
}

ControlSelectPlayer::~ControlSelectPlayer() {
	if (joystick1 != NULL && SDL_JoystickGetAttached(joystick1)){
		SDL_JoystickClose( joystick1 );
		joystick1 = NULL;
	}
	if (joystick2 != NULL && SDL_JoystickGetAttached(joystick2)){
		SDL_JoystickClose( joystick2 );
		joystick2 = NULL;
	}
}

