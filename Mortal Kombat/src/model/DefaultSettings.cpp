#include "DefaultSettings.h"

using namespace std;


Sprite* crearSpritePorDefecto(const char* accion_sprite, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje) {
	Sprite* sprite;

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream json_sprites;
	json_sprites.open( JSON_SPRITES_DEFAULT );

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
		if ( loop ) {
			loop_accion[i] = true;
		}
		frames[i] = new Frame(x, y, alto, ancho);
	}
	try {
		sprite = new Sprite(string(PERSONAJE_CARPETA_SPRITES_DEFAULT) + spritesheet, frames, ventana, ratio_x_personaje, ratio_y_personaje );
		for ( unsigned int j=0; j < frames.size(); j++ ) {
			if ( loop_accion[j] ) sprite->setLoop(j);
		}
	} catch ( CargarImagenException &e ) {
		delete sprite;
		log( "No se pudo abrir el spritesheet por defecto de la accion. Se aborta el programa. " + string(e.what()), LOG_ERROR );
		throw runtime_error( "No se pudo abrir el spritesheet por defecto de la accion." );
	}
	return sprite;
}

vector<Sprite*> generarSpritesDefault( Ventana* ventana, float personaje_ancho, float personaje_alto ) {

	vector<Sprite*> sprites;

	// Calculo ratios para el personaje en base a las dimensiones del sprite inicial por defecto.
	float ratio_x_personaje = PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	float ratio_y_personaje = PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;

	sprites.push_back( crearSpritePorDefecto("parado", ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpritePorDefecto("caminar", ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpritePorDefecto("saltar", ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpritePorDefecto("saltardiagonal", ventana, ratio_x_personaje, ratio_y_personaje) );
	sprites.push_back( crearSpritePorDefecto("agachar", ventana, ratio_x_personaje, ratio_y_personaje) );

	return sprites;
}

Mundo* generarMundoDefault() {

	float ratio_x = VENTANA_ANCHO_PX_DEFAULT/VENTANA_ANCHO_DEFAULT;
	float ratio_y = VENTANA_ALTO_PX_DEFAULT/ESCENARIO_ALTO_DEFAULT;

	Mundo* mundo = new Mundo(ESCENARIO_ANCHO_DEFAULT,ESCENARIO_ALTO_DEFAULT);
	Ventana* ventana = new Ventana(VENTANA_ANCHO_PX_DEFAULT,VENTANA_ALTO_PX_DEFAULT,ratio_x,ratio_y);

	if( ! ventana->create_window() ) {
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}

	Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault( ventana,PERSONAJE_ANCHO_DEFAULT,PERSONAJE_ALTO_DEFAULT), PERSONAJE_VELOCIDAD, PERSONAJE_FLIPPED_DEFAULT);

	personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2),Y_PISO_DEFAULT);

	mundo->setVentana(ventana);
	mundo->setTiempo(new Tiempo(TIEMPO_DEFAULT));

	mundo->addPersonaje(personaje_default);

	CapaFondo* capa_0 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_0_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_0_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_0);
	CapaFondo* capa_1 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_1_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+1,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_1_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_1);
	CapaFondo* capa_2 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_2_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+2,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_2_BACKGROUND_DEFAULT,ventana);
	mundo->addCapa(capa_2);

	CapaPrincipal* capa_principal = new CapaPrincipal(ESCENARIO_ALTO_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,VENTANA_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,personaje_default);
	mundo->addCapaPrincipal(capa_principal,PERSONAJE_Z_INDEX_DEFAULT);

	return mundo;
}
