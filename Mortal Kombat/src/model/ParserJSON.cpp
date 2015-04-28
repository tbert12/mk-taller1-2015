#include "ParserJSON.h"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	m_ruta_archivo = ruta_archivo;
}

ParserJSON::~ParserJSON() {
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



Sprite* ParserJSON::cargarSprite( Json::Value root, string ruta_carpeta, const char accion_sprite[], string spritesheet_accion, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje ) {
	Sprite* sprite;
	string spritesheet;
	if ( ! root.isMember(accion_sprite) ) {
		log( "No se encontro el sprite correspondiente a la accion del personaje. Se generan el sprite de la accion por defecto.", LOG_ERROR );
		return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
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
		if ( ! root[accion_sprite].isMember("frames") || ! root[accion_sprite]["frames"].isArray() ) {
			log( "No se encontraron especificaciones sobre los frames del spritesheet de la accion. Se genera el sprite por defecto.", LOG_ERROR );
			return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
		} else {
			const Json::Value frames_accion = root[accion_sprite]["frames"];
			vector<Frame*> frames( frames_accion.size() );
			vector<bool> loop_accion(frames.size(), false);
			for ( unsigned int i=0; i < frames_accion.size(); i++ ) {
				int x, y, alto, ancho;
				try {
					x = frames_accion[i].get( "x", -100 ).asInt();
					if ( x < 0 ) {
						log( "No se especifico la posicion X del frame o es negativa. Se genera el sprite de la accion por defecto.", LOG_ERROR );
						return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "La posicion X del frame indicada no es valida y no puede ser convertida a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				try {
					y = frames_accion[i].get( "y", -100 ).asInt();
					if ( y < 0 ) {
						log( "No se especifico la posicion Y del frame o es negativa. Se genera el sprite de la accion por defecto", LOG_ERROR );
						return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "La posicion Y del frame indicada es invalida y no puede ser convertida a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				try {
					alto = frames_accion[i].get( "Alto", -100 ).asInt();
					if ( alto < 0 ) {
						log( "No se especifico el alto del frame o es negativo. Se genera el sprite de la accion por defecto.", LOG_ERROR );
						return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "El alto del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				try {
					ancho = frames_accion[i].get( "Ancho", -100 ).asInt();
					if ( ancho < 0 ) {
						log( "No se especifico el ancho del frame o es negativo. Se genera el sprite de la accion por defecto.", LOG_ERROR );
						return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
					}
				} catch (exception &e) {
					log ( "El ancho del frame indicado es invalido y no puede ser convertido a un numero. Se genera el sprite de la accion por defecto.", LOG_ERROR );
					return crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				}
				bool loop;
				try {
					loop = frames_accion[i].get( "loop", false ).asBool();
				} catch (exception &e) {
					log ( "No se reconoce como booleano el parametro pasado para determinar si se debe loopear o no el sprite de la accion. Se setea en false por defecto.", LOG_ERROR );
					loop = false;
				}
				if ( loop ) {
					loop_accion[i] = true;
				}
				frames[i] = new Frame(x, y, alto, ancho);
				log( "Se creo correctamente un frame del spritesheet de la accion.", LOG_DEBUG );
			}
			try {
				sprite = new Sprite( ruta_carpeta + spritesheet, frames, ventana, ratio_x_personaje, ratio_y_personaje );
				for ( unsigned int j=0; j < frames.size(); j++ ) {
					if ( loop_accion[j] ) sprite->setLoop(j);
				}
				log( "Se creo correctamente el sprite para la accion del personaje.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				delete sprite;
				sprite = crearSpritePorDefecto(accion_sprite, ventana, ratio_x_personaje, ratio_y_personaje);
				log( "No se pudo abrir el spritesheet de la accion. Se genera el sprite por defecto. " + string(e.what()), LOG_ERROR );
			}
		}
	}
	return sprite;
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


	// Calculo los ratios del personaje.
	float ratio_x_personaje = getRatioXPersonaje(root, personaje_ancho);
	float ratio_y_personaje = getRatioYPersonaje(root, personaje_alto);

	// Cargo uno por uno los sprites correspondientes a cada accion.
	log( "Se cargara el sprite inicial para la accion de estar parado.", LOG_DEBUG );
	Sprite* sprite_parado =  cargarSprite( root, ruta_carpeta, "parado", SPRITESHEET_PARADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_parado );

	log( "Se cargara el sprite para la accion de caminar del personaje", LOG_DEBUG );
	Sprite* sprite_caminar =  cargarSprite( root, ruta_carpeta, "caminar", SPRITESHEET_CAMINAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_caminar );

	log( "Se cargara el sprite para la accion de saltar del personaje", LOG_DEBUG );
	Sprite* sprite_saltar =  cargarSprite( root, ruta_carpeta, "saltar", SPRITESHEET_SALTAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_saltar );

	log( "Se cargara el sprite para la accion de saltar en diagonal del personaje", LOG_DEBUG );
	Sprite* sprite_saltar_diagonal =  cargarSprite( root, ruta_carpeta, "saltardiagonal", SPRITESHEET_SALTAR_DIAGONAL_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_saltar_diagonal );

	log( "Se cargara el sprite para la accion de agacharse del personaje", LOG_DEBUG );
	Sprite* sprite_agachar =  cargarSprite( root, ruta_carpeta, "agachar", SPRITESHEET_AGACHAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_agachar );

	log( "Se cargara el sprite para la accion de pegar patada alta estando agachado del personaje", LOG_DEBUG );
	Sprite* sprite_agachado_patada_alta =  cargarSprite( root, ruta_carpeta, "agachadoPatadaAlta", SPRITESHEET_AGACHADO_PATADA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_agachado_patada_alta );

	log( "Se cargara el sprite para la accion de pegar patada baja estando agachado del personaje", LOG_DEBUG );
	Sprite* sprite_agachado_patada_baja =  cargarSprite( root, ruta_carpeta, "agachadoPatadaBaja", SPRITESHEET_AGACHADO_PATADA_BAJA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_agachado_patada_baja );

	log( "Se cargara el sprite para la accion de caerse por una barrida del personaje", LOG_DEBUG );
	Sprite* sprite_caer_en_z =  cargarSprite( root, ruta_carpeta, "caeEnZ", SPRITESHEET_CAER_EN_Z_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_caer_en_z );

	log( "Se cargara el sprite para la accion de caerse y levantarse inmediatamente del personaje", LOG_DEBUG );
	Sprite* sprite_caer_y_levantarse =  cargarSprite( root, ruta_carpeta, "caeYSeLevanta", SPRITESHEET_CAER_Y_LEVANTAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_caer_y_levantarse );

	log( "Se cargara el sprite para la accion de cubrirse del personaje", LOG_DEBUG );
	Sprite* sprite_cubrirse =  cargarSprite( root, ruta_carpeta, "cubrirse", SPRITESHEET_CUBRIRSE_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_cubrirse );

	log( "Se cargara el sprite para la accion de cubrirse agachado del personaje", LOG_DEBUG );
	Sprite* sprite_cubrirse_agachado =  cargarSprite( root, ruta_carpeta, "cubrirseAgachado", SPRITESHEET_CUBRIRSE_AGACHADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_cubrirse_agachado );

	log( "Se cargara el sprite para la pose de victoria del personaje", LOG_DEBUG );
	Sprite* sprite_ganar =  cargarSprite( root, ruta_carpeta, "gana", SPRITESHEET_GANAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_ganar );

	log( "Se cargara el sprite para la accion de gancho del personaje", LOG_DEBUG );
	Sprite* sprite_gancho =  cargarSprite( root, ruta_carpeta, "gancho", SPRITESHEET_GANCHO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_gancho );

	log( "Se cargara el sprite para la accion de morirse del personaje", LOG_DEBUG );
	Sprite* sprite_morir =  cargarSprite( root, ruta_carpeta, "muere", SPRITESHEET_MORIR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_morir );

	log( "Se cargara el sprite para la accion de patada alta del personaje", LOG_DEBUG );
	Sprite* sprite_patada_alta =  cargarSprite( root, ruta_carpeta, "patadaAlta", SPRITESHEET_PATADA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_patada_alta );

	log( "Se cargara el sprite para la accion de patada circular del personaje", LOG_DEBUG );
	Sprite* sprite_patada_circular =  cargarSprite( root, ruta_carpeta, "patadaConGiro", SPRITESHEET_PATADA_CIRCULAR_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_patada_circular );

	log( "Se cargara el sprite para la accion de patada saltando del personaje", LOG_DEBUG );
	Sprite* sprite_patada_saltando =  cargarSprite( root, ruta_carpeta, "patadaEnSalto", SPRITESHEET_PATADA_SALTANDO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_patada_saltando );

	log( "Se cargara el sprite para la accion de pina agachado del personaje", LOG_DEBUG );
	Sprite* sprite_pina_agachado =  cargarSprite( root, ruta_carpeta, "pinaAgachado", SPRITESHEET_PINA_AGACHADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_pina_agachado );

	log( "Se cargara el sprite para la accion de pina alta del personaje", LOG_DEBUG );
	Sprite* sprite_pina_alta =  cargarSprite( root, ruta_carpeta, "pinaAlta", SPRITESHEET_PINA_ALTA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_pina_alta );

	log( "Se cargara el sprite para la accion de pina baja del personaje", LOG_DEBUG );
	Sprite* sprite_pina_baja =  cargarSprite( root, ruta_carpeta, "pinaBaja", SPRITESHEET_PINA_BAJA_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_pina_baja );

	log( "Se cargara el sprite para la accion de pina saltando del personaje", LOG_DEBUG );
	Sprite* sprite_pina_saltando =  cargarSprite( root, ruta_carpeta, "pinaEnSalto", SPRITESHEET_PINA_SALTANDO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_pina_saltando );

	log( "Se cargara el sprite para la accion recibir golpe agachado del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_agachado =  cargarSprite( root, ruta_carpeta, "recibeGolpeAgachado", SPRITESHEET_RECIBIR_GOLPE_AGACHADO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_recibir_golpe_agachado );

	log( "Se cargara el sprite para la accion de recibir golpe alto del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_alto =  cargarSprite( root, ruta_carpeta, "recibeGolpeAlto", SPRITESHEET_RECIBIR_GOLPE_ALTO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_recibir_golpe_alto );

	log( "Se cargara el sprite para la accion de recibir golpe bajo del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_bajo =  cargarSprite( root, ruta_carpeta, "recibeGolpeBajo", SPRITESHEET_RECIBIR_GOLPE_BAJO_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_recibir_golpe_bajo );

	log( "Se cargara el sprite para la accion de recibir golpes fuerte del personaje", LOG_DEBUG );
	Sprite* sprite_recibir_golpe_fuerte =  cargarSprite( root, ruta_carpeta, "recibeGolpeFuerte", SPRITESHEET_RECIBIR_GOLPE_FUERTE_DEFAULT, ventana, ratio_x_personaje, ratio_y_personaje );
	sprites.push_back( sprite_recibir_golpe_fuerte );


	log( "Se crearon todos los sprites del personaje.", LOG_DEBUG );
	return sprites;

}


void ParserJSON::cargarMapaComandos(Json::Value root) {
	if ( ! root.isMember("botones") ) {
		mapaComandosDefault();
		return;
	}

	char pina_baja;
	if ( ! root["botones"].isMember("pina baja") ) {
		pina_baja = COMANDO_PINA_BAJA_DEFAULT;
	} else {
		try {
			string pina_baja_s;
			pina_baja_s = root["botones"].get( "pina baja", "" ).asString();
			if ( pina_baja_s == "" ) pina_baja = COMANDO_PINA_BAJA_DEFAULT;
			pina_baja = pina_baja_s[0];
		} catch ( exception &e ) {
			pina_baja = COMANDO_PINA_BAJA_DEFAULT;
			log( "El boton correspondiente a la pina baja no es un caracter valido.", LOG_ERROR );
		}
	}
	comandos["pina baja"] = pina_baja;

	char pina_alta;
	if ( ! root["botones"].isMember("pina alta") ) {
		pina_alta = COMANDO_PINA_ALTA_DEFAULT;
	} else {
		try {
			string pina_alta_s;
			pina_alta_s = root["botones"].get( "pina alta", "" ).asString();
			if ( pina_alta_s == "" ) pina_alta = COMANDO_PINA_ALTA_DEFAULT;
			pina_alta = pina_alta_s[0];
		} catch ( exception &e ) {
			pina_alta = COMANDO_PINA_ALTA_DEFAULT;
			log( "El boton correspondiente a la pina alta no es un caracter valido.", LOG_ERROR );
		}
	}
	comandos["pina alta"] = pina_alta;

	char patada_baja;
	if ( ! root["botones"].isMember("patada baja") ) {
		patada_baja = COMANDO_PATADA_BAJA_DEFAULT;
	} else {
		try {
			string patada_baja_s;
			patada_baja_s = root["botones"].get( "patada baja", "" ).asString();
			if ( patada_baja_s == "" ) patada_baja = COMANDO_PATADA_BAJA_DEFAULT;
			patada_baja = patada_baja_s[0];
		} catch ( exception &e ) {
			patada_baja = COMANDO_PATADA_BAJA_DEFAULT;
			log( "El boton correspondiente a la patada baja no es un caracter valido.", LOG_ERROR );
		}
	}
	comandos["patada baja"] = patada_baja;

	char patada_alta;
	if ( ! root["botones"].isMember("patada alta") ) {
		patada_alta = COMANDO_PATADA_ALTA_DEFAULT;
	} else {
		try {
			string patada_alta_s;
			patada_alta_s = root["botones"].get( "patada alta", "" ).asString();
			if ( patada_alta_s == "" ) patada_alta = COMANDO_PATADA_ALTA_DEFAULT;
			patada_alta = patada_alta_s[0];
		} catch ( exception &e ) {
			patada_alta = COMANDO_PATADA_ALTA_DEFAULT;
			log( "El boton correspondiente a la patada alta no es un caracter valido.", LOG_ERROR );
		}
	}
	comandos["patada alta"] = patada_alta;

	char cubrirse;
	if ( ! root["botones"].isMember("cubrirse") ) {
		cubrirse = COMANDO_CUBRIRSE_DEFAULT;
	} else {
		try {
			string cubrirse_s;
			cubrirse_s = root["botones"].get( "cubrirse", "" ).asString();
			if ( cubrirse_s == "" ) cubrirse = COMANDO_CUBRIRSE_DEFAULT;
			cubrirse = cubrirse_s[0];
		} catch ( exception &e ) {
			cubrirse = COMANDO_CUBRIRSE_DEFAULT;
			log( "El boton correspondiente al comando de cubrirse no es un caracter valido.", LOG_ERROR );
		}
	}
	comandos["cubrirse"] = cubrirse;

	char lanzar_arma;
	if ( ! root["botones"].isMember("lanzar arma") ) {
		lanzar_arma = COMANDO_LANZAR_ARMA_DEFAULT;
	} else {
		try {
			string lanzar_arma_s;
			lanzar_arma_s = root["botones"].get( "lanzar_arma", "" ).asString();
			if ( lanzar_arma_s == "" ) lanzar_arma = COMANDO_LANZAR_ARMA_DEFAULT;
			lanzar_arma = lanzar_arma_s[0];
		} catch ( exception &e ) {
			lanzar_arma = COMANDO_LANZAR_ARMA_DEFAULT;
			log( "El boton correspondiente al comando de lanzar el arma arrojable no es un caracter valido.", LOG_ERROR );
		}
	}
	comandos["lanzar arma"] = lanzar_arma;

	log( "Se cargo correctamente el mapa de comandos y botones del controlador.", LOG_DEBUG );

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
	if ( ! root.isMember("tiempo") ) {
		log( "No se especifico el tiempo de combate. Se setea en 3 minutos por defecto.", LOG_WARNING );
		tiempo_combate = new Tiempo(TIEMPO_DEFAULT);
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
	if ( ! root.isMember("ventana") ) {
		log( "No se encontraron parametros para la creacion de la ventana. Se asignan valores por defecto.", LOG_ERROR );
		ventana_ancho_px = VENTANA_ANCHO_PX_DEFAULT;
		ventana_alto_px = VENTANA_ALTO_PX_DEFAULT;
		ventana_ancho = VENTANA_ANCHO_DEFAULT;
	} else {
		if ( ! root["ventana"].isMember("ancho-px") ) {
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
		if ( ! root["ventana"].isMember("alto-px") ) {
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
		if ( ! root["ventana"].isMember("ancho") ) {
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
	int personajes_z_index;
	bool z_index_ok = true;
	if ( ! root.isMember("escenario") ) {
		log( "No se encontraron parametros para la creacion del escenario. Se asignan valores por defecto.", LOG_ERROR );
		escenario_ancho = ESCENARIO_ANCHO_DEFAULT;
		escenario_alto = ESCENARIO_ALTO_DEFAULT;
		y_piso = Y_PISO_DEFAULT;
		personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
		z_index_ok = false;
	} else {
		if ( ! root["escenario"].isMember("ancho") ) {
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
		if ( ! root["escenario"].isMember("alto") ) {
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
		if ( ! root["escenario"].isMember("y-piso") ) {
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
		if ( ! root["escenario"].isMember("z-index_personajes") ) {
			personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
			z_index_ok = false;
			log( "No se especifico el z-index de los personajes. Se setean delante de todas las capas por defecto.", LOG_WARNING );
		} else {
			try {
				personajes_z_index = root["escenario"].get( "z-index_personajes", PERSONAJES_Z_INDEX_DEFAULT ).asInt();
				if ( personajes_z_index < 0 ) {
					personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
					z_index_ok = false;
					log( "El z-index de los personajes no puede ser negativo. Se colocan por defecto los personajes delante de todas las capas.", LOG_WARNING );
				} else	log( "Se cargo correctamente el z-index de los personajes.", LOG_DEBUG );
			} catch ( exception &e ) {
				personajes_z_index = PERSONAJES_Z_INDEX_DEFAULT;
				z_index_ok = false;
				log( "El z-index de los personajes indicado no es valido y no pudo ser convertido a un numero entero. Se setea por defecto.", LOG_ERROR );
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
	bool capas_ok = true;
	int i=0;
	if ( ! root.isMember("capas") || ! root["capas"].isArray() ) {
		log( "No se encontraron parametros en un vector para la creacion de las capas. Se crean capas y se asignan valores por defecto.", LOG_ERROR );
		CapaFondo* capa_0 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_0_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_0_BACKGROUND_DEFAULT,ventana);
		nuevo_mundo->addCapa(capa_0);
		CapaFondo* capa_1 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_1_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+1,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_1_BACKGROUND_DEFAULT,ventana);
		nuevo_mundo->addCapa(capa_1);
		CapaFondo* capa_2 = new CapaFondo(ESCENARIO_ALTO_DEFAULT,CAPA_2_ANCHO_DEFAULT,CAPA_Z_INDEX_DEFAULT+2,ESCENARIO_ANCHO_DEFAULT,PERSONAJE_VELOCIDAD,CAPA_2_BACKGROUND_DEFAULT,ventana);
		nuevo_mundo->addCapa(capa_2);
		capas_ok = false;
	} else {
		const Json::Value capas = root["capas"];
		for ( ; i < (int)capas.size(); i++ ) {
			if ( ! capas[i].isMember("imagen_fondo") ) {
				background = BACKGROUND_DEFAULT;
				log( "No se especifico la imagen de fondo de la capa. Se asigna una imagen por defecto.", LOG_ERROR );
			} else {
				try {
					background = capas[i].get( "imagen_fondo", BACKGROUND_DEFAULT ).asString();

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
			if ( ! capas[i].isMember("ancho") ) {
				capa_ancho = VENTANA_ANCHO_DEFAULT;
				log( "No se especifico el ancho logico de la capa. Se setea en 600 por defecto.", LOG_WARNING );
			} else {
				try {
					capa_ancho = capas[i].get( "ancho", VENTANA_ANCHO_DEFAULT ).asFloat();
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

			capa_z_index = i;

			// Setear alto logico de la capa de acuerdo al alto del escenario.
			capa_alto = escenario_alto;
			log ( "Se fijo el alto logico de la capa.", LOG_DEBUG );

			// Creo capas de fondo.
			CapaFondo* capa_fondo;
			try {
				capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, background, ventana );
				log( "Se creo correctamente la capa.", LOG_DEBUG );
			} catch ( CargarImagenException &e ) {
				delete capa_fondo;
				capa_fondo = new CapaFondo( capa_alto, capa_ancho, capa_z_index, escenario_ancho, PERSONAJE_VELOCIDAD, BACKGROUND_DEFAULT, ventana );
				log( "No se pudo cargar la imagen de la capa. Se carga imagen por defecto. " + string(e.what()), LOG_ERROR );
			}

			// Agrego capa al mundo.
			//nuevo_mundo->addCapa(capa_fondo, capa_z_index);
			nuevo_mundo->addCapa(capa_fondo);
			log( "Se agrego la capa al mundo.", LOG_DEBUG );
		}
	}

	// Creo vector de personajes.
	vector<Personaje*> personajes;

	// Obtener el personaje.
	// Si no se especifica o no se encuentra la carpeta de sprites del personaje, se usa una por defecto.
	// Si no se especifica el z-index se fija uno por defecto.
	float personaje_ancho, personaje_alto;
	string personaje_carpeta_sprites, personaje_nombre;
	bool flipped;
	if ( ! root.isMember("personajes") || ! root["personajes"].isArray() ) {
		Personaje* personaje_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault( ventana,PERSONAJE_ANCHO_DEFAULT,PERSONAJE_ALTO_DEFAULT), PERSONAJE_VELOCIDAD, PERSONAJE_FLIPPED_DEFAULT);
		personaje_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2),Y_PISO_DEFAULT);
		Personaje* personaje2_default = new Personaje(PERSONAJE_NOMBRE_DEFAULT, generarSpritesDefault( ventana,PERSONAJE_ANCHO_DEFAULT,PERSONAJE_ALTO_DEFAULT), PERSONAJE_VELOCIDAD, !PERSONAJE_FLIPPED_DEFAULT);
		personaje2_default->setPosition((ESCENARIO_ANCHO_DEFAULT/2),Y_PISO_DEFAULT);
		nuevo_mundo->addPersonaje(personaje_default);
		nuevo_mundo->addPersonaje(personaje2_default);
		log( "No se especificaron parametros para la creacion de los personajes en un vector. Se generan dos personajes iguales por defecto.", LOG_ERROR );
	} else {
		for ( int k=0; k < (int)root["personajes"].size(); k++ ) {
			if ( ! root["personajes"][k].isMember("ancho") ) {
				personaje_ancho = PERSONAJE_ANCHO_DEFAULT;
				log( "No se especifico el ancho logico del personaje. Se setea por defecto en 30.", LOG_WARNING );
			} else {
				try {
					personaje_ancho = root["personajes"][k].get( "ancho", PERSONAJE_ANCHO_DEFAULT ).asFloat();
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
			if ( ! root["personajes"][k].isMember("alto") ) {
				personaje_alto = PERSONAJE_ALTO_DEFAULT;
				log( "No se especifico el alto logico del personaje. Se setea por defecto en 60.", LOG_WARNING );
			} else {
				try {
					personaje_alto = root["personajes"][k].get( "alto", PERSONAJE_ALTO_DEFAULT ).asFloat();
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
			if ( ! root["personajes"][k].isMember("nombre") ) {
				personaje_nombre = PERSONAJE_NOMBRE_DEFAULT;
				log( "No se especifico el nombre del personaje. Se llama Jugador por defecto.", LOG_ERROR );
			} else {
				try {
					personaje_nombre = root["personajes"][k].get ( "nombre", PERSONAJE_NOMBRE_DEFAULT ).asString();
					log ( "Se cargo el nombre del personaje.", LOG_DEBUG );
				} catch ( exception &e ) {
					personaje_nombre = PERSONAJE_NOMBRE_DEFAULT;
					log( "El nombre del personaje indicado no es una cadena de texto valida. Se setea por defecto.", LOG_ERROR );
				}
			}
			if ( ! root["personajes"][k].isMember("flipped") ) {
				if ( k % 2 == 0 ) flipped = PERSONAJE_FLIPPED_DEFAULT;
				else flipped = ! PERSONAJE_FLIPPED_DEFAULT;
				log( "No se especifico si el personaje debe estar flippeado o no. Se setea por defecto.", LOG_WARNING );
			} else {
				try {
					flipped = root["personajes"][k].get( "flipped", PERSONAJE_FLIPPED_DEFAULT ).asBool();
					log( "Se cargo el booleano flipped que indica si el personaje inicia mirando hacia la derecha (false) o hacia la izquierda (true).", LOG_DEBUG );
				} catch ( exception &e ) {
					if ( k % 2 == 0 ) flipped = PERSONAJE_FLIPPED_DEFAULT;
					else flipped = ! PERSONAJE_FLIPPED_DEFAULT;
					log( "El valor de flipped del personaje no es un booleano valido. Se setea por defecto.", LOG_ERROR );
				}
			}
			// Creo Sprites del personaje.
			vector<Sprite*> sprites = cargarSprites(personaje_carpeta_sprites, ventana, personaje_ancho, personaje_alto);

			// Crear personaje.
			Personaje* personaje = new Personaje(personaje_nombre, sprites, PERSONAJE_VELOCIDAD, flipped);
			log( "Se creo correctamente el personaje.", LOG_DEBUG );

			// Agrego personaje al vector de personajes.
			personajes.push_back(personaje);

			// Indico posicion inicial del personaje.
			personaje->setPosition( (escenario_ancho/2), y_piso );
			log( "Se seteo la posicion inicial en el escenario del personaje.", LOG_DEBUG );

			// Agrego Personaje al mundo.
			nuevo_mundo->addPersonaje(personaje);
			log( "Se agrego el personaje al mundo", LOG_DEBUG );
		}
	}


	// Crear capa principal, donde estan los personajes y se desarrolla la accion.
	// Validaciones para el z-index de los personajes.
	if ( capas_ok && (! z_index_ok) ) personajes_z_index = i+1;
	CapaPrincipal* capa_principal = new CapaPrincipal( escenario_alto, escenario_ancho, personajes_z_index, escenario_ancho, ventana_ancho, PERSONAJE_VELOCIDAD, personajes );
	log( "Se creo correctamente la capa principal.", LOG_DEBUG );

	// Agrego capa principal al mundo.
	nuevo_mundo->addCapaPrincipal( capa_principal, personajes_z_index );
	log( "Se agrego la capa principal al mundo.", LOG_DEBUG );

	// Obtener hash de comandos.
	cargarMapaComandos(root);


	return nuevo_mundo;


}

