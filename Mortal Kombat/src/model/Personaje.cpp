/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites, std::vector<ObjetoArrojable*> arrojables ,float velocidad, bool fliped) {
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];
	poderes = arrojables;


	m_xActual = 0;
	m_yActual = 0;
	m_yPiso = 0;

	m_velocidadActual = 0;

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

	m_rectanguloAtaque = new Rect_Logico;
	m_rectanguloDefensa = new Rect_Logico;
}

void Personaje::reset(){
	vida = 100;
	spriteActual = sprites[SPRITE_INICIAL];
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
}

//-------------------------------------------------------------------------------------------------------------------------
//Manejo de attributos logicos

ObjetoArrojable* Personaje::getPoderActivo(){
	if (poderes[0] != NULL){
		if(poderes[0]->getVida())
			return poderes[0];
	}
	return NULL;
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

std::vector<Sprite*> Personaje::getSprites(){
	printf("Si alguna vez ven esto diganle a Tomi\n");
	return sprites;
}

Sprite* Personaje::getSpriteActual(){
	printf("Si alguna vez ven esto diganle a Tomi\n");
	return spriteActual;
}

void Personaje::setDimensionesMundo(float h,float w){
	m_AltoMundo = h;
	m_AnchoMundo = w;
}

int Personaje::getVida(){
	return vida;
}

void Personaje::setPosition(float x, float y){
	m_xActual = x;
	if(y < 0)
		m_yActual = m_yPiso;
	else
		m_yActual = m_yPiso = y;
}

void Personaje::setPositionX(float x){
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
	if (_estaSaltando > 0 or flip == m_fliped) {
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

void Personaje::Update(float posDeOtroJugador,bool forzado){
	//Actualizo La X para cada caso y verificando limites
	if (_estaMuerto){
		if (!spriteActual->inLoop()){
			if (m_fliped){
				m_xActual += m_velocidad;
			}
			else {
				m_xActual -=m_velocidad;
			}
		}
		return;
	}
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
					if(m_mover) m_xActual = renderX;
				}
			} else {
				if(m_mover /*and !estaElotroJugador*/) m_xActual = renderX;
			}
		}
	}

	if(m_xActual > maximo){
		m_xActual = maximo;
	} else if(m_xActual < minimo){
		m_xActual = minimo;
	}

	//Actualizo la Y
	if(_estaSaltando > 0 and !forzado){
		_actualizarY();
	} else if (_estaSaltando == 0){
		m_yActual = m_yPiso;
	}

	m_mover = true;
	_UpdatePoder();

}

void Personaje::_UpdatePoder(){
	if(poderes.size() <= 0) return;
	else{
		for(int j= 0;j< (int)poderes.size();j++){
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
	return _estaSaltando <= 0;
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

int Personaje::getAccionDeAtaque(){
	//Devuelve -1 si no encuentra la Accion del Sprite
	//Nunca va a pasar, pero por el compilador
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
	spriteActual->render(m_xActual - x_dist_ventana,m_yActual ,m_fliped);

	//render poderes
	if(poderes.size() > 0){
		for(int j= 0;j< (int)poderes.size();j++){
			poderes[j]->renderizar(x_dist_ventana);
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

	Rect_Logico* rectangulo = m_rectanguloAtaque;
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
	} else if (Accion == SPRITE_PATADA_CIRCULAR or Accion == SPRITE_PATADA_SALTANDO or Accion == SPRITE_PATADA_BAJA_AGACHADO){
		propH = 2;
		propY = propH;
	} else if (Accion == SPRITE_PINA_SALTANDO){
		propH = 3;
		propY = 2;
	} else if (Accion == SPRITE_GANCHO){
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

	return rectangulo;
}

Rect_Logico* Personaje::rectanguloDefensa(){
	Rect_Logico* rectangulo = m_rectanguloDefensa;
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
	return rectangulo;
}

//-------------------------------------------------------------------------------------------------------------------------
//Manejo de Sprites

void Personaje::AvanzarSprite(){
	//Los If son muy parecidos, pero hay que tenerlos separados para entender el codigo
	if (spriteActual->ultimoFrame() or (!_estaSaltando and !_recibioGolpe) ){
		//Termina de atacar o agacharse o saltando = 0 (justo en el momento que cae)
		if ( (_estaAtacando and !_estaAgachado) or (_estaAgachado and !_estaCubriendose and !_estaAtacando and !_recibioGolpe) or !_estaSaltando ){
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
			_cambiarSprite(SPRITE_INICIAL);
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
			_cambiarSprite(SPRITE_INICIAL);
		} else {
			_cambiarSprite(SPRITE_AGACHAR);
			spriteActual->doLoop(true);
			spriteActual->Advance();
		}
		_estaAtacando = false;
	}

	if (_recibioGolpe and spriteActual->ultimoFrame()){
		//Termina de recibir Golpe (Ya sea agachado o parado)
		m_velocidadActual = 0;
		if ( _estaAgachado ){
			_cambiarSprite(SPRITE_AGACHAR);
			spriteActual->doLoop(true);
			spriteActual->Advance();
		} else {
			_cambiarSprite(SPRITE_INICIAL);
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
	if (_estaMuerto) return;

	if(_estaSaltando > 0) {
		//Ataque en saltos
		bool SpriteAtaqueEnSalto = (SpriteAccion == SPRITE_PINA_SALTANDO or SpriteAccion == SPRITE_PATADA_SALTANDO);
		if (!SpriteAtaqueEnSalto) return;
	}
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
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _estaAtacando or _recibioGolpe) return;
	m_velocidadActual = 0;
	Inicial();
}

void Personaje::CaminarDerecha(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _estaAtacando or _recibioGolpe) return;
	_Caminar(true);
}

void Personaje::CaminarIzquierda(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _estaAtacando or _recibioGolpe) return;
	_Caminar(false);
}

void Personaje::_Caminar(bool derecha){
	float factor = 1;
	if (derecha){
		if (m_fliped)
			factor = 0.8;

	} else {
		factor = -0.8;
		if (m_fliped)
			factor = -1;
	}
	m_velocidadActual = m_velocidad*factor;
	_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::Saltar(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose or _recibioGolpe) return;

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
	m_velocidadActual = m_velocidad*1.8;
}

void Personaje::_SaltarIzquierda(){
	_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	m_velocidadActual = - m_velocidad*1.8;
}

void Personaje::_SaltarHorizontal(){
	_cambiarSprite(SPRITE_SALTAR);
	_estaSaltando = 1;
	spriteActual->doLoop(true);
}

//Funciones Logicas de Salto
void Personaje::_actualizarY(){
	//Actualiza la Y
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
	if (_estaSaltando > 0 or  _estaAgachado or _recibioGolpe ) return;

	_cambiarSprite(SPRITE_AGACHAR);
	_estaAgachado = true;
	spriteActual->doLoop(true);

}

void Personaje::Levantarse(){
	if (_estaSaltando > 0 or !_estaAgachado or _recibioGolpe) return;
	if (_estaCubriendose){
		dejarDeCubrirse();
	}
	spriteActual->doLoop(false);
	spriteActual->doReverse(true);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++CUBRIRSE++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::cubrirse() {
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
	if ( !_estaCubriendose ) return;
	spriteActual->doLoop(false);
	spriteActual->doReverse(true);

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++ATAQUE - PINA+++++++++++++++++++++++++++++++++++++++++++

void Personaje::pinaBaja() {
	_pina(false);
}

void Personaje::pinaAlta() {
	_pina(true);
}

void Personaje::_pina(bool alta){
	if (_estaCubriendose or _recibioGolpe) return;
	int sprite = SPRITE_PINA_BAJA;
	int spritecombo = SPRITE_COMBO_PINA_BAJA;
	if (alta){
		sprite = SPRITE_PINA_ALTA;
		spritecombo = SPRITE_COMBO_PINA_ALTA;
	}
	int accionActual = getAccionDeAtaque();
	if (_estaAtacando and (accionActual != sprite)) return;
	if ( _estaAgachado ) {
		if (alta) _gancho();
		else _pinaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_pinaSaltando();
	} else {
		if (accionActual == sprite or accionActual == spritecombo){
			_cambiarSprite(spritecombo);
		} else {
			_cambiarSprite(sprite);
		}
	}
	_estaAtacando = true;

}

void Personaje::_pinaAgachado() {
	_cambiarSprite(SPRITE_PINA_AGACHADO);
}

void Personaje::_gancho() {
	//Destrabarlo
	_cambiarSprite(SPRITE_GANCHO);
	spriteActual->freezeSprite();
}

void Personaje::_pinaSaltando() {
	if ( tiempoDeSalto >= TIEMPOTOTALDESALTO/3 ){
		_cambiarSprite(SPRITE_PINA_SALTANDO);
		spriteActual->doLoop(true);
	}
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++ATAQUE - PATADA+++++++++++++++++++++++++++++++++++++++++

void Personaje::patadaBaja() {
	if (_estaCubriendose or _recibioGolpe) return;
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
	if (_estaCubriendose or _recibioGolpe) return;
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
	if (_recibioGolpe) return false;
	if (_estaCubriendose){
		QuitarVida(1);
		spriteActual->vibrar();
		return false;
	}
	bool golpeFuerte = false;

	std::map<int, int> reaccionesAGolpes;
	reaccionesAGolpes[SPRITE_GANCHO] = 				SPRITE_RECIBE_GANCHO;
	reaccionesAGolpes[SPRITE_PINA_ALTA] = 			SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_ALTA] = 		SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_SALTANDO] = 	SPRITE_RECIBE_FUERTE;
	reaccionesAGolpes[SPRITE_PINA_SALTANDO] = 		SPRITE_RECIBE_FUERTE;
	reaccionesAGolpes[GOLPE_DE_PODER] = 			SPRITE_RECIBE_FUERTE; //PODER
	reaccionesAGolpes[SPRITE_PATADA_ALTA_AGACHADO]= _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_BAJA_AGACHADO]= _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PINA_AGACHADO]= 		_estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_BAJA]=  		_estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PINA_BAJA]= 			_estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_CIRCULAR] = 	SPRITE_RECIBE_PATADA_GIRA;

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

	_cambiarSprite(reaccionesAGolpes[CodigoGolpe]);
	QuitarVida(DanioPorGolpe[CodigoGolpe]);
	spriteActual->freezeSprite();

	if (CodigoGolpe == SPRITE_GANCHO){
		maxAlturaDeSalto = ALTURA_SALTO_GANCHO * getAlto();
		tiempoDeSalto = 1;
		_estaSaltando = 1;
		spriteActual->doLoop(true);
	}

	if (DanioPorGolpe[CodigoGolpe] >= MIN_GOLPE_FUERTE and CodigoGolpe != SPRITE_PATADA_CIRCULAR){
		golpeFuerte = true;
		if (m_fliped){
			m_velocidadActual = m_velocidad;
		} else {
			m_velocidadActual = -m_velocidad;
		}
	}

	_recibioGolpe = true;
	return golpeFuerte;
}
//+++++++++++++++++++++++++++++TOMA++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Personaje::toma1(){
	_cambiarSprite(SPRITE_TOMA_1);
	spriteActual->freezeSprite();
	_estaAtacando = true;
}
//+++++++++++++++++++++PODER Y FATALITY++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::poder1(){
	/*Siempre relacionado a lanzar un objeto*/
	_cambiarSprite(SPRITE_PODER_1);
	spriteActual->freezeSprite();
	_estaAtacando = true;
}

void Personaje::poder2(){
	/* Hay que pensar algo de las fatalityes
	 * Porque son todas distintas, puede haber una clase global que sea Fatality
	 * en donde Fatality1-Liukang / Fatality2-SubZero Hereda de Fatality y minupulan
	 * cosas del personaje.
	 *
	 * */
}


//+++++++++++++++++++++DEAD o FINISH HIM+++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Personaje::finishHim(){
	_cambiarSprite(SPRITE_FINISH);
}

void Personaje::morir(){
	_cambiarSprite(SPRITE_MUERE);
	_estaMuerto = true;
	spriteActual->doLoop(true);
}


//+++++++++++++++++++++++++++++VICTORIA++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::victoria() {
	_cambiarSprite(SPRITE_GANA);
	spriteActual->doLoop(true);
	spriteActual->freezeSprite();
}

//-------------------------------------------------------------------------------------------------------------------------
//FIN MANEJO DE SPRITES :)

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
	delete m_rectanguloAtaque;
	delete m_rectanguloDefensa;
}


