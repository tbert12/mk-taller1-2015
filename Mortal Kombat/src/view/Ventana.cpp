#include "Ventana.h"

//The window we'll be rendering to
SDL_Window* Window = NULL;

//The window renderer
SDL_Renderer* Renderer = NULL;

SDL_Renderer* getRenderer(){
	return Renderer;
}


bool create_window(int screenWidth, int screenHeight)
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
		Window = SDL_CreateWindow( "World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );
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

	return success;
}

void close_window()
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

/*
bool loadMedia(std::string ruta)
{
	//Booleano a devolver
	bool OK = true;

	//Cargar Sprite
	if( !gSpriteSheetTexture.loadFromFile( ruta ) )
	{
		printf( "Error en cargar Sprite\n" );
		OK = false;
	}
	else
	{
		int wSprite = 68;
		for (int i = 0; i < ANIMATION_IMAGES;i++){
			//Set Sprite Position (+64)
			gSpriteClips[i].x = wSprite*i;
			gSpriteClips[i].y = 0;
			gSpriteClips[i].w = wSprite;
			gSpriteClips[i].h = 133;
		}
	}

	return OK;
}
*/

void Refresh(Sprite* spriteActual,int SCREEN_WIDTH,int SCREEN_HEIGHT){
	//Limpiar pantalla
	SDL_SetRenderDrawColor( Renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( Renderer );

	//Renderizar estado actual
	//SDL_Rect* currentClip = &gSpriteClips[ frame ];
	SDL_Rect* currentClip = spriteActual->nextFrame();
	LTexture* SpriteSheetTexture = spriteActual->getSpriteSheetTexture();
	SpriteSheetTexture->render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

	//Actualizar pantalla
	SDL_RenderPresent( Renderer );
}
