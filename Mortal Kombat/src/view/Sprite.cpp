/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana,float ratio_x, float ratio_y, bool cambiar_color, float h_inicial, float h_final, float desplazamiento, LSound* sonido_accion){
	frameActual = 0;
	SpriteSheetTexture = ventana->crearTextura();

	//recorre los frame en sentido contrario
	reverse = false;
	//m_pong hace efecto espejo, llega al valor de m_pong vuelve hasta el inicial y comienza de nuevo;
	m_pong = 0;

	//Guarda el pong comun y hace m_pong hasta el ultimo frame
	m_fullpong = 0;

	//Si el frameLoop es 3, y estas en frameActual 0, hace 0,1,2,3 y se queda (hasta que sea false)
	doloop = false;
	frameLoop = 0;

	//Dejar congelado un frame
	frezee = false; //Hay que Congelar el Sprite
	frezeeCount = 0;//Cronometro para controlarl el tiempo congelado
	frezeeTime = 0; //Congelarlo por frezeeTime whiles
	frezeeFrame = 0;//Congelarlo en el Frame frezeeFrame

	sonido = sonido_accion;
	frameSound = 0;

	if( !SpriteSheetTexture->loadFromFile( ruta, cambiar_color, h_inicial, h_final, desplazamiento ) ){
		log( "Error al intentar abrir la imagen del sprite.", LOG_ERROR );
		throw CargarImagenException( "No se pudo cargar la imagen del sprite como textura SDL" );
	}

	cantidadFrames = frames.size();
	
	spriteFrames = new Rect_Objeto[cantidadFrames];
	for (int i=0;i < cantidadFrames;i++){
		spriteFrames[i].x = frames[i]->X;
		spriteFrames[i].y = frames[i]->Y;
		spriteFrames[i].h = frames[i]->Alto;
		spriteFrames[i].w = frames[i]->Ancho;
		spriteFrames[i].w_log = frames[i]->Ancho/ratio_x;
		spriteFrames[i].h_log = frames[i]->Alto/ratio_y;

		delete frames[i];
	}

	//PARA TESTEAR EL PERSONAJE EN LAS COLISIONES
	RectanguloTest1 = ventana->crearTextura();
	if (!RectanguloTest1->loadFromFile("data/img/forColisionTest/cuadrado_rojo.png")){
		printf("No se creo Rectangulo\n");
	}
	RectanguloTest1->setAlpha(100);
	RectanguloTest1->setColor(100,255,255);

	RectanguloTest2 = ventana->crearTextura();
	if (!RectanguloTest2->loadFromFile("data/img/forColisionTest/cuadrado_rojo.png")){
		printf("No se creo Rectangulo\n");
	}
	RectanguloTest2->setAlpha(100);
	RectanguloTest2->setColor(100,255,0);
}

bool Sprite::loop(){
	return doloop;
}

Sprite::~Sprite(){
	delete SpriteSheetTexture;
	delete []spriteFrames;
	delete RectanguloTest1;
	delete RectanguloTest2;
	delete sonido;
}


float Sprite::getAncho(){
	return spriteFrames[frameActual].w_log;
}

float Sprite::getAlto(){
	return spriteFrames[frameActual].h_log;
}

bool Sprite::Advance(){
	if (frezee and (frezeeFrame == frameActual) and frezeeTime ){
		frezeeCount++;
		if (frezeeCount >= frezeeTime){
			frezeeCount = 0;
			frezee = false;
		}
		return true;
	}
	if (m_pong and (m_pong != frameActual) ){
		if ( ultimoFrame() ){
			reverse = !reverse;
			Reset();

		}
	}
	if (!doloop){
		if (reverse)
			frameActual--;
		else
			frameActual++;
	} else {
		if (frameActual != frameLoop){
			if (reverse)
				frameActual--;
			else
				frameActual++;
		}
	}
	if (m_pong and (m_pong == frameActual) ){
		reverse = !reverse;
	}

	if (frameActual >= cantidadFrames or frameActual < 0){
		Reset();
	}
	return true;
}

void Sprite::Reset(){
	if (reverse) {
		frameActual = cantidadFrames - 1;
	}
	else frameActual = 0;
}

void Sprite::render(float x, float y, bool fliped){
	Rect_Objeto* currentClip = &spriteFrames[frameActual];
	//printf("Frame: %i | Total: %i\n",frameActual,cantidadFrames);
	SpriteSheetTexture->renderObjeto(currentClip,x ,y - currentClip->h_log, fliped);
	playSound();
}

void Sprite::setLoop(int num_frame) {
	if (num_frame >= cantidadFrames ) return;
	frameLoop = num_frame;
}

void Sprite::doLoop(bool loop){
	if (doloop == loop) return;
	doloop = loop;
}

bool Sprite::inLoop(){
	return (doloop and frameActual==frameLoop) ;
}

void Sprite::doReverse(bool Reverse){
	reverse = Reverse;
}

void Sprite::setSoundIn(int index_frame) {
	frameSound = index_frame;
}

void Sprite::playSound() {
	/* El sonido se reproduce solo cuando se esta reproduciendo el sprite sin reverse
	 * Esto evita que se reproduzca dos veces cuando hace pong
	 */
	if ( sonido and frameActual == frameSound and !reverse) {
			sonido->play();
		}
}

bool Sprite::ultimoFrame(){
	if (doloop or frezeeCount) return false;
	if (reverse){
		return (frameActual == 0);
	}
	return (frameActual + 1 == cantidadFrames);
}

bool Sprite::inFrezee(){
	return (frezee and (frezeeFrame == frameActual) and frezeeTime and frezeeCount);
}

bool Sprite::proxFrameUltimo(){
	if (doloop) return false;
	if (reverse){
		return (frameActual == 1);
	}
	return (frameActual + 1 == cantidadFrames - 1);
}

bool Sprite::primerFrame(){
	if (doloop) return false;
	if (reverse){
		return (frameActual + 1 == cantidadFrames);
	}
	return (frameActual == 0);
}

void Sprite::doPongIn(int pong){
	if (pong <= 0 or pong >= cantidadFrames) {
		m_pong = 0;
		return;
	}
	m_pong = pong;
}

void Sprite::doFullPong(){
	m_fullpong = m_pong;
	m_pong = cantidadFrames - 1;
}

void Sprite::setFrezeeFrame(int frame,int time){
	if (frame < 0 or frame >= cantidadFrames) return;
	frezeeTime = time;
	frezeeFrame = frame;
}

bool Sprite::inReverse(){
	return reverse;
}

void Sprite::freezeSprite(){
	frezee = true;
}

void Sprite::vibrar(){
	SpriteSheetTexture->setVibrar();
}

void Sprite::hardReset(){
	reverse = false;
	doloop = false;
	frezeeCount = 0;
	frezee = false;
	if (m_fullpong) m_pong = m_fullpong;

	Reset();
}

// Para mostrar algo y testear Colisiones //
void Sprite::RENDERCOLISIONTEST(float x_ventana, float y, bool fliped,Rect_Logico* rectanguloAtaque,Rect_Logico* rectanguloDefensa){
	if (rectanguloAtaque != NULL){
		RectanguloTest1->renderRectangulo(rectanguloAtaque,rectanguloAtaque->x -  x_ventana, rectanguloAtaque->y - rectanguloAtaque->h);
	}
	if (rectanguloDefensa != NULL){
		RectanguloTest2->renderRectangulo(rectanguloDefensa,rectanguloDefensa->x - x_ventana, rectanguloDefensa->y - rectanguloDefensa->h);
	}
}

