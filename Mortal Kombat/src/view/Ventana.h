#ifndef SRC_VIEW_VENTANA_H_
#define SRC_VIEW_VENTANA_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "LTexture.h"

#define RUTA_ICONO "data/img/etc/icono.png"

class Ventana
{
private:
	int m_ancho_px;
	int m_alto_px;
	float ratio_x;
	float ratio_y;
	bool m_vibrar;
	SDL_Window* Window;
	SDL_Renderer* Renderer;
	std::vector<LTexture*> texturas;
	SDL_Texture* textura_texto;
	TTF_Font* font;

public:

	Ventana(int screenWidth, int screenHeight,float ratiox,float ratioy);
	~Ventana();
	float obtenerAncho();
	float obtenerAlto();
	float obtenerRatioX();
	float obtenerRatioY();
	//Starts up SDL and creates window
	bool create_window();

	SDL_Window* getWindow();

	//Refrescar el mundo (la pantalla, para cada ciclo)
	void Refresh();

	void vibrar();

	//Frees media and shuts down SDL
	void close_window();

	//Obtener Renderer para los objetos Renderizables
	SDL_Renderer* getRenderer();

	LTexture* crearTextura();

	bool mostrarImagen(string ruta);
	bool mostrarTexto(string texto);

	//limpia la pantalla
	void clear();
};
#endif /* SRC_VIEW_VENTANA_H_ */
