/*
 * SoundMenu.cpp
 *
 *  Created on: 9/6/2015
 *      Author: facu
 */

#include "SoundMenu.h"

SoundMenu::SoundMenu() {
	fondo = new LSound(RUTA_SOUND_FONDO);
	move = new LSound(RUTA_SOUND_MOVE);
	select = new LSound(RUTA_SOUND_SELECT);

}

void SoundMenu::play(int sound){
	switch(sound){
		case SELECT:
			select->play();
			break;
		case MOVE:
			move->play();
			break;
		case FONDO:
			fondo->play(3);
			break;
	}
}

void SoundMenu::stop(int sound){
	switch(sound){
		case SELECT:
			select->stop();
			break;
		case MOVE:
			move->stop();
			break;
		case FONDO:
			fondo->stop();
			break;
	}
}

SoundMenu::~SoundMenu() {
	delete fondo;
	delete move;
	delete select;
}

