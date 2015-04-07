#include "logging.h"

using namespace std;

int nivel = 1;
const string ruta_logfile = "data/log/registro.log";

// Obtener la fecha y hora actual. Formato YYYY-MM-DD.HH:mm:ss.
const string fechaHora() {
    time_t ahora = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&ahora);
    strftime( buf, sizeof(buf), "[%Y-%m-%d.%X]-", &tstruct );

    return buf;
}

// Escribir un mensaje en una nueva linea del archivo log.
void registrarMensaje( const string mensaje) {
	fstream logfile;
	logfile.open ( ruta_logfile.c_str(),std::fstream::app );
	logfile << fechaHora();
	logfile << mensaje;
	logfile << endl;
	logfile.close();
}

// Bitacora del programa.
// Niveles de registro:
// 1 = Errores, Warnings, Sucesos (DEBUG)
// 2 = Errores, Warnings
// 3 = Errores
void log( const string mensaje) {
	if ( strstr( mensaje.c_str(), "ERROR:" ) ) {
		// DETALLO ERROR
		registrarMensaje(mensaje);
	} else if ( strstr( mensaje.c_str(), "WARNING:" ) ) {
		if ( nivel < 3 ) {
			// DETALLO WARNING
			registrarMensaje(mensaje);
		}
	} else {
		if ( nivel < 2 ) {
			// DETALLO SUCESO (DEBUG)
			registrarMensaje(mensaje);
		}
	}
}

// Indicar comienzo de un nuevo run del programa.
void prepararLog() {
	fstream logfile;
	logfile.open ( ruta_logfile.c_str(), std::fstream::app );
	logfile << "\n";
	logfile << "---------------------------------------------------------------------------------------------" << endl;
	logfile << "\n";
	logfile.close();
}


