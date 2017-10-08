

#ifndef SRC_MODEL_TIEMPO_H_
#define SRC_MODEL_TIEMPO_H_

#include <ctime>
#include <iostream>

class Tiempo {
public:
	Tiempo(int segundos);
	bool tiempoTerminado();
	float tiempoEnMinutos();
	void start();
	void actualizar();
	int getTiempo();
	void reset();
	virtual ~Tiempo();
private:
	int m_tiempoLimite;
	int m_tiempoRestante;
	time_t tiempo;
};

#endif /* SRC_MODEL_TIEMPO_H_ */
