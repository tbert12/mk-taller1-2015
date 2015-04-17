#include "ParserJSON.h"

#define LOGLVL_DEFAULT 2
#define TIEMPO_DEFAULT 180
#define VENTANA_ANCHO_PX_DEFAULT 512
#define VENTANA_ALTO_PX_DEFAULT 384
#define VENTANA_ANCHO_DEFAULT 200.0
#define ESCENARIO_ANCHO_DEFAULT 600.0
#define ESCENARIO_ALTO_DEFAULT 150.0
#define Y_PISO_DEFAULT 135.0
#define BACKGROUND_DEFAULT "data/img/background/default/unknown.png"
#define CAPA_0_BACKGROUND_DEFAULT "data/img/background/default/background_0.png"
#define CAPA_1_BACKGROUND_DEFAULT "data/img/background/default/background_1.png"
#define CAPA_2_BACKGROUND_DEFAULT "data/img/background/default/background_2.png"
#define CAPA_0_ANCHO_DEFAULT 200.0
#define CAPA_1_ANCHO_DEFAULT 226.6
#define CAPA_2_ANCHO_DEFAULT 600.0
#define CAPA_Z_INDEX_DEFAULT 0
#define PERSONAJE_Z_INDEX_DEFAULT 3
#define PERSONAJE_CARPETA_SPRITES_DEFAULT "data/players/default/sprites/"
#define PERSONAJE_NOMBRE_DEFAULT "Jugador"
#define PERSONAJE_FLIPPED_DEFAULT false
#define PERSONAJE_ANCHO_PX_DEFAULT 72
#define PERSONAJE_ALTO_PX_DEFAULT 133
#define PERSONAJE_ANCHO_DEFAULT 40
#define PERSONAJE_ALTO_DEFAULT 70

#define SPRITESHEET_PARADO_DEFAULT "initial.png"
#define SPRITESHEET_CAMINAR_DEFAULT "walk.png"
#define SPRITESHEET_SALTAR_DEFAULT "salto.png"
#define SPRITESHEET_SALTAR_DIAGONAL_DEFAULT "diag.png"
#define SPRITESHEET_AGACHAR_DEFAULT "agachar.png"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
}

ParserJSON::~ParserJSON() {
}

Sprite* ParserJSON::crearSpriteParadoDefault(Ventana* ventana, float personaje_ancho, float personaje_alto) {
	vector<Frame*> framesParado(9);

	int wParado = PERSONAJE_ANCHO_PX_DEFAULT;
	for ( int i=0; i < 9; i++ ){
		framesParado[i] = new Frame( wParado*i, 0, PERSONAJE_ALTO_PX_DEFAULT, wParado );
	}

	// Calculo ratios para el personaje.
	float ratio_x_personaje = PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	float ratio_y_personaje = PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;

	Sprite* spriteParado = new Sprite( string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + string(SPRITESHEET_PARADO_DEFAULT), framesParado, ventana, ratio_x_personaje, ratio_y_personaje );
	return spriteParado;
}

Sprite* ParserJSON::crearSpriteCaminarDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje ) {
	vector<Frame*> framesCaminar(9);

	int wParado = 68;
	for ( int i=0; i < 9; i++ ){
		framesCaminar[i] = new Frame( wParado*i, 0, PERSONAJE_ALTO_PX_DEFAULT, wParado );
	}

	Sprite* spriteCaminar = new Sprite( string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + string(SPRITESHEET_CAMINAR_DEFAULT), framesCaminar, ventana, ratio_x_personaje, ratio_y_personaje );
	return spriteCaminar;
}

Sprite* ParserJSON::crearSpriteSaltarDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje ) {
	vector<Frame*> framesSaltar(3);

	vector<int> xSaltar = { 0, 71, 141 };
	vector<int> hSaltar = { 139, 96, 107 };
	vector<int> wSaltar = { 69, 70, 60 };

	for ( int i=0; i < 3; i++ ) {
		framesSaltar[i] = new Frame( xSaltar[i], 0, hSaltar[i], wSaltar[i] );
	}

	Sprite* spriteSaltar = new Sprite( string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + string(SPRITESHEET_SALTAR_DEFAULT), framesSaltar, ventana, ratio_x_personaje, ratio_y_personaje );
	spriteSaltar->setLoop(1);
	return spriteSaltar;
}

Sprite* ParserJSON::crearSpriteSaltarDiagonalDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje) {
	vector<Frame*> framesSaltarDiagonal(8);

	vector<int> xSaltarDiagonal = { 0, 72, 127, 208, 283, 335, 392, 472 };
	vector<int> hSaltarDiagonal = { 136, 82, 59, 55, 81, 81, 59, 62 };
	vector<int> wSaltarDiagonal = { 72, 55, 74, 74, 53, 55, 75, 74 };

	for ( int i=0; i < 8; i++ ) {
		framesSaltarDiagonal[i] = new Frame( xSaltarDiagonal[i], 0, hSaltarDiagonal[i], wSaltarDiagonal[i] );
	}

	Sprite* spriteSaltarDiagonal = new Sprite( string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + string(SPRITESHEET_SALTAR_DIAGONAL_DEFAULT), framesSaltarDiagonal, ventana, ratio_x_personaje, ratio_y_personaje );
	return spriteSaltarDiagonal;
}

Sprite* ParserJSON::crearSpriteAgacharDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje) {
	vector<Frame*> framesAgachar(3);

	vector<int> xAgachar = { 0, 60, 122 };
	vector<int> hAgachar = { 107, 89, 71 };
	vector<int> wAgachar = { 69, 62, 64 };

	for ( int i=0; i < 3; i++ ) {
		framesAgachar[i] = new Frame( xAgachar[i], 0, hAgachar[i], wAgachar[i] );
	}

	Sprite* spriteAgachar = new Sprite( string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + string(SPRITESHEET_AGACHAR_DEFAULT), framesAgachar, ventana, ratio_x_personaje, ratio_y_personaje );
	spriteAgachar->setLoop(2);
	return spriteAgachar;
}

vector<Sprite*> ParserJSON::generarSpritesDefault( Ventana* ventana, float personaje_ancho, float personaje_alto ) {
	vector<Sprite*> sprites;

	sprites.push_back( crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto) );

	// Calculo ratios para el personaje en base a las dimensiones del sprite inicial.
	float ratio_x_personaje = PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	float ratio_y_personaje = PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;

	sprites.push_back( crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje) );

	return sprites;
}

Mundo* ParserJSON::generarMundoDefault( ) {

	float ratio_x = VENTANA_ANCHO_PX_DEFAULT/VENTANA_ANCHO_DEFAULT;
	float ratio_y = VENTANA_ALTO_PX_DEFAULT/ESCENARIO_ALTO_DEFAULT;

	Mundo* mundo = new Mundo(ESCENARIO_ANCHO_DEFAULT,ESCENARIO_ALTO_DEFAULT);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT,ratio_x,ratio_y);

	if( ! ventana->create_window() ) {
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}

	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault(ventana,PERSONAJE_ANCHO_DEFAULT,PERSONAJE_ALTO_DEFAULT), PERSONAJE_VELOCIDAD, PERSONAJE_FLIPPED_DEFAULT);

	personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2),Y_PISO_DEFAULT);

	mundo->setVentana(ventana);
	mundo->setTiempo(new Tiempo(TIEMPO_DEFAULT));

	mundo->addPersonaje(personaje_default);

	CapaFondo* capa_0 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_0_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_0_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_0,CAPA_Z_INDEX_DEFAULT);
	CapaFondo* capa_1 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_1_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+1,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_1_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_1,CAPA_Z_INDEX_DEFAULT+1);
	CapaFondo* capa_2 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_2_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+2,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_2_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_2,CAPA_Z_INDEX_DEFAULT+2);

	CapaPrincipal* capa_principal = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,VENTANA_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,personaje_default);
	mundo->addCapaPrincipal(capa_principal,PERSONAJE_Z_INDEX_DEFAULT);

	return mundo;
}

vector<Sprite*> ParserJSON::cargarSprites(string ruta_carpeta, Ventana* ventana, float personaje_ancho, float personaje_alto) {

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
		return generarSpritesDefault(ventana, personaje_ancho, personaje_alto);
	}
	log ( "Se abrio el archivo JSON de sprites.", LOG_DEBUG );

	// Si no se pudo parsear archivo, generar mundo por defecto.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se generan sprites por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return generarSpritesDefault(ventana, personaje_ancho, personaje_alto);
	} else log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON de sprites.", LOG_DEBUG );

	// Calculo por defecto los ratios del personaje. Seran modificados al cargar el sprite inicial.
	float ratio_x_personaje = PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	float ratio_y_personaje = PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;

	// Creo Sprite para personaje parado.
	Sprite* sprite_parado;
	bool sprite_parado_ok = true;
	string spritesheet_parado;
	if ( root.get( "parado", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje parado. Se genera el sprite inicial por defecto.", LOG_ERROR );
		sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
	} else {
		if ( root["parado"].get( "nombre", "" ) == "" ) {
			spritesheet_parado = SPRITESHEET_PARADO_DEFAULT;
			log( "No se especifico el nombre de la imagen para el spritesheet del personaje parado. Se setea uno por defecto.", LOG_WARNING );
		} else {
			try {
				spritesheet_parado = root["parado"].get( "nombre", SPRITESHEET_PARADO_DEFAULT ).asString();
			} catch ( exception &e ) {
				spritesheet_parado = SPRITESHEET_PARADO_DEFAULT;
				log( "El nombre ingresado del spritesheet para el personaje parado no es una cadena de texto. Se setea un nombre por defecto.", LOG_ERROR );
			}
		}
		if ( root["parado"].get( "frames", "" ) == "" ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet para el jugador parado. Se genera el sprite inicial por defecto.", LOG_ERROR );
			sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
		} else {
			const Json::Value frames_parado = root["parado"]["frames"];
			vector<Frame*> framesParado( frames_parado.size() );
			vector<bool> loop_parado(framesParado.size(), false);
			for ( unsigned int i=0; i < frames_parado.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_parado[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite inicial por defecto.", LOG_ERROR );
						sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
						sprite_parado_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada es invalida y no puede ser convertida a un numero. Se genera el sprite inicial por defecto.", LOG_ERROR );
					sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
					sprite_parado_ok = false;
					break;
				}
				try {
					y = frames_parado[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite inicial por defecto", LOG_ERROR );
						sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
						sprite_parado_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada es invalida y no puede ser convertida a un numero. Se genera el sprite inicial por defecto.", LOG_ERROR );
					sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
					sprite_parado_ok = false;
					break;
				}
				try {
					alto = frames_parado[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite inicial por defecto.", LOG_ERROR );
						sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
						sprite_parado_ok = false;
						break;
					}
					// Actualizo el ratio y del personaje de acuerdo al alto en pixeles de los frames del sprite inicial (el alto es constante mientras esta parado).
					ratio_y_personaje = alto / personaje_alto;
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite inicial por defecto.", LOG_ERROR );
					sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
					sprite_parado_ok = false;
					break;
				}
				try {
					ancho = frames_parado[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el ancho del frame o es negativo. Se genera el sprite inicial por defecto.", LOG_ERROR );
						sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
						sprite_parado_ok = false;
						break;
					}
					// Actualizo el ratio x del personaje de acuerdo al ancho en pixeles de los frames del sprite inicial (el ancho es constante mientras esta parado).
					ratio_x_personaje = ancho / personaje_ancho;
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite inicial por defecto.", LOG_ERROR );
					sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
					sprite_parado_ok = false;
					break;
				}
				bool loop;
				try {
					loop = frames_parado[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite inicial. Se setea en false por defecto.", LOG_ERROR );
					loop = false;
				}
				if ( loop ) {
					loop_parado[i] = true;
				}
				framesParado[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet del personaje parado.", LOG_DEBUG );
			}
			if ( sprite_parado_ok ) {
				try {
					sprite_parado = new Sprite( ruta_carpeta + spritesheet_parado, framesParado, ventana, ratio_x_personaje, ratio_y_personaje);
					for ( unsigned int j=0; j < framesParado.size(); j++ ) {
						if ( loop_parado[j] ) sprite_parado->setLoop(j);
					}
					log( "Se creo correctamente el sprite para el personaje parado.", LOG_DEBUG );
				} catch ( CargarImagenException &e ) {
					delete sprite_parado;
					sprite_parado = crearSpriteParadoDefault(ventana, personaje_ancho, personaje_alto);
					log( "No se pudo abrir el spritesheet del personaje parado. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
				}
			}
		}
		sprites.push_back( sprite_parado );
	}

	// Creo Sprite para personaje caminando.
	Sprite* sprite_caminar;
	bool sprite_caminar_ok = true;
	string spritesheet_caminar;
	if ( root.get( "caminar", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje caminando. Se genera el sprite de caminata por defecto.", LOG_ERROR );
		sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
	} else {
		if ( root["caminar"].get( "nombre", "" ) == "" ) {
			spritesheet_caminar = SPRITESHEET_CAMINAR_DEFAULT;
			log( "No se especifico el nombre de la imagen para el spritesheet del personaje caminando. Se setea uno por defecto.", LOG_WARNING );
		} else {
			try {
				spritesheet_caminar = root["caminar"].get( "nombre", SPRITESHEET_CAMINAR_DEFAULT ).asString();
			} catch (exception &e) {
				spritesheet_caminar = SPRITESHEET_CAMINAR_DEFAULT;
				log( "El nombre ingresado del spritesheet para el personaje caminando no es una cadena de texto. Se setea un nombre por defecto.", LOG_ERROR );
			}
		}
		if ( root["caminar"].get( "frames", "" ) == "" ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet para el jugador caminando. Se genera el sprite de caminar por defecto.", LOG_ERROR );
			sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
		} else {
			const Json::Value frames_caminar = root["caminar"]["frames"];
			vector<Frame*> framesCaminar( frames_caminar.size() );
			vector<bool> loop_caminar(framesCaminar.size(), false);
			for ( unsigned int i=0; i < frames_caminar.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_caminar[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite de caminata por defecto.", LOG_ERROR );
						sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_caminar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de caminar por defecto.", LOG_ERROR );
					sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_caminar_ok = false;
					break;
				}
				try {
					y = frames_caminar[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite de caminata por defecto", LOG_ERROR );
						sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_caminar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada es invalida y no puede ser convertida a un numero. Se genera el sprite de caminar por defecto.", LOG_ERROR );
					sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_caminar_ok = false;
					break;
				}
				try {
					alto = frames_caminar[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite de caminata por defecto.", LOG_ERROR );
						sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_caminar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de caminar por defecto.", LOG_ERROR );
					sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_caminar_ok = false;
					break;
				}
				try {
					ancho = frames_caminar[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el ancho del frame o es negativo. Se genera el sprite de caminata por defecto.", LOG_ERROR );
						sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_caminar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de caminar por defecto.", LOG_ERROR );
					sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_caminar_ok = false;
					break;
				}
				bool loop;
				try {
					loop = frames_caminar[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite de caminar. Se setea en false por defecto.", LOG_ERROR );
					loop = false;
				}
				if ( loop ) {
					loop_caminar[i] = true;
				}
				framesCaminar[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet del personaje caminando.", LOG_DEBUG );
			}
			if ( sprite_caminar_ok ) {
				try {
					sprite_caminar = new Sprite( ruta_carpeta + spritesheet_caminar, framesCaminar, ventana, ratio_x_personaje, ratio_y_personaje );
					for ( unsigned int j=0; j < framesCaminar.size(); j++ ) {
						if ( loop_caminar[j] ) sprite_caminar->setLoop(j);
					}
					log( "Se creo correctamente el sprite para el personaje caminando.", LOG_DEBUG );
				} catch ( CargarImagenException &e ) {
					delete sprite_caminar;
					sprite_caminar = crearSpriteCaminarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					log( "No se pudo abrir el spritesheet del personaje caminando. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
				}
			}
		}
		sprites.push_back( sprite_caminar );
	}

	// Creo Sprites para personaje saltando.
	Sprite* sprite_saltar;
	bool sprite_saltar_ok = true;
	string spritesheet_saltar;
	if ( root.get( "saltar", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje saltando. Se genera el sprite de salto por defecto.", LOG_ERROR );
		sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
	} else {
		if ( root["saltar"].get( "nombre", "" ) == "" ) {
			spritesheet_saltar = SPRITESHEET_SALTAR_DEFAULT;
			log( "No se especifico el nombre de la imagen para el spritesheet del personaje saltando. Se setea uno por defecto.", LOG_WARNING );
		} else {
			try {
				spritesheet_saltar = root["saltar"].get( "nombre", SPRITESHEET_SALTAR_DEFAULT ).asString();
			} catch (exception &e) {
				spritesheet_saltar = SPRITESHEET_SALTAR_DEFAULT;
				log( "El nombre ingresado del spritesheet para el personaje saltando no es una cadena de texto. Se setea un nombre por defecto.", LOG_ERROR );
			}
		}
		if ( root["saltar"].get( "frames", "" ) == "" ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet para el jugador saltando. Se genera el sprite de salto por defecto.", LOG_ERROR );
			sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
		} else {
			const Json::Value frames_saltar = root["saltar"]["frames"];
			vector<Frame*> framesSaltar( frames_saltar.size() );
			vector<bool> loop_saltar(framesSaltar.size(), false);
			for ( unsigned int i=0; i < frames_saltar.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_saltar[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite del salto por defecto.", LOG_ERROR );
						sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de saltar por defecto.", LOG_ERROR );
					sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_ok = false;
					break;
				}
				try {
					y = frames_saltar[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite del salto por defecto.", LOG_ERROR );
						sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de saltar por defecto.", LOG_ERROR );
					sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_ok = false;
					break;
				}
				try {
					alto = frames_saltar[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite del salto por defecto.", LOG_ERROR );
						sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de saltar por defecto.", LOG_ERROR );
					sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_ok = false;
					break;
				}
				try {
					ancho = frames_saltar[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el ancho del frame o es negativo. Se genera el sprite del salto por defecto.", LOG_ERROR );
						sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de saltar por defecto.", LOG_ERROR );
					sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_ok = false;
					break;
				}
				bool loop;
				try {
					loop = frames_saltar[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite de salto. Se setea en false por defecto.", LOG_ERROR );
					loop = false;
				}
				if ( loop ) {
					loop_saltar[i] = true;
				}
				framesSaltar[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet del personaje saltando verticalmente.", LOG_DEBUG );
			}
			if ( sprite_saltar_ok ) {
				try {
					sprite_saltar = new Sprite( ruta_carpeta + spritesheet_saltar, framesSaltar, ventana, ratio_x_personaje, ratio_y_personaje );
					for ( unsigned int j=0; j < framesSaltar.size(); j++ ) {
						if ( loop_saltar[j] ) sprite_saltar->setLoop(j);
					}
					log( "Se creo correctamente el sprite para el personaje saltando.", LOG_DEBUG );
				} catch ( CargarImagenException &e ) {
					delete sprite_saltar;
					sprite_saltar = crearSpriteSaltarDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					log( "No se pudo abrir el spritesheet del personaje saltando. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
				}
			}
		}
		sprites.push_back( sprite_saltar );
	}

	// Creo Sprite para personaje saltando en diagonal.
	Sprite* sprite_saltar_diagonal;
	bool sprite_saltar_diagonal_ok = true;
	string spritesheet_saltar_diagonal;
	if ( root.get( "saltardiagonal", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje saltando en diagonal. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
		sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
	} else {
		if ( root["saltardiagonal"].get( "nombre", "" ) == "" ) {
			spritesheet_saltar_diagonal = SPRITESHEET_SALTAR_DIAGONAL_DEFAULT;
			log( "No se especifico el nombre de la imagen para el spritesheet del personaje saltando en diagonal. Se setea uno por defecto.", LOG_WARNING );
		} else {
			try {
				spritesheet_saltar_diagonal = root["saltardiagonal"].get( "nombre", SPRITESHEET_SALTAR_DIAGONAL_DEFAULT ).asString();
			} catch (exception &e) {
				spritesheet_saltar_diagonal = SPRITESHEET_SALTAR_DIAGONAL_DEFAULT;
				log( "El nombre ingresado del spritesheet para el personaje saltando en diagonal no es una cadena de texto. Se setea un nombre por defecto.", LOG_ERROR );
			}
		}
		if ( root["saltardiagonal"].get( "frames", "" ) == "" ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet para el jugador saltando en diagonal. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
			sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
		} else {
			const Json::Value frames_saltar_diagonal = root["saltardiagonal"]["frames"];
			vector<Frame*> framesSaltarDiagonal( frames_saltar_diagonal.size() );
			vector<bool> loop_saltar_diagonal(framesSaltarDiagonal.size(), false);
			for ( unsigned int i=0; i < frames_saltar_diagonal.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_saltar_diagonal[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
						sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_diagonal_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
					sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_diagonal_ok = false;
					break;
				}
				try {
					y = frames_saltar_diagonal[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
						sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_diagonal_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
					sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_diagonal_ok = false;
					break;
				}
				try {
					alto = frames_saltar_diagonal[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
						sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_diagonal_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
					sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_diagonal_ok = false;
					break;
				}
				try {
					ancho = frames_saltar_diagonal[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el ancho del frame o es negativo. Se genera el sprite del salto en diagonal por defecto.", LOG_ERROR );
						sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_saltar_diagonal_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de salto en diagonal por defecto.", LOG_ERROR );
					sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_saltar_diagonal_ok = false;
					break;
				}
				bool loop;
				try {
					loop = frames_saltar_diagonal[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite de salto en diagonal. Se setea en false por defecto.", LOG_ERROR );
					loop = false;
				}
				if ( loop ) {
					loop_saltar_diagonal[i] = true;
				}
				framesSaltarDiagonal[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet del personaje saltando en diagonal.", LOG_DEBUG );
			}
			if ( sprite_saltar_diagonal_ok ) {
				try {
					sprite_saltar_diagonal = new Sprite( ruta_carpeta + spritesheet_saltar_diagonal, framesSaltarDiagonal, ventana, ratio_x_personaje, ratio_y_personaje );
					for ( unsigned int j=0; j < framesSaltarDiagonal.size(); j++ ) {
						if ( loop_saltar_diagonal[j] ) sprite_saltar_diagonal->setLoop(j);
					}
					log( "Se creo correctamente el sprite para el personaje saltando en diagonal.", LOG_DEBUG );
				} catch ( CargarImagenException &e ) {
					delete sprite_saltar_diagonal;
					sprite_saltar_diagonal = crearSpriteSaltarDiagonalDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					log( "No se pudo abrir el spritesheet del personaje saltando en diagonal. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
				}
			}
		}
		sprites.push_back( sprite_saltar_diagonal );
	}

	// Creo Sprite para personaje agachado.
	Sprite* sprite_agachar;
	bool sprite_agachar_ok = true;
	string spritesheet_agachar;
	if ( root.get( "agachar", "" ) == "" ) {
		log( "No se encontro el sprite correspondiente al personaje agachado. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
		sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
	} else {
		if ( root["agachar"].get( "nombre", "" ) == "" ) {
			spritesheet_agachar = SPRITESHEET_AGACHAR_DEFAULT;
			log( "No se especifico el nombre de la imagen para el spritesheet del personaje agachandose. Se setea uno por defecto.", LOG_WARNING );
		} else {
			try {
			spritesheet_agachar = root["agachar"].get( "nombre", SPRITESHEET_AGACHAR_DEFAULT ).asString();
			} catch (exception &e) {
				spritesheet_agachar = SPRITESHEET_AGACHAR_DEFAULT;
				log( "El nombre ingresado del spritesheet para el personaje agachado no es una cadena de texto. Se setea un nombre por defecto.", LOG_ERROR );
			}
		}
		if ( root["agachar"].get( "frames", "" ) == "" ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet para el jugador agachandose. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
			sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
		} else {
			const Json::Value frames_agachar = root["agachar"]["frames"];
			vector<Frame*> framesAgachar( frames_agachar.size() );
			vector<bool> loop_agachar(framesAgachar.size(), false);
			for ( unsigned int i=0; i < frames_agachar.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_agachar[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
						sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_agachar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
					sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_agachar_ok = false;
					break;
				}
				try {
					y = frames_agachar[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
						sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_agachar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
					sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_agachar_ok = false;
					break;
				}
				try {
					alto = frames_agachar[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
						sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_agachar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
					sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_agachar_ok = false;
					break;
				}
				try {
					ancho = frames_agachar[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
						sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
						sprite_agachar_ok = false;
						break;
					}
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de agacharse por defecto.", LOG_ERROR );
					sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					sprite_agachar_ok = false;
					break;
				}
				bool loop;
				try {
					loop = frames_agachar[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite de salto en diagonal. Se setea en false por defecto.", LOG_ERROR );
					loop = false;
				}
				if ( loop ) {
					loop_agachar[i] = true;
				}
				framesAgachar[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet del personaje agachandose.", LOG_DEBUG );
			}
			if ( sprite_agachar_ok ) {
				try {
					sprite_agachar = new Sprite( ruta_carpeta + spritesheet_agachar, framesAgachar, ventana, ratio_x_personaje, ratio_y_personaje );
					for ( unsigned int j=0; j < framesAgachar.size(); j++ ) {
						if ( loop_agachar[j] ) sprite_agachar->setLoop(j);
					}
					log( "Se creo correctamente el sprite para el personaje agachado.", LOG_DEBUG );
				} catch ( CargarImagenException &e ) {
					delete sprite_agachar;
					sprite_agachar = crearSpriteAgacharDefault(ventana, ratio_x_personaje, ratio_y_personaje);
					log( "No se pudo abrir el spritesheet del personaje agachandose. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
				}
			}
		}
		sprites.push_back( sprite_agachar );
	}

	log( "Se crearon todos los sprites del personaje.", LOG_DEBUG );
	return sprites;

}

Mundo* ParserJSON::cargarMundo() {

	// Variables para poder registrar los errores/warnings luego de setear el nivel de bitacora.
	bool error_abrir_archivo = false;
	bool json_invalido = false;
	bool loglvl_no_seteado = false;
	bool loglvl_invalido = false;

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(m_ruta_archivo.c_str());

	// Si no se pudo abrir archivo, generar mundo por defecto.
	if ( ! archivoConfig.is_open() ) {
		error_abrir_archivo = true;
	} else {
		// Si no se pudo parsear archivo, generar mundo por defecto.
		bool exito = reader.parse( archivoConfig, root, false );
		if ( ! exito ) {
			json_invalido = true;
		}
		// Cerrar archivo.
		archivoConfig.close();

		// Obtener el nivel de detalle de la bitacora. Si no se especifica
		// se considera nivel DEBUG por defecto, que es el mas completo y reporta cada
		// evento del programa.
		int loglvl;
		if ( root.get( "loglvl", "" ) == "" ) {
			loglvl = LOGLVL_DEFAULT;
			loglvl_no_seteado = true;
		} else {
			loglvl = root.get( "loglvl", LOGLVL_DEFAULT ).asInt();
			if ( loglvl > 2 ) {
				loglvl = LOGLVL_DEFAULT;
				loglvl_invalido = true;
			}
		}
		// Setear nivel de logging del programa.
		nivel = loglvl;
	}

	// Indicar modo de registro en bitacora del programa.
	indicarModo();

	// Registrar sucesos anteriores al seteo del nivel de logging.
	log( string("Se cargara el archivo de configuracion JSON: " + m_ruta_archivo), LOG_DEBUG );

	if ( error_abrir_archivo ) {
		log( "No se pudo abrir el archivo de configuracion JSON, se genera una partida por defecto.", LOG_ERROR );
		return generarMundoDefault();
	}
	if ( json_invalido ) {
	    log( "No se pudo interpretar el JSON, se genera una partida por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return generarMundoDefault();
	}
	if ( loglvl_no_seteado ) {
		log( "No se especifico el nivel de logging. Se setea en modo DEBUG por defecto.", LOG_WARNING );

	}
	if ( loglvl_invalido ) {
		log ( " Nivel de logging incorrecto. Los niveles de logging son: 0-ERRORES, 1-WARNINGS/ERRORES, 2-SUCESOS/WARNINGS/ERRORES (DEBUG). Se setea por defecto nivel DEBUG.", LOG_WARNING );

	}

	log ( "Se abrio el archivo JSON de configuración.", LOG_DEBUG );
	log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );
	log ( "Se cerro el archivo JSON de configuracion.", LOG_DEBUG );
	log( "Se cargo correctamente el nivel de logging.", LOG_DEBUG );

	log( "Se seteo el nivel de logging para la ejecucion del programa.", LOG_DEBUG );

	// Obtener tiempo limite del combate.
	float tiempo;
	Tiempo* tiempo_combate;
	if ( root.get( "tiempo", "" ) == "" ) {
		log( "No se especifico el tiempo de combate. Se setea en 3 minutos por defecto.", LOG_WARNING );
	} else {
		try {
			tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asInt();
			if ( tiempo < 0 ) {
				tiempo_combate = new Tiempo( TIEMPO_DEFAULT) ;
				// Informar al usuario el cambio de tiempo de la ronda.
				log ( "El tiempo no puede ser negativo. Se setea automaticamente en 3 minutos.", LOG_WARNING );
			} else {
				// Crear tiempo.
				tiempo_combate = new Tiempo( tiempo );
				log( "Se cargo correctamente el tiempo del combate.", LOG_DEBUG );
			}
		} catch (exception &e) {
			delete tiempo_combate;
			tiempo_combate = new Tiempo( TIEMPO_DEFAULT );
			log( "El tiempo indicado no pudo ser convertido a un numero. Se setea un tiempo por defecto", LOG_ERROR );
		}
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
		if ( root["ventana"].get( "ancho-px", "" ) == "" ) {
			ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
			log( "No se especifico el ancho en pixeles de la ventana. Se seta en 512px por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
				if ( ventana_ancho_px < 0 ) {
					ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
					// Informar al usuario el cambio de ancho.
					log( "El ancho en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 512px.", LOG_WARNING );
				} else log( "Se cargo correctamente el ancho en pixeles de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
				log( "El ancho en pixeles de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["ventana"].get( "alto-px", "" ) == "" ) {
			ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
			log( "No se especifico el alto en pixeles de la ventana. Se seta en 384px por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
				if ( ventana_alto_px < 0 ) {
					ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
					// Informar al usuario el cambio de alto.
					log( "El alto en pixeles de la ventana no puede ser negativo. Se setea automaticamente a 384px.", LOG_WARNING );
				} else log( "Se cargo correctamente el alto en pixeles de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
				log( "El alto en pixeles de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["ventana"].get( "ancho", "" ) == "" ) {
			ventana_ancho = VENTANA_ANCHO_DEFAULT;
			log( "No se especifico el ancho logico de la ventana. Se seta en 200 por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asFloat();
				if ( ventana_ancho < 0 ) {
					ventana_ancho = VENTANA_ANCHO_DEFAULT;
					// Informar al usuario el cambio de ancho logico.
					log( "El ancho logico de la ventana no puede ser negativo. Se setea automaticamente a 200.", LOG_WARNING );
				} else log( "Se cargo correctamente el ancho logico de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_ancho = VENTANA_ANCHO_DEFAULT;
				log( "El ancho logico de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
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
		if ( root["escenario"].get( "ancho", "" ) == "" ) {
			escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
			log( "No se especifico el ancho logico del escenario. Se setea en 600 por defecto.", LOG_WARNING );
		} else {
			try {
				escenario_ancho = root["escenario"].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asFloat();
				if ( escenario_ancho < 0 ) {
					escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
					// Informar al usuario el cambio de ancho logico.
					log( "El ancho del escenario no puede ser negativo. Se setea automaticamente a 600.", LOG_WARNING );
				} else log( "Se cargo correctamente el ancho logico del escenario.", LOG_DEBUG );
			} catch ( exception &e ) {
				escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
				log( "El ancho logico del escenario indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["escenario"].get( "alto", "" ) == "" ) {
			escenario_alto = ESCENARIO_ALTO_DEFAULT;
			log( "No se especifico el alto logico del escenario. Se setea en 150 por defecto.", LOG_WARNING );
		} else {
			try {
				escenario_alto = root["escenario"].get( "alto", ESCENARIO_ALTO_DEFAULT ).asFloat();
				if ( escenario_alto < 0 ) {
					escenario_alto = ESCENARIO_ALTO_DEFAULT;
					// Informar al usuario el cambio de alto logico.
					log( "El alto del escenario no puede ser negativo. Se setea automaticamente a 150.", LOG_WARNING );
				} else log( "Se cargo correctamente el alto logico del escenario.", LOG_DEBUG );
			} catch ( exception &e ) {
				escenario_alto = ESCENARIO_ALTO_DEFAULT;
				log( "El alto logico del escenario indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["escenario"].get( "y-piso", "" ) == "" ) {
			y_piso = Y_PISO_DEFAULT;
			log( "No se especifico la altura del piso del escenario. Se setea en 135 por defecto.", LOG_WARNING );
		} else {
			try {
				y_piso = root["escenario"].get( "y-piso", Y_PISO_DEFAULT ).asFloat();
				log ( "Se cargo correctamente la altura del piso.", LOG_DEBUG );
			} catch ( exception &e ) {
				y_piso = Y_PISO_DEFAULT;
				log( "La altura del piso del escenario (y-piso) indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
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
	log ( "Se creo correctamente un mundo vacio.", LOG_DEBUG );

	// Agregar tiempo de combate.
	nuevo_mundo->setTiempo( tiempo_combate );
	log ( "Se agrego el tiempo de combate a la pelea.", LOG_DEBUG );

	// Crear Ventana y abrirla.
	Ventana* ventana = new Ventana( ventana_ancho_px, ventana_alto_px, ratio_x, ratio_y );
	log ( "Se creo correctamente la ventana (camara).", LOG_DEBUG );
	if( ! ventana->create_window() ) {
		log( "No se puede inicializar la ventana. El programa no puede continuar.", LOG_ERROR );
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}

	// Asigno Ventana al Mundo.
	nuevo_mundo->setVentana(ventana);
	log( "Se le asigno la ventana creada al nuevo mundo.", LOG_DEBUG );

	// Obtener las capas del escenario. La primera capa es el fondo del escenario.
	// Se setea por defecto el ancho en caso de error.
	// Si la imagen no existe, se usa una por defecto.
	string background;
	float capa_ancho, capa_alto;
	int capa_z_index;
	if ( root.get( "capas", "" ) == "" ) {
		log( "No se encontraron parametros para la creacion de las capas. Se crea una unica capa y se asignan valores por defecto.", LOG_ERROR );
		CapaFondo* capa_0 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_0_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_0_BACKGROUND_DEFAULT,ventana);
		nuevo_mundo->addCapa(capa_0,CAPA_Z_INDEX_DEFAULT);
		CapaFondo* capa_1 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_1_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+1,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_1_BACKGROUND_DEFAULT,ventana);
		nuevo_mundo->addCapa(capa_1,CAPA_Z_INDEX_DEFAULT+1);
		CapaFondo* capa_2 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_2_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+2,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_2_BACKGROUND_DEFAULT,ventana);
		nuevo_mundo->addCapa(capa_2,CAPA_Z_INDEX_DEFAULT+2);
	} else {
		const Json::Value capas = root["capas"];
		for ( unsigned int i=0; i < capas.size(); i++ ) {
			if ( capas[i].get( "imagen_fondo", "" ) == "" ) {
				background = BACKGROUND_DEFAULT;
				log( "No se especifico la imagen de fondo de la capa. Se asigna una imagen por defecto.", LOG_ERROR );
			} else {
				try {
					background = capas[i].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();
					log( "Se cargo el nombre de la imagen de la capa.", LOG_DEBUG );
				} catch ( exception &e ) {
					background = BACKGROUND_DEFAULT;
					log( "La ruta del archivo de la imagen de la capa no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
				}
			}
			if ( capas[i].get( "ancho", "" ) == "" ) {
				capa_ancho = VENTANA_ANCHO_DEFAULT;
				log( "No se especifico el ancho logico de la capa. Se setea en 600 por defecto.", LOG_WARNING );
			} else {
				try {
					capa_ancho = capas[i].get( "ancho", VENTANA_ANCHO_DEFAULT ).asFloat();
					if ( capa_ancho < 0 ) {
						capa_ancho = VENTANA_ANCHO_DEFAULT;
						// Informar al usuario el cambio de ancho.
						log( "El ancho de la capa no puede ser negativo. Se setea automaticamente en 600.", LOG_WARNING );
					} else if ( capa_ancho > escenario_ancho ) {
						capa_ancho = VENTANA_ANCHO_DEFAULT;
						// Informar al usuario el cambio de ancho.
						log ( "El ancho de la capa no puede superar el del escenario. Se setea automaticamente en 600.", LOG_WARNING );
					} else log( "Se cargo correctamente el ancho logico de la capa.", LOG_DEBUG );
				} catch ( exception &e ) {
					capa_ancho = VENTANA_ANCHO_DEFAULT;
					log( "El ancho de la capa es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
				}
			}
			if ( capas[i].get( "z-index", "" ) == "" ) {
				capa_z_index = CAPA_Z_INDEX_DEFAULT + i;
				log( "No se especifico el z-index de la capa. Se le asigna un indice por defecto.", LOG_WARNING );
			} else {
				try {
					capa_z_index = capas[i].get( "z-index", CAPA_Z_INDEX_DEFAULT + i ).asInt();
					log ( "Se cargo el z-index de la capa.", LOG_DEBUG );
				} catch ( exception &e ) {
					capa_z_index = CAPA_Z_INDEX_DEFAULT +i ;
					log( "El z-index de la capa es invalido y no puede ser convertido a un numero. Se setea por defecto de acuerdo al orden de carga de las capas.", LOG_ERROR );
				}
			}

			// Setear alto logico de la capa de acuerdo al alto del escenario.
			capa_alto = escenario_alto;
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
	float personaje_ancho, personaje_alto;
	string personaje_carpeta_sprites, personaje_nombre;
	bool flipped;
	if ( root.get( "personaje", "" ) == "" ) {
		personaje_z_index = PERSONAJE_Z_INDEX_DEFAULT;
		personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
		personaje_nombre = PERSONAJE_NOMBRE_DEFAULT;
		flipped = PERSONAJE_FLIPPED_DEFAULT;
	} else {
		if ( root["personaje"].get( "ancho", "" ) == "" ) {
			personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
			log( "No se especifico el ancho logico del personaje. Se setea por defecto en 30.", LOG_WARNING );
		} else {
			try {
				personaje_ancho = root["personaje"].get( "ancho", PERSONAJE_ANCHO_DEFAULT ).asFloat();
				if ( personaje_ancho < 0 ) {
					personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
					log( "El ancho del personaje no puede negativo. Se setea por defecto en 30.", LOG_WARNING );
				} else if ( personaje_ancho > escenario_ancho ) {
					personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
					log( "El ancho del personaje no puede superar el del escenario. Se setea por defecto en 30.", LOG_WARNING );
				} else	log( "Se cargo correctamente el ancho logico del personaje.", LOG_DEBUG );
			} catch ( exception &e ) {
				personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
				log( "El ancho logico del personaje inidicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["personaje"].get( "alto", "" ) == "" ) {
			personaje_alto = PERSONAJE_ALTO_DEFAULT;
			log( "No se especifico el alto logico del personaje. Se setea por defecto en 60.", LOG_WARNING );
		} else {
			try {
				personaje_alto = root["personaje"].get( "alto", PERSONAJE_ALTO_DEFAULT ).asFloat();
				if ( personaje_alto < 0 ) {
					personaje_alto = PERSONAJE_ALTO_DEFAULT;
					log( "El alto del personaje no puede negativo. Se setea por defecto en 60.", LOG_WARNING );
				} else if ( personaje_alto > escenario_alto ) {
					personaje_alto = PERSONAJE_ALTO_DEFAULT;
					log( "El alto del personaje no puede superar el del escenario. Se setea por defecto en 60.", LOG_WARNING );
				} else	log( "Se cargo correctamente el alto logico del personaje.", LOG_DEBUG );
			} catch ( exception &e ) {
				personaje_alto = PERSONAJE_ALTO_DEFAULT;
				log( "El alto logico del personaje inidicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["personaje"].get( "z-index", "" ) == "" ) {
			personaje_z_index = PERSONAJE_Z_INDEX_DEFAULT;
			log( "No se especifico el z-index del personaje. Se le asigna indice 3 por defecto.", LOG_WARNING );
		} else {
			try {
				personaje_z_index = root["personaje"].get( "z-index", PERSONAJE_Z_INDEX_DEFAULT ).asInt();
				log ( "Se cargo correctamente el z-index del personaje.", LOG_DEBUG );
			} catch ( exception &e ) {
				personaje_z_index = PERSONAJE_Z_INDEX_DEFAULT;
				log( "El z-index del personaje indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["personaje"].get( "sprites", "" ) == "" ) {
			personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
			log( "No se especifico la carpeta contenedora de los sprites del personaje. Se utiliza carpeta por defecto.", LOG_ERROR );
		} else {
			try {
				personaje_carpeta_sprites = root["personaje"].get( "sprites", PERSONAJE_CARPETA_SPRITES_DEFAULT ).asString();
				log ( "Se cargo correctamente la ruta a la carpeta contenedora de los sprites del personaje.", LOG_DEBUG );
			} catch ( exception &e ) {
				personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
				log( "La ruta a la carpeta contenedora de los sprites del personaje indicada no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["personaje"].get( "nombre", "" ) == "" ) {
			personaje_nombre = PERSONAJE_NOMBRE_DEFAULT;
			log( "No se especifico el nombre del personaje. Se llama Jugador por defecto.", LOG_ERROR );
		} else {
			try {
				personaje_nombre = root["personaje"].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
				log ( "Se cargo el nombre del personaje.", LOG_DEBUG );
			} catch ( exception &e ) {
				personaje_nombre = PERSONAJE_NOMBRE_DEFAULT;
				log( "El nombre del personaje indicado no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( root["personaje"].get( "flipped", "" ) == "" ) {
			flipped = PERSONAJE_FLIPPED_DEFAULT;
			log( "No se especifico si el personaje debe estar flippeado o no. Por defecto, se setea flipped = false, es decir que el personaje mira hacia la derecha.", LOG_WARNING );
		} else {
			try {
				flipped = root["personaje"].get( "flipped", PERSONAJE_FLIPPED_DEFAULT ).asBool();
				log( "Se cargo el booleano flipped que indica si el personaje inicia mirando hacia la derecha (false) o hacia la izquierda (true).", LOG_DEBUG );
			} catch ( exception &e ) {
				flipped = PERSONAJE_FLIPPED_DEFAULT;
				log( "El valor de flipped del personaje no es un booleano valido. Se setea por defecto.", LOG_ERROR );
			}
		}
	}

	// Creo Sprites del personaje.
	vector<Sprite*> sprites = cargarSprites(personaje_carpeta_sprites, ventana, personaje_ancho, personaje_alto);

	// Crear personaje.
	Personaje* personaje = new Personaje(personaje_nombre, sprites, PERSONAJE_VELOCIDAD, flipped);
	log( "Se creo correctamente el personaje.", LOG_DEBUG );

	// Indico posicion inicial del personaje.
	personaje->setPosition( (escenario_ancho/2), y_piso );
	log( "Se seteo la posicion inicial en el escenario del personaje.", LOG_DEBUG );

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

}

