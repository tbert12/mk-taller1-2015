#ifndef SRC_MODEL_CARGARIMAGENEXCEPTION_H_
#define SRC_MODEL_CARGARIMAGENEXCEPTION_H_

#include <stdexcept>
#include <exception>

using namespace std;

class CargarImagenException: public runtime_error {

public:
	CargarImagenException( string ruta_imagen );
	virtual const char* what() const throw();

private:
	string ruta_imagen;

};

#endif /* SRC_MODEL_CARGARIMAGENEXCEPTION_H_ */
