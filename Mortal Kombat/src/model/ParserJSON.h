#ifndef SRC_MODELPARSER_H_
#define SRC_MODEL_PARSER_H_

#include <stdio>
#include "json/jsoncpp.cpp"

using namespace std;

class ParserJSON {

private:
	 string archivoPelea;

public:
	 ParserJSON(string ruta_archivo);

	 // Devuelve un root que se usara para generar la partida.
	 Json::Value parsear();

	 Pelea::Pelea generarPelea( Json::Value );

	 Pelea::Pelea peleaPorDefecto();

}

#endif /* SRC_MODEL_PARSER_H_ */
