#ifndef SRC_MODEL_DEFAULTSETTINGS_H_
#define SRC_MODEL_DEFAULTSETTINGS_H_

#include <stdio.h>
#include <string>
#include <stdexcept>
#include "../../libs/json/json.h"
#include "logging.h"
#include "Mundo.h"
#include <sys/stat.h>

const int LOGLVL_DEFAULT = 2;
const int TIEMPO_DEFAULT = 180;
const int VENTANA_ANCHO_PX_DEFAULT = 512;
const int VENTANA_ALTO_PX_DEFAULT = 384;
const float VENTANA_ANCHO_DEFAULT = 200.0;
const float ESCENARIO_ANCHO_DEFAULT = 600.0;
const float ESCENARIO_ALTO_DEFAULT = 150.0;
const float Y_PISO_DEFAULT = 135.0;
const char* const BACKGROUND_DEFAULT = "data/img/background/default/unknown.png";
const char* const CAPA_0_BACKGROUND_DEFAULT = "data/img/background/default/background_0.png";
const char* const CAPA_1_BACKGROUND_DEFAULT = "data/img/background/default/background_1.png";
const char* const CAPA_2_BACKGROUND_DEFAULT = "data/img/background/default/background_2.png";
const float CAPA_0_ANCHO_DEFAULT = 200.0;
const float CAPA_1_ANCHO_DEFAULT = 226.6;
const float CAPA_2_ANCHO_DEFAULT = 600.0;
const int CAPA_Z_INDEX_DEFAULT = 0;
const int PERSONAJE_Z_INDEX_DEFAULT = 3;
const char* const PERSONAJE_CARPETA_SPRITES_DEFAULT = "data/players/default/sprites/";
const char* const PERSONAJE_NOMBRE_DEFAULT = "Jugador";
const bool PERSONAJE_FLIPPED_DEFAULT = false;
const int PERSONAJE_ANCHO_PX_DEFAULT = 72;
const int PERSONAJE_ALTO_PX_DEFAULT = 133;
const float PERSONAJE_ANCHO_DEFAULT = 40.0;
const float PERSONAJE_ALTO_DEFAULT = 70.0;

const char* const JSON_SPRITES_DEFAULT = "data/players/default/sprites/sprites.json";
const char* const SPRITESHEET_PARADO_DEFAULT = "initial.png";
const char* const SPRITESHEET_CAMINAR_DEFAULT = "walk.png";
const char* const SPRITESHEET_SALTAR_DEFAULT = "salto.png";
const char* const SPRITESHEET_SALTAR_DIAGONAL_DEFAULT = "diag.png";
const char* const SPRITESHEET_AGACHAR_DEFAULT = "agachar.png";

const float PERSONAJE_VELOCIDAD = 7.0;


using namespace std;


Sprite* crearSpritePorDefecto(const char* accion_sprite, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje);
vector<Sprite*> generarSpritesDefault( Ventana* ventana, float personaje_ancho, float personaje_alto );
Mundo* generarMundoDefault();


#endif /* SRC_MODEL_DEFAULTSETTINGS_H_ */
