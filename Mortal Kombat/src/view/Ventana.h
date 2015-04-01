#ifndef SRC_VIEW_VENTANA_H_
#define SRC_VIEW_VENTANA_H_

#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <string>
#include "Sprite.h"
//#include "LTexture.h"

//Starts up SDL and creates window
bool create_window(int screenWidth, int screenHeight);

//Loads media
//bool loadMedia(std::string ruta);

//Refrescar el mundo (la pantalla, para cada ciclo)
void Refresh(Sprite* spriteActual,int SCREEN_WIDTH,int SCREEN_HEIGHT);

//Frees media and shuts down SDL
void close_window();

//The window we'll be rendering to
SDL_Window* Window = NULL;

//The window renderer
SDL_Renderer* Renderer = NULL;

#endif /* SRC_VIEW_VENTANA_H_ */