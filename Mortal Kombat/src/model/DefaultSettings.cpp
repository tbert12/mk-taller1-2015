#include "Mundo.h"
#include "logging.h"
#include <algorithm>

#define TIEMPO_DEFAULT 3.00
#define VENTANA_ANCHO_PX_DEFAULT 640
#define VENTANA_ALTO_PX_DEFAULT 480
#define ESCENARIO_ANCHO_DEFAULT 1000
#define ESCENARIO_ALTO_DEFAULT 250
#define Y_PISO_DEFAULT 200
#define BACKGROUND_0_DEFAULT "data/img/background/background_0.png"
#define BACKGROUND_0__ANCHOPX_DEFAULT 512
#define BACKGROUND_0__ALTOPX_DEFAULT 384
#define BACKGROUND_0_Z_INDEX 0
#define BACKGROUND_1_DEFAULT "data/img/background/background_1.png"
#define BACKGROUND_1__ANCHOPX_DEFAULT 1024
#define BACKGROUND_1__ALTOPX_DEFAULT 384
#define BACKGROUND_1_Z_INDEX 1
#define BACKGROUND_2_DEFAULT "data/img/background/background_2.png"
#define BACKGROUND_2__ANCHOPX_DEFAULT 1536
#define BACKGROUND_2__ALTOPX_DEFAULT 384
#define BACKGROUND_2_Z_INDEX 2
#define PERSONAJE_ANCHO_DEFAULT 20
#define PERSONAJE_ALTO_DEFAULT 35
#define PERSONAJE_Z_INDEX_DEFAULT 3
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"
#define PERSONAJE_FACTOR_VELOCIDAD 10
#define PIXEL_A_LOGICO 0.6510

std::vector<Sprite*> GenerarSpritesDefault(SDL_Renderer* renderer){

	std::vector<Frame*> framesInitial(9);

	std::vector<Frame*> framesCaminar(9);

	std::vector<Frame*> framesAntesDeSaltar(1);
	std::vector<Frame*> framesDeSaltar(1);
	std::vector<Frame*> framesDespuesDeSaltar(1);

	std::vector<Frame*> framesAntesDeSaltarDiagonal(1);
	std::vector<Frame*> framesSaltoDiagonal(7);
	std::vector<Frame*> framesSaltoDiagonalAtras(7);
	std::vector<int> xSaltoDiagonal = {0,72,127,208,283,335,392,472};
	std::vector<int> hSaltoDiagonal = {136,82,59,55,81,81,59,62};
	std::vector<int> wSaltoDiagonal = {72,55,74,74,53,55,75,74};

	std::vector<Frame*> framesAgacharse(2);
	framesAgacharse[0] = new Frame(0,0,107,60);
	framesAgacharse[1] = new Frame(60,0,89,62);
	std::vector<Frame*> framesLevantarse(framesAgacharse);
	std::reverse(framesLevantarse.begin(),framesLevantarse.end());

	std::vector<Frame*> framesAgachado(1);
	framesAgachado[0] = new Frame(122,0,71,64);

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

	framesAntesDeSaltarDiagonal[0] = new Frame(xSaltoDiagonal[0],0,hSaltoDiagonal[0],wSaltoDiagonal[0]);

	for (size_t i = 0; i < framesSaltoDiagonal.size(); i++){
		framesSaltoDiagonal[i] = new Frame(xSaltoDiagonal[i+1],0,hSaltoDiagonal[i+1],wSaltoDiagonal[i+1]);
		framesSaltoDiagonalAtras[framesSaltoDiagonal.size()-i-1] = new Frame(xSaltoDiagonal[i+1],0,hSaltoDiagonal[i+1],wSaltoDiagonal[i+1]);
	}
	std::string rutaInitial = "data/players/subzero/sprites/initial.png";
	std::string rutaCaminar = "data/players/subzero/sprites/walk.png";
	std::string rutaCaminarAtras = "data/players/subzero/sprites/walk.png";
	std::string rutaSalto = "data/players/subzero/sprites/salto.png";
	std::string rutaSaltoDiagonal = "data/players/subzero/sprites/diag.png";
	std::string rutaAgacharse = "data/players/subzero/sprites/agachar.png";

	Sprite* Initial = new Sprite(rutaInitial,framesInitial,renderer);
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar,renderer);
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras,renderer);
	Sprite* AntesDeSaltar = new Sprite(rutaSalto,framesAntesDeSaltar,renderer);
	Sprite* Salto = new Sprite(rutaSalto,framesDeSaltar,renderer);
	Sprite* DespuesDeSaltar = new Sprite(rutaSalto,framesDespuesDeSaltar,renderer);
	AntesDeSaltar->setSpriteSiguiente(Salto);
	DespuesDeSaltar->setSpriteSiguiente(Initial);

	Sprite* AntesSaltoDiagonal = new Sprite(rutaSaltoDiagonal,framesAntesDeSaltarDiagonal,renderer);
	Sprite* SaltoDiagonal = new Sprite(rutaSaltoDiagonal,framesSaltoDiagonal,renderer);
	AntesSaltoDiagonal->setSpriteSiguiente(SaltoDiagonal);

	Sprite* AntesSaltoDiagonalAtras = new Sprite(rutaSaltoDiagonal,framesAntesDeSaltarDiagonal,renderer);
	Sprite* SaltoDiagonalAtras = new Sprite(rutaSaltoDiagonal,framesSaltoDiagonalAtras,renderer);
	AntesSaltoDiagonalAtras->setSpriteSiguiente(SaltoDiagonalAtras);

	Sprite* Agacharse = new Sprite(rutaAgacharse,framesAgacharse,renderer);
	Sprite* Agachado = new Sprite(rutaAgacharse,framesAgachado,renderer);
	Sprite* Levantarse = new Sprite(rutaAgacharse,framesLevantarse,renderer);
	Agacharse->setSpriteSiguiente(Agachado);
	Levantarse->setSpriteSiguiente(Initial);

	//{Initial,Caminar,CaminarAtras,AntesDeSaltar,Salto,DespuesDeSaltar,SaltoDiagonal}
	std::vector<Sprite*> sprites = {Initial,Caminar,CaminarAtras,Salto,AntesDeSaltar,DespuesDeSaltar,AntesSaltoDiagonal,SaltoDiagonal,AntesSaltoDiagonalAtras,SaltoDiagonalAtras,Agacharse,Agachado,Levantarse};
	printf("Termine carga sprite\n");
	return sprites;
}

Mundo* CrearMundoDefault(){
	log("Se comienza a crear un Mundo con valores Default",LOG_DEBUG);

	//ESTO ES LO QUE HACIA EL BUBY, no se si está bien!
	float ratio_x = ESCENARIO_ANCHO_DEFAULT;
	float ratio_y = ESCENARIO_ALTO_DEFAULT;
	Mundo* mundo = new Mundo(ratio_x,ratio_y);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT);
	ventana->setPixelaLogico(PIXEL_A_LOGICO);

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

	// CREO LAS CAPAS, SON 3 NIVELES
	// La relacion entre el las medidas logicas y los pixeles es la divicion

	//capa 0, es la ultima. de la misma medida que la ventana
	CapaFondo* capa_0 =new CapaFondo(BACKGROUND_0__ALTOPX_DEFAULT*PIXEL_A_LOGICO,BACKGROUND_0__ANCHOPX_DEFAULT*PIXEL_A_LOGICO,BACKGROUND_0_Z_INDEX,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,BACKGROUND_0_DEFAULT,ventana);
	mundo->addCapa(capa_0);
	//capa 1 ,es la del medio. del doble que la ventana
	CapaFondo* capa_1 =new CapaFondo(BACKGROUND_1__ALTOPX_DEFAULT*PIXEL_A_LOGICO,BACKGROUND_1__ANCHOPX_DEFAULT*PIXEL_A_LOGICO,BACKGROUND_1_Z_INDEX,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,BACKGROUND_1_DEFAULT,ventana);
	mundo->addCapa(capa_1);
	//capa 2 es la mas grande, la del escenario
	CapaFondo* capa_2 = new CapaFondo(BACKGROUND_2__ALTOPX_DEFAULT*PIXEL_A_LOGICO,BACKGROUND_2__ANCHOPX_DEFAULT*PIXEL_A_LOGICO,BACKGROUND_2_Z_INDEX,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,BACKGROUND_2_DEFAULT,ventana);
	mundo->addCapa(capa_2);
	//la que contiene el escenario
	CapaPrincipal* capa_principal = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,personaje_default);
	mundo->addCapa(capa_principal);
	log("Capas agregadas al Mundo",LOG_DEBUG);
	return mundo;
}
