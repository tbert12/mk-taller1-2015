#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio.h>
#include <string>
#include <stdexcept>
#include "../../libs/json/json.h"
#include "logging.h"
#include "Mundo.h"
#include "DefaultSettings.h"
#include <sys/stat.h>

const float PERSONAJE_VELOCIDAD = 7.0;

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;

public:
	 ParserJSON(string ruta_archivo);
	 ~ParserJSON();
	 Mundo* cargarMundo();
	 Mundo* generarMundoDefault();
	 Sprite* cargarSprite( Json::Value root, string ruta_carpeta, string accion_sprite, string spritesheet_default, Sprite* (*crearSpritePorDefecto)(Ventana*, float, float), Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje );
	 vector<Sprite*> generarSpritesDefault(Ventana* ventana, float personaje_ancho, float personaje_alto);
	 vector<Sprite*> cargarSprites(string ruta_carpeta, Ventana* ventana, float personaje_ancho, float personaje_alto);
	 Sprite* crearSpriteParadoDefault(Ventana* ventana, float personaje_ancho, float personaje_alto);
	 Sprite* crearSpriteCaminarDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje);
	 Sprite* crearSpriteSaltarDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje);
	 Sprite* crearSpriteSaltarDiagonalDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje);
	 Sprite* crearSpriteAgacharDefault(Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje);
};

#endif /* SRC_MODEL_PARSER_H_ */
