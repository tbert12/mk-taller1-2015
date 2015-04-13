#include "ParserJSON.h"

#define LOGLVL_DEFAULT 2
#define TIEMPO_DEFAULT 180
#define VENTANA_ANCHO_PX_DEFAULT 512
#define VENTANA_ALTO_PX_DEFAULT 384
#define VENTANA_ANCHO_DEFAULT 200.0
#define ESCENARIO_ANCHO_DEFAULT 600.0
#define ESCENARIO_ALTO_DEFAULT 150.0
#define Y_PISO_DEFAULT 135.0
#define BACKGROUND_DEFAULT "data/img/default/background/unknown.png"
#define CAPA_ANCHO_DEFAULT 600.0
#define CAPA_Z_INDEX_DEFAULT 0
#define PERSONAJE_Z_INDEX_DEFAULT 3
#define PERSONAJE_CARPETA_SPRITES_DEFAULT "data/img/default/sprites/"
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"

#define SPRITESHEET_PARADO_DEFAULT "initial.png"
#define SPRITESHEET_CAMINAR_DEFAULT "walk.png"
#define SPRITESHEET_SALTAR_DEFAULT "salto.png"
#define SPRITESHEET_SALTAR_DIAGONAL_DEFAULT "diag.png"
#define SPRITESHEET_AGACHAR_DEFAULT "agachar.png"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
}

Sprite* ParserJSON::crearSpriteParadoDefault(Ventana* ventana, float ratio_x, float ratio_y) {
	vector<Frame*> framesParado(9);

	int wParado = 72;
	for ( int i=0; i < 9; i++ ){
		framesParado[i] = new Frame( wParado*i/ratio_x, 0, 133/ratio_y, wParado/ratio_x );
	}

	Sprite* spriteParado = new Sprite( SPRITESHEET_PARADO_DEFAULT, framesParado, ventana );
	return spriteParado;
}

Sprite* ParserJSON::crearSpriteCaminarDefault(Ventana* ventana, float ratio_x, float ratio_y) {
	vector<Frame*> framesCaminar(9);

	int wParado = 68;
	for ( int i=0; i < 9; i++ ){
		framesCaminar[i] = new Frame( wParado*i/ratio_x, 0, 133/ratio_y, wParado/ratio_x );
	}

	Sprite* spriteCaminar = new Sprite( SPRITESHEET_CAMINAR_DEFAULT, framesCaminar, ventana );
	return spriteCaminar;
}

Sprite* ParserJSON::crearSpriteSaltarDefault(Ventana* ventana, float ratio_x, float ratio_y) {
	vector<Frame*> framesSaltar(3);

	vector<int> xSaltar = { 0, 71, 141 };
	vector<int> hSaltar = { 139, 96, 107 };
	vector<int> wSaltar = { 69, 70, 60 };

	for ( int i=0; i < 3; i++ ) {
		framesSaltar[i] = new Frame( xSaltar[i]/ratio_x, 0, hSaltar[i]/ratio_y, wSaltar[i]/ratio_x );
	}

	Sprite* spriteSaltar = new Sprite( SPRITESHEET_SALTAR_DEFAULT, framesSaltar, ventana );
	spriteSaltar->setLoop(1);
	return spriteSaltar;
}

Sprite* ParserJSON::crearSpriteSaltarDiagonalDefault(Ventana* ventana, float ratio_x, float ratio_y) {
	vector<Frame*> framesSaltarDiagonal(8);

	vector<int> xSaltarDiagonal = { 0, 72, 127, 208, 283, 335, 392, 472 };
	vector<int> hSaltarDiagonal = { 136, 82, 59, 55, 81, 81, 59, 62 };
	vector<int> wSaltarDiagonal = { 72, 55, 74, 74, 53, 55, 75, 74 };

	for ( int i=0; i < 8; i++ ) {
		framesSaltarDiagonal[i] = new Frame( xSaltarDiagonal[i]/ratio_x, 0, hSaltarDiagonal[i]/ratio_y, wSaltarDiagonal[i]/ratio_x );
	}

	Sprite* spriteSaltarDiagonal = new Sprite( SPRITESHEET_SALTAR_DIAGONAL_DEFAULT, framesSaltarDiagonal, ventana );
	return spriteSaltarDiagonal;
}

Sprite* ParserJSON::crearSpriteAgacharDefault(Ventana* ventana, float ratio_x, float ratio_y) {
	vector<Frame*> framesAgachar(3);

	vector<int> xAgachar = { 0, 60, 122 };
	vector<int> hAgachar = { 107, 89, 71 };
	vector<int> wAgachar = { 69, 62, 64 };

	for ( int i=0; i < 3; i++ ) {
		framesAgachar[i] = new Frame( xAgachar[i]/ratio_x, 0, hAgachar[i]/ratio_y, wAgachar[i]/ratio_x );
	}

	Sprite* spriteAgachar = new Sprite( SPRITESHEET_SALTAR_DEFAULT, framesAgachar, ventana );
	spriteAgachar->setLoop(2);
	return spriteAgachar;
}

vector<Sprite*> ParserJSON::generarSpritesDefault( Ventana* ventana, float ratio_x, float ratio_y ) {
	vector<Sprite*> sprites;

	sprites.push_back( this->crearSpriteParadoDefault(ventana, ratio_x, ratio_y) );
	sprites.push_back( this->crearSpriteCaminarDefault(ventana, ratio_x, ratio_y) );
	sprites.push_back( this->crearSpriteSaltarDefault(ventana, ratio_x, ratio_y) );
	sprites.push_back( this->crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y) );
	sprites.push_back( this->crearSpriteAgacharDefault(ventana, ratio_x, ratio_y) );

	return sprites;
}

Mundo* ParserJSON::generarMundoDefault(  ) {

	float ratio_x = VENTANA_ANCHO_PX_DEFAULT/VENTANA_ANCHO_DEFAULT;
	float ratio_y = VENTANA_ALTO_PX_DEFAULT/ESCENARIO_ALTO_DEFAULT;
	Mundo* mundo = new Mundo(ESCENARIO_ANCHO_DEFAULT,ESCENARIO_ALTO_DEFAULT);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT,ratio_x,ratio_y);

	if( ! ventana->create_window() ) {
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}

	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, this->generarSpritesDefault(ventana,ratio_x,ratio_y), PERSONAJE_VELOCIDAD);
	// Si flippeado, descomentar la siguiente linea:
	//Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, this->generarSpritesDefault(ventana,ratio_x,ratio_y), PERSONAJE_VELOCIDAD, true);

	personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2),Y_PISO_DEFAULT);

	mundo->setVentana(ventana);
	mundo->setTiempo(new Tiempo(TIEMPO_DEFAULT));

	mundo->addPersonaje(personaje_default);

	CapaFondo* capa = new CapaFondo(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa,CAPA_Z_INDEX_DEFAULT);

	CapaPrincipal* capa_principal = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,VENTANA_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,personaje_default);
	mundo->addCapaPrincipal(capa_principal,PERSONAJE_Z_INDEX_DEFAULT);

	return mundo;
}

vector<Sprite*> ParserJSON::cargarSprites(string ruta_carpeta, Ventana* ventana, float ratio_x, float ratio_y) {

	vector<Sprite*> sprites;

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	string ruta_archivo_json = ruta_carpeta + "sprites.json";
	archivoConfig.open(ruta_archivo_json.c_str());

	// Si no se pudo abrir archivo, generar mundo por defecto.
	if ( ! archivoConfig.is_open() ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo de sprites JSON, se generan sprites por defecto.", LOG_ERROR );
		return this->generarSpritesDefault(ventana, ratio_x, ratio_y);
	}
	log ( "Se abrio el archivo JSON de sprites.", LOG_DEBUG );

	// Si no se pudo parsear archivo, generar mundo por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se generan sprites por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return this->generarSpritesDefault(ventana, ratio_x, ratio_y);
	} else log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON de sprites.", LOG_DEBUG );

	// Creo Sprite para personaje parado.
	Sprite* sprite_parado;
	bool sprite_parado_ok = true;
	if ( root.get( "parado", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje parado. Se genera el sprite inicial por defecto.", LOG_ERROR );
		sprite_parado = crearSpriteParadoDefault(ventana, ratio_x, ratio_y);
		sprite_parado_ok = false;
	} else {
		string spritesheet_parado = root["parado"].get( "nombre", SPRITESHEET_PARADO_DEFAULT ).asString();
		const Json::Value frames_parado = root["parado"]["frames"];
		vector<Frame*> framesParado( frames_parado.size() );
		vector<bool> loop_parado(framesParado.size(), false);
		for ( unsigned int i=0; i < frames_parado.size(); i++ ) {
			int x = frames_parado[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite inicial por defecto.", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault(ventana, ratio_x, ratio_y);
				sprite_parado_ok = false;
				break;
			}
			int y = frames_parado[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite inicial por defecto", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault(ventana, ratio_x, ratio_y);
				sprite_parado_ok = false;
				break;
			}
			int alto = frames_parado[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto del frame o es negativo. Se genera el sprite inicial por defecto.", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault(ventana, ratio_x, ratio_y);
				sprite_parado_ok = false;
				break;
			}
			int ancho = frames_parado[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el ancho del frame o es negativo. Se genera el sprite inicial por defecto.", LOG_ERROR );
				sprite_parado = crearSpriteParadoDefault(ventana, ratio_x, ratio_y);
				sprite_parado_ok = false;
				break;
			}
			bool loop = frames_parado[i].get( "loop", false ).asBool();
			if ( loop ) {
				loop_parado[i] = true;
			}
			framesParado[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje parado.", LOG_DEBUG );
		}
		if ( sprite_parado_ok ) {
			try {
				sprite_parado = new Sprite( ruta_carpeta + spritesheet_parado, framesParado, ventana);
				for ( unsigned int j=0; j < framesParado.size(); j++ ) {
					if ( loop_parado[j] ) sprite_parado->setLoop(j);
				}
				log( "Se creo correctamente el sprite para el personaje parado.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				sprite_parado = crearSpriteParadoDefault(ventana, ratio_x, ratio_y);
				log( "No se pudo abrir el spritesheet del personaje parado. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
		sprites.push_back( sprite_parado );
	}

	// Creo Sprite para personaje caminando.
	Sprite* sprite_caminar;
	bool sprite_caminar_ok = true;
	if ( root.get( "caminar", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje caminando. Se genera el sprite de caminata por defecto.", LOG_ERROR );
		sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x, ratio_y);
		sprite_caminar_ok = false;
	} else {
		string spritesheet_caminar = root["caminar"].get( "nombre", SPRITESHEET_CAMINAR_DEFAULT ).asString();
		const Json::Value frames_caminar = root["caminar"]["frames"];
		vector<Frame*> framesCaminar( frames_caminar.size() );
		vector<bool> loop_caminar(framesCaminar.size(), false);
		for ( unsigned int i=0; i < frames_caminar.size(); i++ ) {
			int x = frames_caminar[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite de caminata por defecto.", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x, ratio_y);
				sprite_caminar_ok = false;
				break;
			}
			int y = frames_caminar[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite de caminata por defecto", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x, ratio_y);
				sprite_caminar_ok = false;
				break;
			}
			int alto = frames_caminar[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto del frame o es negativo. Se genera el sprite de caminata por defecto.", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x, ratio_y);
				sprite_caminar_ok = false;
				break;
			}
			int ancho = frames_caminar[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el ancho del frame o es negativo. Se genera el sprite de caminata por defecto.", LOG_ERROR );
				sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x, ratio_y);
				sprite_caminar_ok = false;
				break;
			}
			framesCaminar[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje caminando.", LOG_DEBUG );
			bool loop = frames_caminar[i].get( "loop", false ).asBool();
			if ( loop ) {
				loop_caminar[i] = true;
			}
		}
		if ( sprite_caminar_ok ) {
			try {
				sprite_caminar = new Sprite( ruta_carpeta + spritesheet_caminar, framesCaminar, ventana );
				for ( unsigned int j=0; j < framesCaminar.size(); j++ ) {
					if ( loop_caminar[j] ) sprite_caminar->setLoop(j);
				}
				log( "Se creo correctamente el sprite para el personaje caminando.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x, ratio_y);
				log( "No se pudo abrir el spritesheet del personaje caminando. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
		sprites.push_back( sprite_caminar );
	}

	// Creo Sprites para personaje saltando.
	Sprite* sprite_saltar;
	bool sprite_saltar_ok = true;
	if ( root.get( "saltar", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje saltando. Se genera el sprite de salto por defecto.", LOG_ERROR );
		sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x, ratio_y);
		sprite_saltar_ok = false;

	} else {
		string spritesheet_saltar = root["saltar"].get( "ruta", SPRITESHEET_SALTAR_DEFAULT ).asString();
		const Json::Value frames_saltar = root["saltar"]["frames"];
		vector<Frame*> framesSaltar( frames_saltar.size() );
		vector<bool> loop_saltar(framesSaltar.size(), false);
		for ( unsigned int i=0; i < frames_saltar.size(); i++ ) {
			int x = frames_saltar[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite del salto por defecto.", LOG_ERROR );
				sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_ok = false;
				break;
			}
			int y = frames_saltar[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite del salto por defecto.", LOG_ERROR );
				sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_ok = false;
				break;
			}
			int alto = frames_saltar[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto del frame o es negativo. Se genera el sprite del salto por defecto.", LOG_ERROR );
				sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_ok = false;
				break;
			}
			int ancho = frames_saltar[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el ancho del frame o es negativo. Se genera el sprite del salto por defecto.", LOG_ERROR );
				sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_ok = false;
				break;
			}
			framesSaltar[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje saltando horizontalmente.", LOG_DEBUG );
			bool loop = frames_saltar[i].get( "loop", false ).asBool();
			if ( loop ) {
				loop_saltar[i] = true;
			}
		}
		if ( sprite_saltar_ok ) {
			try {
				sprite_saltar = new Sprite( ruta_carpeta + spritesheet_saltar, framesSaltar, ventana );
				for ( unsigned int j=0; j < framesSaltar.size(); j++ ) {
					if ( loop_saltar[j] ) sprite_saltar->setLoop(j);
				}
				log( "Se creo correctamente el sprite para el personaje saltando.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x, ratio_y);
				log( "No se pudo abrir el spritesheet del personaje saltando. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
		sprites.push_back( sprite_saltar );
	}

	// Creo Sprite para personaje saltando en diagonal.
	Sprite* sprite_saltar_diagonal;
	bool sprite_saltar_diagonal_ok = true;
	if ( root.get( "saltardiagonal", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje saltando en diagonal. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
		sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y);
		sprite_saltar_diagonal_ok = false;
	} else {
		string spritesheet_saltar_diagonal = root["saltardiagonal"].get( "ruta", SPRITESHEET_SALTAR_DIAGONAL_DEFAULT ).asString();
		const Json::Value frames_saltar_diagonal = root["saltardiagonal"]["frames"];
		vector<Frame*> framesSaltarDiagonal( frames_saltar_diagonal.size() );
		vector<bool> loop_saltar_diagonal(framesSaltarDiagonal.size(), false);
		for ( unsigned int i=0; i < frames_saltar_diagonal.size(); i++ ) {
			int x = frames_saltar_diagonal[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
				sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_diagonal_ok = false;
				break;
			}
			int y = frames_saltar_diagonal[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
				sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_diagonal_ok = false;
				break;
			}
			int alto = frames_saltar_diagonal[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto del frame o es negativo. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
				sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_diagonal_ok = false;
				break;
			}
			int ancho = frames_saltar_diagonal[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el ancho del frame o es negativo. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
				sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y);
				sprite_saltar_diagonal_ok = false;
				break;
			}
			framesSaltarDiagonal[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje saltando en diagonal.", LOG_DEBUG );
			bool loop = frames_saltar_diagonal[i].get( "loop", false ).asBool();
			if ( loop ) {
				loop_saltar_diagonal[i] = true;
			}
		}
		if ( sprite_saltar_diagonal_ok ) {
			try {
				sprite_saltar_diagonal = new Sprite( ruta_carpeta + spritesheet_saltar_diagonal, framesSaltarDiagonal, ventana );
				for ( unsigned int j=0; j < framesSaltarDiagonal.size(); j++ ) {
					if ( loop_saltar_diagonal[j] ) sprite_saltar_diagonal->setLoop(j);
				}
				log( "Se creo correctamente el sprite para el personaje saltando en diagonal.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x, ratio_y);
				log( "No se pudo abrir el spritesheet del personaje saltando en diagonal. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
		sprites.push_back( sprite_saltar_diagonal );
	}

	// Creo Sprite para personaje agachado.
	Sprite* sprite_agachar;
	bool sprite_agachar_ok = true;
	if ( root.get( "agachar", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje agachado. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
		sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x, ratio_y);
		sprite_agachar_ok = false;
	} else {
		string spritesheet_agachar = root["agachar"].get( "ruta", SPRITESHEET_AGACHAR_DEFAULT ).asString();
		const Json::Value frames_agachar = root["agachar"]["frames"];
		vector<Frame*> framesAgachar( frames_agachar.size() );
		vector<bool> loop_agachar(framesAgachar.size(), false);
		for ( unsigned int i=0; i < frames_agachar.size(); i++ ) {
			int x = frames_agachar[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
				sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x, ratio_y);
				sprite_agachar_ok = false;
				break;
			}
			int y = frames_agachar[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
				sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x, ratio_y);
				sprite_agachar_ok = false;
				break;
			}
			int alto = frames_agachar[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto del frame o es negativo. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
				sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x, ratio_y);
				sprite_agachar_ok = false;
				break;
			}
			int ancho = frames_agachar[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el alto del frame o es negativo. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
				sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x, ratio_y);
				sprite_agachar_ok = false;
				break;
			}
			framesAgachar[i] = new Frame(x/ratio_x, y/ratio_y, alto/ratio_y, ancho/ratio_x);
			log( "Se creo correctamente un frame del spritesheet del personaje agachandose.", LOG_DEBUG );
			bool loop = frames_agachar[i].get( "loop", false ).asBool();
			if ( loop ) {
				loop_agachar[i] = true;
			}
		}
		if ( sprite_agachar_ok ) {
			try {
				sprite_agachar = new Sprite( ruta_carpeta + spritesheet_agachar, framesAgachar, ventana );
				for ( unsigned int j=0; j < framesAgachar.size(); j++ ) {
					if ( loop_agachar[j] ) sprite_agachar->setLoop(j);
				}
				log( "Se creo correctamente el sprite para el personaje agachado.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x, ratio_y);
				log( "No se pudo abrir el spritesheet del personaje agachandose. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
		sprites.push_back( sprite_agachar );
	}

	log( "Se crearon todos los sprites del personaje.", LOG_DEBUG );
	return sprites;

}

Mundo* ParserJSON::cargarMundo() {

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(m_ruta_archivo.c_str());

	// Si no se pudo abrir archivo, generar mundo por defecto.
	if ( ! archivoConfig.is_open() ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo de configuracion JSON, se genera una partida por defecto.", LOG_ERROR );
		return this->generarMundoDefault();
	}
	log ( "Se abrio el archivo JSON de configuración.", LOG_DEBUG );

	// Si no se pudo parsear archivo, generar mundo por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se genera una partida por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return this->generarMundoDefault();
	} else log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON de configuracion.", LOG_DEBUG );

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

	Tiempo* tiempo_combate;
	// Obtener tiempo limite del combate.
	float tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asInt();
	if ( tiempo < 0 ) {
		tiempo_combate = new Tiempo( TIEMPO_DEFAULT) ;
		// Informar al usuario el cambio de tiempo de la ronda.
		log ( "El tiempo no puede ser negativo. Se setea automaticamente en 3 minutos.", LOG_WARNING );
	}
	else {
		// Crear tiempo.
		tiempo_combate = new Tiempo( tiempo );
		log( "Se cargo correctamente el tiempo del combate.", LOG_DEBUG );
	}

	// Obtener dimensiones de la ventana. Se setean por defecto en caso de error.
	// El alto se seteara luego dependiendo del escenario.
	int ventana_ancho_px, ventana_alto_px;
	float ventana_ancho;
	if ( root.get( "ventana", "" ) == "" ) {
		log( "No se encontraron parametros para la creacion de la ventana. Se asignan valores por defecto.", LOG_ERROR );
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		ventana_ancho = VENTANA_ANCHO_DEFAULT;
	} else {
		ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
		if ( ventana_ancho_px < 0 ) {
			ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
			// Informar al usuario el cambio de ancho.
			log( "El ancho en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 512px.", LOG_WARNING );
		} else log( "Se cargo correctamente el ancho en pixeles de la ventana.", LOG_DEBUG );
		ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
		if ( ventana_alto_px < 0 ) {
			ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
			// Informar al usuario el cambio de alto.
			log( "El alto en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 384px.", LOG_WARNING );
		} else log( "Se cargo correctamente el alto en pixeles de la ventana.", LOG_DEBUG );
		ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asFloat();
		if ( ventana_ancho < 0 ) {
			ventana_ancho = VENTANA_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho logico.
			log( "El ancho logico de la ventana no puede ser negativo. Se setea automaticamente a 200.", LOG_WARNING );
		} else log( "Se cargo correctamente el ancho logico de la ventana.", LOG_DEBUG );
	}

	// Obtener las dimensiones logicas del escenario.
	// En caso de error se setean por defecto.
	float escenario_ancho, escenario_alto, y_piso;
	if ( root.get( "escenario", "" ) == "" ) {
		log( "No se encontraron parametros para la creacion del escenario. Se asignan valores por defecto.", LOG_ERROR );
		escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
		escenario_alto = ESCENARIO_ALTO_DEFAULT;
		y_piso = Y_PISO_DEFAULT;
	} else {
		escenario_ancho = root["escenario"].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asFloat();
		if ( escenario_ancho < 0 ) {
			escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
			// Informar al usuario el cambio de ancho logico.
			log( "El ancho del escenario no puede ser negativo. Se setea automaticamente a 600.", LOG_WARNING );
		} else log( "Se cargo correctamente el ancho logico del escenario.", LOG_DEBUG );
		escenario_alto = root["escenario"].get( "alto", ESCENARIO_ALTO_DEFAULT ).asFloat();
		if ( escenario_alto < 0 ) {
			escenario_alto = ESCENARIO_ALTO_DEFAULT;
			// Informar al usuario el cambio de alto logico.
			log( "WARNING: El alto del escenario no puede ser negativo. Se setea automaticamente a 150.", LOG_WARNING );
		} else log( "Se cargo correctamente el alto logico del escenario.", LOG_DEBUG );
		y_piso = root["escenario"].get( "y-piso", Y_PISO_DEFAULT ).asFloat();
		log ( "Se cargo correctamente la altura del piso.", LOG_DEBUG );
	}

	// Setear alto logico de la ventana de acuerdo al alto del escenario.
	float ventana_alto = escenario_alto;
	log ( "Se fijo el alto logico de la ventana.", LOG_DEBUG );

	// Obtener relaciones entre pixeles y unidades logicas del mundo.
	float ratio_x = ventana_ancho_px / ventana_ancho;
	float ratio_y = ventana_alto_px / ventana_alto;
	log ( "Se calcularon las relaciones para el ancho y el alto entre los pixeles y las unidades logicas del mundo.", LOG_DEBUG );

	// Crear Mundo.
	Mundo* nuevo_mundo = new Mundo(escenario_ancho, escenario_alto);
	log ( "Se creo correctamente un mundo vacio", LOG_DEBUG );

	// Agregar tiempo de combate.
	nuevo_mundo->setTiempo( tiempo_combate );

	/************ NO SE USA ESCENARIO
	// Crear Escenario.
	Escenario* escenario = new Escenario();
	*********************************/

	// Crear Ventana y abrirla.
	Ventana* ventana = new Ventana( ventana_ancho_px, ventana_alto_px, ratio_x, ratio_y );
	log ( "Se creo correctamente la ventana (camara)", LOG_DEBUG );
	if( ! ventana->create_window() ) {
		log( "No se puede inicializar la ventana. El programa no puede continuar.", LOG_ERROR );
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}

	// Asigno Ventana al Mundo.
	nuevo_mundo->setVentana(ventana);

	// Obtener las capas del escenario. La primera capa es el fondo del escenario.
	// Se setea por defecto el ancho en caso de error.
	// Si la imagen no existe, se usa una por defecto.
	string background;
	float capa_ancho, capa_alto;
	int capa_z_index;
	if ( root.get( "capas", "" ) == "" ) {
		log( "No se encontraron parametros para la creacion de las capas. Se crea una unica capa y se asignan valores por defecto.", LOG_ERROR );
		background = BACKGROUND_DEFAULT;
		capa_ancho = CAPA_ANCHO_DEFAULT;
		capa_alto = ESCENARIO_ALTO_DEFAULT;
		capa_z_index = CAPA_Z_INDEX_DEFAULT;
		CapaFondo* capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, background, ventana );
		nuevo_mundo->addCapa(capa_fondo, capa_z_index);
	} else {
		const Json::Value capas = root["capas"];
		for ( unsigned int i=0; i < capas.size(); i++ ) {
			background = capas[i].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();
			log( "Se cargo el nombre de la imagen de la capa.", LOG_DEBUG );
			capa_ancho = capas[i].get( "ancho", CAPA_ANCHO_DEFAULT ).asFloat();
			if ( capa_ancho < 0 ) {
				capa_ancho = CAPA_ANCHO_DEFAULT;
				// Informar al usuario el cambio de ancho.
				log( "El ancho de la capa no puede ser negativo. Se setea automaticamente en 600.", LOG_WARNING );
			} else if ( capa_ancho > escenario_ancho ) {
				capa_ancho = CAPA_ANCHO_DEFAULT;
				// Informar al usuario el cambio de ancho.
				log ( "El ancho de la capa no puede superar el del escenario. Se setea automaticamente en 600.", LOG_WARNING );
			} else log( "Se cargo correctamente el ancho logico de la capa.", LOG_DEBUG );
			capa_z_index = capas[i].get( "z-index", CAPA_Z_INDEX_DEFAULT + i ).asInt();
			log ( "Se cargo el z-index de la capa.", LOG_DEBUG );

			// Setear alto logico de la capa de acuerdo al alto del escenario.
			float capa_alto = escenario_alto;
			log ( "Se fijo el alto logico de la capa.", LOG_DEBUG );

			// Creo capas de fondo.
			CapaFondo* capa_fondo;
			try {
				capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, background, ventana );
				log( "Se creo correctamente la capa.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, BACKGROUND_DEFAULT, ventana );
				log( "No se pudo cargar la imagen de la capa. Se carga imagen por defecto. " + string(e.what()), LOG_ERROR );
			}

			// Agrego capa al mundo.
			nuevo_mundo->addCapa(capa_fondo, capa_z_index);
			log( "Se agrego la capa al mundo.", LOG_DEBUG );
		}
	}

	// Obtener el personaje.
	// Si no se especifica o no se encuentra la carpeta de sprites del personaje, se usa una por defecto.
	// Si no se especifica el z-index se fija uno por defecto.
	int personaje_z_index;
	string personaje_carpeta_sprites, personaje_nombre;
	if ( root.get( "personaje", "" ) == "" ) {
		personaje_z_index = PERSONAJE_Z_INDEX_DEFAULT;
		personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
		personaje_nombre = PERSONAJE_NOMBRE_DEFAULT;
	} else {
		personaje_z_index = root["personaje"].get( "z-index", PERSONAJE_Z_INDEX_DEFAULT ).asInt();
		log ( "Se cargo correctamente el z-index del personaje.", LOG_DEBUG );
		personaje_carpeta_sprites = root["personaje"].get( "sprites", PERSONAJE_CARPETA_SPRITES_DEFAULT ).asString();
		log ( "Se cargo correctamente la ruta a la carpeta contenedora de los sprites del personaje.", LOG_DEBUG );
		personaje_nombre = root["personaje"].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
		log ( "Se cargo el nombre del personaje.", LOG_DEBUG );
	}

	// Creo Sprites del personaje.
	vector<Sprite*> sprites = cargarSprites(personaje_carpeta_sprites, ventana, ratio_x, ratio_y);

	// Crear personaje.
	Personaje* personaje = new Personaje(personaje_nombre, sprites, PERSONAJE_VELOCIDAD);
	log( "Se creo correctamente el personaje.", LOG_DEBUG );

	// Indico posicion inicial del personaje.
	personaje->setPosition( (escenario_ancho/2), y_piso );

	// Agrego Personaje al mundo.
	nuevo_mundo->addPersonaje(personaje);
	log( "Se agrego el personaje al mundo", LOG_DEBUG );

	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personaje_z_index, escenario_ancho, ventana_ancho, PERSONAJE_VELOCIDAD, personaje );
	log( "Se creo correctamente la capa principal.", LOG_DEBUG );

	// Agrego capa principal al mundo.
	nuevo_mundo->addCapaPrincipal( capa_principal, personaje_z_index );
	log( "Se agrego la capa principal al mundo.", LOG_DEBUG );

	return nuevo_mundo;


	// PERSONAJE SE LE PASA VELOCIDAD_PERSONAJE POR CONSTRUCTOR PERO NUNCA LO USA.
	// CAPA PRINCIPAL RECIBE DOS VECES EL MISMO PARAMETRO, EL ANCHO DEL ESCENARIO!!!
	// EL ESCENARIO NI LO USAMOS, PARA QUE ESTA?

}

