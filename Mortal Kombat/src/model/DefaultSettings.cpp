#include "Mundo.h"
#include "logging.h"
#include <algorithm>

#define TIEMPO_DEFAULT 3.00
#define VENTANA_ANCHO_PX_DEFAULT 512
#define VENTANA_ALTO_PX_DEFAULT 384
#define VENTANA_ANCHO_LOG 200.0
#define VENTANA_ALTO_LOG 150.0
#define ESCENARIO_ANCHO_DEFAULT 600.0
#define ESCENARIO_ALTO_DEFAULT 150.0
#define Y_PISO_DEFAULT 135.0
#define BACKGROUND_0_DEFAULT "data/img/background/background_0.png"
#define BACKGROUND_0__ANCHO_DEFAULT 200.0
#define BACKGROUND_0__ALTO_DEFAULT 150.0
#define BACKGROUND_0_Z_INDEX 0
#define BACKGROUND_1_DEFAULT "data/img/background/background_1.png"
#define BACKGROUND_1__ANCHO_DEFAULT 400.0
#define BACKGROUND_1__ALTO_DEFAULT 150.0
#define BACKGROUND_1_Z_INDEX 1
#define BACKGROUND_2_DEFAULT "data/img/background/background_2.png"
#define BACKGROUND_2__ANCHO_DEFAULT 600.0
#define BACKGROUND_2__ALTO_DEFAULT 150.0
#define BACKGROUND_2_Z_INDEX 2
#define PERSONAJE_Z_INDEX_DEFAULT 3
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"
#define PERSONAJE_FACTOR_VELOCIDAD 10

std::vector<Sprite*> GenerarSpritesDefault(Ventana* ventana,float rx, float ry){

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
	framesAgacharse[0] = new Frame(.0f,.0f,107/ry,60/rx);
	framesAgacharse[1] = new Frame(60/rx,.0f,89/ry,62/rx);
	std::vector<Frame*> framesLevantarse(framesAgacharse);
	std::reverse(framesLevantarse.begin(),framesLevantarse.end());

	std::vector<Frame*> framesAgachado(1);
	framesAgachado[0] = new Frame(122/rx,.0f,71/ry,64/rx);

	int wInitial = 72,wCaminar = 68;
	for (int i=0;i<9;i++){
		framesInitial[i] = new Frame(wInitial*i/rx,0,133/ry,wInitial/rx);
		framesCaminar[i] = new Frame(wCaminar*i/rx,0,133/ry,wCaminar/rx);
	}
	std::vector<Frame*> framesCaminarAtras (framesCaminar);
	std::reverse(framesCaminarAtras.begin(),framesCaminarAtras.end());

	framesAntesDeSaltar[0] = new Frame(0,0,139/ry,69/rx);
	framesDeSaltar[0] = new Frame(71/rx,0,96/ry,70/rx);
	framesDespuesDeSaltar[0] = new Frame(141/rx,0,107/ry,60/rx);

	framesAntesDeSaltarDiagonal[0] = new Frame(xSaltoDiagonal[0]/rx,0,hSaltoDiagonal[0]/ry,wSaltoDiagonal[0]/ry);

	for (size_t i = 0; i < framesSaltoDiagonal.size(); i++){
		framesSaltoDiagonal[i] = new Frame(xSaltoDiagonal[i+1]/rx,0,hSaltoDiagonal[i+1]/ry,wSaltoDiagonal[i+1]/rx);
		framesSaltoDiagonalAtras[framesSaltoDiagonal.size()-i-1] = new Frame(xSaltoDiagonal[i+1]/rx,0,hSaltoDiagonal[i+1]/ry,wSaltoDiagonal[i+1]/rx);
	}
	std::string rutaInitial = "data/players/subzero/sprites/initial.png";
	std::string rutaCaminar = "data/players/subzero/sprites/walk.png";
	std::string rutaCaminarAtras = "data/players/subzero/sprites/walk.png";
	std::string rutaSalto = "data/players/subzero/sprites/salto.png";
	std::string rutaSaltoDiagonal = "data/players/subzero/sprites/diag.png";
	std::string rutaAgacharse = "data/players/subzero/sprites/agachar.png";

	Sprite* Initial = new Sprite(rutaInitial,framesInitial,ventana);
	Sprite* Caminar = new Sprite(rutaCaminar,framesCaminar,ventana);
	Sprite* CaminarAtras = new Sprite(rutaCaminar,framesCaminarAtras,ventana);
	Sprite* AntesDeSaltar = new Sprite(rutaSalto,framesAntesDeSaltar,ventana);
	Sprite* Salto = new Sprite(rutaSalto,framesDeSaltar,ventana);
	Sprite* DespuesDeSaltar = new Sprite(rutaSalto,framesDespuesDeSaltar,ventana);
	AntesDeSaltar->setSpriteSiguiente(Salto);
	DespuesDeSaltar->setSpriteSiguiente(Initial);

	Sprite* AntesSaltoDiagonal = new Sprite(rutaSaltoDiagonal,framesAntesDeSaltarDiagonal,ventana);
	Sprite* SaltoDiagonal = new Sprite(rutaSaltoDiagonal,framesSaltoDiagonal,ventana);
	AntesSaltoDiagonal->setSpriteSiguiente(SaltoDiagonal);

	Sprite* AntesSaltoDiagonalAtras = new Sprite(rutaSaltoDiagonal,framesAntesDeSaltarDiagonal,ventana);
	Sprite* SaltoDiagonalAtras = new Sprite(rutaSaltoDiagonal,framesSaltoDiagonalAtras,ventana);
	AntesSaltoDiagonalAtras->setSpriteSiguiente(SaltoDiagonalAtras);

	Sprite* Agacharse = new Sprite(rutaAgacharse,framesAgacharse,ventana);
	Sprite* Agachado = new Sprite(rutaAgacharse,framesAgachado,ventana);
	Sprite* Levantarse = new Sprite(rutaAgacharse,framesLevantarse,ventana);
	Agacharse->setSpriteSiguiente(Agachado);
	Levantarse->setSpriteSiguiente(Initial);

	//{Initial,Caminar,CaminarAtras,AntesDeSaltar,Salto,DespuesDeSaltar,SaltoDiagonal}
	std::vector<Sprite*> sprites = {Initial,Caminar,CaminarAtras,Salto,AntesDeSaltar,DespuesDeSaltar,AntesSaltoDiagonal,SaltoDiagonal,AntesSaltoDiagonalAtras,SaltoDiagonalAtras,Agacharse,Agachado,Levantarse};
	printf("Termine carga sprite\n");
	return sprites;
}

Mundo* CrearMundoDefault(){
	log("Se comienza a crear un Mundo con valores Default",LOG_DEBUG);

	float ratio_x = (float)VENTANA_ANCHO_PX_DEFAULT/VENTANA_ANCHO_LOG;
	float ratio_y = (float)VENTANA_ALTO_PX_DEFAULT/VENTANA_ALTO_LOG;
	Mundo* mundo = new Mundo(ESCENARIO_ANCHO_DEFAULT,ESCENARIO_ALTO_DEFAULT);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT,ratio_x,ratio_y);

	if(!ventana->create_window()){
		log("No se puede inicializar la ventana",LOG_ERROR);
	}

	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, GenerarSpritesDefault(ventana,ratio_x,ratio_y), PERSONAJE_FACTOR_VELOCIDAD);
	personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2)*1.0f,Y_PISO_DEFAULT*1.0f);
	log("Creado Personaje Default (SubZero)",LOG_DEBUG);

	mundo->setVentana(ventana);
	mundo->setTiempo(new Tiempo(TIEMPO_DEFAULT));

	log("Creado el tiempo, la ventana y el escenario. Seteados a Mundo",LOG_DEBUG);
	if (!mundo->addPersonaje(personaje_default)){
		log("Personaje Default NO agregado al Mundo",LOG_ERROR);
	}
	log("Personaje Default agregado al Mundo",LOG_DEBUG);

	// CREO LAS CAPAS, SON 3 NIVELES
	// La relacion entre el las medidas logicas y los pixeles es la divicion


	//capa 0, es la ultima. de la misma medida que la ventana
	CapaFondo* capa_0 =new CapaFondo(BACKGROUND_0__ALTO_DEFAULT,BACKGROUND_0__ANCHO_DEFAULT,BACKGROUND_0_Z_INDEX,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,BACKGROUND_0_DEFAULT,ventana);
	mundo->addCapa(capa_0);

	//capa 1 ,es la del medio. del doble que la ventana
	CapaFondo* capa_1 =new CapaFondo(BACKGROUND_1__ALTO_DEFAULT,BACKGROUND_1__ANCHO_DEFAULT,BACKGROUND_1_Z_INDEX,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,BACKGROUND_1_DEFAULT,ventana);
	mundo->addCapa(capa_1);

	//capa 2 es la mas grande, la del escenario
	CapaFondo* capa_2 = new CapaFondo(BACKGROUND_2__ALTO_DEFAULT,BACKGROUND_2__ANCHO_DEFAULT,BACKGROUND_2_Z_INDEX,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,BACKGROUND_2_DEFAULT,ventana);
	mundo->addCapa(capa_2);

	//la que contiene el escenario

	CapaPrincipal* capa_principal = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_FACTOR_VELOCIDAD,personaje_default);
	mundo->addCapa(capa_principal);

	//log("Capas agregadas al Mundo",LOG_DEBUG);
	return mundo;
}
