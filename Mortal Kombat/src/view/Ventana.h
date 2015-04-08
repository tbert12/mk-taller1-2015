#ifndef SRC_VIEW_VENTANA_H_
#define SRC_VIEW_VENTANA_H_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"
//#include "LTexture.h"

class Ventana
{
private:
	int m_ancho;
	int m_alto;
	float m_pixel_a_logico;

public:

	Ventana(int screenWidth, int screenHeight);

	void setPixelaLogico(float p_a_l);

	int obtenerAncho();

	//Starts up SDL and creates window
	bool create_window();

	//Refrescar el mundo (la pantalla, para cada ciclo)
	void Refresh();

	//Frees media and shuts down SDL
	void close_window();

	//Obtener Renderer para los objetos Renderizables
	SDL_Renderer* getRenderer();

	//limpia la pantalla
	void clear();
};
#endif /* SRC_VIEW_VENTANA_H_ */
