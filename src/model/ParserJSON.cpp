#include "ParserJSON.h"

#define RUTA_ARCHIVO_JSON_FIGHT "data/img/textosPelea/fight/sprites.json"
#define RUTA_CARPETA_SPRITE_FIGHT "data/img/textosPelea/fight/"
#define RUTA_CARPETA_SONIDO_FIGHT "data/img/textosPelea/fight/"

#define RUTA_ARCHIVO_JSON_FATALITY "data/img/textosPelea/fatality/sprites.json"
#define RUTA_CARPETA_SPRITE_FATALITY "data/img/textosPelea/fatality/"
#define RUTA_CARPETA_SONIDO_FATALITY "data/img/textosPelea/fatality/"

#define RUTA_ARCHIVO_JSON_FINISHHIM "data/img/textosPelea/finishHim/sprites.json"
#define RUTA_CARPETA_SPRITE_FINISHHIM "data/img/textosPelea/finishHim/"
#define RUTA_CARPETA_SONIDO_FINISHHIM "data/img/textosPelea/finishHim/"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
	m_ventana = NULL;
	comandos_luchador1 = NULL;
	comandos_luchador2 = NULL;
}

ParserJSON::~ParserJSON() {
	delete comandos_luchador1;
	delete comandos_luchador2;
}

float ParserJSON::getRatioXPersonaje( Json::Value root_sprites, float personaje_ancho ) {
	if ( ! root_sprites.isMember("parado") ) {
		log( "No se encontro la etiqueta para la creacion del sprite inicial del personaje. Se setea el ratio_x del personaje por defecto.", LOG_ERROR );
		return PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	}
	if ( ! root_sprites["parado"].isMember("frames") || ! root_sprites["parado"]["frames"].isArray() ) {
		log( "No se encontraron especificaciones en un vector para la creacion del sprite inicial del personaje. Se setea el ratio_x del personaje por defecto.", LOG_ERROR );
		return PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	}
	int ancho_px;
	try {
		ancho_px = root_sprites["parado"]["frames"][0].get( "Ancho", -100 ).asInt();
		if ( ancho_px < 0 ) {
			log( "No se especifico el ancho en pixeles del personaje o es negativo. No se puede calcular el ratio_x del personaje. Se setea por defecto.", LOG_ERROR );
			return PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
		}
	} catch ( exception &e ) {
		log( "El ancho en pixeles indicado del personaje no puede ser convertido a numero. Se setea el ratio_x del personaje por defecto.", LOG_ERROR );
		return PERSONAJE_ANCHO_PX_DEFAULT / personaje_ancho;
	}

	float ratio_x_personaje = ancho_px / personaje_ancho;
	log( "Se calculo el ratio_x del personaje.", LOG_DEBUG );
	return ratio_x_personaje;
}

float ParserJSON::getRatioYPersonaje( Json::Value root_sprites, float personaje_alto ) {
	if ( ! root_sprites.isMember("parado") ) {
		log( "No se encontro la etiqueta para la creacion del sprite inicial del personaje. Se setea el ratio_y del personaje por defecto.", LOG_ERROR );
		return PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;
	}
	if ( ! root_sprites["parado"].isMember("frames") || ! root_sprites["parado"]["frames"].isArray() ) {
		log( "No se encontraron especificaciones en un vector para la creacion del sprite inicial del personaje. Se setea el ratio_y del personaje por defecto.", LOG_ERROR );
		return PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;
	}
	int alto_px;
	try {
		alto_px = root_sprites["parado"]["frames"][0].get( "Alto", -100 ).asInt();
		if ( alto_px < 0 ) {
			log( "No se especifico el alto en pixeles del personaje o es negativo. No se puede calcular el ratio_y del personaje. Se setea por defecto.", LOG_ERROR );
			return PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;
		}
	} catch ( exception &e ) {
		log( "El alto en pixeles indicado del personaje no puede ser convertido a numero. Se setea el ratio_y del personaje por defecto.", LOG_ERROR );
		return PERSONAJE_ALTO_PX_DEFAULT / personaje_alto;
	}

	float ratio_y_personaje = alto_px / personaje_alto;
	log( "Se calculo el ratio_y del personaje.", LOG_DEBUG );
	return ratio_y_personaje;
}

float ParserJSON::getRatioXArrojable( Json::Value root_arrojables, float arrojable_ancho ) {
	if ( ! root_arrojables.isMember("objetoArrojable") ) {
		log( "No se encontro la etiqueta para la creacion del objeto arrojable del personaje. Se setea el ratio_x del arrojable del personaje por defecto.", LOG_ERROR );
		return ARROJABLE_ANCHO_PX_DEFAULT / arrojable_ancho;
	}
	if ( ! root_arrojables["objetoArrojable"].isMember("frames") || ! root_arrojables["objetoArrojable"]["frames"].isArray() ) {
		log( "No se encontraron especificaciones en un vector para la creacion del sprite del objeto arrojable del personaje. Se setea el ratio_x del arrojable por defecto.", LOG_ERROR );
		return ARROJABLE_ANCHO_PX_DEFAULT / arrojable_ancho;
	}
	int ancho_px;
	try {
		ancho_px = root_arrojables["objetoArrojable"]["frames"][0].get( "Ancho", -100 ).asInt();
		if ( ancho_px < 0 ) {
			log( "No se especifico el ancho en pixeles del objeto arrojable o es negativo. No se puede calcular el ratio_x del arrojable. Se setea por defecto.", LOG_ERROR );
			return ARROJABLE_ANCHO_PX_DEFAULT / arrojable_ancho;
		}
	} catch ( exception &e ) {
		log( "El ancho en pixeles indicado del objeto arrojable no puede ser convertido a numero. Se setea el ratio_x del arrojable por defecto.", LOG_ERROR );
		return ARROJABLE_ANCHO_PX_DEFAULT / arrojable_ancho;
	}

	float ratio_x_arrojable = ancho_px / arrojable_ancho;
	log( "Se calculo el ratio_x del objeto arrojable del personaje.", LOG_DEBUG );
	return ratio_x_arrojable;
}

float ParserJSON::getRatioYArrojable( Json::Value root_arrojables, float arrojable_alto ) {
	if ( ! root_arrojables.isMember("objetoArrojable") ) {
		log( "No se encontro la etiqueta para la creacion del objeto arrojable del personaje. Se setea el ratio_y del arrojable del personaje por defecto.", LOG_ERROR );
		return ARROJABLE_ALTO_PX_DEFAULT / arrojable_alto;
	}
	if ( ! root_arrojables["objetoArrojable"].isMember("frames") || ! root_arrojables["objetoArrojable"]["frames"].isArray() ) {
		log( "No se encontraron especificaciones en un vector para la creacion del sprite del objeto arrojable del personaje. Se setea el ratio_y del arrojable por defecto.", LOG_ERROR );
		return ARROJABLE_ALTO_PX_DEFAULT / arrojable_alto;
	}
	int alto_px;
	try {
		alto_px = root_arrojables["objetoArrojable"]["frames"][0].get( "Alto", -100 ).asInt();
		if ( alto_px < 0 ) {
			log( "No se especifico el alto en pixeles del objeto arrojable o es negativo. No se puede calcular el ratio_y del arrojable. Se setea por defecto.", LOG_ERROR );
			return ARROJABLE_ALTO_PX_DEFAULT / arrojable_alto;
		}
	} catch ( exception &e ) {
		log( "El alto en pixeles indicado del objeto arrojable no puede ser convertido a numero. Se setea el ratio_y del arrojable por defecto.", LOG_ERROR );
		return ARROJABLE_ALTO_PX_DEFAULT / arrojable_alto;
	}

	float ratio_y_arrojable = alto_px / arrojable_alto;
	log( "Se calculo el ratio_y del objeto arrojable del personaje.", LOG_DEBUG );
	return ratio_y_arrojable;
}

float ParserJSON::getRatioXDroppable( Json::Value root_droppables, float droppable_ancho ) {
	if ( ! root_droppables.isMember("objetoDroppable") ) {
		log( "No se encontro la etiqueta para la creacion del objeto droppables del personaje. Se setea el ratio_x del droppable del personaje por defecto.", LOG_ERROR );
		return DROPPABLE_ANCHO_PX_DEFAULT / droppable_ancho;
	}
	if ( ! root_droppables["objetoDroppable"].isMember("frames") || ! root_droppables["objetoDroppable"]["frames"].isArray() ) {
		log( "No se encontraron especificaciones en un vector para la creacion del sprite del objeto droppable del personaje. Se setea el ratio_x del droppable por defecto.", LOG_ERROR );
		return DROPPABLE_ANCHO_PX_DEFAULT / droppable_ancho;
	}
	int ancho_px;
	try {
		ancho_px = root_droppables["objetoDroppable"]["frames"][0].get( "Ancho", -100 ).asInt();
		if ( ancho_px < 0 ) {
			log( "No se especifico el ancho en pixeles del objeto droppable o es negativo. No se puede calcular el ratio_x del droppable. Se setea por defecto.", LOG_ERROR );
			return DROPPABLE_ANCHO_PX_DEFAULT / droppable_ancho;
		}
	} catch ( exception &e ) {
		log( "El ancho en pixeles indicado del objeto droppable no puede ser convertido a numero. Se setea el ratio_x del droppable por defecto.", LOG_ERROR );
		return DROPPABLE_ANCHO_PX_DEFAULT / droppable_ancho;
	}

	float ratio_x_droppable = ancho_px / droppable_ancho;
	log( "Se calculo el ratio_x del objeto droppable del personaje.", LOG_DEBUG );
	return ratio_x_droppable;
}

float ParserJSON::getRatioYDroppable( Json::Value root_droppables, float droppable_alto ) {
	if ( ! root_droppables.isMember("objetoDroppable") ) {
		log( "No se encontro la etiqueta para la creacion del objeto droppables del personaje. Se setea el ratio_y del droppable del personaje por defecto.", LOG_ERROR );
		return DROPPABLE_ALTO_PX_DEFAULT / droppable_alto;
	}
	if ( ! root_droppables["objetoDroppable"].isMember("frames") || ! root_droppables["objetoDroppable"]["frames"].isArray() ) {
		log( "No se encontraron especificaciones en un vector para la creacion del sprite del objeto droppable del personaje. Se setea el ratio_y del droppable por defecto.", LOG_ERROR );
		return DROPPABLE_ALTO_PX_DEFAULT / droppable_alto;
	}
	int alto_px;
	try {
		alto_px = root_droppables["objetoDroppable"]["frames"][0].get( "Alto", -100 ).asInt();
		if ( alto_px < 0 ) {
			log( "No se especifico el alto en pixeles del objeto droppable o es negativo. No se puede calcular el ratio_y del droppable. Se setea por defecto.", LOG_ERROR );
			return DROPPABLE_ALTO_PX_DEFAULT / droppable_alto;
		}
	} catch ( exception &e ) {
		log( "El alto en pixeles indicado del objeto droppable no puede ser convertido a numero. Se setea el ratio_y del droppable por defecto.", LOG_ERROR );
		return DROPPABLE_ALTO_PX_DEFAULT / droppable_alto;
	}

	float ratio_y_droppable = alto_px / droppable_alto;
	log( "Se calculo el ratio_y del objeto droppable del personaje.", LOG_DEBUG );
	return ratio_y_droppable;
}

// Devuelve el puntero al mapa de comandos.
map<string, int>* ParserJSON::getComandos1() {
	return comandos_luchador1;
}

map<string, int>* ParserJSON::getComandos2() {
	return comandos_luchador2;
}


Sprite* ParserJSON::cargarSprite( Json::Value root, string ruta_carpeta, string ruta_sonidos, const char accion_sprite[], string spritesheet_accion, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje, bool cambiar_color, float h_inicial, float h_final, float desplazamiento ) {
	Sprite* sprite;
	LSound* sonido;
	string spritesheet;
	string nombre_sonido;
	if ( ! root.isMember(accion_sprite) ) {
		log( "No se encontro el sprite correspondiente a la accion del personaje. Se generan el sprite de la accion por defecto.", LOG_ERROR );
		return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color);
	} else {
		if ( ! root[accion_sprite].isMember("nombre") ) {
			log( "No se especifico el nombre de la imagen para el spritesheet de la accion. Se setea uno por defecto.", LOG_WARNING );
			spritesheet = spritesheet_accion;
		} else {
			try {
				spritesheet = root[accion_sprite].get( "nombre", spritesheet_accion ).asString();
				struct stat sb;
				if ( stat((ruta_carpeta + spritesheet).c_str(), &sb) != 0 ) {
					log( "La ruta al spritesheet no existe. Se carga la ruta por defecto.", LOG_ERROR );
					spritesheet = spritesheet_accion;
					ruta_carpeta = PERSONAJE_CARPETA_SPRITES_DEFAULT;
				} else log( "Se cargo correctamente el nombre del archivo de imagen del spritesheet.", LOG_DEBUG );
			} catch (exception &e) {
				spritesheet = spritesheet_accion;
				log( "El nombre ingresado del spritesheet no es una cadena de texto valida. Se setea un nombre por defecto.", LOG_ERROR );
			}
		}

		if ( ! root[accion_sprite].isMember("sonido") ) {
			log( "No se especifico el sonido de la imagen para el spritesheet de la accion. No se carga sonido.", LOG_WARNING );
			nombre_sonido = "";
		} else {
			try {
				nombre_sonido = root[accion_sprite].get( "sonido", "" ).asString();
				struct stat sb;
				if ( stat((ruta_sonidos + nombre_sonido).c_str(), &sb) != 0 ) {
					log( "La ruta al sonido no existe. No se carga el sonido.", LOG_ERROR );
					nombre_sonido = "";
					ruta_sonidos = PERSONAJE_CARPETA_SONIDOS_DEFAULT;
				} else
					log( "Se cargo correctamente el nombre del archivo de sonido del sprite.", LOG_DEBUG );
			} catch (exception &e) {
				nombre_sonido = "";
				log( "El nombre ingresado del sonido no es una cadena de texto valida. No se carga un sonido para la accion.", LOG_ERROR );
			}
		}
		if (nombre_sonido == "")
			sonido = NULL;
		else
			sonido = new LSound(ruta_sonidos + nombre_sonido);

		if ( ! root[accion_sprite].isMember("frames") || ! root[accion_sprite]["frames"].isArray() ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet de la accion. Se genera el sprite por defecto.", LOG_ERROR );
			return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
		} else {
			const Json::Value frames_accion = root[accion_sprite]["frames"];
			vector<Frame*> frames( frames_accion.size() );
			vector<bool> loop_accion(frames.size(), false);
			vector<bool> pong_accion(frames.size(), false);
			vector<int> freeze_accion(frames.size(), 0);
			vector<bool> sound_accion(frames.size(), false);
			for ( unsigned int i=0; i < frames_accion.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_accion[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite de la accion por defecto.", LOG_ERROR );
						return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				try {
					y = frames_accion[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite de la accion por defecto", LOG_ERROR );
						return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada es invalida y no puede ser convertida a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				try {
					alto = frames_accion[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite de la accion por defecto.", LOG_ERROR );
						return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				try {
					ancho = frames_accion[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el ancho del frame o es negativo. Se genera el sprite de la accion por defecto.", LOG_ERROR );
						return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}

				bool loop;
				try {
					loop = frames_accion[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite de la accion. Se setea en false por defecto.", LOG_WARNING );
					loop = false;
				}
				loop_accion[i] = loop;

				bool pong;
				try {
					pong = frames_accion[i].get( "pong", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe hacer pong o no a un frame del sprite de la accion. Se setea en false por defecto.", LOG_WARNING );
					pong = false;
				}
				pong_accion[i] = pong;

				int freezeTime; // Numero de bucles iterados.
				try {
					freezeTime = frames_accion[i].get( "freeze", 0 ).asInt();
				} catch ( exception &e ) {
					log( "La cantidad de bucles de freeze no es un numero valido. Se setea por defecto en 0 (no hay freeze).", LOG_WARNING );
					freezeTime = 0;
				}
				freeze_accion[i] = freezeTime;

				bool playSound;
				try {
					playSound = frames_accion[i].get( "playSound", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe ejecutar o no el sonido de la accion en el frame actual. Se setea en false por defecto.", LOG_WARNING );
					playSound = false;
				}
				sound_accion[i] = playSound;

				frames[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet de la accion.", LOG_DEBUG );
			}
			try {
				sprite = new Sprite( ruta_carpeta + spritesheet, frames, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento, sonido );
				for ( unsigned int j=0; j < frames.size(); j++ ) {
					if ( loop_accion[j] ) {
						sprite->setLoop(j);
						log( "Se seteo en loop el frame recien creado.", LOG_DEBUG );
					}
					if( freeze_accion[j] != 0 ) {
						sprite->setFrezeeFrame(j, freeze_accion[j]);
						sprite->freezeSprite();
						log( "Se seteo un tiempo de freeze para el frame recien creado.", LOG_DEBUG );
					}
					if ( pong_accion[j] ) {
						sprite->doPongIn(j);
						log( "Se seteo como frame pong el frame recien creado.", LOG_DEBUG );
					}
					if ( sound_accion[j] ) {
						sprite->setSoundIn(j);
						log( "Se le asigno la ejecucion del sonido de la accion al frame recien creado.", LOG_DEBUG );
					}
				}
				log( "Se creo correctamente el sprite para la accion del personaje.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				delete sprite;
				sprite = crearSpritePorDefecto(ruta_carpeta.c_str(), accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				log( "No se pudo abrir el spritesheet de la accion. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
	}
	return sprite;
}


vector<ObjetoArrojable*> ParserJSON::cargarArrojables(string ruta_carpeta, string ruta_sonidos, Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color, float h_inicial, float h_final, float desplazamiento) {

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoArrojable;
	string ruta_archivo_json = ruta_carpeta + "poderes.json";
	archivoArrojable.open(ruta_archivo_json.c_str());

	if ( ! archivoArrojable.is_open() ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo del objeto arrojable JSON, se genera el objeto por defecto.", LOG_ERROR );
		return generarArrojableDefault(ventana);
	}
	log ( "Se abrio el archivo JSON del objeto arrojable.", LOG_DEBUG );

	bool exito = reader.parse( archivoArrojable, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON, se genera el objeto arrojable por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return generarArrojableDefault(ventana);
	} else log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivoArrojable.close();
	log ( "Se cerro el archivo JSON del objeto arrojable.", LOG_DEBUG );

	vector<ObjetoArrojable*> objetosArrojables;
	if ( ! root.isMember("poderes") || ! root["poderes"].isArray() ) {
		log( "No se encuentran especificaciones para los poderes. Se setean los objetos por defecto. ", LOG_ERROR );
		return generarArrojableDefault(ventana);
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
				log( "Se cargo correctamente el nombre del objeto arrojable.", LOG_DEBUG );
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

		// Calculo los ratios del arrojable.
		float ratio_x_arrojable = getRatioXArrojable(arrojables[i], arrojable_ancho);
		float ratio_y_arrojable = getRatioYArrojable(arrojables[i], arrojable_alto);

		log( "Se cargara el sprite para el objeto arrojable del personaje", LOG_DEBUG );
		Sprite* sprite_objeto_arrojable =  cargarSprite( arrojables[i], ruta_carpeta, ruta_sonidos, "objetoArrojable", SPRITESHEET_OBJETO_ARROJABLE_DEFAULT, ventana, ratio_x_arrojable, ratio_y_arrojable );

		ObjetoArrojable* arrojable = new ObjetoArrojable(arrojable_nombre, arrojable_velocidad, sprite_objeto_arrojable, arrojable_danio);
		objetosArrojables.push_back(arrojable);
	}
	return objetosArrojables;
}


vector<ObjetoDroppable*> ParserJSON::cargarDroppables(string ruta_carpeta, string ruta_sonidos, Ventana* ventana) {

	vector<ObjetoDroppable*> objetosDroppables;

	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoDroppables;
	string ruta_archivo_json = ruta_carpeta + "droppables.json";
	archivoDroppables.open(ruta_archivo_json.c_str());

	if ( ! archivoDroppables.is_open() ) {
		// Informar al usuario la falla y la resolucion tomada.
		log( "No se pudo abrir el archivo JSON de los droppables, se genera el objeto por defecto.", LOG_ERROR );
		return objetosDroppables;
	}
	log ( "Se abrio el archivo JSON de los objetos droppables.", LOG_DEBUG );

	bool exito = reader.parse( archivoDroppables, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    log( "No se pudo interpretar el JSON." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return objetosDroppables;
	} else log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivoDroppables.close();
	log ( "Se cerro el archivo JSON de los objetos droppable.", LOG_DEBUG );

	if ( ! root.isMember("droppables") || ! root["droppables"].isArray() ) {
		log( "No se encuentran especificaciones para los droppables.", LOG_ERROR );
		return objetosDroppables;
	}
	Json::Value droppables = root["droppables"];
	for ( int i=0; i < (int)droppables.size(); i++ ) {

		string droppable_nombre;
		float droppable_velocidad, droppable_ancho, droppable_alto;
		if ( ! droppables[i].isMember("nombre") ) {
			droppable_nombre = DROPPABLE_NOMBRE_DEFAULT;
			log( "No se especifico el nombre del objeto droppable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				droppable_nombre = droppables[i].get("nombre", DROPPABLE_NOMBRE_DEFAULT).asString();
				log( "Se cargo correctamente el nombre del objeto droppable.", LOG_DEBUG );
			} catch ( exception &e ) {
				droppable_nombre = DROPPABLE_NOMBRE_DEFAULT;
				log( "El nombre indicado para el objeto droppable no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! droppables[i].isMember("velocidad") ) {
			droppable_velocidad = DROPPABLE_VELOCIDAD_DEFAULT;
			log( "No se especifico la velocidad del objeto droppable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				droppable_velocidad = droppables[i].get("velocidad", DROPPABLE_VELOCIDAD_DEFAULT).asFloat();
				log( "Se cargo correctamente la velocidad del objeto droppable.", LOG_DEBUG );
			} catch ( exception &e ) {
				droppable_velocidad = DROPPABLE_VELOCIDAD_DEFAULT;
				log( "La velocidad indicada para el objeto droppable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! droppables[i].isMember("ancho") ) {
			droppable_ancho = DROPPABLE_ANCHO_DEFAULT;
			log( "No se especifico el ancho logico del objeto droppable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				droppable_ancho = droppables[i].get("ancho", DROPPABLE_ANCHO_DEFAULT).asFloat();
				log( "Se cargo correctamente el ancho logico del objeto droppable.", LOG_DEBUG );
			} catch ( exception &e ) {
				droppable_ancho = DROPPABLE_ANCHO_DEFAULT;
				log( "El ancho logico indicado para el objeto droppable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! droppables[i].isMember("alto") ) {
			droppable_alto = DROPPABLE_ALTO_DEFAULT;
			log( "No se especifico el alto logico del objeto droppable. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				droppable_alto = droppables[i].get("alto", DROPPABLE_ALTO_DEFAULT).asFloat();
				log( "Se cargo correctamente el alto logico del objeto droppable.", LOG_DEBUG );
			} catch ( exception &e ) {
				droppable_alto = DROPPABLE_ALTO_DEFAULT;
				log( "El alto logico indicado para el objeto droppable no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}

		// Calculo los ratios del arrojable.
		float ratio_x_droppable = getRatioXDroppable(droppables[i], droppable_ancho);
		float ratio_y_droppable = getRatioYDroppable(droppables[i], droppable_alto);

		log( "Se cargara el sprite para el objeto droppable del personaje", LOG_DEBUG );
		Sprite* sprite_objeto_droppable =  cargarSprite( droppables[i], ruta_carpeta, ruta_sonidos, "objetoDroppable", SPRITESHEET_OBJETO_DROPPABLE_DEFAULT, ventana, ratio_x_droppable, ratio_y_droppable );

		ObjetoDroppable* droppable = new ObjetoDroppable(droppable_nombre, droppable_velocidad, sprite_objeto_droppable, false);
		objetosDroppables.push_back(droppable);
	}
	return objetosDroppables;
}

vector<Sprite*> ParserJSON::cargarSprites(string ruta_carpeta, string ruta_sonidos, Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color, float h_inicial, float h_final, float desplazamiento) {

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


	// Calculo los ratios del personaje.
	float ratio_x_personaje = getRatioXPersonaje(root, personaje_ancho);
	float ratio_y_personaje = getRatioYPersonaje(root, personaje_alto);

	// Cargo uno por uno los sprites correspondientes a cada accion.
	log( "Se cargara el sprite inicial para la accion de estar parado.", LOG_DEBUG );
	Sprite* sprite_parado =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "parado", SPRITESHEET_PARADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_parado );

	log( "Se cargara el sprite para la accion de caminar del personaje", LOG_DEBUG );
	Sprite* sprite_caminar =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "caminar", SPRITESHEET_CAMINAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_caminar );

	log( "Se cargara el sprite para la accion de saltar del personaje", LOG_DEBUG );
	Sprite* sprite_saltar =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "saltar", SPRITESHEET_SALTAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_saltar );

	log( "Se cargara el sprite para la accion de saltar en diagonal del personaje", LOG_DEBUG );
	Sprite* sprite_saltar_diagonal =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "saltardiagonal", SPRITESHEET_SALTAR_DIAGONAL_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_saltar_diagonal );

	log( "Se cargara el sprite para la accion de agacharse del personaje", LOG_DEBUG );
	Sprite* sprite_agachar =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "agachar", SPRITESHEET_AGACHAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_agachar );

	log( "Se cargara el sprite para la accion de pegar patada alta estando agachado del personaje", LOG_DEBUG );
	Sprite* sprite_agachado_patada_alta =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "agachadoPatadaAlta", SPRITESHEET_AGACHADO_PATADA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_agachado_patada_alta );

	log( "Se cargara el sprite para la accion de pegar patada baja estando agachado del personaje", LOG_DEBUG );
	Sprite* sprite_agachado_patada_baja =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "agachadoPatadaBaja", SPRITESHEET_AGACHADO_PATADA_BAJA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_agachado_patada_baja );

	log( "Se cargara el sprite para la accion de caerse por una barrida del personaje", LOG_DEBUG );
	Sprite* sprite_caer_en_z =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "caeEnZ", SPRITESHEET_CAER_EN_Z_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_caer_en_z );

	log( "Se cargara el sprite para la accion de caerse y levantarse inmediatamente del personaje", LOG_DEBUG );
	Sprite* sprite_caer_y_levantarse =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "caeYSeLevanta", SPRITESHEET_CAER_Y_LEVANTAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_caer_y_levantarse );

	log( "Se cargara el sprite para la accion de cubrirse del personaje", LOG_DEBUG );
	Sprite* sprite_cubrirse =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "cubrirse", SPRITESHEET_CUBRIRSE_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_cubrirse );

	log( "Se cargara el sprite para la accion de cubrirse agachado del personaje", LOG_DEBUG );
	Sprite* sprite_cubrirse_agachado =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "cubrirseAgachado", SPRITESHEET_CUBRIRSE_AGACHADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_cubrirse_agachado );

	log( "Se cargara el sprite para la pose de victoria del personaje", LOG_DEBUG );
	Sprite* sprite_ganar =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "gana", SPRITESHEET_GANAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_ganar );

	log( "Se cargara el sprite para la accion de gancho del personaje", LOG_DEBUG );
	Sprite* sprite_gancho =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "gancho", SPRITESHEET_GANCHO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_gancho );

	log( "Se cargara el sprite para la accion de morirse del personaje", LOG_DEBUG );
	Sprite* sprite_morir =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "muere", SPRITESHEET_MORIR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_morir );

	log( "Se cargara el sprite para la accion de patada alta del personaje", LOG_DEBUG );
	Sprite* sprite_patada_alta =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "patadaAlta", SPRITESHEET_PATADA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_patada_alta );

	log( "Se cargara el sprite para la accion de patada baja del personaje", LOG_DEBUG );
	Sprite* sprite_patada_baja =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "patadaBaja", SPRITESHEET_PATADA_BAJA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_patada_baja );

	log( "Se cargara el sprite para la accion de patada circular del personaje", LOG_DEBUG );
	Sprite* sprite_patada_circular =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "patadaConGiro", SPRITESHEET_PATADA_CIRCULAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_patada_circular );

	log( "Se cargara el sprite para la accion de patada saltando del personaje", LOG_DEBUG );
	Sprite* sprite_patada_saltando =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "patadaEnSalto", SPRITESHEET_PATADA_SALTANDO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_patada_saltando );

	log( "Se cargara el sprite para la accion de pina agachado del personaje", LOG_DEBUG );
	Sprite* sprite_pina_agachado =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "pinaAgachado", SPRITESHEET_PINA_AGACHADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_pina_agachado );

	log( "Se cargara el sprite para la accion de pina alta del personaje", LOG_DEBUG );
	Sprite* sprite_pina_alta =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "pinaAlta", SPRITESHEET_PINA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_pina_alta );

	log( "Se cargara el sprite para la accion de pina baja del personaje", LOG_DEBUG );
	Sprite* sprite_pina_baja =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "pinaBaja", SPRITESHEET_PINA_BAJA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_pina_baja );

	log( "Se cargara el sprite para la accion de pina saltando del personaje", LOG_DEBUG );
	Sprite* sprite_pina_saltando =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "pinaEnSalto", SPRITESHEET_PINA_SALTANDO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_pina_saltando );

	log( "Se cargara el sprite para la accion recibir golpe agachado del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_agachado =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "recibeGolpeAgachado", SPRITESHEET_RECIBIR_GOLPE_AGACHADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_recibir_golpe_agachado );

	log( "Se cargara el sprite para la accion de recibir golpe alto del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_alto =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "recibeGolpeAlto", SPRITESHEET_RECIBIR_GOLPE_ALTO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_recibir_golpe_alto );

	log( "Se cargara el sprite para la accion de recibir golpe bajo del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_bajo =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "recibeGolpeBajo", SPRITESHEET_RECIBIR_GOLPE_BAJO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_recibir_golpe_bajo );

	log( "Se cargara el sprite para la accion de recibir golpes fuerte del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_fuerte =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "recibeGolpeFuerte", SPRITESHEET_RECIBIR_GOLPE_FUERTE_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_recibir_golpe_fuerte );

	log( "Se cargara el sprite para la accion de combo de pina baja del personaje", LOG_DEBUG );
	Sprite* sprite_combo_pina_baja =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "comboPinaBaja", SPRITESHEET_COMBO_PINA_BAJA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_combo_pina_baja );

	log( "Se cargara el sprite para la accion de combo de pina alta del personaje", LOG_DEBUG );
	Sprite* sprite_combo_pina_alta =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "comboPinaAlta", SPRITESHEET_COMBO_PINA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_combo_pina_alta );

	log( "Se cargara el sprite para la toma 1 del personaje", LOG_DEBUG );
	Sprite* sprite_toma_1 =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "toma1", SPRITESHEET_TOMA_1_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_toma_1 );

	log( "Se cargara el sprite para la accion del poder 1 del personaje", LOG_DEBUG );
	Sprite* sprite_poder_1 =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "poder1", SPRITESHEET_PODER_1_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_poder_1 );

	log( "Se cargara el sprite para la accion del poder 2 del personaje", LOG_DEBUG );
	Sprite* sprite_poder_2 =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "poder2", SPRITESHEET_PODER_2_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_poder_2 );

	log( "Se cargara el sprite para la accion de finish del personaje", LOG_DEBUG );
	Sprite* sprite_finish =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "finish", SPRITESHEET_FINISH_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_finish );

	log( "Se cargara el sprite para la accion de la fatality 1 del personaje", LOG_DEBUG );
	Sprite* sprite_fatality_1 =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "fatality1", SPRITESHEET_FATALITY_1_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_fatality_1 );

	log( "Se cargara el sprite para la accion de ser tomado del personaje", LOG_DEBUG );
	Sprite* sprite_tomado =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "esTomado", SPRITESHEET_TOMADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_tomado );

	log( "Se cargara el sprite para el personaje bebe", LOG_DEBUG );
	Sprite* sprite_bebe =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "bebe", SPRITESHEET_BEBE_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_bebe);

	log( "Se cargara el sprite para la accion de que se le arranque la cabeza con un gancho al personaje.", LOG_DEBUG );
	Sprite* sprite_fatality_gancho =  cargarSprite( root, ruta_carpeta, ruta_sonidos, "fatalityGancho", SPRITESHEET_FATALITY_GANCHO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje, cambiar_color, h_inicial, h_final, desplazamiento );
	sprites.push_back( sprite_fatality_gancho );

	log( "Se crearon todos los sprites del personaje.", LOG_DEBUG );
	return sprites;

}

vector<Combo*> ParserJSON::cargarCombos(Json::Value root, bool fatality) {

	vector<Combo*> combos;
	log("Se inicia la carga de los combos del personaje.", LOG_DEBUG);

	if (!root.isMember("combos") || !root["combos"].isArray()) {
		log("No se especificaron parametros para los combos del personaje en un vector. El personaje no tendra ningun combo.", LOG_WARNING);
	} else {
		for (int i = 0; i < (int) root["combos"].size(); i++) {
			try {
				string combostream = root["combos"][i].asString();
				bool combo_valido = true;
				for(int i = 0; i < (int) combostream.size(); i++) {
					if ( !isdigit(combostream.at(i)) )
						combo_valido = false;
						break;
				}
				if (combo_valido) {
					Combo* combo = new Combo(combostream, fatality);
					combos.push_back(combo);
					log("El combo fue cargado correctamente. ", LOG_DEBUG);
				} else {
					log("El combo no es una cadena de numeros consecutivos. No es un combo valido. Se ignora la carga del combo.", LOG_ERROR);
				}
			} catch (exception &e) {
				log("El combo no es una cadena de texto valida. Se ignora la carga del combo.");
				continue;
			}
		}
	}
	return combos;
}


int ParserJSON::cargarComando( Json::Value botones, const char* accion, int comando_default) {
	int comando_accion;
	if ( ! botones.isMember(accion) ) {
		comando_accion = comando_default;
		log("No se especifico la configuracion del comando de la accion. Se setea por defecto.", LOG_WARNING);
	} else {
		try {
			comando_accion = botones.get( accion, -1 ).asInt();
			if ( comando_accion == -1 )
				comando_accion = comando_default;
		} catch ( exception &e ) {
			comando_accion = comando_default;
			log( "El boton correspondiente a la accion no es un numero valido. Se setea por defecto.", LOG_ERROR );
		}
	}
	return comando_accion;
}


void ParserJSON::cargarMapaComandos(Json::Value root) {

	if ( ! root.isMember("comandos") ) {
		log("No se especificaron parametros para el mapeo de comandos y botones. Se setean por defecto.", LOG_WARNING);
		mapaComandosDefault(comandos_luchador1, comandos_luchador2);
		return;
	}

	if ( ! root["comandos"].isMember("luchador1") || ! root["comandos"].isMember("luchador2") ) {
		log("No se especificaron correctamente los parametros para el mapeo de comandos y botones de los jugadores o de algun jugador. Se setean por defecto.", LOG_WARNING);
		mapaComandosDefault(comandos_luchador1, comandos_luchador2);
		return;
	}

	log("Se cargara la configuracion del comando de pina baja.", LOG_DEBUG);
	int comando_pina_baja1 = cargarComando(root["comandos"]["luchador1"], "pina baja", COMANDO_PINA_BAJA_DEFAULT);
	int comando_pina_baja2 = cargarComando(root["comandos"]["luchador2"], "pina baja", COMANDO_PINA_BAJA_DEFAULT);

	log("Se cargara la configuracion del comando de patada baja.", LOG_DEBUG);
	int comando_patada_baja1 = cargarComando(root["comandos"]["luchador1"], "patada baja", COMANDO_PATADA_BAJA_DEFAULT);
	int comando_patada_baja2 = cargarComando(root["comandos"]["luchador2"], "patada baja", COMANDO_PATADA_BAJA_DEFAULT);

	log("Se cargara la configuracion del comando de pina alta.", LOG_DEBUG);
	int comando_pina_alta1 = cargarComando(root["comandos"]["luchador1"], "pina alta", COMANDO_PINA_ALTA_DEFAULT);
	int comando_pina_alta2 = cargarComando(root["comandos"]["luchador2"], "pina alta", COMANDO_PINA_ALTA_DEFAULT);

	log("Se cargara la configuracion del comando de patada alta.", LOG_DEBUG);
	int comando_patada_alta1 = cargarComando(root["comandos"]["luchador1"], "patada alta", COMANDO_PATADA_ALTA_DEFAULT);
	int comando_patada_alta2 = cargarComando(root["comandos"]["luchador2"], "patada alta", COMANDO_PATADA_ALTA_DEFAULT);

	log("Se cargara la configuracion del comando de cubrirse.", LOG_DEBUG);
	int comando_cubrirse1 = cargarComando(root["comandos"]["luchador1"], "cubrirse", COMANDO_CUBRIRSE_DEFAULT);
	int comando_cubrirse2 = cargarComando(root["comandos"]["luchador2"], "cubrirse", COMANDO_CUBRIRSE_DEFAULT);

	log("Se cargara la configuracion del comando de volver al menu inicial.", LOG_DEBUG);
	int comando_menu1 = cargarComando(root["comandos"]["luchador1"], "menu", COMANDO_MENU_DEFAULT);
	int comando_menu2 = cargarComando(root["comandos"]["luchador2"], "menu", COMANDO_MENU_DEFAULT);

	log("Se cargara la configuracion del comando de reset en modo practica.", LOG_DEBUG);
	int comando_reset1 = cargarComando(root["comandos"]["luchador1"], "reset", COMANDO_RESET_DEFAULT);
	int comando_reset2 = cargarComando(root["comandos"]["luchador2"], "reset", COMANDO_RESET_DEFAULT);


	std::map<std::string, int>* mapita1 = new std::map<std::string,int>;
	mapita1->operator[](string("pina baja")) = comando_pina_baja1;
	mapita1->operator[](string("patada baja")) = comando_patada_baja1;
	mapita1->operator[](string("pina alta")) = comando_pina_alta1;
	mapita1->operator[](string("patada alta")) = comando_patada_alta1;
	mapita1->operator[](string("cubrirse"))= comando_cubrirse1;
	mapita1->operator[](string("menu")) = comando_menu1;
	mapita1->operator[](string("reset")) = comando_reset1;

	comandos_luchador1 = mapita1;
	log( "Se cargo correctamente el mapa de comandos y botones del primer controlador.", LOG_DEBUG );

	std::map<std::string, int>* mapita2 = new std::map<std::string,int>;
	mapita2->operator[](string("pina baja")) = comando_pina_baja2;
	mapita2->operator[](string("patada baja")) = comando_patada_baja2;
	mapita2->operator[](string("pina alta")) = comando_pina_alta2;
	mapita2->operator[](string("patada alta")) = comando_patada_alta2;
	mapita2->operator[](string("cubrirse"))= comando_cubrirse2;
	mapita2->operator[](string("menu")) = comando_menu2;
	mapita1->operator[](string("reset")) = comando_reset2;

	comandos_luchador2 = mapita2;
	log( "Se cargo correctamente el mapa de comandos y botones del segundo controlador.", LOG_DEBUG );

}

vector<float> ParserJSON::cargarColorAlternativo(Json::Value personaje) {
	float h_inicial, h_final, desplazamiento;
	vector<float> color;

	if ( ! personaje.isMember("color-alternativo") ) {
		log( "No se especificaron parametros para el color alternativo para el personaje. No se cambiarian los colores.", LOG_WARNING );
	} else {
		if ( ! personaje["color-alternativo"].isMember("h-inicial") ) {
			h_inicial = COLOR_H_INICIAL_DEFAULT;
			log( "No se especifico el hue inicial para desplazar hacia otro color alternativo. Se setea por defecto.", LOG_ERROR );
		} else {
			try {
				h_inicial = personaje["color-alternativo"].get( "h-inicial", COLOR_H_INICIAL_DEFAULT ).asFloat();
				if (h_inicial < 0) log( "El hue se expresa en grados sexagesimales. El valor es menor a 0, pero se adapta al rango [0,360] de la circunferencia.", LOG_WARNING );
				else if (h_inicial > 360) log( "El hue se expresa en grados sexagesimales. El valor es mayor a 360, pero se adapta al rango [0,360] de la circunferencia.", LOG_WARNING );
				else log( "Se cargo el hue inicial para el desplazamiento al color alternativo.", LOG_DEBUG );
			} catch ( exception &e ) {
				h_inicial = COLOR_H_INICIAL_DEFAULT;
				log( "El hue inicial especificado para el desplazamiento al color alternativo no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! personaje["color-alternativo"].isMember("h-final") ) {
			h_final = COLOR_H_FINAL_DEFAULT;
			log( "No se especifico el hue final para desplazar hacia otro color alternativo. Se setea por defecto.", LOG_ERROR );
		} else {
			try {
				h_final = personaje["color-alternativo"].get( "h-final", COLOR_H_FINAL_DEFAULT ).asFloat();
				if (h_final < 0) log( "El hue se expresa en grados sexagesimales. El valor es menor a 0, pero se adapta al rango [0,360] de la circunferencia.", LOG_WARNING );
				else if (h_final > 360) log( "El hue se expresa en grados sexagesimales. El valor es mayor a 360, pero se adapta al rango [0,360] de la circunferencia.", LOG_WARNING );
				else log( "Se cargo el hue final para el desplazamiento al color alternativo.", LOG_DEBUG );
			} catch ( exception &e ) {
				h_final = COLOR_H_FINAL_DEFAULT;
				log( "El hue final especificado para el desplazamiento al color alternativo no es un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! personaje["color-alternativo"].isMember("desplazamiento") ) {
			desplazamiento = COLOR_DESPLAZAMIENTO_DEFAULT;
			log( "No se especificaron los grados de desplazamiento hacia otro color alternativo. Se setea por defecto.", LOG_ERROR );
		} else {
			try {
				desplazamiento = personaje["color-alternativo"].get( "desplazamiento", COLOR_DESPLAZAMIENTO_DEFAULT ).asFloat();
				log( "Se cargaron los grados de el desplazamiento hacia el color alternativo.", LOG_DEBUG );
			} catch ( exception &e ) {
				desplazamiento = COLOR_DESPLAZAMIENTO_DEFAULT;
				log( "Los grados de desplazamiento hacia el color alternativo especificados no son un numero valido. Se setea por defecto.", LOG_ERROR );
			}
		}
	}
	color.push_back(h_inicial);
	color.push_back(h_final);
	color.push_back(desplazamiento);

	return color;
}


Personaje* ParserJSON::cargarPersonaje(string nombre_personaje, Json::Value root, Ventana* ventana, bool cambiar_color) {

	Personaje* personaje;
	float personaje_ancho, personaje_alto, personaje_velocidad;
	string personaje_carpeta_sprites, personaje_carpeta_arrojables, personaje_carpeta_droppables, personaje_carpeta_sonidos, personaje_nombre, personaje_foto;
	if ( ! root.isMember("personajes") || ! root["personajes"].isArray() ) {
		personaje = generarPersonajeDefault(ventana);
		log( "No se especificaron parametros para la creacion de los personajes en un vector. Se generan el personaje por defecto.", LOG_ERROR );
	} else {
		for ( int k=0; k < (int)root["personajes"].size(); k++ ) {
			if ( ! root["personajes"][k].isMember("nombre") ) {
				continue;
			} else {
				try {
					personaje_nombre = root["personajes"][k].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
					if ( ! personaje_nombre.string::compare(nombre_personaje) ) {
						log ( "Se encontro el personaje con el nombre indicado.", LOG_DEBUG );
						if ( ! root["personajes"][k].isMember("ancho") ) {
							personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
							log( "No se especifico el ancho logico del personaje. Se setea por defecto en 30.", LOG_WARNING );
						} else {
							try {
								personaje_ancho = root["personajes"][k].get( "ancho", PERSONAJE_ANCHO_DEFAULT ).asFloat();
								if ( personaje_ancho < 0 ) {
									personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
									log( "El ancho del personaje no puede ser negativo. Se setea por defecto en 30.", LOG_WARNING );
								} else
									log( "Se cargo correctamente el ancho logico del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
								log( "El ancho logico del personaje inidicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
							}
						}
						if ( ! root["personajes"][k].isMember("alto") ) {
							personaje_alto = PERSONAJE_ALTO_DEFAULT;
							log( "No se especifico el alto logico del personaje. Se setea por defecto en 60.", LOG_WARNING );
						} else {
							try {
								personaje_alto = root["personajes"][k].get( "alto", PERSONAJE_ALTO_DEFAULT ).asFloat();
								if ( personaje_alto < 0 ) {
									personaje_alto = PERSONAJE_ALTO_DEFAULT;
									log( "El alto del personaje no puede negativo. Se setea por defecto en 60.", LOG_WARNING );
								} else
									log( "Se cargo correctamente el alto logico del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_alto = PERSONAJE_ALTO_DEFAULT;
								log( "El alto logico del personaje inidicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
							}
						}
						if ( ! root["personajes"][k].isMember("velocidad") ) {
							personaje_velocidad = PERSONAJE_VELOCIDAD_DEFAULT;
							log( "No se especifico la velocidad del personaje. Se setea por defecto.", LOG_WARNING );
						} else {
							try {
								personaje_velocidad = root["personajes"][k].get( "velocidad", PERSONAJE_VELOCIDAD_DEFAULT ).asFloat();
								if ( personaje_velocidad < 0 ) {
									personaje_velocidad = PERSONAJE_VELOCIDAD_DEFAULT;
									log( "La velocidad del personaje no puede ser negativa. Se setea por defecto.", LOG_WARNING );
								} else
									log( "Se cargo correctamente la velocidad del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_velocidad = PERSONAJE_VELOCIDAD_DEFAULT;
								log( "La velocidad del personaje indicada es invalida y no puede ser convertida a un numero. Se setea por defecto.", LOG_ERROR );
							}
						}
						if ( ! root["personajes"][k].isMember("sprites") ) {
							personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
							log( "No se especifico la carpeta contenedora de los sprites del personaje. Se utiliza carpeta por defecto.", LOG_ERROR );
						} else {
							try {
								personaje_carpeta_sprites = root["personajes"][k].get( "sprites", PERSONAJE_CARPETA_SPRITES_DEFAULT ).asString();
								struct stat sb;
								if ( stat(personaje_carpeta_sprites.c_str(), &sb) != 0 ) {
									log( "La ruta a la carpeta de sprites del personaje no existe. Se carga la ruta por defecto.", LOG_ERROR );
									personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
								} else	log ( "Se cargo correctamente la ruta a la carpeta contenedora de los sprites del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_carpeta_sprites = PERSONAJE_CARPETA_SPRITES_DEFAULT;
								log( "La ruta a la carpeta contenedora de los sprites del personaje indicada no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
							}
						}

						if ( ! root["personajes"][k].isMember("foto") ) {
							personaje_foto = PERSONAJE_FOTO_DEFAULT;
							log( "No se especifico la foto del personaje. Se utiliza una por defecto.", LOG_WARNING );
						} else {
							try {
								personaje_foto = root["personajes"][k].get( "foto", PERSONAJE_FOTO_DEFAULT ).asString();
								struct stat sb;
								if ( stat(personaje_foto.c_str(), &sb) != 0 ) {
									log( "La ruta a la foto del personaje no existe. Se carga la ruta por defecto.", LOG_ERROR );
									personaje_foto = PERSONAJE_FOTO_DEFAULT;
								} else	log ( "Se cargo correctamente la ruta a la foto del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_foto = PERSONAJE_FOTO_DEFAULT;
								log( "La ruta a la foto del personaje indicada no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
							}
						}

						if ( ! root["personajes"][k].isMember("poderes") ) {
							personaje_carpeta_arrojables = PERSONAJE_CARPETA_ARROJABLES_DEFAULT;
							log( "No se especifico la carpeta contenedora de los poderes arrojables del personaje. Se utiliza carpeta por defecto.", LOG_ERROR );
						} else {
							try {
								personaje_carpeta_arrojables = root["personajes"][k].get( "poderes", PERSONAJE_CARPETA_ARROJABLES_DEFAULT ).asString();
								struct stat sb;
								if ( stat(personaje_carpeta_arrojables.c_str(), &sb) != 0 ) {
									log( "La ruta a la carpeta de poderes del personaje no existe. Se carga la ruta por defecto.", LOG_ERROR );
									personaje_carpeta_arrojables = PERSONAJE_CARPETA_ARROJABLES_DEFAULT;
								} else	log ( "Se cargo correctamente la ruta a la carpeta contenedora de los poderes del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_carpeta_arrojables = PERSONAJE_CARPETA_ARROJABLES_DEFAULT;
								log( "La ruta a la carpeta contenedora de los poderes del personaje indicada no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
							}
						}

						if ( ! root["personajes"][k].isMember("droppables") ) {
							personaje_carpeta_droppables = PERSONAJE_CARPETA_DROPPABLES_DEFAULT;
							log( "No se especifico la carpeta contenedora de los objetos droppables del personaje. Se utiliza carpeta por defecto.", LOG_ERROR );
						} else {
							try {
								personaje_carpeta_droppables = root["personajes"][k].get( "droppables", PERSONAJE_CARPETA_DROPPABLES_DEFAULT ).asString();
								struct stat sb;
								if ( stat(personaje_carpeta_droppables.c_str(), &sb) != 0 ) {
									log( "La ruta a la carpeta de droppables del personaje no existe. Se carga la ruta por defecto.", LOG_ERROR );
									personaje_carpeta_droppables = PERSONAJE_CARPETA_DROPPABLES_DEFAULT;
								} else	log ( "Se cargo correctamente la ruta a la carpeta contenedora de los droppables del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_carpeta_droppables = PERSONAJE_CARPETA_DROPPABLES_DEFAULT;
								log( "La ruta a la carpeta contenedora de los droppables del personaje indicada no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
							}
						}

						if ( ! root["personajes"][k].isMember("sonidos") ) {
							personaje_carpeta_sonidos = PERSONAJE_CARPETA_SONIDOS_DEFAULT;
							log( "No se especifico la carpeta contenedora de los sonidos del personaje. Se utiliza carpeta por defecto.", LOG_ERROR );
						} else {
							try {
								personaje_carpeta_sonidos = root["personajes"][k].get( "sonidos", PERSONAJE_CARPETA_SONIDOS_DEFAULT ).asString();
								struct stat sb;
								if ( stat(personaje_carpeta_sonidos.c_str(), &sb) != 0 ) {
									log( "La ruta a la carpeta de sonidos del personaje no existe. Se carga la ruta por defecto.", LOG_ERROR );
									personaje_carpeta_sonidos = PERSONAJE_CARPETA_SONIDOS_DEFAULT;
								} else	log ( "Se cargo correctamente la ruta a la carpeta contenedora de los sonidos del personaje.", LOG_DEBUG );
							} catch ( exception &e ) {
								personaje_carpeta_sonidos = PERSONAJE_CARPETA_SONIDOS_DEFAULT;
								log( "La ruta a la carpeta contenedora de los sonidos del personaje indicada no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
							}
						}

						// Cargo los combos del personaje.
						vector<Combo*> combos = cargarCombos(root["personajes"][k]);

						// Cargo las fatalities del personaje.
						vector<Combo*> fatalities = cargarCombos(root["personajes"][k], true);
						// Inserto las fatalities en el vector de combos.
						for (int g = 0; g < (int) fatalities.size(); g++) {
							combos.push_back(fatalities[g]);
						}

						// Cargo los parametros para el cambio de color del personaje.
						vector<float> colorAlternativo = cargarColorAlternativo(root["personajes"][k]);

						// Creo Sprites del personaje.
						vector<Sprite*> sprites = cargarSprites(personaje_carpeta_sprites, personaje_carpeta_sonidos, ventana, personaje_ancho, personaje_alto, cambiar_color, colorAlternativo[0], colorAlternativo[1], colorAlternativo[2]);

						// Creo objetos arrojables (poderes).
						vector<ObjetoArrojable*> arrojables = cargarArrojables(personaje_carpeta_arrojables, personaje_carpeta_sonidos, ventana, personaje_ancho, personaje_alto, cambiar_color, colorAlternativo[0], colorAlternativo[1], colorAlternativo[2]);

						// Creo objetos droppables.
						vector<ObjetoDroppable*> droppables = cargarDroppables(personaje_carpeta_droppables, personaje_carpeta_sonidos, ventana);


						// Crear personaje.
						Personaje* personaje;
						if (!personaje_nombre.string::compare(string("Liu Kang")))
							personaje = new LiuKang(personaje_nombre, sprites, arrojables, personaje_velocidad);
						else if (!personaje_nombre.string::compare(string("Sub-Zero")))
							personaje = new SubZero(personaje_nombre, sprites, arrojables, personaje_velocidad);
						else if (!personaje_nombre.string::compare(string("Jax")))
							personaje = new Jax(personaje_nombre, sprites, arrojables, personaje_velocidad);
						else
							personaje = new Personaje(personaje_nombre, sprites, arrojables, personaje_velocidad);
						log( "Se creo correctamente el personaje.", LOG_DEBUG );

						personaje->setCombos(combos);
						log("Se le asignaron los combos correspondientes.", LOG_DEBUG);

						personaje->setObjetos(droppables);
						log("Se le asignaron los objetos droppables correspondientes al personaje.", LOG_DEBUG);

						personaje->setPathLogo(personaje_foto);
						log("Se le asigno al personaje su foto de perfil.", LOG_DEBUG);

						return personaje;
					}
				} catch ( exception &e ) {
					continue;
				}
			}
		}
		personaje = generarPersonajeDefault(ventana);
		log( "No se encontro el personaje con el nombre indicado en el vector de personajes. Se genera personaje por defecto.", LOG_ERROR );
	}
	return personaje;
}

vector<Personaje*> ParserJSON::cargarPersonajes(Json::Value root, Ventana* ventana) {
	vector<Personaje*> personajes;
	vector<string> nombres_personajes;
	Personaje* personaje;
	string nombre;

	log( "Se cargaran todos los personajes del juego.", LOG_DEBUG );
	if ( ! root.isMember("personajes") || ! root["personajes"].isArray() || root["personajes"].size() < 2 ) {
		personajes = generarPersonajesDefault(ventana);
		log( "No se especificaron parametros para la creacion de los personajes en un vector. Se generan dos personajes por defecto.", LOG_ERROR );
	} else {
		for ( int i=0; i < (int) root["personajes"].size(); i++ ) {
			log( "Se cargara un personaje nuevo.", LOG_DEBUG );
			if ( ! root["personajes"][i].isMember("nombre") ) {
				log( "El personaje no tiene especificado un nombre. Se ignorara su carga.", LOG_ERROR );
				continue;
			}
			try {
				nombre = root["personajes"][i].get( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
				if ( find(nombres_personajes.begin(), nombres_personajes.end(), nombre) != nombres_personajes.end() ) {
					log( "Ya se cargo un personaje con este nombre. Se ignora la carga de este personaje.", LOG_ERROR );
				} else {
					nombres_personajes.push_back(nombre);
					personaje = cargarPersonaje(nombre, root, ventana, false);
					personajes.push_back(personaje);
				}
			} catch ( exception &e ) {
				log( "El nombre indicado no es una cadena de texto valida. Se ignora la carga del personaje.", LOG_ERROR );
				continue;
			}
		}
	}

	// Verifico que se tengan al menos un personaje.
	if ( personajes.size() < 1 ) {
		personajes.push_back( generarPersonajeDefault(ventana) );
		log( "No se cargo ningun personaje. Se setea un personaje por defecto.", LOG_ERROR );
	}

	// Verifico que haya 12 personajes. Sino, se repite la carga hasta completarlos.
	int cant_personajes_inicial = personajes.size();
	if (cant_personajes_inicial < CANTIDAD_PERSONAJES_DEFAULT)
		log("Se requiere un minimo de 12 personajes. Se repite la carga de los personajes en orden hasta alcanzar esa cantidad.", LOG_WARNING);
	while (personajes.size() < CANTIDAD_PERSONAJES_DEFAULT) {
		for (int j = 0; j < cant_personajes_inicial; j++) {
			if (personajes.size() >= CANTIDAD_PERSONAJES_DEFAULT)
				break;
			nombre = personajes[j]->getNombre();
			personaje = cargarPersonaje(nombre, root, ventana, false);
			personajes.push_back(personaje);
		}
	}

	return personajes;

}

Escenario* ParserJSON::cargarEscenario(string nombre_escenario, Json::Value root, Ventana* ventana, float ventana_ancho) {

	Escenario* escenario;

	// Obtener las dimensiones logicas del escenario.
	// En caso de error se setean por defecto.
	string escenario_nombre;
	float escenario_ancho, escenario_alto, y_piso;
	int personajes_z_index;
	bool z_index_ok = true;
	if (! root.isMember("escenarios") || ! root["escenarios"].isArray() || root["escenarios"].size() == 0) {
		escenario = generarEscenarioDefault(ventana);
		log("No se especificaron parametros para la creacion de escenarios en un vector o el vector esta vacio. Se genera un escenario por defecto.", LOG_ERROR);
	} else {
		for (int i = 0; i < (int) root["escenarios"].size(); i++) {
			if ( ! root["escenarios"][i].isMember("nombre") ) {
				continue;
			} else {
				try {
					escenario_nombre = root["escenarios"][i].get ( "nombre", ESCENARIO_NOMBRE_DEFAULT ).asString();
					if ( ! escenario_nombre.string::compare(nombre_escenario) ) {
						log("Se encontro el escenario con el nombre indicado.", LOG_DEBUG);
						if ( ! root["escenarios"][i].isMember("ancho") ) {
							escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
							log( "No se especifico el ancho logico del escenario. Se setea por defecto.", LOG_WARNING );
						} else {
							try {
								escenario_ancho = root["escenarios"][i].get( "ancho", ESCENARIO_ANCHO_DEFAULT ).asFloat();
								if ( escenario_ancho < 0 ) {
									escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
									// Informar al usuario el cambio de ancho logico.
									log( "El ancho del escenario no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
								} else
									log( "Se cargo correctamente el ancho logico del escenario.", LOG_DEBUG );
							} catch ( exception &e ) {
								escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
								log( "El ancho logico del escenario indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
							}
						}
						if ( ! root["escenarios"][i].isMember("alto") ) {
							escenario_alto = ESCENARIO_ALTO_DEFAULT;
							log( "No se especifico el alto logico del escenario. Se setea por defecto.", LOG_WARNING );
						} else {
							try {
								escenario_alto = root["escenarios"][i].get( "alto", ESCENARIO_ALTO_DEFAULT ).asFloat();
								if ( escenario_alto < 0 ) {
									escenario_alto = ESCENARIO_ALTO_DEFAULT;
									// Informar al usuario el cambio de alto logico.
									log( "El alto del escenario no puede ser negativo. Se setea automaticamente por defecto.", LOG_WARNING );
								} else
									log( "Se cargo correctamente el alto logico del escenario.", LOG_DEBUG );
							} catch ( exception &e ) {
								escenario_alto = ESCENARIO_ALTO_DEFAULT;
								log( "El alto logico del escenario indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
							}
						}
						if ( ! root["escenarios"][i].isMember("y-piso") ) {
							y_piso = Y_PISO_DEFAULT;
							log( "No se especifico la altura del piso del escenario. Se setea por defecto.", LOG_WARNING );
						} else {
							try {
								y_piso = root["escenarios"][i].get( "y-piso", Y_PISO_DEFAULT ).asFloat();
								log ( "Se cargo correctamente la altura del piso.", LOG_DEBUG );
							} catch ( exception &e ) {
								y_piso = Y_PISO_DEFAULT;
								log( "La altura del piso del escenario (y-piso) indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
							}
						}
						if ( ! root["escenarios"][i].isMember("z-index_personajes") ) {
							personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
							z_index_ok = false;
							log( "No se especifico el z-index de los personajes. Se posicionan delante de todas las capas por defecto.", LOG_WARNING );
						} else {
							try {
								personajes_z_index = root["escenarios"][i].get( "z-index_personajes", PERSONAJES_Z_INDEX_DEFAULT ).asInt();
								log( "Se cargo correctamente el z-index de los personajes.", LOG_DEBUG );
							} catch ( exception &e ) {
								personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
								z_index_ok = false;
								log( "El z-index de los personajes indicado no es valido y no pudo ser convertido a un numero entero. Se colocan por defecto delante de todas las capas.", LOG_ERROR );
							}
						}


						// Creo el escenario
						escenario = new Escenario(escenario_nombre);
						log( "Se creo un escenario vacio", LOG_DEBUG );

						// Obtener las capas del escenario. La primera capa es el fondo del escenario.
						// Se setea por defecto el ancho en caso de error.
						// Si la imagen no existe, se usa una por defecto.
						string background;
						float capa_ancho, capa_alto;
						int capa_z_index;
						bool capas_ok = true;
						int j=0;
						if ( ! root["escenarios"][i].isMember("capas") || ! root["escenarios"][i]["capas"].isArray() ) {
							log( "No se encontraron parametros en un vector para la creacion de las capas. Se crean capas y se asignan valores por defecto.", LOG_ERROR );
							CapaFondo* capa_0 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_0_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,CAPA_0_BACKGROUND_DEFAULT,ventana);
							escenario->addCapa(capa_0);
							CapaFondo* capa_1 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_1_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+1,ESCENARIO_ANCHO_DEFAULT,CAPA_1_BACKGROUND_DEFAULT,ventana);
							escenario->addCapa(capa_1);
							CapaFondo* capa_2 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_2_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+2,ESCENARIO_ANCHO_DEFAULT,CAPA_2_BACKGROUND_DEFAULT,ventana);
							escenario->addCapa(capa_2);
							personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
							capas_ok = false;
						} else {
							const Json::Value capas = root["escenarios"][i]["capas"];
							for ( ; j < (int)capas.size(); j++ ) {
								if ( ! capas[j].isMember("imagen_fondo") ) {
									background = BACKGROUND_DEFAULT;
									log( "No se especifico la imagen de fondo de la capa. Se asigna una imagen por defecto.", LOG_ERROR );
								} else {
									try {
										background = capas[j].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();

										struct stat sb;
										if ( stat(background.c_str(), &sb) != 0 ) {
											log( "La ruta a la imagen de la capa no existe. Se carga la ruta por defecto.", LOG_ERROR );
											background = BACKGROUND_DEFAULT;
										} else log( "Se cargo el nombre de la imagen de la capa.", LOG_DEBUG );
									} catch ( exception &e ) {
										background = BACKGROUND_DEFAULT;
										log( "La ruta del archivo de la imagen de la capa no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
									}
								}
								if ( ! capas[j].isMember("ancho") ) {
									capa_ancho = VENTANA_ANCHO_DEFAULT;
									log( "No se especifico el ancho logico de la capa. Se setea en 600 por defecto.", LOG_WARNING );
								} else {
									try {
										capa_ancho = capas[j].get( "ancho", VENTANA_ANCHO_DEFAULT ).asFloat();
										if ( capa_ancho < 0 ) {
											capa_ancho = VENTANA_ANCHO_DEFAULT;
											// Informar al usuario el cambio de ancho.
											log( "El ancho de la capa no puede ser negativo. Se setea automaticamente en 600.", LOG_WARNING );
										}
										else log( "Se cargo correctamente el ancho logico de la capa.", LOG_DEBUG );
									} catch ( exception &e ) {
										capa_ancho = VENTANA_ANCHO_DEFAULT;
										log( "El ancho de la capa es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
									}
								}

								capa_z_index = j;

								// Setear alto logico de la capa de acuerdo al alto del escenario.
								capa_alto = escenario_alto;
								log ( "Se fijo el alto logico de la capa.", LOG_DEBUG );

								// Creo capas de fondo.
								CapaFondo* capa_fondo;
								try {
									capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, background, ventana );
									log( "Se creo correctamente la capa.", LOG_DEBUG );
								} catch ( CargarImagenException &e ) {
									delete capa_fondo;
									capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, BACKGROUND_DEFAULT, ventana );
									log( "No se pudo cargar la imagen de la capa. Se carga imagen por defecto. " + string(e.what()), LOG_ERROR );
								}

								// Agrego capa al escenario.
								escenario->addCapa(capa_fondo);
								log( "Se agrego la capa al mundo.", LOG_DEBUG );
							}
						}

						// Crear capa principal, donde estan los personajes y se desarrolla la accion.
						// Validaciones para el z-index de los personajes.
						if ( capas_ok && (! z_index_ok) ) personajes_z_index = i+1;
						CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personajes_z_index, escenario_ancho, ventana_ancho,y_piso);
						log( "Se creo correctamente la capa principal.", LOG_DEBUG );

						// Agrego capa principal al escenario.
						escenario->addCapaPrincipal( capa_principal, personajes_z_index );
						log( "Se agrego la capa principal al escenario.", LOG_DEBUG );



					} else
						log("No se encontro el escenario con el nombre indicado.", LOG_WARNING);
				} catch (exception &e) {
					log("El nombre del escenario no es una cadena de texto valida. Se ignora la carga del escenario en el mundo.", LOG_ERROR);
					continue;
				}
			}

		}
	}
	return escenario;
}

vector<Escenario*> ParserJSON::cargarEscenarios(Json::Value root, Ventana* ventana, float ventana_ancho) {

	vector<Escenario*> escenarios;
	vector<string> nombres_escenarios;
	Escenario* escenario;
	string nombre;

	log( "Se cargaran todos los escenarios del juego.", LOG_DEBUG );
	if ( ! root.isMember("escenarios") || ! root["escenarios"].isArray() || root["escenarios"].size() == 0 ) {
		escenarios.push_back( generarEscenarioDefault(ventana) );
		log( "No se especificaron parametros para la creacion de los escenarios en un vector. Se genera un escenario por defecto.", LOG_ERROR );
	} else {
		for ( int i=0; i < (int) root["escenarios"].size(); i++ ) {
			log( "Se cargara un escenario nuevo.", LOG_DEBUG );
			if ( ! root["escenarios"][i].isMember("nombre") ) {
				log( "El escenario no tiene especificado un nombre. Se ignorara la carga del escenario.", LOG_ERROR );
				continue;
			}
			try {
				nombre = root["escenarios"][i].get( "nombre", ESCENARIO_NOMBRE_DEFAULT ).asString();
				if ( find(nombres_escenarios.begin(), nombres_escenarios.end(), nombre) != nombres_escenarios.end() ) {
					log( "Ya se cargo un escenario con este nombre. Se ignora la carga de este escenario.", LOG_ERROR );
				} else {
					nombres_escenarios.push_back(nombre);
					escenario = cargarEscenario(nombre, root, ventana, ventana_ancho);
					escenarios.push_back(escenario);
				}
			} catch ( exception &e ) {
				log( "El nombre indicado no es una cadena de texto valida. Se ignora la carga del escenario.", LOG_ERROR );
				continue;
			}
		}
	}

	// Verifico que se tenga al menos un escenario.
	if ( escenarios.size() < 1 ) {
		escenarios.push_back( generarEscenarioDefault(ventana) );
		log( "No se cargo ningun escenario exitosamente. Se genera un escenario por defecto.", LOG_ERROR );
	}

	return escenarios;

}

Json::Value ParserJSON::obtenerRootDeArchivo(string ruta_archivo) {
	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivo;
	archivo.open(ruta_archivo.c_str());

	// Si no se pudo abrir archivo, se devuelve NULL.
	if ( ! archivo.is_open() ) {
		log( "No se pudo abrir el archivo JSON. Se arroja una excepcion.", LOG_ERROR );
		throw exception();
	}
	log ( "Se abrio el archivo JSON.", LOG_DEBUG );

	// Si no se pudo parsear archivo, se devuelve NULL.
	bool exito = reader.parse( archivo, root, false );
	if ( ! exito ) {
	    log( "No se pudo interpretar el JSON. Se arroja una excepcion. " + reader.getFormattedErrorMessages(), LOG_ERROR );
	    throw exception();
	} else
		log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivo.close();
	log ( "Se cerro el archivo JSON.", LOG_DEBUG );

	return root;
}

void ParserJSON::cargarTextosPelea(Mundo* mundo) {
	TextosPelea* textosPelea = new TextosPelea();

	Json::Value root = obtenerRootDeArchivo(string(RUTA_ARCHIVO_JSON_FIGHT));
	float ratio_x_ventana = m_ventana->obtenerRatioX();
	float ratio_y_ventana = m_ventana->obtenerRatioY();

	Sprite* spriteFight = cargarSprite(root, string(RUTA_CARPETA_SPRITE_FIGHT), string(RUTA_CARPETA_SONIDO_FIGHT), "fight", "fight.png", m_ventana, ratio_x_ventana, ratio_y_ventana);
	Sprite* spriteFinishHim = cargarSprite(root, string(RUTA_CARPETA_SPRITE_FINISHHIM), string(RUTA_CARPETA_SONIDO_FINISHHIM), "finishHim", "finishHim.png", m_ventana, ratio_x_ventana, ratio_y_ventana);
	Sprite* spriteFatality = cargarSprite(root, string(RUTA_CARPETA_SPRITE_FATALITY), string(RUTA_CARPETA_SONIDO_FATALITY), "fatality", "fatality.png", m_ventana, ratio_x_ventana, ratio_y_ventana);

	textosPelea->setTextoFight(spriteFight);
	textosPelea->setTextoFinishHim(spriteFinishHim);
	textosPelea->setTextoFatality(spriteFatality);

	mundo->setTextosPelea(textosPelea);
}

Personaje* ParserJSON::cambiarColorPersonaje(Personaje* el_personaje) {
	string nombre_personaje = el_personaje->getNombreDeCarga();
	string nombre_personaje_cambiado = el_personaje->getNombre();
	Json::Value root;
	Json::Reader reader;

	// Abrir archivo.
	ifstream archivoConfig;
	archivoConfig.open(m_ruta_archivo.c_str());

	// Si no se pudo abrir archivo, se devuelve NULL.
	if ( ! archivoConfig.is_open() ) {
		log( "No se pudo abrir el archivo de configuracion JSON para cargar el personaje con el cambio de color. No se cambia el color del personaje.", LOG_ERROR );
		return NULL;
	}
	log ( "Se abrio el archivo JSON de configuracion para efectuar el cambio de color del personaje.", LOG_DEBUG );

	// Si no se pudo parsear archivo, se devuelve NULL.
	bool exito = reader.parse( archivoConfig, root, false );
	if ( ! exito ) {
	    log( "No se pudo interpretar el JSON. No se cambia el color del personaje." + reader.getFormattedErrorMessages(), LOG_ERROR );
	    return NULL;
	} else
		log( "El archivo JSON es valido y fue interpretado correctamente.", LOG_DEBUG );

	// Cerrar archivo.
	archivoConfig.close();
	log ( "Se cerro el archivo JSON de configuracion.", LOG_DEBUG );

	// Cargo el personaje con el cambio de color seteado en true.
	Personaje* personaje = cargarPersonaje(nombre_personaje, root, m_ventana, true);
	personaje->setNombre(nombre_personaje_cambiado);
	return personaje;
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
		archivoConfig.open(JSON_CONFIG_DEFAULT);
		reader.parse( archivoConfig, root, false );
	}
	if ( json_invalido ) {
	    log( "No se pudo interpretar el JSON, se genera una partida por defecto." + reader.getFormattedErrorMessages(), LOG_ERROR );
		archivoConfig.open(JSON_CONFIG_DEFAULT);
		reader.parse( archivoConfig, root, false );
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
	int tiempo_combate;
	if ( ! root.isMember("tiempo") ) {
		log( "No se especifico el tiempo de combate. Se setea en 3 minutos por defecto.", LOG_WARNING );
		tiempo_combate = TIEMPO_DEFAULT;
	} else {
		try {
			tiempo = root.get( "tiempo", TIEMPO_DEFAULT ).asInt();
			if ( tiempo < 0 ) {
				tiempo_combate = TIEMPO_DEFAULT;
				// Informar al usuario el cambio de tiempo de la ronda.
				log ( "El tiempo no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
			} else {
				// Crear tiempo.
				tiempo_combate = tiempo;
				log( "Se cargo correctamente el tiempo del combate.", LOG_DEBUG );
			}
		} catch (exception &e) {
			tiempo_combate = TIEMPO_DEFAULT;
			log( "El tiempo indicado no pudo ser convertido a un numero. Se setea un tiempo por defecto", LOG_ERROR );
		}
	}

	// Obtener tiempo maximo de espera en los combos.
	int combos_tiempo_max;
	if ( ! root.isMember("tiempo_max_combos") ) {
		log( "No se especifico el tiempo max de espera de los combos. Se setea por defecto.", LOG_WARNING );
		combos_tiempo_max = COMBOS_TIEMPO_MAX_DEFAULT;
	} else {
		try {
			combos_tiempo_max = root.get( "tiempo_max_combos", COMBOS_TIEMPO_MAX_DEFAULT ).asInt();
			if ( combos_tiempo_max < 0 ) {
				combos_tiempo_max = COMBOS_TIEMPO_MAX_DEFAULT;
				log ( "El tiempo max de espera de los combos no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
			} else
				log( "Se cargo correctamente el tiempo maximo de espera de los combos.", LOG_DEBUG );
		} catch (exception &e) {
			combos_tiempo_max = COMBOS_TIEMPO_MAX_DEFAULT;
			log( "El tiempo indicado no pudo ser convertido a un numero. Se setea un tiempo por defecto", LOG_ERROR );
		}
	}

	// Obtener tolerancia de misses en los combos.
	int combos_tolerancia;
	if ( ! root.isMember("tolerancia_combos") ) {
		log( "No se especifico la tolerancia de misses de los combos. Se setea por defecto.", LOG_WARNING );
		combos_tolerancia = COMBOS_TOLERANCIA_DEFAULT;
	} else {
		try {
			combos_tolerancia = root.get( "tolerancia_combos", COMBOS_TOLERANCIA_DEFAULT ).asInt();
			if ( combos_tolerancia < 0 ) {
				combos_tolerancia = COMBOS_TOLERANCIA_DEFAULT;
				log ( "La tolerancia de misses de los combos no puede ser negativa. Se setea automaticamente.", LOG_WARNING );
			} else
				log( "Se cargo correctamente la tolerancia de misses de los combos.", LOG_DEBUG );
		} catch (exception &e) {
			combos_tolerancia = COMBOS_TOLERANCIA_DEFAULT;
			log( "La cantidad de misses posibles en un combo indicada no pudo ser convertida a un numero. Se setea por defecto", LOG_ERROR );
		}
	}

	// Obtener dimensiones de la ventana. Se setean por defecto en caso de error.
	// El alto se seteara luego dependiendo del escenario.
	int ventana_ancho_px, ventana_alto_px;
	float ventana_ancho, ventana_alto;
	if ( ! root.isMember("ventana") ) {
		log( "No se encontraron parametros para la creacion de la ventana. Se asignan valores por defecto.", LOG_ERROR );
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		ventana_ancho = VENTANA_ANCHO_DEFAULT;
		ventana_alto = VENTANA_ALTO_DEFAULT;
	} else {
		if ( ! root["ventana"].isMember("ancho-px") ) {
			ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
			log( "No se especifico el ancho en pixeles de la ventana. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_ancho_px = root["ventana"].get( "ancho-px", VENTANA_ANCHO_PX_DEFAULT ).asInt();
				if ( ventana_ancho_px < 0 ) {
					ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
					// Informar al usuario el cambio de ancho.
					log( "El ancho en pixeles de la ventana no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
				} else log( "Se cargo correctamente el ancho en pixeles de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
				log( "El ancho en pixeles de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! root["ventana"].isMember("alto-px") ) {
			ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
			log( "No se especifico el alto en pixeles de la ventana. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_alto_px = root["ventana"].get( "alto-px", VENTANA_ALTO_PX_DEFAULT ).asInt();
				if ( ventana_alto_px < 0 ) {
					ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
					// Informar al usuario el cambio de alto.
					log( "El alto en pixeles de la ventana no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
				} else log( "Se cargo correctamente el alto en pixeles de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
				log( "El alto en pixeles de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! root["ventana"].isMember("ancho") ) {
			ventana_ancho = VENTANA_ANCHO_DEFAULT;
			log( "No se especifico el ancho logico de la ventana. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_ancho = root["ventana"].get( "ancho", VENTANA_ANCHO_DEFAULT ).asFloat();
				if ( ventana_ancho < 0 ) {
					ventana_ancho = VENTANA_ANCHO_DEFAULT;
					// Informar al usuario el cambio de ancho logico.
					log( "El ancho logico de la ventana no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
				} else log( "Se cargo correctamente el ancho logico de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_ancho = VENTANA_ANCHO_DEFAULT;
				log( "El ancho logico de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
		if ( ! root["ventana"].isMember("alto") ) {
			ventana_alto = VENTANA_ALTO_DEFAULT;
			log( "No se especifico el alto logico de la ventana. Se setea por defecto.", LOG_WARNING );
		} else {
			try {
				ventana_alto = root["ventana"].get( "alto", VENTANA_ALTO_DEFAULT ).asFloat();
				if ( ventana_alto < 0 ) {
					ventana_ancho = VENTANA_ALTO_DEFAULT;
					// Informar al usuario el cambio de alto logico.
					log( "El alto logico de la ventana no puede ser negativo. Se setea automaticamente.", LOG_WARNING );
				} else log( "Se cargo correctamente el alto logico de la ventana.", LOG_DEBUG );
			} catch ( exception &e ) {
				ventana_alto = VENTANA_ALTO_DEFAULT;
				log( "El alto logico de la ventana indicado es invalido y no puede ser convertido a un numero. Se setea por defecto.", LOG_ERROR );
			}
		}
	}

	// Obtener relaciones entre pixeles y unidades logicas del mundo.
	float ratio_x = ventana_ancho_px / ventana_ancho;
	float ratio_y = ventana_alto_px / ventana_alto;
	log ( "Se calcularon las relaciones para el ancho y el alto entre los pixeles y las unidades logicas del mundo.", LOG_DEBUG );

	// Crear Ventana y abrirla.
	Ventana* ventana = new Ventana( ventana_ancho_px, ventana_alto_px, ratio_x, ratio_y );
	log ( "Se creo correctamente la ventana (camara).", LOG_DEBUG );
	if( ! ventana->create_window() ) {
		log( "No se puede inicializar la ventana. El programa no puede continuar.", LOG_ERROR );
		throw runtime_error( "No se pudo abrir la ventana del programa." );
	}
	m_ventana = ventana;

	// Se va a mostrar en pantalla una imagen durante el tiempo de carga
	if(ventana->mostrarImagen("data/img/etc/load.png")){
		log("Se muestra imagen bienvenida en Ventanta durante tiempo de carga", LOG_DEBUG );
	}

	// Obtener hash de comandos.
	this->cargarMapaComandos(root);

	Mundo* nuevo_mundo = new Mundo(ventana,tiempo_combate,comandos_luchador1,comandos_luchador2, combos_tiempo_max , combos_tolerancia);
	log ( "Se creo correctamente un mundo vacio.", LOG_DEBUG );
	log( "Se le asigno la ventana creada al nuevo mundo.", LOG_DEBUG );

	// Cargo todos los escenarios.
	vector<Escenario*> escenarios = cargarEscenarios(root, ventana, ventana_ancho);
	nuevo_mundo->addEscenarios(escenarios);
	log("Se agregaron los escenarios al nuevo mundo de la partida.", LOG_DEBUG);

	// Cargo todos los personajes.
	vector<Personaje*> personajes = cargarPersonajes(root, ventana);
	nuevo_mundo->addPersonajes(personajes);
	log( "Se agregaron los personajes al nuevo mundo de la partida.", LOG_DEBUG );

	// Cargo los textos de la pelea.
	//cargarTextosPelea(nuevo_mundo);
	//log("Los textos de pelea se cargaron correctamente.", LOG_DEBUG);

	return nuevo_mundo;
}

