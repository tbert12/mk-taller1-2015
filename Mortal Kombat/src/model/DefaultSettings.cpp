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

std::vector<Sprite*> GenerarSpritesDefault(SDL_Renderer* renderer){
	std::vector<Frame*> framesInitial(9);
	std::vector<Frame*> framesCaminar(9);
	int wInitial = 72,wCaminar = 68;
	for (int i=0;i<9;i++){
		framesInitial[i] = new Frame(wInitial*i,0,133,wInitial);
		framesCaminar[i] = new Frame(wCaminar*i,0,133,wCaminar);
	}
	std::vector<Frame*> framesCaminarAtras (framesCaminar);
	std::reverse(framesCaminarAtras.begin(),framesCaminarAtras.end());


	std::string rutaInitial = "data/players/subzero/sprites/initial.png";
	std::string rutaCaminar = "data/players/subzero/sprites/walk.png";
	std::string rutaCaminarAtras = "data/players/subzero/sprites/walk.png";
	Sprite* Initial = new Sprite(rutaInitial,framesInitial,renderer);
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar,renderer);
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras,renderer);
	std::vector<Sprite*> sprites(3);
	sprites[0] = Initial;
	sprites[1] = Caminar;
	sprites[2] = CaminarAtras;
	return sprites;
}

Mundo* CrearMundoDefault(){
	Mundo* mundo = new Mundo();
	Ventana* ventana = new Ventana(VENTANA_ANCHO_DEFAULT,ESCENARIO_ALTO_DEFAULT);
	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, GenerarSpritesDefault(ventana->getRenderer()), PERSONAJE_FACTOR_VELOCIDAD);
	mundo->ventana = ventana;
	mundo->escenario = NULL;
	mundo->tiempo = NULL;
	mundo->personajes[0] = personaje_default;
	mundo->capas[0] = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT, VENTANA_ANCHO_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, PERSONAJE_FACTOR_VELOCIDAD, personaje_default);

	return mundo;
}

<<<<<<< HEAD
	Tiempo* tiempo_pelea = tiempoPorDefecto();
	pelea->Tiempo(tiempo_pelea);
	Mundo* mundo = MundoPorDefault();
	int Cantidad_de_capas = 2;
	CapaPorDefault(mundo,Cantidad_de_capas);

	//Crear sprites
	Personaje* personaje = new Personaje(PERSONAJE_NOMBRE_DEFAULT, sprites, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD);

	// Crear ventana (capa-camara).
	Capa* camara = new Capa( ESCENARIO_ALTO_DEFAULT, VENTANA_ANCHO_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD );

	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal* capa_principal = new CapaPrincipal( ESCENARIO_ALTO_DEFAULT, ESCENARIO_ANCHO_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, ESCENARIO_ANCHO_DEFAULT/PERSONAJE_FACTOR_VELOCIDAD, personaje );
	capa_principal->camara( camara );

	// Agrego capa principal al mundo.
	nuevo_mundo->capaPrincipal( capa_principal );

	//pelea->mundo(mundo);

	return pelea;
}
=======
>>>>>>> 94cbece54992112c505150734949c81e65243481
;
