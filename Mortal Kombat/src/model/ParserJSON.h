#ifndef SRC_MODEL_PARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio.h>
#include <fstream>
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

};

#endif /* SRC_MODEL_PARSER_H_ */
