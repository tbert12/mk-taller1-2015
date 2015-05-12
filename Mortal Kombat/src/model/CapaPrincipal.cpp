/*
 * CapaPrincipal.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: root
 */

#include "CapaPrincipal.h"
#include <list>


CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, Personaje* personajeUno, Personaje* personajeDos)
:Capa(alto,ancho,zIndex, anchoDeFondo,ancho_ventana,velocidadPrincipal) //call superclass constructorPersonaje* personajeUno
{
	m_Personaje = personajeUno;
	m_PersonajeDos = personajeDos;
	personajeUno->setDimensionesMundo(alto,ancho);
	personajeDos->setDimensionesMundo(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_Personaje->getVelocidadDerecha();
	m_velocidad_izquierda = m_Personaje->getVelocidadIzquierda();
	m_PersonajeQueScrollea = 0;
	rectAtaqueAnterior2 = NULL;
	rectAtaqueAnterior1 = NULL;
	m_personajeConFlip = NULL;
	m_personajeSinFlip = NULL;
	_scroll = 0;
}

CapaPrincipal::CapaPrincipal(float alto, float ancho, int zIndex, float anchoDeFondo,float ancho_ventana, float velocidadPrincipal, vector<Personaje*> personajes)
:Capa(alto,ancho,zIndex, anchoDeFondo,ancho_ventana,velocidadPrincipal) //call superclass constructorPersonaje* personajeUno
{
	m_Personaje = personajes[0];
	m_PersonajeDos = personajes[1];
	personajes[0]->setDimensionesMundo(alto,ancho);
	personajes[1]->setDimensionesMundo(alto,ancho);
	rect->x = rect->x - ancho_ventana/2;//Inicia al medio
	m_velocidad_derecha = m_Personaje->getVelocidadDerecha();
	m_velocidad_izquierda = m_Personaje->getVelocidadIzquierda();
	m_PersonajeQueScrollea = 0;
	rectAtaqueAnterior1 = m_Personaje->rectanguloAtaque();
	rectAtaqueAnterior2 = m_PersonajeDos->rectanguloAtaque();
	m_personajeSinFlip = m_Personaje;
	m_personajeConFlip = m_PersonajeDos;
	_scroll = 0;
}

void CapaPrincipal::_actualizarX(){
	if (rect->x < 0) rect->x = 0;
	if (rect->x > rect->w) rect->x = rect->w;
}

void CapaPrincipal::Update(int scroll){
	if (scroll > 0)this->Mover(true);
	else if (scroll < 0) this->Mover(false);
	this->_actualizarX();

	_scroll = scroll;
}


int CapaPrincipal::CheckearColisiones(){
	Personaje* personaje;
	Personaje* personajeFlippeado;

	if(m_Personaje->getFlipState()){
		personaje = m_PersonajeDos;
		personajeFlippeado = m_Personaje;
	}
	else{
		personajeFlippeado = m_PersonajeDos;
		personaje = m_Personaje;
	}

	int toReturn = this->_CheckearColisiones(personaje,personajeFlippeado);
	//printf("personajex");
	if(personaje->getX() + personaje->getAncho()*.5f > personajeFlippeado->getX() - personajeFlippeado->getAncho()*.5f){
		personaje->setFlip(true);
		personajeFlippeado->setFlip(false);
	}

	m_personajeSinFlip = personaje;
	m_personajeConFlip = personajeFlippeado;

	_LateUpdate();

	return toReturn;
}

void CapaPrincipal::_LateUpdate(){

	if(m_PersonajeQueScrollea==2){
		if (m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f)) {
			m_Personaje->Update(m_PersonajeDos->getVelocidadIzquierda());
		}else if (m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f) ){
			m_Personaje->Update(m_PersonajeDos->getVelocidadDerecha());
		}
		m_Personaje->Update(_scroll>0? m_PersonajeDos->getVelocidadDerecha() : m_PersonajeDos->getVelocidadIzquierda());
	}else
		m_Personaje->Update(0);

	if(m_PersonajeDos){
		if(m_PersonajeQueScrollea==1){
			if (m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f)) {
				m_PersonajeDos->Update(m_Personaje->getVelocidadIzquierda());
			}else if (m_PersonajeDos->getX() <= (getX() + m_ancho_ventana*0.02f) ){
				m_PersonajeDos->Update(m_Personaje->getVelocidadDerecha());
			}
			else
				m_PersonajeDos->Update(0);
		}else{
			m_PersonajeDos->Update(0);
		}
	}

}

bool floatIsBetween(float x, float border1, float deltaX){
	//printf("x:%f, border1: %f, border2: %f\n",x,border1,border1+deltaX);
	return x>=border1 and x<= border1+deltaX;
}

int CapaPrincipal::_CheckearColisiones(Personaje* personaje, Personaje* personajeFlippeado){
	Rect_Logico* rectAtaque1 = personaje->rectanguloAtaque();
	Rect_Logico* rectDefensa1 = personaje->rectanguloDefensa();

	Rect_Logico* rectAtaque2 = personajeFlippeado->rectanguloAtaque();
	Rect_Logico* rectDefensa2 = personajeFlippeado->rectanguloDefensa();

	//printf("actual: %f, anterior: %f, defensa: %f\n",rectAtaque1->x + rectAtaque1->w ,rectAtaqueAnterior1->x + rectAtaqueAnterior1->w,rectDefensa2->x );


	bool colisionaDefensaPersonajesX = (floatIsBetween(rectDefensa2->x ,rectDefensa1->x,rectDefensa1->w*1.5f));
	//bool colisionY = personaje->getY()>personajeFlippeado->getY() or personajeFlippeado->getY()> personaje->getY();
	if(colisionaDefensaPersonajesX and rectAtaque1 == NULL and rectAtaque2 == NULL){
		if(personaje->getSentidoDeMovimiento()>0)
			personaje->Frenar();
		if(personajeFlippeado->getSentidoDeMovimiento()<0)
			personajeFlippeado->Frenar();
		return COLISION_PERSONAJE_PERSONAJE_DEFENSA;
	}

	if (rectAtaque1 != NULL ){

		if(!rectAtaqueAnterior1){
			//printf("uso rect defensa \n");
			rectAtaqueAnterior1 = rectDefensa1;
		}

		bool colisionaAtaquePersonajeSinFlipX = (floatIsBetween(rectDefensa2->x ,rectAtaque1->x,rectAtaque1->w) and
				!floatIsBetween(rectDefensa2->x,rectAtaqueAnterior1->x,rectAtaqueAnterior1->w));

		bool colisionaY = (floatIsBetween(rectDefensa2->y, rectAtaque1->y-rectAtaque1->h , rectAtaque1->h) and floatIsBetween(rectDefensa2->y, rectAtaqueAnterior1->y-rectAtaqueAnterior1->h, rectAtaqueAnterior1->h)) or
				(floatIsBetween(rectAtaque1->y, rectDefensa2->y-rectDefensa2->h , rectDefensa2->h) and floatIsBetween(rectAtaqueAnterior1->y, rectDefensa2->y-rectDefensa2->h, rectDefensa2->h));

		if( colisionaAtaquePersonajeSinFlipX and colisionaY){
			return COLISION_PERSONAJE_PERSONAJE_SIN_FLIP;
			//printf("hubo colision  ppsf\n");
		}
	}else if (rectAtaque2 != NULL ){
		if(!rectAtaqueAnterior2){
			//printf("uso rect defensa \n");
			rectAtaqueAnterior2 = rectDefensa2;
		}
		bool colisionAtaquePersonajeConFlipX = (floatIsBetween(rectDefensa1->x  + rectDefensa1->w, rectAtaque2->x , rectAtaque2->w) and
						!floatIsBetween(rectDefensa1->x + rectDefensa1->w, rectAtaqueAnterior2->x, rectAtaqueAnterior2->w));

		//printf("colisionAtaquePersonajeConFlip: %i \n",colisionAtaquePersonajeConFlipX);
		bool colisionaY = (floatIsBetween(rectDefensa1->y, rectAtaque2->y-rectAtaque2->h , rectAtaque2->h) and floatIsBetween(rectDefensa1->y, rectAtaqueAnterior2->y-rectAtaqueAnterior2->h, rectAtaqueAnterior2->h)) or
				(floatIsBetween(rectAtaque2->y, rectDefensa1->y-rectDefensa1->h , rectDefensa1->h) and floatIsBetween(rectAtaqueAnterior2->y, rectDefensa1->y-rectDefensa1->h, rectDefensa1->h));
		//and colisionaY
		if( colisionAtaquePersonajeConFlipX  and colisionaY){
			return COLISION_PERSONAJE_PERSONAJE_CON_FLIP;
			//printf("hubo colision  ppcf\n");
		}
	}

	rectAtaqueAnterior1 = rectAtaque1;
	rectAtaqueAnterior2 = rectAtaque2;

	ObjetoArrojable* objetoSinFlip = personaje->getPoderActivo();
	ObjetoArrojable* objetoConFlip = personajeFlippeado->getPoderActivo();

	if (objetoSinFlip == NULL and objetoConFlip == NULL )
		return COLISION_NO_COLISION;

	if (objetoSinFlip != NULL and objetoConFlip != NULL ){

		Rect_Logico* rectPoderSinFlip = objetoSinFlip->rectanguloAtaque();
		Rect_Logico* rectPoderConFlip = objetoConFlip->rectanguloAtaque();
		if(rectPoderSinFlip->x>=rectPoderConFlip->x){
			return COLISION_OBJETO_OBJETO;
		}
	}

	if (objetoSinFlip != NULL){

		Rect_Logico* rectPoder = objetoSinFlip->rectanguloAtaque();
		if(rectPoder == NULL or rectPoder->x>rectDefensa2->x)
			return COLISION_NO_COLISION;

		bool colisionaAtaquePersonajeSinFlipX = rectDefensa2->x < rectPoder->x + objetoSinFlip->getVelocidadX() +rectPoder->w and
				rectDefensa2->x > rectPoder->x + rectPoder->w;

		//printf("RectAtaqueXEnd :%f      RectdefensaPos :%f \n",rectPoder->x+rectPoder->w,rectDefensa2->x);
		bool colisionaY = (floatIsBetween(rectDefensa2->y, rectPoder->y-rectPoder->h , rectPoder->h) and floatIsBetween(rectDefensa2->y, rectPoder->y-rectPoder->h, rectPoder->h)) or
				(floatIsBetween(rectPoder->y, rectDefensa2->y-rectDefensa2->h , rectDefensa2->h) and floatIsBetween(rectPoder->y, rectDefensa2->y-rectDefensa2->h, rectDefensa2->h));

		if( colisionaAtaquePersonajeSinFlipX and colisionaY){
			return COLISION_PERSONAJE_OBJETO_SIN_FLIP;
			//printf("hubo colision ppsf\n");
		}
	}

	if (objetoConFlip != NULL ){

		Rect_Logico* rectPoder = objetoConFlip->rectanguloAtaque();

		if(rectPoder == NULL or rectPoder->x + rectPoder->w < rectDefensa1->x )
			return COLISION_NO_COLISION;

		//bool colisionaAtaquePersonajeConFlipX = true;

		printf("x final:   %f\n",rectPoder->x - objetoConFlip->getVelocidadX());
		printf("x inicial: %f\n",rectPoder->x);
		printf("x defensa: %f\n",rectDefensa1->x+rectDefensa1->w);

		bool colisionaAtaquePersonajeConFlipX = rectDefensa1->x + rectDefensa1->w > rectPoder->x - objetoConFlip->getVelocidadX() and
				rectDefensa1->x + rectDefensa1->w < rectPoder->x;

		bool colisionaY = (floatIsBetween(rectDefensa1->y, rectPoder->y-rectPoder->h , rectPoder->h) and floatIsBetween(rectDefensa2->y, rectPoder->y-rectPoder->h, rectPoder->h)) or
				(floatIsBetween(rectPoder->y, rectDefensa2->y-rectDefensa2->h , rectDefensa2->h) and floatIsBetween(rectPoder->y, rectDefensa2->y-rectDefensa2->h, rectDefensa2->h));

		if( colisionaAtaquePersonajeConFlipX and colisionaY){
			return COLISION_PERSONAJE_OBJETO_CON_FLIP;
			//printf("hubo colision ppcf\n");
		}
	}
	return COLISION_NO_COLISION;
}

Personaje* CapaPrincipal::getPersonajSinFlip(){
	return m_personajeSinFlip;
}

Personaje* CapaPrincipal::getPersonajConFlip(){
	return m_personajeConFlip;
}


void CapaPrincipal::Renderizar()
{
	m_Personaje->renderizar(getX(), m_PersonajeDos->getX());
	if(m_PersonajeDos){
		m_PersonajeDos->renderizar(getX(), m_Personaje->getX());
	}
}

int CapaPrincipal::Scrollear(){
	if(getX() == 0 and (m_Personaje->getSentidoDeMovimiento() < 0))return this->CheckSegundoJugador(0);
	if(getX() == rect->w and (m_Personaje->getSentidoDeMovimiento() > 0)) return this->CheckSegundoJugador(0);
	if ((m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f)) and !(m_Personaje->getSentidoDeMovimiento() < 0)) return this->CheckSegundoJugador(0);
	if ((m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f)) and !(m_Personaje->getSentidoDeMovimiento() > 0) ) return this->CheckSegundoJugador(0);
	if ((m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f)) and (m_Personaje->getSentidoDeMovimiento() < 0)) return this->CheckSegundoJugador(-1);
	if ((m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f)) and (m_Personaje->getSentidoDeMovimiento() > 0) ) return this->CheckSegundoJugador(1);
	return this->CheckSegundoJugador(0);
}

int CapaPrincipal::CheckSegundoJugador(int estadoJugador1){
	if(!m_PersonajeDos){
		if(estadoJugador1 == 1)
			m_PersonajeQueScrollea = 1;
		return estadoJugador1;
	}



	switch (estadoJugador1) {
		case 1:
			if ((m_PersonajeDos->getX() <= (getX() + m_ancho_ventana*0.02f))){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			m_PersonajeQueScrollea = 1;
			return 1;
			break;
		case -1:
			if ((m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f))){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			m_PersonajeQueScrollea = 1;
			return -1;
			break;
		default:
			if(getX() == 0 and (m_PersonajeDos->getSentidoDeMovimiento() < 0))return this->_NadieScrollea();
			if(getX() == rect->w and (m_PersonajeDos->getSentidoDeMovimiento() > 0)) return this->_NadieScrollea();
			if ((m_PersonajeDos->getX() <= (getX() + m_ancho_ventana*0.02f)) and (m_PersonajeDos->getSentidoDeMovimiento() < 0)){
				if ((m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f))){
					m_Personaje->setScroll(false);
					m_PersonajeDos->setScroll(false);
					return 0;
				}
				m_PersonajeQueScrollea = 2;
				return -1;
			}
			if ((m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f)) and (m_PersonajeDos->getSentidoDeMovimiento() > 0) ){
				if ((m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f))){
					m_Personaje->setScroll(false);
					m_PersonajeDos->setScroll(false);
					return 0;
				}
				m_PersonajeQueScrollea = 2;
				return 1;
			}
			return this->_NadieScrollea();
			break;
	}
}

int CapaPrincipal::_NadieScrollea(){
	m_PersonajeQueScrollea = 0;
	return 0;
}

CapaPrincipal::~CapaPrincipal() {
	m_velocidad_derecha = 0;
	m_velocidad_izquierda = 0;
	m_Personaje = NULL;
	if(m_PersonajeDos)
		m_PersonajeDos = NULL;
}
