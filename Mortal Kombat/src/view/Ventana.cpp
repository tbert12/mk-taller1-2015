#include "Ventana.h"
#include "../model/logging.h"

//The window we'll be rendering to
SDL_Window* Window = NULL;

//The window renderer
SDL_Renderer* Renderer = NULL;

SDL_Renderer* Ventana::getRenderer(){
	return Renderer;
}

Ventana::Ventana(int screenWidth, int screenHeight, float relacion_pixel_a_ventana)
{
	m_ancho = screenWidth;
	m_alto = screenHeight;
	m_pixel_a_logico = relacion_pixel_a_ventana;
}

LTexture* Ventana::crearTextura(){
	LTexture* m_texture = new LTexture(Renderer);
	m_texture->setRelacionPixel(m_pixel_a_logico);
	return m_texture;
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
		log(string("SDL no puede inicializar! SDL Error: %s\n", SDL_GetError()),LOG_ERROR );
		success = false;
	}
	else
	{
		//Filtrado lineal de textura
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			log("Filtrado lineal de textura no esta habilitado!" ,LOG_WARNING);
		}

		//Crear Ventana
		Window = SDL_CreateWindow( "World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_ancho, m_alto, SDL_WINDOW_SHOWN );
		if( Window == NULL )
		{
			log(string( "La ventana no se puede crear! SDL Error: %s\n", SDL_GetError() ),LOG_ERROR);
			success = false;
		}
		else
		{
			//Vsync-renderer for window
			Renderer = SDL_CreateRenderer( Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( Renderer == NULL )
			{
				log(string( "No se pudo crear la renderizacion! SDL Error: %s\n", SDL_GetError() ),LOG_ERROR);
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
					log(string( "SDL_image no pudo inicializarse! SDL_image Errors: %s\n", IMG_GetError() ),LOG_ERROR);
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

void Ventana::clear(){
	//Limpiar pantalla
	SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( Renderer );
}

void Ventana::Refresh(){
	//Actualizar pantalla
	SDL_RenderPresent( Renderer );
}

