#include "ParserJSON.h"

#define LOGLVL_DEFAULT 1
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


using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
}

// Devuelve un root que se usara para generar la partida.
Pelea::Pelea* ParserJSON::generarPelea() {
	Json::Value root;
	Json::Reader reader;

	// Crear Pelea.
	Pelea::Pelea* nueva_pelea = new Pelea();

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(ruta_archivo);

	// Si no se pudo abrir archivo, generar pelea por defecto.
	if ( ! archivoConfig ) {
		return this->peleaPorDefecto();
		// Informar al usuario la falla y la resolucion tomada.
		log( "ERROR: No se pudo abrir el archivo de configuracion JSON, se genera una partida por defecto." );
	}
	log ( "Se abrio el archivo JSON." );

	// Si no se pudo parsear archivo, generar pelea por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "ERROR: No se pudo interpretar el JSON, se genera una partida por defecto." + reader.getFormattedErrorMessages() );
	    return this->peleaPorDefecto();
	} else log( "El archivo JSON es valido." );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON." );

	// Obtener el nivel de detalle de la bitacora. Si no se especifica
	// se considera nivel 1 por defecto, que es el mas completo y reporta cada
	// evento del programa.
	int loglvl = root.get( "loglvl", LOGLVL_DEFAULT ).asInt();
	if ( loglvl > 3 ) {
		loglvl = LOGLVL_DEFAULT;
		// Informar al usuario el cambio de nivel.
		log ( "WARNING: El maximo nivel de logging es 3. Se setea automaticamente en 1." );
	} else log( "Se cargo correctamente el nivel de logging." );

	// Setear nivel de logging del programa.
	nivel = loglvl;

	// Obtener tiempo limite del combate.
	float tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asFloat();
	if ( tiempo < 0 ) {
		tiempo = TIEMPO_DEFAULT;
		// Informar al usuario el cambio de tiempo de la ronda.
		log ( "WARNING: El tiempo no puede ser negativo. Se setea automaticamente en 3 minutos." );
	} else log( "Se cargo correctamente el tiempo del combate." );

	// Crear tiempo.
	Tiempo::Tiempo* tiempo_pelea = new Tiempo( tiempo );

	// Cargar tiempo a la pelea.
	nueva_pelea->tiempo( tiempo_pelea );

	// Obtener dimensiones de la ventana (camara). Por defecto, 640x480px
	// y 200 de ancho logico. El alto se seteara luego dependiendo del escenario.
	int ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
	if ( ventana_ancho_px < 0 ) {
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		// Informar al usuario el cambio de ancho.
		log( "WARNING: El ancho en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 640px." );
	} else log( "Se cargo correctamente el ancho en pixeles de la ventana." );
	int ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
	if ( ventana_alto_px < 0 ) {
		ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		// Informar al usuario el cambio de alto.
		log( "WARNING: El alto en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 480px." );
	} else log( "Se cargo correctamente el alto en pixeles de la ventana." );
	int ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asInt();
	if ( ventana_ancho < 0 ) {
		ventana_ancho = VENTANA_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
		log( "WARNING: El ancho logico de la ventana no puede ser negativo. Se setea automaticamente a 200." );
	} else log( "Se cargo correctamente el ancho logico de la ventana." );

	// Obtener las dimensiones logicas del escenario.
	// Por defecto: ancho 1000, alto 150, y-piso 20.
	int escenario_ancho = root["escenario"].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asInt();
	if ( escenario_ancho < 0 ) {
		escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
		// Informar al usuario el cambio de ancho logico.
		log( "WARNING: El ancho del escenario no puede ser negativo. Se setea automaticamente a 1000." );
	} else log( "Se cargo correctamente el ancho logico del escenario." );
	int escenario_alto = root["escenario"].get( "alto", ESCENARIO_ALTO_DEFAULT ).asInt();
	if ( escenario_alto < 0 ) {
		escenario_alto = ESCENARIO_ALTO_DEFAULT;
		// Informar al usuario el cambio de alto logico.
		log( "WARNING: El alto del escenario no puede ser negativo. Se setea automaticamente a 1000." );
	} else log( "Se cargo correctamente el alto logico del escenario." );
	int y_piso = root["escenario"].get( "y-piso", Y_PISO_DEFAULT ).asInt();
	log ( "Se cargo correctamente la altura del piso." );

	// Setear alto logico de la ventana de acuerdo al alto del escenario.
	int ventana_alto = escenario_alto;

	// Setear velocidad del personaje.
	int personaje_velocidad = escenario_ancho / PERSONAJE_FACTOR_VELOCIDAD;

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
			// Informar al usuario el cambio de ancho.
			log( "WARNING: El ancho de la capa no puede ser negativo. Se setea automaticamente en 1000." );
		} else if ( capa_ancho > escenario_ancho ) {
			capa_ancho = CAPA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho.
			log ( "WARNING: El ancho de la capa no puede superar el del escenario. Se setea automaticamente en 1000." );
		} else log( "Se cargo correctamente el ancho logico de la capa." );
		int capa_z_index = capas[i].get( "z-index", CAPA_Z_INDEX_DEFAULT + i ).asInt();

		// Setear alto logico de la capa de acuerdo al alto del escenario.
		int capa_alto = escenario_alto;


		Capa::Capa* nueva_capa = new Capa( capa_alto, capa_ancho, capa_z_index, escenario_ancho, personaje_velocidad );
		// Cargo imagen. Si no existe o no se pudo abrir,
		// se devuelve false y se usa la imagen por defecto.
		if ( ! nueva_capa->cargarBackground(background) ) {
			nueva_capa->cargarBackground(BACKGROUND_DEFAULT);
			// Informar al usuario el cambio de fondo.
			log( "ERROR: No se pudo cargar la imagen de la capa. Se carga imagen por defecto." );
		} else log( "Se cargo correctamente la imagen de la capa." );

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
	Sprites::Sprites* sprites = new Sprites();
	// Al agregar un sprite, se devuelve false si
	// la imagen no existe o no se pudo abrir.
	if ( ! sprites->spriteInicial( personaje_sprite_inicial ) ) {
		sprites->spriteInicial( PERSONAJE_SPRITE_INICIAL_DEFAULT );
		// Informar al usuario el cambio de sprite.
		log ( "ERROR: No se pudo cargar el sprite del personaje. Se carga sprite por defecto." );
	} else log( "Se cargo correctamente el sprite del personaje." );
	if ( ! sprites->spriteCaminata( personaje_sprite_caminata ) ) {
		sprites->spriteCaminata( PERSONAJE_SPRITE_CAMINATA_DEFAULT );
		// Informar al usuario el cambio de sprite.
		log ( "ERROR: No se pudo cargar el sprite del personaje. Se carga sprite por defecto." );
	} else log( "Se cargo correctamente el sprite del personaje." );


	// Crear personaje.
	Personaje::Personaje* personaje = new Personaje(personaje_nombre, sprites, personaje_alto, personaje_ancho );

	// Crear ventana (capa-camara).
	// ACA HAY QUE MOSTRAR LA VENTANA CON SDL, YA TENEMOS LOS PIXELES!!!!!
	Capa::Capa* camara = new Capa( ventana_alto, ventana_ancho, personaje_z_index );


	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal::CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personaje_z_index );
	capa_principal->agregarPersonaje( personaje );
	capa_principal->camara( camara );

	// Agrego capa principal al mundo.
	nuevo_mundo->capaPrincipal( capa_principal );

	// Cargar mundo a la pelea.
	nueva_pelea->mundo( nuevo_mundo );

	log( "Se creo una nueva pelea." );
	return nueva_pelea;


	// FALTA MOSTRAR LA VENTANA CON SDL AL CREAR LA VENTANA (CAPA-CAMARA).
	// FALTAN SPRITES POR DEFECTO PARA POSICIONES DE LUCHA, SALTO, ETC.
	// FALTA CREAR CLASE MOVIMIENTO PARA ABSTRAER.
	// NO VA A COMPILAR NUNCA HASTA QUE TENGAMOS LOS CONSTRUCTORES DE MUNDO CAPA PERSONAJE ETC

}

