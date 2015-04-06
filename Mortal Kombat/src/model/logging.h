#ifndef SRC_MODEL_LOGGING_H_
#define SRC_MODEL_LOGGING_H_

#include <fstream>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;

extern int nivel;
extern const string ruta_logfile;

const string fechaHora();
void registrarMensaje( const string mensaje );
void log( const string mensaje );
void prepararLog();


#endif /* SRC_MODEL_LOGGING_H_ */
