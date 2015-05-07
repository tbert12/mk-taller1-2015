

#ifndef SRC_MODEL_TIEMPO_H_
#define SRC_MODEL_TIEMPO_H_

#include <ctime>

class Tiempo {
public:
	Tiempo(int segundos);
	bool transcurrir(int segundos);
	bool tiempoTerminado();
	float tiempoEnMinutos();
	void start();
	void actualizar();
	int getTiempo();
	virtual ~Tiempo();
private:
	int m_tiempoLimite;
	int m_tiempoRestante;
	time_t m_tiempo_de_inicio;
	time_t m_time;
	time_t m_tiempo_anterior;
};

#endif /* SRC_MODEL_TIEMPO_H_ */
