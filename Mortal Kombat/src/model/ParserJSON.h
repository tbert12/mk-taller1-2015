#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <ctype.h>
#include "DefaultSettings.h"
#include "CapaFondo.h"
#include "Escenario.h"
#include "CapaPrincipal.h"
#include "../view/LSound.h"


using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;
	 Ventana* m_ventana;
	 map<string, int>* comandos_luchador1;
	 map<string, int>* comandos_luchador2;

public:
	 ParserJSON(string ruta_archivo);
	 ~ParserJSON();
	 float getRatioXPersonaje( Json::Value root_sprites, float personaje_ancho );
	 float getRatioYPersonaje( Json::Value root_sprites, float personaje_alto );
	 float getRatioXArrojable( Json::Value root_arrojables, float arrojable_ancho );
	 float getRatioYArrojable( Json::Value root_arrojables, float arrojable_alto );
	 map<string, int>* getComandos1();
	 map<string, int>* getComandos2();
	 Mundo* cargarMundo();
	 int cargarComando(Json::Value root, const char* accion, int comando_default);
	 void cargarMapaComandos(Json::Value root);
	 vector<ObjetoArrojable*> cargarArrojables(string ruta_carpeta, string ruta_sonidos, Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color, float h_inicial, float h_final, float desplazamiento);
	 Sprite* cargarSprite( Json::Value root, string ruta_carpeta, string ruta_sonidos, const char accion_sprite[], string spritesheet_accion, Ventana* ventana, float ratio_x_personaje, float ratio_y_personaje, bool cambiar_color = false, float h_inicial = 0, float h_final = 0, float desplazamiento = 0 );
	 vector<Sprite*> cargarSprites(string ruta_carpeta, string ruta_sonidos, Ventana* ventana, float personaje_ancho, float personaje_alto, bool cambiar_color = false, float h_inicial = COLOR_H_INICIAL_DEFAULT, float h_final = COLOR_H_FINAL_DEFAULT, float desplazamiento = COLOR_DESPLAZAMIENTO_DEFAULT);
	 Personaje* cargarPersonaje(string nombre_personaje, Json::Value root, Ventana* ventana, bool cambiar_color);
	 vector<Personaje*> cargarPersonajes(Json::Value root, Ventana* ventana);
	 Escenario* cargarEscenario(string nombre_escenario, Json::Value root, Ventana* ventana, float ventana_ancho);
	 vector<Escenario*> cargarEscenarios(Json::Value root, Ventana* ventana, float ventana_ancho);
	 vector<float> cargarColorAlternativo(Json::Value personaje);
	 vector<Combo*> cargarCombos(Json::Value root);
	 Personaje* cambiarColorPersonaje(Personaje* personaje);

};

#endif /* SRC_MODEL_PARSER_H_ */
