#ifndef SRC_MODELPARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio>
#include "json/jsoncpp.cpp"
#include <SLD2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class ParserJSON {

private:
	 string archivoConfig;

public:
	 ParserJSON(string ruta_archivo);

	 Pelea::Pelea* generarPelea();

	 Pelea::Pelea* peleaPorDefecto();

}

#endif /* SRC_MODEL_PARSER_H_ */
