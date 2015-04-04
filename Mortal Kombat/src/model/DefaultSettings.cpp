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


Tiempo* tiempoPorDefecto(){
	Tiempo* tiempo = new Tiempo( TIEMPO_DEFAULT );
	return tiempo;
}

Pelea* peleaPorDefault(){

	Pelea* pelea = new Pelea();

	Tiempo* tiempo_pelea = tiempoPorDefecto();
	pelea->Tiempo(tiempo_pelea);




	return pelea;
}

;
