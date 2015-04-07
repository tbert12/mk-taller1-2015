#include "Mundo.h"
#include "logging.h"
#include <algorithm>

#define TIEMPO_DEFAULT 3.00
#define VENTANA_ANCHO_PX_DEFAULT 640
#define VENTANA_ALTO_PX_DEFAULT 480
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
	std::vector<Frame*> framesAntesDeSaltar(1);
	std::vector<Frame*> framesDeSaltar(1);
	std::vector<Frame*> framesDespuesDeSaltar(1);
	int wInitial = 72,wCaminar = 68;
	for (int i=0;i<9;i++){
		framesInitial[i] = new Frame(wInitial*i,0,133,wInitial);
		framesCaminar[i] = new Frame(wCaminar*i,0,133,wCaminar);
	}
	std::vector<Frame*> framesCaminarAtras (framesCaminar);
	std::reverse(framesCaminarAtras.begin(),framesCaminarAtras.end());

	framesAntesDeSaltar[0] = new Frame(0,0,139,69);
	framesDeSaltar[0] = new Frame(71,0,96,70);
	framesDespuesDeSaltar[0] = new Frame(141,0,107,60);

	std::string rutaInitial = "data/players/subzero/sprites/initial.png";
	std::string rutaCaminar = "data/players/subzero/sprites/walk.png";
	std::string rutaCaminarAtras = "data/players/subzero/sprites/walk.png";
	std::string rutaSalto = "data/players/subzero/sprites/salto.png";
	Sprite* Initial = new Sprite(rutaInitial,framesInitial,renderer);
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar,renderer);
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras,renderer);
	Sprite* AntesDeSaltar = new Sprite(rutaSalto,framesAntesDeSaltar,renderer);
	Sprite* Salto = new Sprite(rutaSalto,framesDeSaltar,renderer);
	Sprite* DespuesDeSaltar = new Sprite(rutaSalto,framesDespuesDeSaltar,renderer);

	AntesDeSaltar->setSpriteSiguiente(Salto);
	DespuesDeSaltar->setSpriteSiguiente(Initial);
	std::vector<Sprite*> sprites(6);
	sprites[0] = Initial;
	sprites[1] = Caminar;
	sprites[2] = CaminarAtras;
	sprites[3] = AntesDeSaltar;
	sprites[4] = Salto;
	sprites[5] = DespuesDeSaltar;
	return sprites;
}

Mundo* CrearMundoDefault(){
	log("Se comienza a crear un Mundo con valores Default",LOG_DEBUG);

	//ESTO ES LO QUE HACIA EL BUBY, no se si está bien!
	float ratio_x = VENTANA_ANCHO_PX_DEFAULT / ESCENARIO_ANCHO_DEFAULT ;
	float ratio_y = VENTANA_ALTO_PX_DEFAULT / ESCENARIO_ALTO_DEFAULT ;

	Mundo* mundo = new Mundo(ratio_x,ratio_y);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT);

	if(!ventana->create_window()){
		log("No se puede inicializar la ventana",LOG_ERROR);
	}

	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, GenerarSpritesDefault(ventana->getRenderer()), PERSONAJE_FACTOR_VELOCIDAD);
	log("Creado Personaje Default (SubZero)",LOG_DEBUG);

	mundo->setVentana(ventana);
	//mundo->escenario = NULL;

	mundo->setTiempo(new Tiempo(TIEMPO_DEFAULT));

	log("Creado el tiempo, la ventana y el escenario. Seteados a Mundo",LOG_DEBUG);
	if (!mundo->addPersonaje(personaje_default)){
		log("Personaje Default NO agregado al Mundo",LOG_ERROR);
	}
	log("Personaje Default agregado al Mundo",LOG_DEBUG);

	Capa* capa =  new CapaPrincipal(VENTANA_ALTO_PX_DEFAULT, VENTANA_ANCHO_PX_DEFAULT, PERSONAJE_Z_INDEX_DEFAULT, ESCENARIO_ANCHO_DEFAULT, PERSONAJE_FACTOR_VELOCIDAD, personaje_default);
	mundo->addCapa(capa);
	log("Capa principal agregada al Mundo",LOG_DEBUG);

	return mundo;
}
