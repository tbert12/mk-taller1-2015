#ifndef SRC_MODEL_LOGGING_H_
#define SRC_MODEL_LOGGING_H_

#include <fstream>
#include <cstring>
#include <stdio.h>
#include <time.h>

//Constantes de tipos de loggeo.
const int LOG_ERROR = 0;
const int LOG_WARNING = 1;
const int LOG_DEBUG = 2;


using namespace std;

extern int nivel;
extern const string ruta_logfile;

void log( const string mensaje, int tipo_de_log);
void prepararLog();


#endif /* SRC_MODEL_LOGGING_H_ */
