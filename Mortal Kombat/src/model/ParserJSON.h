#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio.h>
#include <string>
#include <stdexcept>
#include "../../libs/json/json.h"
#include "logging.h"
#include "Mundo.h"
#include "DefaultSettings.h"

const float PERSONAJE_VELOCIDAD = 10.0;

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;

public:
	 ParserJSON(string ruta_archivo);
	 Mundo* cargarMundo();
	 Mundo* generarMundoDefault();
	 vector<Sprite*> generarSpritesDefault(Ventana* ventana, float ratio_x, float ratio_y);
	 vector<Sprite*> cargarSprites(string ruta_carpeta, Ventana* ventana, float ratio_x, float ratio_y);
	 Sprite* crearSpriteParadoDefault(Ventana* ventana, float ratio_x, float ratio_y);
	 Sprite* crearSpriteCaminarDefault(Ventana* ventana, float ratio_x, float ratio_y);
	 Sprite* crearSpriteSaltarDefault(Ventana* ventana, float ratio_x, float ratio_y);
	 Sprite* crearSpriteSaltarDiagonalDefault(Ventana* ventana, float ratio_x, float ratio_y);
	 Sprite* crearSpriteAgacharDefault(Ventana* ventana, float ratio_x, float ratio_y);
};

#endif /* SRC_MODEL_PARSER_H_ */
