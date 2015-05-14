#include "DefaultSettings.h"

using namespace std;

Sprite* crearSpritePorDefecto(const char* archivo_json, const char* accion_sprite, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje, bool cambiar_color, float h_inicial, float h_final, float h_desplazamiento ) {
	Sprite* sprite;

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream json_sprites;
	json_sprites.open( archivo_json );

	if ( ! json_sprites.is_open() ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo por defecto de sprites JSON. Se aborta el programa.", LOG_ERROR );
		throw runtime_error( "No se pudo abrir el archivo por defecto de sprites JSON." );
	}

	bool exito = reader.parse( json_sprites, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON de sprites por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    throw runtime_error( "No se pudo interpretar el JSON de sprites por defecto." );
	}

	// Cerrar archivo.
	json_sprites.close();

	string spritesheet;
	try {
		if ( ! root[accion_sprite].isMember("nombre") ) {
			log( "No se encontro el nombre de la imagen del spritesheet de la accion por defecto. Se aborta el programa", LOG_ERROR );
			throw runtime_error( "No se encontro el nombre de la imagen del spritesheet de la accion por defecto." );
		}
		spritesheet = root[accion_sprite].get( "nombre", "" ).asString();
		struct stat sb;
		if ( stat((string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + spritesheet).c_str(), &sb) != 0 ) {
			log( "La ruta al spritesheet por defecto de la accion no existe. Se aborta el programa", LOG_ERROR );
			throw runtime_error( "La ruta al spritesheet por defecto de la accion no existe." );
		}
	} catch (exception &e) {
		log( "La ruta al spritesheet por defecto de la accion no es una cadena de texto valida. Se aborta el programa.", LOG_ERROR );
		throw runtime_error( "La ruta al spritesheet por defecto de la accion no es una cadena de texto valida." );
	}
	if ( ! root[accion_sprite].isMember("frames") || ! root[accion_sprite]["frames"].isArray() ) {
		log( "No se especificaron parametros en un vector para los frames del sprite por defecto de la accion. Se aborta el programa.", LOG_ERROR );
		throw runtime_error( "No se especificaron parametros para los frames del sprite por defecto de la accion." );
	}
	const Json::Value frames_accion = root[accion_sprite]["frames"];
	vector<Frame*> frames( frames_accion.size() );
	vector<bool> loop_accion(frames.size(), false);
	vector<bool> pong_accion(frames.size(), false);
	vector<int> freeze_accion(frames.size(), 0);
	for ( unsigned int i=0; i < frames_accion.size(); i++ ) {
		int x, y, alto, ancho;
		try {
			x = frames_accion[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X de un frame del sprite por defecto de la accion o es negativa. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico la posicion X de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "La posicion X de un frame del sprite por defecto indicada no es valida y no puede ser convertida a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "La posicion X de un frame del sprite por defecto de la accion no pudo ser convertida a numero." );
		}
		try {
			y = frames_accion[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y de un frame del sprite por defecto de la accion o es negativa. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico la posicion Y de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "La posicion Y de un frame del sprite por defecto de la accion indicada no es valida y no puede ser convertida a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "La posicion Y de un frame del sprite por defecto de la accion no pudo ser convertida a numero." );
		}
		try {
			alto = frames_accion[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto de un frame del sprite por defecto de la accion o es negativo. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico el alto de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "El alto de un frame del sprite por defecto de la accion indicada no es valido y no puede ser convertido a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "El alto de un frame del sprite por defecto de la accion no pudo ser convertido a numero." );
		}
		try {
			ancho = frames_accion[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el ancho de un frame del sprite por defecto de la accion o es negativo. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico el ancho de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "El ancho de un frame del sprite por defecto de la accion indicada no es valido y no puede ser convertido a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "El ancho de un frame del sprite por defecto de la accion no pudo ser convertido a numero." );
		}
		bool loop;
		try {
			loop = frames_accion[i].get( "loop", false ).asBool();
		} catch (exception &e) {
			log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite por defecto de la accion. Se setea en false por defecto.", LOG_WARNING );
			loop = false;
		}
		loop_accion[i] = loop;

		bool pong;
		try {
			pong = frames_accion[i].get( "pong", false ).asBool();
		} catch (exception &e) {
			log ( "No se reconoce como booleano el parametro pasado para determinar si se debe hacer pong o no a un frame del sprite por defecto de la accion. Se setea en false por defecto.", LOG_ERROR );
			pong = false;
		}
		pong_accion[i] = pong;

		int freezeTime; // Numero de bucles iterados.
		try {
			freezeTime = frames_accion[i].get( "freeze", 0 ).asInt();
		} catch ( exception &e ) {
			log( "La cantidad de bucles de freeze no es un numero valido. Se setea por defecto en 0 (no hay freeze).", LOG_ERROR );
			freezeTime = 0;
		}
		freeze_accion[i] = freezeTime;

		frames[i] = new Frame(x, y, alto, ancho);
	}
	try {
		sprite = new Sprite(string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + spritesheet, frames, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento );
		for ( unsigned int j=0; j < frames.size(); j++ ) {
			if ( loop_accion[j] ) sprite->setLoop(j);
			if ( pong_accion[j] ) sprite->doPongIn(j);
			if( freeze_accion[j] != 0 ) {
				sprite->setFrezeeFrame(j, freeze_accion[j]);
				sprite->freezeSprite();
			}
		}
	} catch ( CargarImagenException &e ) {
		delete sprite;
		log( "No se pudo abrir el spritesheet por defecto de la accion. Se aborta el programa. " + string(e.what()), LOG_ERROR );
		throw runtime_error( "No se pudo abrir el spritesheet por defecto de la accion." );
	}
	return sprite;
}

Sprite* crearSpriteArrojablePorDefecto(Json::Value root_poderes, const char* accion_sprite, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje, bool cambiar_color, float h_inicial, float h_final, float h_desplazamiento ) {
	Sprite* sprite;

	string spritesheet;
	try {
		if ( ! root_poderes[accion_sprite].isMember("nombre") ) {
			log( "No se encontro el nombre de la imagen del spritesheet de la accion por defecto. Se aborta el programa", LOG_ERROR );
			throw runtime_error( "No se encontro el nombre de la imagen del spritesheet de la accion por defecto." );
		}
		spritesheet = root_poderes[accion_sprite].get( "nombre", "" ).asString();
		struct stat sb;
		if ( stat((string(PERSONAJE_CARPETA_ARROJABLES_DEFAULT) + spritesheet).c_str(), &sb) != 0 ) {
			log( "La ruta al spritesheet por defecto de la accion no existe. Se aborta el programa", LOG_ERROR );
			throw runtime_error( "La ruta al spritesheet por defecto de la accion no existe." );
		}
	} catch (exception &e) {
		log( "La ruta al spritesheet por defecto de la accion no es una cadena de texto valida. Se aborta el programa.", LOG_ERROR );
		throw runtime_error( "La ruta al spritesheet por defecto de la accion no es una cadena de texto valida." );
	}
	if ( ! root_poderes[accion_sprite].isMember("frames") || ! root_poderes[accion_sprite]["frames"].isArray() ) {
		log( "No se especificaron parametros en un vector para los frames del sprite por defecto de la accion. Se aborta el programa.", LOG_ERROR );
		throw runtime_error( "No se especificaron parametros para los frames del sprite por defecto de la accion." );
	}
	const Json::Value frames_accion = root_poderes[accion_sprite]["frames"];
	vector<Frame*> frames( frames_accion.size() );
	vector<bool> loop_accion(frames.size(), false);
	vector<bool> pong_accion(frames.size(), false);
	vector<int> freeze_accion(frames.size(), 0);
	for ( unsigned int i=0; i < frames_accion.size(); i++ ) {
		int x, y, alto, ancho;
		try {
			x = frames_accion[i].get( "x", -100 ).asInt();
			if ( x < 0 ) {
				log( "No se especifico la posicion X de un frame del sprite por defecto de la accion o es negativa. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico la posicion X de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "La posicion X de un frame del sprite por defecto indicada no es valida y no puede ser convertida a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "La posicion X de un frame del sprite por defecto de la accion no pudo ser convertida a numero." );
		}
		try {
			y = frames_accion[i].get( "y", -100 ).asInt();
			if ( y < 0 ) {
				log( "No se especifico la posicion Y de un frame del sprite por defecto de la accion o es negativa. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico la posicion Y de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "La posicion Y de un frame del sprite por defecto de la accion indicada no es valida y no puede ser convertida a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "La posicion Y de un frame del sprite por defecto de la accion no pudo ser convertida a numero." );
		}
		try {
			alto = frames_accion[i].get( "Alto", -100 ).asInt();
			if ( alto < 0 ) {
				log( "No se especifico el alto de un frame del sprite por defecto de la accion o es negativo. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico el alto de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "El alto de un frame del sprite por defecto de la accion indicada no es valido y no puede ser convertido a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "El alto de un frame del sprite por defecto de la accion no pudo ser convertido a numero." );
		}
		try {
			ancho = frames_accion[i].get( "Ancho", -100 ).asInt();
			if ( ancho < 0 ) {
				log( "No se especifico el ancho de un frame del sprite por defecto de la accion o es negativo. Se aborta el programa.", LOG_ERROR );
				throw runtime_error( "No se especifico el ancho de un frame del sprite por defecto de la accion." );
			}
		} catch (exception &e) {
			log ( "El ancho de un frame del sprite por defecto de la accion indicada no es valido y no puede ser convertido a un numero. Se aborta el programa.", LOG_ERROR );
			throw runtime_error( "El ancho de un frame del sprite por defecto de la accion no pudo ser convertido a numero." );
		}
		bool loop;
		try {
			loop = frames_accion[i].get( "loop", false ).asBool();
		} catch (exception &e) {
			log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite por defecto de la accion. Se setea en false por defecto.", LOG_WARNING );
			loop = false;
		}
		loop_accion[i] = loop;

		bool pong;
		try {
			pong = frames_accion[i].get( "pong", false ).asBool();
		} catch (exception &e) {
			log ( "No se reconoce como booleano el parametro pasado para determinar si se debe hacer pong o no a un frame del sprite por defecto de la accion. Se setea en false por defecto.", LOG_ERROR );
			pong = false;
		}
		pong_accion[i] = pong;

		int freezeTime; // Numero de bucles iterados.
		try {
			freezeTime = frames_accion[i].get( "freeze", 0 ).asInt();
		} catch ( exception &e ) {
			log( "La cantidad de bucles de freeze no es un numero valido. Se setea por defecto en 0 (no hay freeze).", LOG_ERROR );
			freezeTime = 0;
		}
		freeze_accion[i] = freezeTime;

		frames[i] = new Frame(x, y, alto, ancho);
	}
	try {
		sprite = new Sprite(string(PERSONAJE_CARPETA_ARROJABLES_DEFAULT) + spritesheet, frames, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento );
		for ( unsigned int j=0; j < frames.size(); j++ ) {
			if ( loop_accion[j] ) sprite->setLoop(j);
			if ( pong_accion[j] ) sprite->doPongIn(j);
			if( freeze_accion[j] != 0 ) {
				sprite->setFrezeeFrame(j, freeze_accion[j]);
				sprite->freezeSprite();
			}
		}
	} catch ( CargarImagenException &e ) {
		delete sprite;
		log( "No se pudo abrir el spritesheet por defecto de la accion. Se aborta el programa. " + string(e.what()), LOG_ERROR );
		throw runtime_error( "No se pudo abrir el spritesheet por defecto de la accion." );
	}
	return sprite;
}

vector<Sprite*> generarSpritesDefault( Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color, float h_inicial, float h_final, float h_desplazamiento ) {

	vector<Sprite*> sprites;

	// Calculo ratios para el personaje en base a las dimensiones del sprite inicial por defecto.
	float ratio_x_personaje = PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	float ratio_y_personaje = PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;

	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*0*/ "parado", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*1*/ "caminar", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*2*/ "saltar", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*3*/ "saltardiagonal", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*4*/ "agachar", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*5*/ "agachadoPatadaAlta", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*6*/ "agachadoPatadaBaja", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*7*/ "caeEnZ", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*8*/ "caeYSeLevanta", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*9*/ "cubrirse", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*10*/ "cubrirseAgachado", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*11*/ "gana", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*12*/ "gancho", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*13*/ "muere", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*14*/ "patadaAlta", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*15*/ "patadaBaja", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*16*/ "patadaConGiro", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*17*/ "patadaEnSalto", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*18*/ "pinaAgachado", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*19*/ "pinaAlta", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*20*/ "pinaBaja", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*21*/ "pinaEnSalto", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*22*/ "recibeGolpeAgachado", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*23*/ "recibeGolpeAlto", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*24*/ "recibeGolpeBajo", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*25*/ "recibeGolpeFuerte", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*26*/ "comboPinaBaja", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );
	sprites.push_back( crearSpritePorDefecto(JSON_SPRITES_DEFAULT,/*27*/ "comboPinaAlta", ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, h_desplazamiento) );

	return sprites;
}

vector<ObjetoArrojable*> generarArrojableDefault(Ventana* ventana) {
	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoArrojable;
	string ruta_archivo_json = string(PERSONAJE_CARPETA_ARROJABLES_DEFAULT) + "poderes.json";
	archivoArrojable.open(ruta_archivo_json.c_str());

	if ( ! archivoArrojable.is_open() ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo JSON de poderes por defecto. Se aborta el programa.", LOG_ERROR );
		throw runtime_error("No se pudo abrir el archivo JSON del objeto arrojable por defecto.");
	}

	bool exito = reader.parse( archivoArrojable, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON de poderes por defecto. Se aborta el programa." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    throw runtime_error("No se pudo interpretar el JSON de poderes por defecto.");
	}

	// Cerrar archivo.
	archivoArrojable.close();

	vector<ObjetoArrojable*> objetosArrojables;
	if ( ! root.isMember("poderes") || ! root["poderes"].isArray() ) {
		log( "No se encuentran especificaciones para los poderes por defecto. Se aborta el programa. ", LOG_ERROR );
		throw runtime_error("No se encuentran especificaciones para los poderes por defecto.");
	}
	Json::Value arrojables = root["poderes"];
	for ( int i=0; i < (int)arrojables.size(); i++ ) {

		string arrojable_nombre;
		float arrojable_velocidad, arrojable_ancho, arrojable_alto;
		int arrojable_danio;
		if ( ! arrojables[i].isMember("nombre") ) {
			arrojable_nombre = ARROJABLE_NOMBRE_DEFAULT;
			log( "No se especifico el nombre del objeto arrojable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				arrojable_nombre = arrojables[i].get("nombre", ARROJABLE_NOMBRE_DEFAULT).asString();
			} catch ( exception &e ) {
				arrojable_nombre = ARROJABLE_NOMBRE_DEFAULT;
				log( "El nombre indicado para el objeto arrojable no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! arrojables[i].isMember("velocidad") ) {
			arrojable_velocidad = ARROJABLE_VELOCIDAD_DEFAULT;
			log( "No se especifico la velocidad del objeto arrojable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				arrojable_velocidad = arrojables[i].get("velocidad", ARROJABLE_VELOCIDAD_DEFAULT).asFloat();
				log( "Se cargo correctamente la velocidad del objeto arrojable.", LOG_DEBUG );
			} catch ( exception &e ) {
				arrojable_velocidad = ARROJABLE_VELOCIDAD_DEFAULT;
				log( "La velocidad indicada para el objeto arrojable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! arrojables[i].isMember("danio") ) {
			arrojable_danio = ARROJABLE_DANIO_DEFAULT;
			log( "No se especifico el danio del objeto arrojable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				arrojable_danio = arrojables[i].get("danio", ARROJABLE_DANIO_DEFAULT).asInt();
				log( "Se cargo correctamente el danio del objeto arrojable.", LOG_DEBUG );
			} catch ( exception &e ) {
				arrojable_danio = ARROJABLE_DANIO_DEFAULT;
				log( "El danio indicado para el objeto arrojable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! arrojables[i].isMember("ancho") ) {
			arrojable_ancho = ARROJABLE_ANCHO_DEFAULT;
			log( "No se especifico el ancho logico del objeto arrojable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				arrojable_ancho = arrojables[i].get("ancho", ARROJABLE_ANCHO_DEFAULT).asFloat();
				log( "Se cargo correctamente el ancho logico del objeto arrojable.", LOG_DEBUG );
			} catch ( exception &e ) {
				arrojable_ancho = ARROJABLE_ANCHO_DEFAULT;
				log( "El ancho logico indicado para el objeto arrojable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! arrojables[i].isMember("alto") ) {
			arrojable_alto = ARROJABLE_ALTO_DEFAULT;
			log( "No se especifico el alto logico del objeto arrojable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				arrojable_alto = arrojables[i].get("alto", ARROJABLE_ALTO_DEFAULT).asFloat();
				log( "Se cargo correctamente el alto logico del objeto arrojable.", LOG_DEBUG );
			} catch ( exception &e ) {
				arrojable_alto = ARROJABLE_ALTO_DEFAULT;
				log( "El alto logico indicado para el objeto arrojable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}

		// Calculo ratios para el arrojable.
		float ratio_x_arrojable = ARROJABLE_ANCHO_PX_DEFAULT / arrojable_ancho;
		float ratio_y_arrojable = ARROJABLE_ALTO_PX_DEFAULT / arrojable_alto;

		Sprite* sprite_objeto_arrojable =  crearSpriteArrojablePorDefecto( arrojables[i], "objetoArrojable", ventana, ratio_x_arrojable, ratio_y_arrojable );

		ObjetoArrojable* arrojable = new ObjetoArrojable(arrojable_nombre, arrojable_velocidad, sprite_objeto_arrojable, arrojable_danio);
		objetosArrojables.push_back(arrojable);
	}
	return objetosArrojables;
}

Personaje* generarPersonajeDefault( int nro_personaje, Ventana* ventana, float ventana_ancho, float escenario_ancho, float escenario_alto, float y_piso, float personaje_ancho, float personaje_alto, bool cambiar_color, bool flipped ) {
	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault( ventana,personaje_ancho,personaje_alto, cambiar_color, COLOR_H_INICIAL_DEFAULT, COLOR_H_FINAL_DEFAULT, COLOR_DESPLAZAMIENTO_DEFAULT), generarArrojableDefault(ventana), PERSONAJE_VELOCIDAD, flipped);
	if ( nro_personaje == 1 )
		personaje_default->setPosition((escenario_ancho/2) - (ventana_ancho/2) * PERSONAJE_POS_RESPECTO_CAM,y_piso);
	else if ( nro_personaje == 2 )
		personaje_default->setPosition((escenario_ancho/2) + (ventana_ancho/2) * PERSONAJE_POS_RESPECTO_CAM,y_piso);
	return personaje_default;
}

vector<Personaje*> generarPersonajesDefault( Ventana* ventana) {
	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault( ventana,PERSONAJE_ANCHO_DEFAULT,PERSONAJE_ALTO_DEFAULT, false, COLOR_H_INICIAL_DEFAULT, COLOR_H_FINAL_DEFAULT, COLOR_DESPLAZAMIENTO_DEFAULT), generarArrojableDefault(ventana), PERSONAJE_VELOCIDAD, PERSONAJE_FLIPPED_DEFAULT);
	personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2) - (VENTANA_ANCHO_DEFAULT/2) * PERSONAJE_POS_RESPECTO_CAM,Y_PISO_DEFAULT);

	Personaje* personaje2_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault( ventana,PERSONAJE_ANCHO_DEFAULT,PERSONAJE_ALTO_DEFAULT, true, COLOR_H_INICIAL_DEFAULT, COLOR_H_FINAL_DEFAULT, COLOR_DESPLAZAMIENTO_DEFAULT), generarArrojableDefault(ventana), PERSONAJE_VELOCIDAD, !PERSONAJE_FLIPPED_DEFAULT);
	personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2) + (VENTANA_ANCHO_DEFAULT/2) * PERSONAJE_POS_RESPECTO_CAM,Y_PISO_DEFAULT);

	vector<Personaje*> personajes;
	personajes.push_back(personaje_default);
	personajes.push_back(personaje2_default);

	return personajes;
}

void mapaComandosDefault(map<string, int>* comandos1, map<string, int>* comandos2) {

	comandos1->operator[](string("pina baja")) = COMANDO_PINA_BAJA_DEFAULT;
	comandos1->operator[](string("patada baja")) = COMANDO_PATADA_BAJA_DEFAULT;
	comandos1->operator[](string("pina alta")) = COMANDO_PINA_ALTA_DEFAULT;
	comandos1->operator[](string("patada alta")) = COMANDO_PATADA_ALTA_DEFAULT;
	comandos1->operator[](string("cubrirse"))= COMANDO_CUBRIRSE_DEFAULT;
	comandos1->operator[](string("lanzar arma")) = COMANDO_LANZAR_ARMA_DEFAULT;

	comandos2->operator[](string("pina baja")) = COMANDO_PINA_BAJA_DEFAULT;
	comandos2->operator[](string("patada baja")) = COMANDO_PATADA_BAJA_DEFAULT;
	comandos2->operator[](string("pina alta")) = COMANDO_PINA_ALTA_DEFAULT;
	comandos2->operator[](string("patada alta")) = COMANDO_PATADA_ALTA_DEFAULT;
	comandos2->operator[](string("cubrirse"))= COMANDO_CUBRIRSE_DEFAULT;
	comandos2->operator[](string("lanzar arma")) = COMANDO_LANZAR_ARMA_DEFAULT;

}



/*
Mundo* generarMundoDefault() {

	float ratio_x = VENTANA_ANCHO_PX_DEFAULT/VENTANA_ANCHO_DEFAULT;
	float ratio_y = VENTANA_ALTO_PX_DEFAULT/ESCENARIO_ALTO_DEFAULT;

	Mundo* mundo = new Mundo(ESCENARIO_ANCHO_DEFAULT,ESCENARIO_ALTO_DEFAULT);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT,ratio_x,ratio_y);

	if( ! ventana->create_window() ) {
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}

	vector<Personaje*> personajes = generarPersonajesDefault(ventana);

	mundo->setVentana(ventana);
	mundo->setTiempo(new Tiempo(TIEMPO_DEFAULT));

	mundo->addPersonaje(personajes[0]);
	mundo->addPersonaje(personajes[1]);

	CapaFondo* capa_0 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_0_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_0_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_0);
	CapaFondo* capa_1 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_1_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+1,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_1_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_1);
	CapaFondo* capa_2 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_2_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+2,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_2_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_2);

	CapaPrincipal* capa_principal = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJES_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,VENTANA_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,personajes);
	mundo->addCapaPrincipal(capa_principal,PERSONAJES_Z_INDEX_DEFAULT);


	return mundo;
}
*/
