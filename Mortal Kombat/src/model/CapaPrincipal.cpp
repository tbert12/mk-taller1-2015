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
}

void CapaPrincipal::_actualizarX(){
	if (rect->x < 0) rect->x = 0;
	if (rect->x > rect->w) rect->x = rect->w;
}

void CapaPrincipal::Update(int scroll){
	if (scroll > 0)this->Mover(true);
	else if (scroll < 0) this->Mover(false);
	this->_actualizarX();
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

	this->_CheckearColisiones(personaje,personajeFlippeado);

	if(personaje->getX() + personaje->getAncho()*.5f > personajeFlippeado->getX() - personajeFlippeado->getAncho()*.5f){
		personaje->setFlip(true);
		personajeFlippeado->setFlip(false);
	}

	if(m_PersonajeQueScrollea==2){
		if (m_Personaje->getX() >= (getX() + m_ancho_ventana*0.80f)) {
			m_Personaje->Update(m_PersonajeDos->getVelocidadIzquierda());
		}else if (m_Personaje->getX() <= (getX() + m_ancho_ventana*0.02f) ){
			m_Personaje->Update(m_PersonajeDos->getVelocidadDerecha());
		}
		m_Personaje->Update(scroll>0? m_PersonajeDos->getVelocidadDerecha() : m_PersonajeDos->getVelocidadIzquierda());
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

void CapaPrincipal::_CheckearColisiones(Personaje* personaje, Personaje* personajeFlippeado){
	Rect_Logico* rectAtaque1 = personaje->rectanguloAtaque();
	Rect_Logico* rectDefensa1 = personaje->rectanguloDefensa();

	Rect_Logico* rectAtaque2 = personajeFlippeado->rectanguloAtaque();
	Rect_Logico* rectDefensa2 = personajeFlippeado->rectanguloDefensa();

	//printf("actual: %f, anterior: %f, defensa: %f\n",rectAtaque1->x + rectAtaque1->w ,rectAtaqueAnterior1->x + rectAtaqueAnterior1->w,rectDefensa2->x );

	if (rectAtaque1 != NULL ){

		if(!rectAtaqueAnterior1){
			printf("uso rect defensa \n");
			rectAtaqueAnterior1 = rectDefensa1;
		}

		bool colisionaAtaquePersonajeSinFlipX = (floatIsBetween(rectDefensa2->x - rectDefensa2->w,rectAtaque1->x,rectAtaque1->w) and
				!floatIsBetween(rectDefensa2->x - rectDefensa2->w,rectAtaqueAnterior1->x,rectAtaqueAnterior1->w));

		bool colisionaY = (floatIsBetween(rectDefensa2->y, rectAtaque1->y-rectAtaque1->h , rectAtaque1->h) and floatIsBetween(rectDefensa2->y, rectAtaqueAnterior1->y-rectAtaqueAnterior1->h, rectAtaqueAnterior1->h)) or
				(floatIsBetween(rectAtaque1->y, rectDefensa2->y-rectDefensa2->h , rectDefensa2->h) and floatIsBetween(rectAtaqueAnterior1->y, rectDefensa2->y-rectDefensa2->h, rectDefensa2->h));

		if( colisionaAtaquePersonajeSinFlipX and colisionaY){
			printf("hubo colision\n");
		}
		/*
		else
		{
			printf("rectAtaqueEnd: %f \n",rectAtaque1->x + rectAtaque1->w);
			printf("rectAtaqueAnteriorEnd: %f \n",rectAtaqueAnterior1->x );
			printf("rectDefensaStart: %f \n",rectDefensa2->x);
		}
		*/
			//if(rectAtaque1->x + rectAtaque1->w >= rectDefensa2->x and rectAtaqueAnterior1->x + rectAtaqueAnterior1->w < rectDefensa2->x  )
			//	printf("hubo colision Personaje1 Ataco y personaje 2 recibio\n");
	}else if (rectAtaque2 != NULL ){
		if(!rectAtaqueAnterior2){
			printf("uso rect defensa \n");
			rectAtaqueAnterior2 = rectDefensa2;
		}

		bool colisionAtaquePersonajeConFlipX = (floatIsBetween(rectDefensa1->x , rectAtaque2->x - rectAtaque2->w, rectAtaque2->w) and
				!floatIsBetween(rectDefensa1->x, rectAtaqueAnterior2->x - rectAtaqueAnterior2->w, rectAtaqueAnterior2->w));
		printf("colisionAtaquePersonajeConFlip: %i \n",colisionAtaquePersonajeConFlipX);
		bool colisionaY = (floatIsBetween(rectDefensa1->y, rectAtaque2->y-rectAtaque2->h , rectAtaque2->h) and floatIsBetween(rectDefensa1->y, rectAtaqueAnterior2->y-rectAtaqueAnterior2->h, rectAtaqueAnterior2->h)) or
				(floatIsBetween(rectAtaque2->y, rectDefensa1->y-rectDefensa1->h , rectDefensa1->h) and floatIsBetween(rectAtaqueAnterior2->y, rectDefensa1->y-rectDefensa1->h, rectDefensa1->h));
		//and colisionaY
		if( colisionAtaquePersonajeConFlipX  and colisionaY){
			//printf("rectAtaqueStart: %f \n",rectAtaque2->x - rectAtaque2->w);
			//printf("rectAtaqueAnteriorStart: %f \n",rectAtaqueAnterior2->x - rectAtaqueAnterior2->w);
			//printf("rectDefensaEnd: %f \n",rectDefensa1->x + rectDefensa1->w);
			printf("hubo colision\n");
		}
	}

	rectAtaqueAnterior1 = rectAtaque1;
	rectAtaqueAnterior2 = rectAtaque2;
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
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
			}
			if ((m_PersonajeDos->getX() >= (getX() + m_ancho_ventana*0.80f)) and (m_PersonajeDos->getSentidoDeMovimiento() > 0) ){
				m_Personaje->setScroll(false);
				m_PersonajeDos->setScroll(false);
				return 0;
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
