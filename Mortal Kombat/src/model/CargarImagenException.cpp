#include "CargarImagenException.h"

CargarImagenException::CargarImagenException( string ruta_imagen )
	: runtime_error( "Error al intentar cargar la imagen de la ruta especificada." ), ruta_imagen( ruta_imagen )
	{}

const char* CargarImagenException::what() const throw() {
	return ( "Error al intentar cargar la imagen de la ruta especificada: " + ruta_imagen ).c_str();
}
