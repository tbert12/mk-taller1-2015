#include "Pelea.h"
#include "Tiempo.h"
#include "../view/LTexture.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"

#define TIEMPO_DEFAULT 3.00
#define VENTANA_ANCHO_PX_DEFAULT 640
#define VENTANA_ALTO_PX_DEFAULT 480
#define VENTANA_ANCHO_DEFAULT 200
#define ESCENARIO_ANCHO_DEFAULT 1000
#define ESCENARIO_ALTO_DEFAULT 1000
#define Y_PISO_DEFAULT 20
#define BACKGROUND_DEFAULT "../../data/backgrounds/default.png"
#define CAPA_ANCHO_DEFAULT 1000
#define CAPA_Z_INDEX_DEFAULT 2
#define PERSONAJE_ANCHO_DEFAULT 20
#define PERSONAJE_ALTO_DEFAULT 35
#define PERSONAJE_Z_INDEX_DEFAULT 1
#define PERSONAJE_SPRITE_INICIAL_DEFAULT "../../data/players/subzero/sprites/initial.png"
#define PERSONAJE_SPRITE_CAMINATA_DEFAULT "../../data/players/subzero/sprites/walk.png"
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"
#define PERSONAJE_FACTOR_VELOCIDAD 10


Tiempo* tiempoPorDefault(){
	Tiempo* tiempo = new Tiempo( TIEMPO_DEFAULT );
	return tiempo;
}

Mundo* mundoPorDefault(float ratio_x = NULL,float ratio_y = NULL){

	if(ratio_x == NULL){
		int ventana_ancho = VENTANA_ANCHO_DEFAULT;
		int ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		float ratio_x = ventana_ancho_px / ventana_ancho;
	}
	if (ratio_y == NULL){
		int ventana_alto = ESCENARIO_ALTO_DEFAULT;
		int ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		float ratio_y = ventana_alto_px / ventana_alto;
	}
	Mundo* mundo = new Mundo(ratio_x,ratio_y);
	return mundo;
}
void capaPorDefault(Mundo* mundo,int cant_capas){
	for(int i =0;i<=cant_capas;i++){
		Capa* capa = new Capa( ESCENARIO_ALTO_DEFAULT, CAPA_ANCHO_DEFAULT, CAPA_Z_INDEX_DEFAULT + i, ESCENARIO_ANCHO_DEFAULT, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD );
		return capa;
		capa->cargarBackground(BACKGROUND_DEFAULT);
		mundo->agregarCapa(capa);
	}
}

Pelea* peleaPorDefault(){

	Pelea* pelea = new Pelea();

	Tiempo* tiempo_pelea = tiempoPorDefault();
	pelea->Tiempo(tiempo_pelea);
	Mundo* mundo = mundoPorDefault();
	int Cantidad_de_capas = 2;
	capaPorDefault(mundo,Cantidad_de_capas);

	//Crear sprites
	Personaje::Personaje* personaje = new Personaje(PERSONAJE_NOMBRE_DEFAULT, sprites, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD);

	// Crear ventana (capa-camara).
	Capa::Capa* camara = new Capa( ESCENARIO_ALTO_DEFAULT, VENTANA_ANCHO_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD );

	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal::CapaPrincipal* capa_principal = new CapaPrincipal( ESCENARIO_ALTO_DEFAULT, ESCENARIO_ANCHO_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD, personaje );
	capa_principal->camara( camara );

	// Agrego capa principal al mundo.
	nuevo_mundo->capaPrincipal( capa_principal );

	pelea->mundo(mundo);

	return pelea;
}
;
