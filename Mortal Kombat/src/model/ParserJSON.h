#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio.h>
#include <fstream>
#include "../../libs/json/json.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "logging.h"
#include "Pelea.h"
<<<<<<< HEAD
=======
#include "Mundo.h"
>>>>>>> db67fbc37e75e4e833117e40d72912bb9e139c80
#include "Tiempo.h"
#include "../view/LTexture.h"
#include "Capa.h"
#include "CapaPrincipal.h"
#include "Personaje.h"
#include "../view/Sprite.h"
#include "../view/Frame.h"
#include "DefaultSettings.cpp"
#include "Mundo.h"

using namespace std;

class ParserJSON {

private:
	 string m_ruta_archivo;

public:
	 ParserJSON(string ruta_archivo);
<<<<<<< HEAD
	 CrearMundo();
=======

	 Pelea* generarPelea();
>>>>>>> db67fbc37e75e4e833117e40d72912bb9e139c80

};

#endif /* SRC_MODEL_PARSER_H_ */
