#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include "DefaultSettings.h"

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;
	 map<string, int>* comandos;

public:
	 ParserJSON(string ruta_archivo);
	 ~ParserJSON();
	 float getRatioXPersonaje( Json::Value root_sprites, float personaje_ancho );
	 float getRatioYPersonaje( Json::Value root_sprites, float personaje_alto );
	 map<string, int>* getComandos();
	 Mundo* cargarMundo();
	 int cargarComando(Json::Value root, const char* accion, int comando_default);
	 void cargarMapaComandos(Json::Value root);
	 Sprite* cargarSprite( Json::Value root, string ruta_carpeta, const char accion_sprite[], string spritesheet_accion, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje, bool cambiar_color = false, float h_inicial = 0, float h_final = 0, float desplazamiento = 0 );
	 vector<Sprite*> cargarSprites(string ruta_carpeta, Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color = false, float h_inicial = 0, float h_final = 0, float desplazamiento = 0);

};

#endif /* SRC_MODEL_PARSER_H_ */
