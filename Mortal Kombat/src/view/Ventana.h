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

public:

	Ventana(int screenWidth, int screenHeight);

	int obtenerAncho();

	//Starts up SDL and creates window
	bool create_window(int screenWidth, int screenHeight);

	//Loads media
	//bool loadMedia(std::string ruta);

	//Refrescar el mundo (la pantalla, para cada ciclo)
	void Refresh(Sprite* spriteActual,int SCREEN_WIDTH,int SCREEN_HEIGHT);

	//Frees media and shuts down SDL
	void close_window();

	//Obtener Renderer para los objetos Renderizables
	SDL_Renderer* getRenderer();
};
#endif /* SRC_VIEW_VENTANA_H_ */
