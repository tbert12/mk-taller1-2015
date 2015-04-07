

#ifndef SRC_MODEL_TIEMPO_H_
#define SRC_MODEL_TIEMPO_H_

class Tiempo {
public:
	Tiempo(int segundos);
	bool transcurrir(int segundos);
	bool tiempoTerminado();
	float tiempoEnMinutos();
	virtual ~Tiempo();
private:
	int m_tiempoLimite;
	int m_tiempoRestante;
};

#endif /* SRC_MODEL_TIEMPO_H_ */
