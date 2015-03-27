#include "ParserJSON.h"

using namespace std;

ParserJSON::ParserJSON(string ruta_archivo) {
	archivoPelea = ruta_archivo
}

// Devuelve un root que se usara para generar la partida.
Json::Value ParserJSON::parsear() {
	Json::Value = root;
	Json::Reader = reader;

	// Abro archivo.
	fopen( archivoPelea, 'r' );

	bool exito = reader.parse( archivoPelea, root, false );
	if ( ! exito ) {
	    // Reportar al usuario la falla y su ubicacion en el archivo JSON.
	    std::cout  << "Failed to parse configuration\n"
	               << reader.getFormattedErrorMessages();
	    return peleaPorDefecto();
	}

}

