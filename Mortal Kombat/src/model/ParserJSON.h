#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio.h>
#include <fstream>
#include "../../libs/json/json.h"
#include "logging.h"
#include "Pelea.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;

public:
	 ParserJSON(string ruta_archivo);

	 Pelea::Pelea* generarPelea();

	 Pelea::Pelea* peleaPorDefecto();

};

#endif /* SRC_MODEL_PARSER_H_ */
