#include "ParserJSON.h"

#define LOGLVL_DEFAULT 2
#define TIEMPO_DEFAULT 180
#define VENTANA_ANCHO_PX_DEFAULT 512
#define VENTANA_ALTO_PX_DEFAULT 384
#define VENTANA_ANCHO_DEFAULT 200
#define ESCENARIO_ANCHO_DEFAULT 600
#define ESCENARIO_ALTO_DEFAULT 150
#define Y_PISO_DEFAULT 120
#define BACKGROUND_DEFAULT "/data/img/default/background.png"
#define CAPA_ANCHO_DEFAULT 600
#define CAPA_Z_INDEX_DEFAULT 0
#define PERSONAJE_Z_INDEX_DEFAULT 3
#define PERSONAJE_SPRITE_INICIAL_DEFAULT "../data/players/subzero/sprites/initial.png"
#define PERSONAJE_SPRITE_CAMINATA_DEFAULT "../data/players/subzero/sprites/walk.png"
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
}

Mundo* ParserJSON::cargarMundo() {

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(m_ruta_archivo.c_str());

	// Si no se pudo abrir archivo, generar mundo por defecto.
	if ( ! archivoConfig ) {
		return CrearMundoDefault();
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo de configuracion JSON, se genera una partida por defecto.", LOG_ERROR );
	}
	log ( "Se abrio el archivo JSON.", LOG_DEBUG );

	// Si no se pudo parsear archivo, generar mundo por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se genera una partida por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return CrearMundoDefault();
	} else log( "El archivo JSON es valido.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON.", LOG_DEBUG );

	// Obtener el nivel de detalle de la bitacora. Si no se especifica
	// se considera nivel DEBUG por defecto, que es el mas completo y reporta cada
	// evento del programa.
	int loglvl = root.get( "loglvl", LOGLVL_DEFAULT ).asInt();
	if ( loglvl > 2 ) {
		loglvl = LOGLVL_DEFAULT;
		// Informar al usuario el cambio de nivel.
		log ( " Nivel de logging incorrecto. Los niveles de logging son: 0-ERRORES, 1-WARNINGS/ERRORES, 2-SUCESOS/WARNINGS/ERRORES (DEBUG). Se setea por defecto nivel DEBUG.", LOG_WARNING );
	} else log( "Se cargo correctamente el nivel de logging.", LOG_DEBUG );

	// Setear nivel de logging del programa.
	nivel = loglvl;

	/*
	Tiempo* tiempo_pelea;
	// Obtener tiempo limite del combate.
	float tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asFloat();
	if ( tiempo < 0 ) {
		tiempo_pelea = tiempoPorDefault();
		// Informar al usuario el cambio de tiempo de la ronda.
		log ( "WARNING: El tiempo no puede ser negativo. Se setea automaticamente en 3 minutos." );
	}
	else {
		// Crear tiempo.
		tiempo_pelea = new Tiempo( tiempo );
		log( "Se cargo correctamente el tiempo del combate." );
	}

	// Cargar tiempo a la pelea.
	nueva_pelea->Tiempo( tiempo_pelea );
	*/ /*** -------------EL TIEMPO TODAVIA NO LO USAMOS -------------- ***/

	// Obtener dimensiones de la ventana. Se setean por defecto en caso de error.
	// El alto se seteara luego dependiendo del escenario.
	int ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
	if ( ventana_ancho_px < 0 ) {
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		// Informar al usuario el cambio de ancho.
		log( "El ancho en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 512px.", LOG_WARNING );
	} else log( "Se cargo correctamente el ancho en pixeles de la ventana.", LOG_DEBUG );
	int ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
	if ( ventana_alto_px < 0 ) {
		ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		// Informar al usuario el cambio de alto.
		log( "El alto en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 384px.", LOG_WARNING );
	} else log( "Se cargo correctamente el alto en pixeles de la ventana.", LOG_DEBUG );
	int ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asInt();
	if ( ventana_ancho < 0 ) {
		ventana_ancho = VENTANA_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
		log( "El ancho logico de la ventana no puede ser negativo. Se setea automaticamente a 200.", LOG_WARNING );
	} else log( "Se cargo correctamente el ancho logico de la ventana.", LOG_DEBUG );

	// Obtener las dimensiones logicas del escenario.
	// En caso de error se setean por defecto.
	int escenario_ancho = root["escenario"].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asInt();
	if ( escenario_ancho < 0 ) {
		escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
		log( "El ancho del escenario no puede ser negativo. Se setea automaticamente a 600.", LOG_WARNING );
	} else log( "Se cargo correctamente el ancho logico del escenario.", LOG_DEBUG );
	int escenario_alto = root["escenario"].get( "alto", ESCENARIO_ALTO_DEFAULT ).asInt();
	if ( escenario_alto < 0 ) {
		escenario_alto = ESCENARIO_ALTO_DEFAULT;
		// Informar al usuario el cambio de alto logico.
		log( "WARNING: El alto del escenario no puede ser negativo. Se setea automaticamente a 150.", LOG_WARNING );
	} else log( "Se cargo correctamente el alto logico del escenario.", LOG_DEBUG );
	int y_piso = root["escenario"].get( "y-piso", Y_PISO_DEFAULT ).asInt();
	log ( "Se cargo correctamente la altura del piso.", LOG_DEBUG );

	// Setear alto logico de la ventana de acuerdo al alto del escenario.
	int ventana_alto = escenario_alto;
	log ( "Se fijo el alto logico de la ventana.", LOG_DEBUG );

	// Obtener relaciones entre pixeles y unidades logicas del mundo.
	float ratio_x = ventana_ancho_px / ventana_ancho;
	float ratio_y = ventana_alto_px / ventana_alto;
	log ( "Se calcularon las relaciones para el ancho y el alto entre los pixeles y las unidades logicas del mundo.", LOG_DEBUG );

	// Crear Mundo.
	Mundo* nuevo_mundo = new Mundo(escenario_ancho, escenario_alto);
	log ( "Se creo correctamente un mundo vacio", LOG_DEBUG );

	// Crear Ventana.
	Ventana* ventana = new Ventana( ventana_ancho, ventana_alto, ratio_x, ratio_y );
	log ( "Se creo correctamente la ventana (camara)", LOG_DEBUG );

	// Obtener las capas del escenario. La primera capa es el fondo del escenario.
	// Se setea por defecto el ancho en caso de error.
	// Si la imagen no existe, se usa una por defecto.
	const Json::Value capas = root["capas"];
	for ( unsigned int i=0; i < capas.size(); i++ ) {
		string background = capas[i].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();
		int capa_ancho = capas[i].get( "ancho", CAPA_ANCHO_DEFAULT ).asInt();
		if ( capa_ancho < 0 ) {
			capa_ancho = CAPA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho.
			log( "El ancho de la capa no puede ser negativo. Se setea automaticamente en 600.", LOG_WARNING );
		} else if ( capa_ancho > escenario_ancho ) {
			capa_ancho = CAPA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho.
			log ( "El ancho de la capa no puede superar el del escenario. Se setea automaticamente en 600.", LOG_WARNING );
		} else log( "Se cargo correctamente el ancho logico de la capa.", LOG_DEBUG );
		int capa_z_index = capas[i].get( "z-index", CAPA_Z_INDEX_DEFAULT + i ).asInt();
		log ( "Se cargo el z-index de la capa.", LOG_DEBUG );

		// Setear alto logico de la capa de acuerdo al alto del escenario.
		int capa_alto = escenario_alto;
		log ( "Se fijo el alto logico de la ventana.", LOG_DEBUG );

		// Creo capas de fondo.
		CapaFondo* capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, background, ventana );
		if ( capa_fondo == NULL ) {
			delete capa_fondo;
			capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, BACKGROUND_DEFAULT, ventana );
			log( "No se pudo cargar la imagen de la capa. Se carga imagen por defecto.", LOG_ERROR );
		} else {
			log( "Se creo correctamente la capa.", LOG_DEBUG );
		}

		// Agrego capa al mundo.
		nuevo_mundo->addCapa(capa_fondo);


	}

	// Obtener el personaje.
	// Se consideran sprites por defecto.
	// Por defecto: ancho 20, alto 35, z-index 1.
	int personaje_ancho = root["personaje"].get( "ancho", PERSONAJE_ANCHO_DEFAULT ).asInt();
	if ( personaje_ancho < 0 ) {
		personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho.
		log ( "WARNING: El ancho del personaje no puede ser negativo. Se setea automaticamente en 20." );
	} else if ( personaje_ancho > escenario_ancho ) {
		personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho.
		log ( "WARNING: El ancho del personaje no puede superar el del escenario. Se setea automaticamente en 20." );
	} else log( "Se cargo correctamente el ancho logico del personaje." );
	int personaje_alto = root["personaje"].get( "alto", PERSONAJE_ALTO_DEFAULT ).asInt();
	if ( personaje_alto < 0 ) {
		personaje_alto = PERSONAJE_ALTO_DEFAULT;
		// Informar al usuario el cambio de alto.
		log( "WARNING: El alto del pesonaje no puede ser negativo. Se setea automaticamente en 35." );
	} else if ( personaje_alto > escenario_alto ) {
		personaje_alto = PERSONAJE_ALTO_DEFAULT;
		//Informar al usuario el cambio de alto.
		log ( "WARNING: El alto del personaje no puede superar el del escenario. Se setea automaticamente en 35." );
	} else log( "Se cargo correctamente el alto logico del personaje." );
	int personaje_z_index = root["personaje"].get( "z-index", PERSONAJE_Z_INDEX_DEFAULT ).asInt();
	log ( "Se cargo correctamente el z-index del personaje." );
	string personaje_sprite_inicial = root["personaje"]["sprites"].get( "inicial", PERSONAJE_SPRITE_INICIAL_DEFAULT ).asString();
	string personaje_sprite_caminata = root["personaje"]["sprites"].get ( "caminata", PERSONAJE_SPRITE_CAMINATA_DEFAULT ).asString();
	log ( "Se cargaron los sprites del personaje." );
	string personaje_nombre = root["personaje"].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
	log ( "Se cargo el nombre del personaje." );





	// Crear Sprites.
	Sprite** sprites;
	// Al agregar un sprite, se devuelve false si
	// la imagen no existe o no se pudo abrir.
	Sprite* spriteInicial = new Sprite(personaje_sprite_inicial);
	if ( spriteInicial == NULL ) {
		spriteInicial = new Sprite( PERSONAJE_SPRITE_INICIAL_DEFAULT );
		// Informar al usuario el cambio de sprite.
		log ( "ERROR: No se pudo cargar el sprite del personaje. Se carga sprite por defecto." );
	} else log( "Se cargo correctamente el sprite del personaje." );
	sprites[0] = spriteInicial;
	Sprite* spriteCaminata = new Sprite(personaje_sprite_caminata);
	if ( spriteCaminata == NULL ) {
		spriteCaminata = new Sprite( PERSONAJE_SPRITE_CAMINATA_DEFAULT );
		// Informar al usuario el cambio de sprite.
		log ( "ERROR: No se pudo cargar el sprite del personaje. Se carga sprite por defecto." );
	} else log( "Se cargo correctamente el sprite del personaje." );
	sprites[1] = spriteCaminata;


	// Crear personaje.
	Personaje::Personaje* personaje = new Personaje(personaje_nombre, sprites, personaje_velocidad);

	// Crear ventana (capa-camara).
	Capa::Capa* camara = new Capa( ventana_alto, ventana_ancho, personaje_z_index, escenario_ancho, personaje_velocidad );

	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal::CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personaje_z_index, escenario_ancho, personaje_velocidad, personaje );
	capa_principal->camara( camara );

	// Agrego capa principal al mundo.
	nuevo_mundo->capaPrincipal( capa_principal );

	// Cargar mundo a la pelea.
	nueva_pelea->mundo( nuevo_mundo );

	log( "Se creo una nueva pelea." );
	return nueva_pelea;

	// PERSONAJE SE LE PASA VELOCIDAD_PERSONAJE POR CONSTRUCTOR PERO NUNCA LO USA.
	// PREGUNTAR SI LAS DIMENSIONES DE LAS CAPAS SE PASAN EN INT O SI LES FALTO PUSHEAR.
	// HACER QUE SI NO SE PUEDE CARGAR IMAGEN DE CAPA SE DEVUELVA NULL.

}

