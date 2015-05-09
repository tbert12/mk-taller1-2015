/*
 * Sprite.cpp
 *
 *  Created on: 31/3/2015
 *      Author: tomi
 */

#include "Sprite.h"

Sprite::Sprite(std::string ruta,std::vector<Frame*> frames,Ventana* ventana,float ratio_x, float ratio_y, bool cambiar_color, float h_inicial, float h_final, float desplazamiento){
	frameActual = 0;
	SpriteSheetTexture = ventana->crearTextura();

	//recorre los frame en sentido contrario
	reverse = false;
	//m_pong hace efecto espejo, llega al valor de m_pong vuelve hasta el inicial y comienza de nuevo;
	m_pong = 0;

	//Si el frameLoop es 3, y estas en frameActual 0, hace 0,1,2,3 y se queda (hasta que sea false)
	doloop = false;
	frameLoop = 0;

	//Dejar congelado un frame
	frezee = false; //Hay que Congelar el Sprite
	frezeeCount = 0;//Cronometro para controlarl el tiempo congelado
	frezeeTime = 0; //Congelarlo por frezeeTime whiles
	frezeeFrame = 0;//Congelarlo en el Frame frezeeFrame

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
	RectanguloTest1->setColor(100,0,255);

	RectanguloTest2 = ventana->crearTextura();
	if (!RectanguloTest2->loadFromFile("data/img/forColisionTest/cuadrado_rojo.png")){
		printf("No se creo Rectangulo\n");
	}
	RectanguloTest2->setAlpha(100);
	RectanguloTest2->setColor(100,255,0);
}

Sprite::~Sprite(){
	delete SpriteSheetTexture;
	delete []spriteFrames;
}


float Sprite::getAncho(){
	return spriteFrames[frameActual].w_log;
}

float Sprite::getAlto(){
	return spriteFrames[frameActual].h_log;
}

bool Sprite::Advance(){
	if (frezee and (frezeeFrame == frameActual) ){
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
	if (m_pong == frameActual){
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
	//printf("Frame: %i [%f,%f]\n",frameActual,x,y);
	Rect_Objeto* currentClip = &spriteFrames[frameActual];
	SpriteSheetTexture->renderObjeto(currentClip,x ,y - currentClip->h_log, fliped);
}

void Sprite::setLoop(int num_frame) {
	if (num_frame >= cantidadFrames ) return;
	frameLoop = num_frame;
}

void Sprite::doLoop(bool loop){
	doloop = loop;
}

void Sprite::doReverse(bool Reverse){
	reverse = Reverse;
}

bool Sprite::ultimoFrame(){
	if (doloop) return false;
	if (reverse){
		return (frameActual == 0);
	}
	return (frameActual + 1 == cantidadFrames);
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
	if (pong <= 0 or pong >= cantidadFrames) return;
	m_pong = pong;
}

void Sprite::setFrezeeFrame(int frame,int time){
	if (frame < 0 or frame >= cantidadFrames) return;
	frezeeTime = time;
	frezeeFrame = frame;
}

void Sprite::frezeeSprite(){
	frezee = true;
}

void Sprite::hardReset(){
	reverse = false;
	doloop = false;
	frezee = false;
	frezeeCount = 0;
	m_pong = 0;

	Reset();
}

// Para mostrar algo y testear Colisiones //
void Sprite::RENDERCOLISIONTEST(float x_ventana, float y, bool fliped,Rect_Logico* rectanguloAtaque,Rect_Logico* rectanguloDefensa){
	if (rectanguloAtaque != NULL){
		RectanguloTest1->renderRectangulo(rectanguloAtaque,rectanguloAtaque->x -  x_ventana, rectanguloAtaque->y - rectanguloAtaque->h, fliped);
	}
	RectanguloTest2->renderRectangulo(rectanguloDefensa,rectanguloDefensa->x - x_ventana, rectanguloDefensa->y - rectanguloDefensa->h, fliped);
}

