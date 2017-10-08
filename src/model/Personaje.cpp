/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, std::vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped) {
	nombre = nombre_personaje;
	nombreDeCarga = nombre;
	logo = "";
	vida = 100;

	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];
	poderes = arrojables;


	m_xAnterior = 0;
	m_xActual = 0;
	m_yActual = 0;
	m_yPiso = 0;

	m_velocidadActual = 0;
	m_proximaVelocidad = 0;

	m_AltoMundo = 0;
	m_AnchoMundo = 0;

	m_fliped = fliped;
	nextFlip = fliped;

	m_velocidad = velocidad;
	m_mover = true;

	//Es igual a SpriteActual->getAlto();
	maxAlturaDeSalto = 1.20 * getAlto();
	tiempoDeSalto = 0;
	_estaSaltando = -1;

	_estaCubriendose = false;
	_estaAgachado = false;
	_estaAtacando = false;
	_recibioGolpe = false;

	_estaMuerto = false;
	_gano = false;

	_estaHaciendoFatality2 = false;

	m_rectanguloAtaque = new Rect_Logico;
	m_rectanguloDefensa = new Rect_Logico;
}

void Personaje::reset(){
	vida = 100;
	spriteActual = sprites[SPRITE_INICIAL];
	for (size_t i = 0; i < sprites.size() ; i++){
		sprites[i]->hardReset();
	}
	for (size_t i = 0; i < poderes.size() ; i++){
		poderes[i]->destruir();
	}
	for (size_t i = 0; i < mObjetos.size() ; i++){
		mObjetos[i]->reset();
	}
	m_xActual = 0;
	m_yActual = 0;
	m_yPiso = 0;
	m_velocidadActual = 0;
	m_fliped = false;
	m_mover = true;
	tiempoDeSalto = 0;
	_estaSaltando = -1;
	_estaCubriendose = false;
	_estaAgachado = false;
	_estaAtacando = false;
	_recibioGolpe = false;
	_estaMuerto = false;
	_estaHaciendoFatality2 = false;
	_gano = false;
	_resetPropio();
}

void Personaje::_resetPropio(){}
//-------------------------------------------------------------------------------------------------------------------------
//Manejo de attributos logicos

ObjetoArrojable* Personaje::getPoderActivo(){
	if (poderes[0] != NULL){
		if(poderes[0]->getVida())
			return poderes[0];
	}
	return NULL;
}

void Personaje::setPathLogo( std::string ruta ){
	logo = ruta;
}

std::string Personaje::getPathLogo(){
	return logo;
}

void Personaje::setNombre(string nombre_nuevo){
	nombre = nombre_nuevo;
}

std::string Personaje::getNombreDeCarga(){
	return nombreDeCarga;
}

void Personaje::lanzarObjeto(){
	//ya hay poder lanzado
	if (poderes[0] != NULL){
		if(poderes[0]->getVida())
			return;
	}
	//Poner sprite del personaje para lanzar
	float x;
	float y;
	if (m_fliped){
		x = m_xActual - getAncho()*0.6;
	}
	else{
		x = m_xActual + getAncho()*0.6;
	}
	/* Esto tiene que estar en sprite y seteado desde el Json
	 * El spriteActual = SPRITE_PODER_1
	 */
	y = m_yActual - getAlto()*0.8;
	poderes[0]->lanzar(x, y, m_fliped);

}

void Personaje::setDimensionesMundo(float h,float w){
	m_AltoMundo = h;
	m_AnchoMundo = w;
}

int Personaje::getVida(){
	return vida;
}

void Personaje::setObjetos(std::vector<ObjetoDroppable*> objetosRecibidos){
	mObjetos = objetosRecibidos;
}

void Personaje::setPosition(float x, float y){
	m_xAnterior = m_xActual;
	m_xActual = x;
	if(y < 0)
		m_yActual = m_yPiso;
	else
		m_yActual = m_yPiso = y;

	for (size_t i = 0; i < mObjetos.size();i++){
			mObjetos[i]->y_piso(m_yPiso);
	}
}

void Personaje::setPositionX(float x){
	m_xAnterior = m_xActual;
	m_xActual = x;
}

std::string Personaje::getNombre() {
	return nombre;
}

float Personaje::getX()
{
	return m_xActual;
}

float Personaje::getY()
{

	return m_yActual;
}

bool Personaje::getFlipState()
{
	return m_fliped;
}

void Personaje::QuitarVida(int valor){
	vida = vida - valor;
	if(vida <= 0){
		vida = 0;
	}
}

void Personaje::setCombos( std::vector<Combo*> combos){
	mCombos = combos;
}

std::vector<Combo*> Personaje::getCombos(){
	return mCombos;
}

void Personaje::setScroll(bool scrollear){
	m_mover = scrollear;
}

void Personaje::setFlip(bool flip){
	if (_estaSaltando > 0 or flip == m_fliped or spriteActual == sprites[SPRITE_TOMA_1]) {
		nextFlip = flip;
		return;
	}
	m_fliped= flip;
	nextFlip = flip;
	if (flip){
		//Le sumamos el ancho para que la x siga quedando en la cabeza
		m_xActual += spriteActual->getAncho();
	}
	else{
		m_xActual -= spriteActual->getAncho();
	}
}
void pbool(bool a){
	printf("%s |", a ? "T":"F");
}

void printbools(std::string nombrem,bool a,bool b,bool c,bool d){
	printf("%s: ",nombrem.c_str());
	printf("_estaSaltando: ");
	pbool(a);
	printf("_estaAgachado: ");
	pbool(b);
	printf("_estaCubriendose: ");
	pbool(c);
	printf("_recibioGolpe: ");
	pbool(d);
	printf("\n");
}

void Personaje::Update(float posDeOtroJugador,bool forzado){
	//printbools(nombre,_estaSaltando > 0,_estaAgachado,_estaCubriendose,_recibioGolpe);
	//printf("----SpriteActual: %d\n",getAccionDeAtaque());
	//Actualizo La X para cada caso y verificando limites
	float renderX = m_xActual + m_velocidadActual;
	float maximo,minimo;
	if(m_fliped){
		maximo = m_AnchoMundo;
		minimo = spriteActual->getAncho();
	}else{
		maximo = (m_AnchoMundo + spriteActual->getAncho());
		minimo = 0;
	}

	//bool estaElotroJugador = (m_velocidadActual > 0 and renderX >= posDeOtroJugador) or (m_velocidadActual < 0 and renderX >= posDeOtroJugador);
	if (renderX <= maximo and renderX >= minimo){
		if ( !_estaAgachado and !_estaCubriendose){
			if (_estaAtacando){
				if (_estaSaltando > 0){
					if(m_mover){
						m_xAnterior = m_xActual;
						m_xActual = renderX;
					}
				}
			} else {
				if(m_mover /*and !estaElotroJugador*/){
					m_xAnterior = m_xActual;
					m_xActual = renderX;
				}
			}
		}
	}

	if(m_xActual > maximo){
		m_xActual = maximo;
	} else if(m_xActual < minimo){
		m_xActual = minimo;
	}

	//Actualizo la Y
	if(_estaSaltando and !forzado){
		_actualizarY();
	} else if (!_estaSaltando){
		m_yActual = m_yPiso;
	}

	m_mover = true;
	_UpdatePoder();

}

void Personaje::_UpdatePoder(){
	if(poderes.size() <= 0) return;
	else{
		for(int j= 0;j< (int)poderes.size();j++){
			if (!poderes[j]->getVida()) return;
			poderes[j]->update();
			if(poderes[j]->getPosX() < 0 || poderes[j]->getPosX() > m_AnchoMundo)
				poderes[j]->destruir();
		}
	}
}

bool Personaje::enMovimiento(){
	return (m_velocidadActual != 0);
}
bool Personaje::estaSaltando(){
	return _estaSaltando >= 0;
	return _estaSaltando > 0;
}

bool Personaje::estaCubriendose() {
	return _estaCubriendose;
}

bool Personaje::estaAgachado() {
	return _estaAgachado;
}

bool Personaje::estaAtacando() {
	return _estaAtacando;
}

float Personaje::getAncho(){
	return spriteActual->getAncho();
}

float Personaje::getAlto(){
	return spriteActual->getAlto();
}

int Personaje::_getaccionPropia(){return 0;}

int Personaje::getAccionDeAtaque(){
	//Devuelve -1 si no encuentra la Accion del Sprite
	//Nunca va a pasar, pero por el compilador
	int accionPropia = _getaccionPropia();
	if (accionPropia) return accionPropia;
	for (int i=0; i < (int)sprites.size(); i++){
		if (sprites[i] == spriteActual){
			return i;
		}
	}
	return -1;
}

int Personaje::getSentidoDeMovimiento(){
	if (m_velocidadActual > 0) return 1;
	else if (m_velocidadActual < 0) return -1;
	if(m_xActual-m_xAnterior > 0 ) return 1;
	else if(m_xActual-m_xAnterior < 0 ) return -1;
	return 0;
}

float Personaje::getVelocidad(){
	return m_velocidadActual;
}

float Personaje::getVelocidadDerecha(){
	return m_velocidad;
}

float Personaje::getVelocidadIzquierda(){
	return -m_velocidad;
}

void Personaje::renderizar(float x_dist_ventana,float posOtherPlayer){
	float corrimiento = 0;
	float corr2 = 0;
	if (_estaMuerto) {
		corr2 = sprites[SPRITE_CUBRIRSE]->getAncho();
		corrimiento = getAncho();
		if (m_fliped){
			corr2 = -corr2;
			corrimiento = -corrimiento;
		}
	}
	if ( spriteActual == sprites[SPRITE_GANA] ){
		corrimiento = getAncho()/2;
		corr2 = sprites[SPRITE_CUBRIRSE]->getAncho();
		if (m_fliped){
			corrimiento = -corrimiento;
			corr2 = -corr2;
		}
	}
	spriteActual->render( (m_xActual+corr2) - x_dist_ventana - corrimiento,m_yActual ,m_fliped);

	//render poderes
	if(poderes.size() > 0){
		for(int j= 0;j< (int)poderes.size();j++){
			poderes[j]->renderizar(x_dist_ventana);
		}
	}
	for (size_t i = 0; i<mObjetos.size();i++){
		if (mObjetos[i]->getVida()){
			mObjetos[i]->renderizar(x_dist_ventana);
		}
	}

	//* Para test de colisiones *//
	//spriteActual->RENDERCOLISIONTEST(x_dist_ventana, m_yActual ,m_fliped , rectanguloAtaque() , rectanguloDefensa());
	//* Fin de test para mostrar colisiones *//

	AvanzarSprite();
}

//-------------------------------------------------------------------------------------------------------------------------
//Rectangulo para Colisiones

Rect_Logico* Personaje::rectanguloAtaque(){
	if (!_estaAtacando) return NULL;

	//Devuelve Rect_Nuevo, el ue lo pide se encarga de eliminarlo
	int Accion = getAccionDeAtaque();
	int propH = 1; //Proporsiones Harcodeadas para formar rectangulos acordes
	int propY = 1;
	/* Casos a Resolver
	 * 	OK	-Pina Alta, Patada Alta
	 * 	OK	-Patada Saltando, Pina Saltando
	 * 	OK  -Pina Baja, Patada Baja
	 * 	OK	-Patada Agachado, Pina Agachado
	 * 	OK	-Gancho
	 */

	Rect_Logico* rectangulo = new Rect_Logico;

	if(m_fliped)
		rectangulo->x = m_xActual - getAncho();
	else
		rectangulo->x = m_xActual + sprites[SPRITE_CUBRIRSE]->getAncho()*0.50;

	if (Accion == SPRITE_PATADA_ALTA){
		if ( spriteActual->primerFrame() ) propH = 4;
		else propH = 0;
	} else if (Accion == SPRITE_PINA_ALTA){
		propH = 4;
	} else if (Accion == SPRITE_PATADA_BAJA or Accion == SPRITE_PINA_BAJA or Accion == SPRITE_PINA_AGACHADO or Accion == SPRITE_PATADA_ALTA_AGACHADO){
		propH = 6;
		propY = 2;
	} else if (Accion == SPRITE_PATADA_CIRCULAR or Accion == SPRITE_PATADA_BAJA_AGACHADO){
		propH = 2;
		propY = propH;
	} else if (Accion == SPRITE_PINA_SALTANDO){
		propH = 3;
		propY = 2;
	} else if (Accion == SPRITE_PATADA_SALTANDO){
		propH = 2;
		propY = propH;
	}else if (Accion == SPRITE_GANCHO){
		if (!spriteActual->proxFrameUltimo()){
			propH = 0; //Por lo que veo C++ sabe dividir por 0
		} else {
			propH = 4;
		}
	}
	if (propH) rectangulo->h = getAlto()/propH;
	else rectangulo->h = 0;

	rectangulo->y = m_yActual - getAlto() + rectangulo->h*propY;
	rectangulo->w = spriteActual->getAncho() - sprites[SPRITE_CUBRIRSE]->getAncho()*0.50;

	m_rectanguloAtaque->x = rectangulo->x;
	m_rectanguloAtaque->y = rectangulo->y;
	m_rectanguloAtaque->w = rectangulo->w;
	m_rectanguloAtaque->h = rectangulo->h;

	return rectangulo;
}

Rect_Logico* Personaje::rectanguloDefensa(){
	//Devuelve Rect_Nuevo, el ue lo pide se encarga de eliminarlo
	Rect_Logico* rectangulo = new Rect_Logico;

	float MinAncho = sprites[SPRITE_CUBRIRSE]->getAncho();
	rectangulo->y=  m_yActual;
	if(m_fliped)
		rectangulo->x = m_xActual - MinAncho*0.95;
	else
		rectangulo->x = m_xActual + MinAncho*0.35;
	rectangulo->w = MinAncho - getAncho()*0.25; //El mas Angosto
	if (_estaSaltando > 0 and _estaAtacando){
		rectangulo->w = MinAncho;
	}
	rectangulo->h = spriteActual->getAlto();

	m_rectanguloAtaque->x = rectangulo->x;
	m_rectanguloAtaque->y = rectangulo->y;
	m_rectanguloAtaque->w = rectangulo->w;
	m_rectanguloAtaque->h = rectangulo->h;

	return rectangulo;
}

//-------------------------------------------------------------------------------------------------------------------------
//Manejo de Sprites

bool Personaje::_updatePropio(){
	return false;
}

void Personaje::AvanzarSprite(){
	if ( _updatePropio() ) return;
	//Los If son muy parecidos, pero hay que tenerlos separados para entender el codigo
	if (spriteActual->ultimoFrame() or (!_estaSaltando and !_recibioGolpe) ){
		//Termina de atacar o agacharse o saltando = 0 (justo en el momento que cae)
		if ( (_estaAtacando and !_estaAgachado and !_estaCubriendose) or !_estaSaltando or (_estaAgachado and !_estaAtacando and !_estaCubriendose) ){
			if (m_proximaVelocidad) m_velocidadActual = m_proximaVelocidad;
			else m_velocidadActual = 0;

			if (!m_velocidadActual){
				_cambiarSprite(SPRITE_INICIAL);
			} else {
				setFlip(nextFlip);
				_Caminar( (m_velocidadActual > 0) );
			}
			if (_estaAtacando) _estaAtacando = false;
			if (!_estaSaltando) _estaSaltando = -1;
			if (_estaAgachado and !_estaCubriendose) _estaAgachado = false;
		}
	}
	if ( _estaCubriendose and spriteActual->ultimoFrame() ) {
		//Deja de Cubrirse
		if ( !_estaAgachado ) {
			if (!m_velocidad)
				_cambiarSprite(SPRITE_INICIAL);
			else
				if (m_proximaVelocidad) m_velocidadActual = m_proximaVelocidad;
				_Caminar( ( m_velocidadActual > 0 ) );
		} else {
			_cambiarSprite(SPRITE_AGACHAR);
			spriteActual->doLoop(true);
			spriteActual->Advance();
		}
		_estaCubriendose = false;
	}
	if (_estaAtacando and spriteActual->ultimoFrame()){
		//Termina de accionar un Ataque (Agachado o parado)
		if ( !_estaAgachado ) {
			if (m_proximaVelocidad) m_velocidadActual = m_proximaVelocidad;
			if (!m_velocidadActual){
				_cambiarSprite(SPRITE_INICIAL);
			} else {
				setFlip(nextFlip);
				_Caminar( (m_velocidadActual > 0) );
			}
		} else {
			_cambiarSprite(SPRITE_AGACHAR);
			spriteActual->doLoop(true);
			spriteActual->Advance();
		}
		_estaAtacando = false;
	}

	if (_recibioGolpe and spriteActual->ultimoFrame()){
		//Termina de recibir Golpe (Ya sea agachado o parado)
		if ( _estaAgachado ){
			if (_estaCubriendose){
				_cubrirseAgachado();
			} else {
				_cambiarSprite(SPRITE_AGACHAR);
				spriteActual->doLoop(true);
				spriteActual->Advance();
			}

		} else {
			//No importa porque se la setie yo
			m_velocidadActual = m_proximaVelocidad;
			if (!m_velocidadActual){
				if (_estaCubriendose){
					_cubrirseParado();
				} else {
					_cambiarSprite(SPRITE_INICIAL);
				}
			} else {
				setFlip(nextFlip);
				_Caminar( (m_velocidadActual > 0) );
			}

		}
		_recibioGolpe = false;
	}

	if ( _estaSaltando > 0){
		//Para Saltear primer Frame del Salto diagonal (Toma Impulso)
		if (m_velocidadActual > 0){
			if ( (!m_fliped and spriteActual->ultimoFrame()) or (m_fliped and spriteActual->proxFrameUltimo()) ){
				spriteActual->Advance();
			}
		} else if (m_velocidadActual < 0){
			if ( (!m_fliped and spriteActual->proxFrameUltimo()) or (m_fliped and spriteActual->ultimoFrame())){
				spriteActual->Advance();
			}
		}
	}
	if (_estaAtacando and spriteActual == sprites[SPRITE_PODER_1]){
		if ( spriteActual->inFrezee() ){
			lanzarObjeto();
		}
	}
	spriteActual->Advance();
}

void Personaje::_cambiarSprite(int SpriteAccion){
	//Excepcion del caminar para cambiarlo repentinamente
	if (sprites[SpriteAccion] == spriteActual and SpriteAccion != SPRITE_CAMINAR) return;
	//Dejo el Sprite Limpio antes de cambiarlo
	if (SpriteAccion != SPRITE_CAMINAR) spriteActual->hardReset();
	spriteActual = sprites[SpriteAccion];
	if (SpriteAccion == SPRITE_CAMINAR or
		SpriteAccion == SPRITE_SALTAR_DIAGONAL){
		bool doReverse;
		if (m_velocidadActual > 0){
			doReverse = m_fliped;
		}
		else if (m_velocidadActual < 0){
			doReverse = !m_fliped;
		}
		if (SpriteAccion == SPRITE_SALTAR_DIAGONAL) spriteActual->Reset();
		spriteActual->doReverse(doReverse);
		return;
	}
	//Limpio el Sprite antes de empezar a usarlo (de todos modos ya lo tengo limpio)
	spriteActual->hardReset();

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++CAMINAR/SALTAR/AGACHAR++++++++++++++++++++++++++++++++++

void Personaje::Inicial(){
	//Solo se mueve al sprite Inicial (Parado)
	_cambiarSprite(SPRITE_INICIAL);
}

void Personaje::Frenar(){
	if (_gano or _estaMuerto) return;
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _estaAtacando or _recibioGolpe){
		m_proximaVelocidad = 0;
		return;
	}
	m_velocidadActual = 0;
	m_proximaVelocidad = 0;
	Inicial();
}


float _factorVelocidad(bool flip,bool derecha){
	float factor = 1;
	if (derecha){
		if (flip)
			factor = 0.8;

	} else {
		factor = -0.8;
		if (flip)
			factor = -1;
	}
	return factor;
}

void Personaje::CaminarDerecha(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _estaAtacando) {
		float factor = _factorVelocidad(m_fliped,true);
		m_proximaVelocidad = m_velocidad*factor;
		return;
	}
	_Caminar(true);
}

void Personaje::CaminarIzquierda(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _estaAtacando) {
		float factor = _factorVelocidad(m_fliped,false);
		m_proximaVelocidad = m_velocidad*factor;
		return;
	}
	_Caminar(false);
}

void Personaje::_Caminar(bool derecha){
	if (_gano or _estaMuerto) return;
	float factor = _factorVelocidad(m_fliped,derecha);
	m_velocidadActual = m_velocidad * factor;
	m_proximaVelocidad = m_velocidadActual;
	_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::Saltar(){
	if (_gano or _estaMuerto) return;
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _recibioGolpe or _estaAtacando) return;
	maxAlturaDeSalto = 1.20 * getAlto();

	if (m_velocidadActual > 0){
		_SaltarDerecha();
	} else if (m_velocidadActual < 0) {
		_SaltarIzquierda();
	} else{
		_SaltarHorizontal();
	}
}

void Personaje::_SaltarDerecha(){
	_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	tiempoDeSalto = 1;
	m_velocidadActual = m_velocidad*1.8;
}

void Personaje::_SaltarIzquierda(){
	_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	tiempoDeSalto = 1;
	m_velocidadActual = - m_velocidad*1.8;
}

void Personaje::_SaltarHorizontal(){
	_cambiarSprite(SPRITE_SALTAR);
	_estaSaltando = 1;
	tiempoDeSalto = 1;
	spriteActual->doLoop(true);
}

//Funciones Logicas de Salto
void Personaje::_actualizarY(){
	//Actualiza la Y
	if (!tiempoDeSalto) return;
	m_yActual = _yDeSalto(m_yActual,tiempoDeSalto);
	tiempoDeSalto++;

	//Cuando esta llegando al piso, vuelvo al estado inicial
	if(tiempoDeSalto > TIEMPOTOTALDESALTO){
		tiempoDeSalto = 0;
		_estaSaltando = 0;
		if (_recibioGolpe){
			m_velocidadActual = 0;
			spriteActual->doLoop(false);
		} else {
			if (m_velocidadActual) {
				spriteActual->doReverse(false);
				spriteActual->Reset();
			}
			spriteActual->doLoop(false);
			if (!m_velocidadActual){
				spriteActual->Advance();
			}
		}
	}
}

float Personaje::_yDeSalto(float currentY, float currentT)
{
	float tiempoDeSalto = TIEMPOTOTALDESALTO;

	//Despeje de la Cuadratica dependiendo del MAX;
	float alturaMax = maxAlturaDeSalto/((tiempoDeSalto*tiempoDeSalto)/4);
	return alturaMax * currentT * (currentT - tiempoDeSalto) + m_yPiso;
}

void Personaje::Agachar(){
	if (_gano or _estaMuerto) return;
	if (_estaSaltando > 0 or  _estaAgachado or _recibioGolpe or _estaAtacando or _estaCubriendose) return;

	_cambiarSprite(SPRITE_AGACHAR);
	_estaAgachado = true;
	spriteActual->doLoop(true);

}

void Personaje::Levantarse(){
	if (_gano or _estaMuerto) return;
	if (_estaSaltando > 0 or !_estaAgachado or _recibioGolpe or _estaAtacando or _estaCubriendose) return;
	if (_estaCubriendose){
		dejarDeCubrirse();
	}
	spriteActual->doLoop(false);
	spriteActual->doReverse(true);
	//_estaAgachado = false;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++CUBRIRSE++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::cubrirse() {
	if (_gano or _estaMuerto) return;
	if ( _estaCubriendose or _estaSaltando > 0 or _estaAtacando or _recibioGolpe) return;

	if ( _estaAgachado ) {
		_cubrirseAgachado();
	} else {
		_cubrirseParado();
	}
	_estaCubriendose = true;
}

void Personaje::_cubrirseAgachado() {
	// Destrabarlo
	_cambiarSprite(SPRITE_CUBRIRSE_AGACHADO);
	spriteActual->doLoop(true);
}

void Personaje::_cubrirseParado(){
	_cambiarSprite(SPRITE_CUBRIRSE);
	spriteActual->doLoop(true);
}

void Personaje::dejarDeCubrirse() {
	if (_gano or _estaMuerto) return;
	if ( !_estaCubriendose ) return;
	spriteActual->doLoop(false);
	spriteActual->doReverse(true);

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++ATAQUE - PINA+++++++++++++++++++++++++++++++++++++++++++

void Personaje::pinaBaja() {
	_pina(SPRITE_PINA_BAJA,SPRITE_COMBO_PINA_BAJA);
}

void Personaje::pinaAlta() {
	_pina(SPRITE_PINA_ALTA,SPRITE_COMBO_PINA_ALTA);
}

void Personaje::_pina(int sprite, int spritecombo){
	if (_gano or _estaMuerto) {
		m_cant_pinas = 0;
		return;
	}
	if (_estaCubriendose or _recibioGolpe) {
		m_cant_pinas = 0;
		return;
	}
	int accionActual = getAccionDeAtaque();
	if (_estaAtacando and (accionActual != sprite)) {
		m_cant_pinas = 0;
		return;
	}
	if ( _estaAgachado ) {
		if (sprite == SPRITE_PINA_ALTA)
			_gancho();
		else
			_pinaAgachado();
		m_cant_pinas = 0;
		return;
	}
	if ( _estaSaltando > 0 ) {
		_pinaSaltando();
		m_cant_pinas = 0;
		return;
	}
	if (accionActual == sprite && m_cant_pinas > 2){
		_cambiarSprite(spritecombo);
		m_cant_pinas = 0;
	} else {
		_cambiarSprite(sprite);
		m_cant_pinas++;
	}
	_estaAtacando = true;

}

void Personaje::_pinaAgachado() {
	_cambiarSprite(SPRITE_PINA_AGACHADO);
	_estaAtacando = true;
}

void Personaje::_gancho() {
	//Destrabarlo
	_cambiarSprite(SPRITE_GANCHO);
	spriteActual->freezeSprite();
	_estaAtacando = true;
}

void Personaje::_pinaSaltando() {
	if ( tiempoDeSalto >= TIEMPOTOTALDESALTO/3 and tiempoDeSalto <= TIEMPOTOTALDESALTO - 4){
		_cambiarSprite(SPRITE_PINA_SALTANDO);
		spriteActual->doLoop(true);
		_estaAtacando = true;
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++ATAQUE - PATADA+++++++++++++++++++++++++++++++++++++++++

void Personaje::patadaBaja() {
	if (_gano or _estaMuerto) return;
	if (_estaCubriendose or _recibioGolpe or _estaAtacando) return;
	if ( _estaAgachado ) {
		_patadaBajaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_patadaSaltando();
	} else if ( (m_velocidadActual < 0 and !m_fliped) or (m_velocidadActual > 0 and m_fliped) ) {
		_patadaCircular();
	} else {
		_cambiarSprite(SPRITE_PATADA_BAJA);
	}
	_estaAtacando = true;
}

void Personaje::_patadaBajaAgachado() {
	//Destrabarlo
	_cambiarSprite(SPRITE_PATADA_BAJA_AGACHADO);
}

void Personaje::patadaAlta() {
	if (_gano or _estaMuerto) return;
	if (_estaCubriendose or _recibioGolpe or _estaAtacando) return;
	if ( _estaAgachado ) {
		_patadaAltaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_patadaSaltando();
	} else {
		_cambiarSprite(SPRITE_PATADA_ALTA);
	}
	_estaAtacando = true;
}

void Personaje::_patadaCircular() {
	_cambiarSprite(SPRITE_PATADA_CIRCULAR);
}

void Personaje::_patadaSaltando() {
	if ( tiempoDeSalto >= TIEMPOTOTALDESALTO/4 ){
		_cambiarSprite(SPRITE_PATADA_SALTANDO);
		spriteActual->doLoop(true);
	}
}

void Personaje::_patadaAltaAgachado() {
	//Destrabarlo
	_cambiarSprite(SPRITE_PATADA_ALTA_AGACHADO);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++RECIBE-GOLPES+++++++++++++++++++++++++++++++++++++++++++

bool Personaje::recibirGolpe(int CodigoGolpe, int Danio){
	//printf("RECIBE GOLPE\n");
	if (getAccionDeAtaque() == SPRITE_FINISH) {
		_estaMuerto = false;
		morir();
		return false;
	}
	//El Codigo de golpe esta seteados en todos el mismo
	/*
		--->SPRITE_RECIBE_GANCHO<--- (-10 de Vida)
		GANCHO=         	   12;

		--->SPRITE_RECIBE_FUERTE<--- (-10 de Vida)
		PINA_SALTANDO=  	   21;
		PATADA_SALTANDO=	   17;
		PODER =				   -1;

		--->SPRITE_RECIBE_ALTO<----- (-8 de Vida)
		PINA_ALTA=		 	   19;
		PATADA_ALTA=		   14;

		--->SPRITE_RECIBE_BAJO || SPRITE_RECIBE_AGACHADO<--- (-5 de Vida)
		PINA_AGACHADO=  	   18;
		PATADA_ALTA_AGACHADO=  5;
		PINA_BAJA=		 	   20;
		PATADA_BAJA_AGACHADO=  6;
		PATADA_BAJA=    	   15;

		--->SPRITE_RECIBE_PATADA_GIRA<-- (-8 de Vida)
		PATADA_CIRCULAR=       16;

	*/
	//if (_recibioGolpe) return false;
	if (_estaCubriendose){
		bool puedeRecibirCubierto = (!_estaAgachado) and
									(CodigoGolpe == SPRITE_PINA_AGACHADO or
									 CodigoGolpe == SPRITE_PATADA_BAJA_AGACHADO or
									 CodigoGolpe == SPRITE_PATADA_CIRCULAR);

		puedeRecibirCubierto = (CodigoGolpe == SPRITE_TOMA_1);

		if (!puedeRecibirCubierto){
			QuitarVida(1);
			spriteActual->vibrar();
			return false;
		}
	}
	if (_estaCubriendose) _estaCubriendose = false;
	if (_estaAtacando) _estaAtacando = false;

	bool golpeFuerte = false;

	std::map<int, int> reaccionesAGolpes;
	reaccionesAGolpes[SPRITE_GANCHO] = 				SPRITE_RECIBE_GANCHO;
	reaccionesAGolpes[SPRITE_PINA_ALTA] = 			SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_ALTA] = 		SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_SALTANDO] = 	SPRITE_RECIBE_GANCHO;
	reaccionesAGolpes[SPRITE_PINA_SALTANDO] = 		SPRITE_RECIBE_FUERTE;
	reaccionesAGolpes[GOLPE_DE_PODER] = 			SPRITE_RECIBE_FUERTE; //PODER
	reaccionesAGolpes[SPRITE_COMBO_PINA_BAJA] =		SPRITE_RECIBE_FUERTE;
	reaccionesAGolpes[SPRITE_COMBO_PINA_ALTA] =		SPRITE_RECIBE_FUERTE;
	reaccionesAGolpes[SPRITE_PATADA_ALTA_AGACHADO]= _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_BAJA_AGACHADO]= _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PINA_AGACHADO]= 		_estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_BAJA]=  		_estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PINA_BAJA]= 			_estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_CIRCULAR] = 	SPRITE_RECIBE_PATADA_GIRA;
	reaccionesAGolpes[SPRITE_TOMA_1] = 				SPRITE_ES_TOMADO;

	std::map<int, int> DanioPorGolpe;
	DanioPorGolpe[SPRITE_GANCHO]= 				QUITAR_VIDA_GANCHO;
	DanioPorGolpe[SPRITE_PINA_ALTA]= 			QUITAR_VIDA_GOLPE_ALTO;
	DanioPorGolpe[SPRITE_PATADA_ALTA]=  		QUITAR_VIDA_GOLPE_ALTO;
	DanioPorGolpe[SPRITE_PATADA_SALTANDO]=  	QUITAR_VIDA_GOLPE_ALTO;
	DanioPorGolpe[SPRITE_PINA_SALTANDO]= 		QUITAR_VIDA_GOLPE_ALTO;
	DanioPorGolpe[SPRITE_PATADA_ALTA_AGACHADO]= QUITAR_VIDA_GOLPE_BAJO;
	DanioPorGolpe[SPRITE_PATADA_BAJA_AGACHADO]= QUITAR_VIDA_GOLPE_BAJO;
	DanioPorGolpe[SPRITE_PINA_AGACHADO]= 		QUITAR_VIDA_GOLPE_BAJO;
	DanioPorGolpe[SPRITE_PATADA_BAJA]=  		QUITAR_VIDA_GOLPE_BAJO;
	DanioPorGolpe[SPRITE_PINA_BAJA]= 			QUITAR_VIDA_GOLPE_BAJO;
	DanioPorGolpe[SPRITE_PATADA_CIRCULAR]=  	QUITAR_VIDA_PATADA_CIRCULAR;
	DanioPorGolpe[GOLPE_DE_PODER]=  			Danio;
	DanioPorGolpe[SPRITE_TOMA_1] = 				QUITAR_VIDA_GOLPE_BAJO;
	DanioPorGolpe[SPRITE_COMBO_PINA_BAJA] = 	QUITAR_VIDA_GOLPE_ALTO;
	DanioPorGolpe[SPRITE_COMBO_PINA_ALTA] = 	QUITAR_VIDA_GOLPE_ALTO;

	if (!reaccionesAGolpes.find(CodigoGolpe)->second) return false;
	if (_estaSaltando > 0){
		if (CodigoGolpe != SPRITE_GANCHO) CodigoGolpe = SPRITE_PATADA_SALTANDO;
	}

	_cambiarSprite(reaccionesAGolpes[CodigoGolpe]);
	QuitarVida(DanioPorGolpe[CodigoGolpe]);
	spriteActual->freezeSprite();

	float velocidadDeRetroceso = m_velocidad;
	bool sangrar = false;
	float alturaDesangre = 1;

	if (reaccionesAGolpes[CodigoGolpe] == SPRITE_RECIBE_GANCHO){
		velocidadDeRetroceso = 2.5 * m_velocidad;
		float prop_altura = 0.8;
		if (CodigoGolpe == SPRITE_GANCHO) {
			prop_altura = ALTURA_SALTO_GANCHO;
			velocidadDeRetroceso = m_velocidad;
		}
		maxAlturaDeSalto = prop_altura * getAlto() + (m_yPiso - m_yActual);
		tiempoDeSalto = 1;
		_estaSaltando = 1;
		spriteActual->doLoop(true);
		spriteActual->freezeSprite();
	} else if (reaccionesAGolpes[CodigoGolpe] == SPRITE_ES_TOMADO){
		velocidadDeRetroceso = -3*m_velocidad;
		maxAlturaDeSalto = 0.3 * getAlto() + (m_yPiso - m_yActual);
		tiempoDeSalto = 1;
		_estaSaltando = 1;
		spriteActual->doLoop(true);
		spriteActual->freezeSprite();
	}

	if ( (DanioPorGolpe[CodigoGolpe] >= MIN_GOLPE_FUERTE and CodigoGolpe != SPRITE_PATADA_CIRCULAR) or CodigoGolpe == SPRITE_TOMA_1 or CodigoGolpe == GOLPE_DE_PODER){
		golpeFuerte = true;
		sangrar = true;
		if (CodigoGolpe == SPRITE_TOMA_1) golpeFuerte = false;
		m_velocidadActual = -velocidadDeRetroceso;
		if (m_fliped)
			m_velocidadActual = velocidadDeRetroceso;
		m_proximaVelocidad = 0;
	}
	if (_estaAgachado) sangrar = true;

	_recibioGolpe = true;
	if (mObjetos.size() and sangrar)
		mObjetos[SANGRE_MUCHA]->lanzar(m_xActual,m_yActual - getAlto()*alturaDesangre,!m_fliped,false,1);

	return golpeFuerte;
}

//Despues de colisionar el personaje que ataca recibe un pulso de que colisiono su ataque
void Personaje::terminarAtaque(){}

//+++++++++++++++++++++++++++++TOMA++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Personaje::toma1(){
	if (_gano or _estaMuerto) return;
	if (_recibioGolpe or _estaCubriendose or _estaAgachado or _estaAtacando) return;
	_cambiarSprite(SPRITE_TOMA_1);
	spriteActual->freezeSprite();
	_estaAtacando = true;
}
//+++++++++++++++++++++++++++PODER1++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::poder1(){
	if (poderes[0]->getVida()) return;
	//if (_recibioGolpe or _estaCubriendose or _estaAtacando) return;
	/*Siempre relacionado a lanzar un objeto*/
	_cambiarSprite(SPRITE_PODER_1);
	/* Depende de la posicion del sprite se lanza el poder */
	spriteActual->freezeSprite();
	_estaAtacando = true;
}

//+++++++++++++++++++++++++PODER2 y FATALITY++++++++++++++++++++++++
/* Cada personaje tiene el suyo sumado babality y gancho arranca cabeza */
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Personaje::poder2(){}
void Personaje::fatality1(Personaje* otroPersonaje){}

void Personaje::_recibirFatality2(){
	_cambiarSprite(SPRITE_FATALITY_GANCHO);
	spriteActual->doLoop(true);
	mObjetos[CABEZA]->lanzar(m_xActual,m_yActual - getAlto(),m_fliped,true);
	mObjetos[SANGRE_MUCHA]->lanzar(m_xActual,m_yActual - getAlto(),!m_fliped,false);
}

void Personaje::_updateFatality2(){
	//Caminar hasta donde esta el otro Personaje
	//Reproducir Gancho hacer que el otro Personaje arranque la cabeza
	float xAllegar = personajeQueLaRecibe->getX() - 1.5*sprites[SPRITE_INICIAL]->getAncho();
	bool llego = getX() < xAllegar;
	float velocidad = 2*m_velocidad;
	if (m_fliped){
		 xAllegar = personajeQueLaRecibe->getX() + 1.5*sprites[SPRITE_INICIAL]->getAncho();
		 llego = getX() > xAllegar;
		 velocidad = -2*m_velocidad;
	}
	if (llego){
		_cambiarSprite(SPRITE_CAMINAR);
		m_xActual += velocidad;
		return;
	} else if (m_xActual != xAllegar and getAccionDeAtaque() != SPRITE_AGACHAR){
		m_xActual = xAllegar;
		_cambiarSprite(SPRITE_AGACHAR);
		spriteActual->doLoop(true);
	}
	//YA se agacho!
	if (spriteActual->inLoop() or getAccionDeAtaque() == SPRITE_GANCHO){
		_cambiarSprite(SPRITE_GANCHO);
		spriteActual->freezeSprite();
	}

	//Interaccion con el otro Personaje
	if (getAccionDeAtaque() == SPRITE_GANCHO and spriteActual->proxFrameUltimo()){
		personajeQueLaRecibe->_recibirFatality2();
	}

}

void Personaje::fatality2(Personaje* otroPersonaje){
	if (_estaHaciendoFatality2) return;
	if (_gano) return;
	_gano = true;
	personajeQueLaRecibe = otroPersonaje;
	_estaHaciendoFatality2 = true;

}

//es fatality3 (Combo3)
void Personaje::babality(Personaje* otroPersonaje){
	if (_gano) return;
	if (otroPersonaje != NULL)
		otroPersonaje->babality(NULL);
	_cambiarSprite(SPRITE_BEBE);
	spriteActual->freezeSprite();
	_gano = true;
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


//+++++++++++++++++++++DEAD o FINISH HIM+++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Personaje::finishHim(){
	if (_recibioGolpe or _estaSaltando > 0 or _estaAtacando) return;
	if (_estaMuerto) return;
	for (size_t i = 0;i < poderes.size();i++){
		poderes[i]->hardDestroy();
	}

	_cambiarSprite(SPRITE_FINISH);
	m_proximaVelocidad = 0;
	_estaMuerto = true;
	m_velocidadActual = 0;
}

void Personaje::morir(){
	if (_recibioGolpe or _estaSaltando > 0 or _estaAtacando) return;
	_cambiarSprite(SPRITE_MUERE);
	for (size_t i = 0;i < poderes.size();i++){
			poderes[i]->hardDestroy();
	}
	m_velocidadActual = 0;
	m_proximaVelocidad = 0;
	_estaMuerto = true;
	spriteActual->doLoop(true);
}


//+++++++++++++++++++++++++++++VICTORIA++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::victoria() {
	if (_recibioGolpe or _estaSaltando > 0 or _estaAtacando) return;
	_cambiarSprite(SPRITE_GANA);
	for (size_t i = 0;i < poderes.size();i++){
			poderes[i]->hardDestroy();
	}
	m_velocidadActual = 0;
	m_proximaVelocidad = 0;
	_gano = true;
	spriteActual->doLoop(true);
	spriteActual->freezeSprite();
}

//-------------------------------------------------------------------------------------------------------------------------
//FIN MANEJO DE SPRITES :)

//Genera copia del personaje para repetirlo
Personaje* Personaje::copy(){
	std::vector<ObjetoArrojable*> copiObjetos;
	for (size_t i = 0; i < poderes.size();i++){
		copiObjetos.push_back(poderes[i]->copy());
	}
	Personaje* copiaPersonaje = new Personaje(nombre,sprites,copiObjetos,m_velocidad,m_fliped);
	copiaPersonaje->setPathLogo(logo);
	return copiaPersonaje;
}

Personaje::~Personaje() {
	spriteActual = NULL;
	for (size_t i=0; i < sprites.size() ; i++){
		delete sprites[i];
	}
	for (size_t i=0; i < poderes.size(); i++){
		delete poderes[i];
	}
	for (size_t i=0; i < mCombos.size(); i++){
		delete mCombos[i];
	}
	for (size_t i=0; i < mObjetos.size(); i++){
			delete mObjetos[i];
	}
	delete m_rectanguloAtaque;
	delete m_rectanguloDefensa;
}


