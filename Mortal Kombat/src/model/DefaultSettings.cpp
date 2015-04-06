#include "Tiempo.h"
#include "../view/LTexture.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"
#include "Mundo.h"
#include "../view/Sprite.h"
#include <vector>
#include <algorithm>
#include <string>

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
	Sprite* Initial = new Sprite(rutaInitial,framesInitial);
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar);
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras);
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
	mundo->tiempo = new Tiempo(TIEMPO_DEFAULT);
	mundo->personajes[0] = personaje_default;
	mundo->capas[0] = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT, VENTANA_ANCHO_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, PERSONAJE_FACTOR_VELOCIDAD, personaje_default);

	return mundo;
}
