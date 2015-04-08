#include "Ventana.h"

//The window we'll be rendering to
SDL_Window* Window = NULL;

//The window renderer
SDL_Renderer* Renderer = NULL;

SDL_Renderer* Ventana::getRenderer(){
	return Renderer;
}

Ventana::Ventana(int screenWidth, int screenHeight)
{
	m_ancho = screenWidth;
	m_alto = screenHeight;
}

int Ventana::obtenerAncho()
{
	return m_ancho;
}

bool Ventana::create_window()
{
	//Booleano de inicializacion
	bool success = true;

	//Inicializar SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL no puede inicializar! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Filtrado lineal de textura
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: filtrado lineal de textura no esta habilitado!" );
		}

		//Crear Ventana
		Window = SDL_CreateWindow( "World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ancho, m_alto, SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			printf( "La ventana no se puede crear! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Vsync-renderer for window
			Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( Renderer == NULL )
			{
				printf( "No se pudo crear la renderizacion! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//render Color
				SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Cargador de PNG
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image no pudo inicializarse! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;//Documento sin título
}

void Ventana::close_window()
{
	//Liberar imagenes cargadas
	//gSpriteSheetTexture.free();

	//Destruir Ventanas
	SDL_DestroyRenderer( Renderer );
	SDL_DestroyWindow( Window );
	Window = NULL;
	Renderer = NULL;

	//Cerrar SDL
	IMG_Quit();
	SDL_Quit();
}

void Ventana::Refresh(Sprite* spriteActual){
	//Limpiar pantalla
	SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( Renderer );

	/*
	 * Esto lo tiene que hacer el mundo, el mundo es el que se refresca y que refresca
	 * refresca ted el contenido.
	 * Mundo->render(SCREEN_WIDTH,SCREEN_HEIGHT);
	 * este adentro hace en una de sus partes lo que hago a continuacion con el sprite
	 */
	//spriteActual->Advance();
	SDL_Rect* currentClip = spriteActual->getFrame();
	LTexture* SpriteSheetTexture = spriteActual->getSpriteSheetTexture();
	SpriteSheetTexture->render( ( m_ancho - currentClip->w ) / 2, ( m_alto - currentClip->h ) / 2, currentClip );

	//Actualizar pantalla
	SDL_RenderPresent( Renderer );
}

