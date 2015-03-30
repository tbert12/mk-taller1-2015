#include "ParserJSON.h"

#define LOGLVL_DEFAULT = 1
#define TIEMPO_DEFAULT = 3.00
#define VENTANA_ANCHO_PX_DEFAULT = 800
#define VENTANA_ALTO_PX_DEFAULT = 600
#define VENTANA_ANCHO_DEFAULT = 200
#define ESCENARIO_ANCHO_DEFAULT = 1000
#define ESCENARIO_ALTO_DEFAULT = 1000
#define Y_PISO_DEFAULT = 20
#define BACKGROUND_DEFAULT = "../../data/backgrounds/default.png"
#define CAPA_ANCHO_DEFAULT = 1000
#define CAPA_Z_INDEX_DEFAULT = 2
#define PERSONAJE_ANCHO_DEFAULT = 20
#define PERSONAJE_ALTO_DEFAULT = 35
#define PERSONAJE_Z_INDEX_DEFAULT = 1
#define PERSONAJE_SPRITE_INICIAL_DEFAULT = "../../data/players/subzero/sprites/initial.png"
#define PERSONAJE_SPRITE_CAMINATA_DEFAULT = "../../data/players/subzero/sprites/walk.png"
#define PERSONAJE_NOMBRE_DEFAULT = "Jugador"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	archivoConfig = ruta_archivo;
}

// Devuelve un root que se usara para generar la partida.
Pelea::Pelea* ParserJSON::generarPelea() {
	Json::Value = root;
	Json::Reader = reader;

	// Crear Pelea.
	Pelea::Pelea* nueva_pelea = new Pelea();

	// Abro archivo.
	fopen( archivoConfig.c_str(), 'r' );

	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    std::cout  << "Failed to parse configuration\n"
	               << reader.getFormattedErrorMessages();
	    return this->eleaPorDefecto();
	}

	// Obtener el nivel de detalle de la bitacora. Si no se especifica
	// se considera nivel 1 por defecto, que es el mas completo y reporta cada
	// evento del programa.
	int loglvl = root.get( "loglvl", LOGLVL_DEFAULT ).asInt();
	if ( loglvl > 2 ) {
		loglvl = LOGLVL_DEFAULT;
		// Informar al usuario el cambio de nivel.
	}

	// Obtener tiempo limite del combate.
	float tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asFloat();
	if ( tiempo < 0 ) {
		tiempo = TIEMPO_DEFAULT;
		// Informar al usuario el cambio de tiempo de la ronda.
	}

	// Crear tiempo.
	Tiempo::Tiempo* tiempo_pelea = new Tiempo( tiempo );

	// Cargar tiempo a la pelea.
	nueva_pelea->tiempo( tiempo_pelea );

	// Obtener dimensiones de la ventana (camara). Por defecto, 800x600px
	// y 200 de ancho logico. El alto se seteara luego dependiendo del escenario.
	int ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
	if ( ventana_ancho_px < 0 ) {
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		// Informar al usuario el cambio de ancho.
	}
	int ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
	if ( ventana_alto_px < 0 ) {
			ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
			// Informar al usuario el cambio de alto.
		}
	int ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asInt();
	if ( ventana_ancho < 0 ) {
			ventana_ancho = VENTANA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho logico.
		}

	// Obtener las dimensiones logicas del escenario.
	// Por defecto: ancho 1000, alto 150, y-piso 20.
	int escenario_ancho = root["escenario"].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asInt();
	if ( escenario_ancho < 0 ) {
		escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
	}
	int escenario_alto = root["escenario"].get( "alto", ESCENARIO_ALTO_DEFAULT ).asInt();
	if ( escenario_alto < 0 ) {
			escenario_alto = ESCENARIO_ALTO_DEFAULT;
			// Informar al usuario el cambio de alto logico.
	}
	int y_piso = root["escenario"].get( "y-piso", Y_PISO_DEFAULT ).asInt();

	// Setear alto logico de la ventana de acuerdo al alto del escenario.
	int ventana_alto = escenario_alto;

	// Obtener relaciones entre pixeles y unidades logicas del mundo.
	float ratio_x = ventana_ancho_px / ventana_ancho;
	float ratio_y = ventana_alto_px / ventana_alto;

	// Crear Mundo.
	Mundo::Mundo* nuevo_mundo = new Mundo(ratio_x, ratio_y);

	// Obtener las capas del escenario.
	// Por defecto se considera ancho 1000.
	// Si la imagen no existe, se usa una por defecto.
	const Json::Value capas = root["capas"];
	for ( int i=0; i < capas.size(); ++i ) {
		string background = capas[i].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();
		int capa_ancho = capas[i].get( "ancho", CAPA_ANCHO_DEFAULT ).asInt();
		if ( capa_ancho < 0 ) {
					capa_ancho = CAPA_ANCHO_DEFAULT;
					// Informar al usuario el cambio de ancho logico.
		}
		int capa_z_index = capas[i].get( "z-index", CAPA_Z_INDEX_DEFAULT + i ).asInt();

		// Setear alto logico de la capa de acuerdo al alto del escenario.
		int capa_alto = escenario_alto;


		Capa::Capa* nueva_capa = new Capa( capa_alto, capa_ancho, capa_z_index);
		// Cargo imagen. Si no existe o no se pudo abrir,
		// el constructor devuelve false y se usa la imagen por defecto.
		if ( ! nueva_capa->cargarBackground ) {
			nueva_capa = Capa(BACKGROUND_DEFAULT);
		}

		// Agrego capa al mundo.
		nuevo_mundo->agregarCapa(nueva_capa);

	}

	// Obtener el personaje.
	// Se consideran sprites por defecto.
	// Por defecto: ancho 20, alto 35, z-index 1.
	int personaje_ancho = root["personaje"].get( "ancho", PERSONAJE_ANCHO_DEFAULT ).asInt();
	if ( personaje_ancho < 0 ) {
		personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho.
	} else if ( personaje_ancho > escenario_ancho ) {
		personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho.
	}
	int personaje_alto = root["personaje"].get( "alto", PERSONAJE_ALTO_DEFAULT ).asInt();
	if ( personaje_alto < 0 ) {
		personaje_alto = PERSONAJE_ALTO_DEFAULT;
		// Informar al usuario el cambio de alto.
	} else if ( personaje_alto > escenario_alto ) {
		personaje_alto = PERSONAJE_ALTO_DEFAULT;
		//Informar al usuario el cambio de alto.
	}
	int personaje_z_index = root["personaje"].get( "z-index", PERSONAJE_Z_INDEX_DEFAULT ).asInt();
	string personaje_sprite_inicial = root["personaje"]["sprites"].get( "inicial", PERSONAJE_SPRITE_INICIAL_DEFAULT ).asString();
	string personaje_sprite_caminata = root["personaje"]["sprites"].get ( "caminata", PERSONAJE_SPRITE_CAMINATA_DEFAULT ).asString();
	string personaje_nombre = root["personaje"].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();


	// Crear Sprites.
	Sprites::Sprites* sprites = new Sprites();
	// Al agregar un sprite, se devuelve false si
	// la imagen no existe o no se pudo abrir.
	if ( ! sprites->spriteInicial( personaje_sprite_inicial ) ) {
		sprites->spriteInicial( PERSONAJE_SPRITE_INICIAL_DEFAULT );
	}
	if ( ! sprites->spriteCaminata( personaje_sprite_caminata ) ) {
		sprites->spriteCaminata( PERSONAJE_SPRITE_CAMINATA_DEFAULT );
	}


	// Crear personaje.
	Personaje::Personaje* personaje = new Personaje(personaje_nombre, sprites, personaje_alto, personaje_ancho );

	// Crear ventana (capa-camara).
	// ACA HAY QUE MOSTRAR LA VENTANA CON SDL, YA TENEMOS LOS PIXELES.
	Capa::Capa* camara = new Capa( ventana_alto, ventana_ancho, personaje_z_index );


	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal::CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personaje_z_index );
	capa_principal->agregarPersonaje( personaje );
	capa_principal->camara( camara );

	// Agrego capa principal al mundo.
	nuevo_mundo->capaPrincipal( capa_principal );

	// Cargar mundo a la pelea.
	nueva_pelea->mundo( nuevo_mundo );

	return nueva_pelea;



	// FALTAN MENSAJES DE LOGEO. HACER LOGLVL VARIABLE GLOBAL.
	// FALTAN SPRITES POR DEFECTO PARA POSICIONES DE LUCHA, SALTO, ETC.
	// FALTA CREAR CLASE MOVIMIENTO PARA ABSTRAER Y PARA SIMPLIFICAR CONSTRUCTORES.
	// FALTA VALIDAR QUE EL ANCHO DE LAS CAPAS NO SEA MAYOR AL DEL ESCENARIO.
	// NO VA A COMPILAR NUNCA HASTA QUE TENGAMOS LOS CONSTRUCTORES DE MUNDO CAPA PERSONAJE ETC

}

