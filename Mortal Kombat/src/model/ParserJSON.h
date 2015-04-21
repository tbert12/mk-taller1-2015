#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include "DefaultSettings.h"

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;

public:
	 ParserJSON(string ruta_archivo);
	 ~ParserJSON();
	 float getRatioXPersonaje( Json::Value root_sprites, float personaje_ancho );
	 float getRatioYPersonaje( Json::Value root_sprites, float personaje_alto );
	 Mundo* cargarMundo();
	 Sprite* cargarSprite( Json::Value root, string ruta_carpeta, const char accion_sprite[], string spritesheet_accion, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje );
	 vector<Sprite*> cargarSprites(string ruta_carpeta, Ventana* ventana, float personaje_ancho, float personaje_alto);

};

#endif /* SRC_MODEL_PARSER_H_ */
