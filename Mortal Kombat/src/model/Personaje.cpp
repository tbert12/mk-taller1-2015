/*
 * Personaje.cpp
 *
 *  Created on: 26/3/2015
 *      Author: facu
 */

#include "Personaje.h"

Personaje::Personaje(std::string nombre_personaje,std::vector<Sprite*> Sprites,float velocidad, bool fliped) {
	nombre = nombre_personaje;
	vida = 100;
	sprites = Sprites;
	spriteActual = sprites[SPRITE_INICIAL];

	m_xActual = 0;
	m_yActual = 0;
	m_yPiso = 0;
	poder = NULL;

	m_velocidadActual = 0;

	m_AltoMundo = 0;
	m_AnchoMundo = 0;

	m_fliped = fliped;

	m_velocidad = velocidad;
	m_mover = true;

	//Es igual a SpriteActual->getAlto();
	maxAlturaDeSalto = 1.20 * getAlto();
	tiempoDeSalto = 0;
	_estaSaltando = -1;

	_estaCubriendose = false;
	_estaAgachado = false;
	_estaAtacando = false;
}

//-------------------------------------------------------------------------------------------------------------------------
//Manejo de attributos logicos

void Personaje::lanzarObjeto(){
	//ya hay poder lanzado
	if (poder != NULL){
		if(poder->getVida())
			return;
	}
	//Poner sprite del personaje para lanzar
	/*poder = new ObjetoArrojable("arma subzero",velocidad_poder,sprites poder);
	int x;
	if (m_fliped){
		x = m_xActual + spriteActual->getAncho();
	}
	else{
		x = m_xActual - spriteActual->getAncho();
	}
	poder->lanzar(x,m_yActual,m_fliped);
	*/
}

std::vector<Sprite*> Personaje::getSprites(){
	return sprites;
}

Sprite* Personaje::getSpriteActual(){;
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
	m_yActual = y;
	m_yPiso = m_yActual;
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
		_cambiarSprite(SPRITE_MUERE);
		_estaAgachado = false;
		spriteActual->doLoop(true);
		vida = 0;
	}
}

void Personaje::setScroll(bool scrollear){
	m_mover = scrollear;
}

void Personaje::setFlip(bool flip){
	if (_estaSaltando > 0 || (flip == m_fliped)) return;
		m_fliped= flip;
		if (flip){
			//Le sumamos el ancho para que la x siga quedando en la cabeza
			m_xActual += spriteActual->getAncho();
		}
		else{
			m_xActual -= spriteActual->getAncho();
		}
}

void Personaje::Update(int velocidadScroll){
	//velocidadScroll = 0;
	float renderX = m_xActual;
	if(m_mover)
		renderX += m_velocidadActual;

	float maximo,minimo;
	if(m_fliped){
		maximo = m_AnchoMundo;
		minimo = spriteActual->getAncho();
	}
	else{
		maximo = (m_AnchoMundo - spriteActual->getAncho());
		minimo = 0;
	}
	if (renderX <= maximo and renderX >= minimo){
		if ( !_estaAgachado and !_estaCubriendose){
			if (_estaAtacando){
				if (_estaSaltando > 0)
					if(m_mover) m_xActual += (m_velocidadActual);

			} else {
				if(m_mover) m_xActual += (m_velocidadActual);
			}
		}
	}

	if(m_xActual > maximo)
			m_xActual = maximo;

	else if(m_xActual < minimo)
			m_xActual = minimo;

	if(_estaSaltando > 0){
			_actualizarY();
	}

	else if (_estaSaltando == 0){
		m_yActual = m_yPiso;
		_estaSaltando = -1;
	}

	m_mover = true;

}

bool Personaje::enMovimiento(){
	return (m_velocidadActual != 0);
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

float Personaje::getVelocidadDerecha(){
	return m_velocidad;
}
float Personaje::getVelocidadIzquierda(){
	return -m_velocidad;
}

void Personaje::renderizar(float x_dist_ventana, float posOtherPlayer){
	//HORRIBLE ASQUEROSO DESASTROSO
	//m_fliped = posOtherPlayer - getAncho() < m_xActual;
	spriteActual->render(m_xActual - x_dist_ventana,m_yActual ,m_fliped);
	//printf("->Esta atacnado: %s\n", _estaAtacando ? "True" : "False");
	//printf("->Esta Cubriendose: %s\n", _estaCubriendose ? "True" : "False");
	//* Para test de colisiones *//
	spriteActual->RENDERCOLISIONTEST(x_dist_ventana, m_yActual ,m_fliped , rectanguloAtaque() , rectanguloDefensa());
	//* Fin de test para mostrar colisiones *//

	AvanzarSprite();
}

//-------------------------------------------------------------------------------------------------------------------------
//Rectangulo para Colisiones

Rect_Logico* Personaje::_devolverRectangulo(bool flip, Rect_Logico* rectSinFlip){
	if(!flip)
		return rectSinFlip;
	//rectSinFlip->x -= 2*rectSinFlip->w;
	return rectSinFlip;
}


Rect_Logico* Personaje::rectanguloAtaque(){
	if (!_estaAtacando) return NULL;
	Rect_Logico* rectangulo = new Rect_Logico;
	if(m_fliped)
		rectangulo->x = m_xActual - spriteActual->getAncho() + sprites[SPRITE_CUBRIRSE]->getAncho()*0.25;
	else rectangulo->x = m_xActual + sprites[SPRITE_CUBRIRSE]->getAncho()*0.25;
	rectangulo->x= m_xActual;
	rectangulo->y= m_yActual;
	rectangulo->w = spriteActual->getAncho();
	rectangulo->h = getAlto()/2;
	rectangulo->y -= rectangulo->h;
	return _devolverRectangulo(m_fliped,rectangulo);
}

Rect_Logico* Personaje::nextRectAtaque(){
	if(!_estaAtacando)
		return this->rectanguloAtaque();
	Rect_Logico* rectangulo = new Rect_Logico;
	return _devolverRectangulo(m_fliped,rectangulo);
}

Rect_Logico* Personaje::rectanguloDefensa(){
	Rect_Logico* rectangulo = new Rect_Logico;
	if(m_fliped)
		rectangulo->x = m_xActual - spriteActual->getAncho();
	else rectangulo->x = m_xActual + getAncho()*0.25;
	rectangulo->y=  m_yActual;
	rectangulo->w = sprites[SPRITE_CUBRIRSE]->getAncho() - getAncho()*0.25; //El mas Angosto
	rectangulo->h = spriteActual->getAlto();
	return _devolverRectangulo(m_fliped,rectangulo);
}

//-------------------------------------------------------------------------------------------------------------------------
//Manejo de Sprites

void Personaje::AvanzarSprite(){
	if (spriteActual->ultimoFrame() or !_estaSaltando ){
		if ((_estaAtacando and !_estaAgachado) or (_estaAgachado and !_estaCubriendose and !_estaAtacando) or !_estaSaltando ){
			if (m_velocidadActual == 0){
				_cambiarSprite(SPRITE_INICIAL);
			} else {
				_cambiarSprite(SPRITE_CAMINAR);
			}
			if (_estaAtacando) _estaAtacando = false;
			if (_estaAgachado and !_estaCubriendose) _estaAgachado = false;
		}
	}
	if ( (_estaCubriendose or _estaAtacando) and spriteActual->ultimoFrame() ) {
		if ( !_estaAgachado ) {
			_cambiarSprite(SPRITE_INICIAL);
		} else {
			_cambiarSprite(SPRITE_AGACHAR);
			spriteActual->doLoop(true);
			spriteActual->Advance();
		}
		if (_estaCubriendose) _estaCubriendose = false;
		if (_estaAtacando) _estaAtacando = false;
	}
	if ( _estaSaltando > 0){
		// Alguien vio alguna vez un if tan feo como este
		//Salteo en el Aire el impulso del salto diagonal
		if (m_velocidadActual > 0){
			if (!m_fliped){
				if ( spriteActual->ultimoFrame() )
					spriteActual->Advance();
			} else {
				if (spriteActual->proxFrameUltimo() )
					spriteActual->Advance();
			}
		} else if (m_velocidadActual < 0){
			if (!m_fliped){
				if (spriteActual->proxFrameUltimo() )
					spriteActual->Advance();
			} else {
				if ( spriteActual->ultimoFrame() )
					spriteActual->Advance();
			}
		}
	}

	spriteActual->Advance();
	return;
}

void Personaje::_cambiarSprite(int SpriteAccion){
	if(_estaSaltando > 0) {
		//Ataque en saltos
		if (SpriteAccion == SPRITE_PINA_SALTANDO or SpriteAccion == SPRITE_PATADA_SALTANDO){
			//SOY BURRO, NOSE COMO HACER ESTE IF MAS LINDO
		} else {
			return;
		}
	}
	//Esto es feo Tomi
	if (spriteActual == sprites[SPRITE_MUERE]) return;

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

	spriteActual->doLoop(false);
	spriteActual->doReverse(false);
	spriteActual->Reset();

}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++CAMINAR/SALTAR/AGACHAR++++++++++++++++++++++++++++++++++

void Personaje::Inicial(){
	//Solo se mueve al sprite Inicial (Parado)
	this->_cambiarSprite(SPRITE_INICIAL);
}

void Personaje::Frenar(){
	if (_estaSaltando > 0 or _estaAgachado) return;
	m_velocidadActual = 0;
	Inicial();
}

void Personaje::CaminarDerecha(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose) return;
	m_velocidadActual = m_velocidad;
	this->_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::CaminarIzquierda(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose) return;
	m_velocidadActual = - m_velocidad;
	this->_cambiarSprite(SPRITE_CAMINAR);
}

void Personaje::Saltar(){
	if (_estaSaltando > 0 or _estaAgachado or _estaCubriendose) return;
	if (m_velocidadActual){
		if (m_velocidadActual > 0){
			_SaltarDerecha();
		} else {
			_SaltarIzquierda();
		}
	}
	else{
		_SaltarHorizontal();
	}

}

void Personaje::_SaltarDerecha(){
	this->_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	m_velocidadActual = m_velocidad;
}

void Personaje::_SaltarIzquierda(){
	this->_cambiarSprite(SPRITE_SALTAR_DIAGONAL);
	_estaSaltando = 1;
	m_velocidadActual = - m_velocidad;
}

void Personaje::_SaltarHorizontal(){
	this->_cambiarSprite(SPRITE_SALTAR);
	spriteActual->doLoop(true);
	_estaSaltando = 1;
}

//Funciones Logicas de Salto
void Personaje::_actualizarY(){
	//Si esta Saltanto va actualizando
	if(_estaSaltando > 0){
		m_yActual = _yDeSalto(m_yActual,tiempoDeSalto);
		tiempoDeSalto++;
	}

	//Cuando esta llegando al piso, vuelvo a las condiciones iniciales
	if(tiempoDeSalto > TIEMPOTOTALDESALTO){
		tiempoDeSalto = 0;
		_estaSaltando = 0;
		if (m_velocidadActual) {
			spriteActual->doReverse(false);
			spriteActual->Reset();
		}
		spriteActual->doLoop(false);
		if (!m_velocidadActual) spriteActual->Advance();
		return;
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
	if (_estaSaltando > 0 or  _estaAgachado ) return;

	_cambiarSprite(SPRITE_AGACHAR);
	_estaAgachado = true;
	spriteActual->doLoop(true);

	//Quitar Vida Prueba Barra
	this->QuitarVida(13);

}

void Personaje::Levantarse(){
	if (_estaSaltando > 0 or !_estaAgachado) return;
	spriteActual->doLoop(false);
	spriteActual->doReverse(true);
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++CUBRIRSE++++++++++++++++++++++++++++++++++++++++++++++++

void Personaje::cubrirse() {
	if ( _estaCubriendose or _estaSaltando > 0 or _estaAtacando) return;

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
	//if (_estaAtacando) return;
	if ( _estaAgachado ) {
		_pinaAgachado();
	}else if ( _estaSaltando > 0 )  {
		_pinaSaltando();
	} else {
		_cambiarSprite(SPRITE_PINA_BAJA);
	}
	_estaAtacando = true;
}

void Personaje::_pinaAgachado() {
	_cambiarSprite(SPRITE_PINA_AGACHADO);
}

void Personaje::pinaAlta() {
	if ( _estaAgachado ) {
		_gancho();
	} else if ( _estaSaltando > 0 ) {
		_pinaSaltando();
	} else {
		_cambiarSprite(SPRITE_PINA_ALTA);
	}
	_estaAtacando = true;
}

void Personaje::_gancho() {
	//Destrabarlo
	_cambiarSprite(SPRITE_GANCHO);
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
	if ( _estaAgachado ) {
		_patadaBajaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_patadaSaltando();
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
	if ( _estaAgachado ) {
		_patadaAltaAgachado();
	} else if ( _estaSaltando > 0 ) {
		_patadaSaltando();
	} else if (m_velocidadActual < 0) {
		_patadaCircular();
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

void Personaje::recibirGolpe(int CodigoGolpe, int Danio){
	//El Codigo de golpe esta seteados en todos el mismo
	/*
		--->SPRITE_RECIBE_GANCHO<--- (-10 de Vida)
		GANCHO=         	   12;

		--->SPRITE_RECIBE_FUERTE<--- (-10 de Vida)

		--->SPRITE_RECIBE_ALTO<----- (-8 de Vida)
		PINA_ALTA=		 	   19;
		PATADA_ALTA=		   14;
		PATADA_SALTANDO=	   17;
		PINA_SALTANDO=  	   21;

		--->SPRITE_RECIBE_BAJO || SPRITE_RECIBE_AGACHADO<--- (-5 de Vida)
		PINA_AGACHADO=  	   18;
		PATADA_ALTA_AGACHADO=  5;
		PINA_BAJA=		 	   20;
		PATADA_BAJA_AGACHADO=  6;
		PATADA_BAJA=    	   15;

		--->SPRITE_RECIBE_PATADA_GIRA<-- (-8 de Vida)
		PATADA_CIRCULAR=       16;

	*/
	std::map<int, int> reaccionesAGolpes;
	reaccionesAGolpes[SPRITE_GANCHO] = SPRITE_RECIBE_GANCHO;
	reaccionesAGolpes[SPRITE_PINA_ALTA] = SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_ALTA] = SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_SALTANDO] = SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PINA_SALTANDO] = SPRITE_RECIBE_ALTO;
	reaccionesAGolpes[SPRITE_PATADA_ALTA_AGACHADO] = _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_BAJA_AGACHADO] = _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PINA_AGACHADO] = _estaAgachado ? SPRITE_RECIBE_AGACHADO : SPRITE_RECIBE_BAJO;;
	reaccionesAGolpes[SPRITE_PATADA_BAJA] = SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PINA_BAJA] = SPRITE_RECIBE_BAJO;
	reaccionesAGolpes[SPRITE_PATADA_CIRCULAR] = SPRITE_RECIBE_PATADA_GIRA;

	//_cambiarSprite(reaccionesAGolpes[CodigoGolpe]);
}

//-------------------------------------------------------------------------------------------------------------------------
//FIN MANEJO DE SPRITES :)

Personaje::~Personaje() {
	spriteActual = NULL;
	for (size_t i=0; i < sprites.size() ; i++){
		delete sprites[i];
	}
}


