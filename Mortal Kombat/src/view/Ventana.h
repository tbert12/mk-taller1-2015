#ifndef SRC_VIEW_VENTANA_H_
#define SRC_VIEW_VENTANA_H_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include "LTexture.h"

class Ventana
{
private:
	int m_ancho;
	int m_alto;
	float ratio_x;
	float ratio_y;

public:

	Ventana(int screenWidth, int screenHeight,float ratiox,float ratioy);

	int obtenerAncho();

	//Starts up SDL and creates window
	bool create_window();

	//Refrescar el mundo (la pantalla, para cada ciclo)
	void Refresh();

	//Frees media and shuts down SDL
	void close_window();

	//Obtener Renderer para los objetos Renderizables
	SDL_Renderer* getRenderer();

	LTexture* crearTextura();

	//limpia la pantalla
	void clear();
};
#endif /* SRC_VIEW_VENTANA_H_ */
