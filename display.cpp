#include "display.h"
#include <SDL_mixer.h>
//#include"endgame.cpp"
//int m=0;
//The music that will be played
//Mix_Music *gMusic = NULL;

//The sound effects that will be used
Mix_Chunk *a1 = NULL;
Mix_Chunk *b1 = NULL;
Mix_Chunk *c1 = NULL;
Mix_Chunk *d1 = NULL;
Mix_Chunk *e1 = NULL;
Mix_Chunk *f1 = NULL;
Mix_Chunk *g1 = NULL;
int m=0;
bool Display::init(){

	//Initialization flag
	bool success = true;
	if(TTF_Init()<0){
        std::cout<<"error in TTF initialization";
	}

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else{
        //Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		window = SDL_CreateWindow( "Piano Tiles", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN );

		if( window == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
			if( renderer == NULL)
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( renderer, 0x00, 0xBB, 0xAC, 0x08);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

    return success;
}

bool Display::loadMedia(){

    bool success = true;                                          //added...

    a1 = Mix_LoadWAV( "a1.wav" );
	if( a1 == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	//Load sound effects
	b1 = Mix_LoadWAV( "b1.wav" );
	if( b1 == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	c1 = Mix_LoadWAV( "c1.wav" );
	if( c1 == NULL )
	{
		printf( "Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	 d1= Mix_LoadWAV( "d1.wav" );
	if( d1 == NULL )
	{
		printf( "Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}



     e1 = Mix_LoadWAV( "e1.wav" );
	if( e1 == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	f1 = Mix_LoadWAV( "f1.wav" );
	if( f1 == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	g1 = Mix_LoadWAV( "g1.wav" );
	if( g1 == NULL )
	{
		printf( "Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	return success;

    //Loading success flag


	//Nothing to load
	//return success;
}

void Display::close(){
    //Destroy window
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	window = NULL;
	renderer = NULL;
	Mix_FreeChunk( a1 );
	Mix_FreeChunk( b1 );
	Mix_FreeChunk( c1 );
	Mix_FreeChunk( d1);
	Mix_FreeChunk( e1 );
	Mix_FreeChunk( f1 );
	Mix_FreeChunk( g1 );
	a1 = NULL;
	b1 = NULL;
	c1= NULL;
	d1= NULL;
	e1= NULL;
    f1= NULL;
    g1= NULL;



	//Free the music
//	Mix_FreeMusic( gMusic );
	//gMusic = NULL;


	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
	TTF_Quit();
}

void Display::initializeTiles(){

    for(int i=0; i<6; i++){
        tiles[i].setDimension(i*screenWidth/5, i*screenHeight/5-screenHeight/5-400, screenWidth/5, screenHeight/5);
        /*if(i%2){
            tiles[i].setColor(0x00, 0x00, 0x00, 0x88);
        }
        else{*/
         for(int i=0; i<5; i++){
            if(i==0){
                tiles[i].setColor(0x00, 0x00, 0x00, 0xFF);
                //Mix_PlayChannel( -1, gHigh, 0 );

            }
            else if(i==1){
                tiles[i].setColor(0xFF, 0xFF, 0x00, 0xFF);
               // Mix_PlayChannel( -1, gMedium, 0 );
            }
            else if(i==2){
                tiles[i].setColor(0x00, 0xFF, 0x00, 0xFF);
               // Mix_PlayChannel( -1, gLow, 0 );
            }
             else if(i==3){
                tiles[i].setColor(0xFF, 0x00, 0x00, 0xFF);
            }
             else if(i==4){
                tiles[i].setColor(0xFF, 0x00, 0x66, 0xFF);
            }

         }
        }
    }


/*void Display::textInput(){
    // for text
    TTF_Font* Sans = TTF_OpenFont("OpenSans-Regular.ttf", 24); //this opens a font style and sets a size

    SDL_Color White = {255, 255, 255};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "aaabbbccedd", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 100; // controls the width of the rect
    Message_rect.h = 100; // controls the height of the rect
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect); //you put the renderer's name first, the Message, the crop size(you can ignore this if you don't want to dabble with cropping), and the rect which is the size and coordinate of your texture
}*/


//void Display::generateTile(int n){
 //   int random = rand()%n;
//}


void Display::draw(){


    //Clear screen
    SDL_SetRenderDrawColor(renderer, 0x00, 0xBB, 0xAC, 0x08);
    SDL_RenderClear(renderer);
    Message_rect.x = screenWidth/2-100;
    Message_rect.y =570;
    Message_rect.w = 200;
    Message_rect.h = 80;
    std::stringstream ss ;
    ss<<score;
    std::string num= "Your Score:"+ss.str();
    font =TTF_OpenFont( "data.ttf", 32 );
    surfaceMessage = TTF_RenderText_Solid(font,&num[0],White);
    Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_RenderCopy(renderer, Message,NULL,&Message_rect);

    for(int i=0; i<5; i++){
        tiles[i].render(renderer);
        if (m!=1)
        tiles[i].moveDown();

        if(tiles[i].posY + tiles[i].height > screenHeight){

        if(!(tiles[i].rgbColor.red == 0x00&&
                tiles[i].rgbColor.green == 0xBB &&
                tiles[i].rgbColor.blue == 0xAC &&
                tiles[i].rgbColor.alpha == 0x08 ))
                {
                    m++;
                   //  SDL_Delay(400000);

                   //  Mix_PlayChannel( -1, gLow, 0 );
                   /*

                   Endgame page;
                  page.init();
                  page.loadMedia();
                  page.close();
                   std::cout<<"1";
                int mn=1;*/
                }
            int random = rand()%5;
            tiles[i].setDimension(screenWidth/5 * random, -1*screenHeight/5, screenWidth/5, screenHeight/5);
            if(i==0){
                tiles[i].setColor(0x00, 0x00, 0x00, 0xFF);
                //Mix_PlayChannel( -1, gLow, 0 );
            }
            else if(i==1){
                tiles[i].setColor(0x00, 0x00, 0xFF,  0xFF);
               //Mix_PlayChannel( -1, gLow, 0 );
            }
            else if(i==2){
                tiles[i].setColor(0x00, 0xFF, 0x00, 0xFF);
               // Mix_PlayChannel( -1, gLow, 0 );
            }
             else if(i==3){
                tiles[i].setColor(0xFF, 0x00, 0xFF, 0xFF);
              // Mix_PlayChannel( -1, gLow, 0 );
            }
             else if(i==4){
                tiles[i].setColor(0xFF, 0xFF, 0xFF, 0xFF);
               // Mix_PlayChannel( -1, gLow, 0 );
            }

        }
    }

    //Update screen
    SDL_RenderPresent(renderer);
    TTF_CloseFont(font);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}


void Display::handleEvents(SDL_Event& e){

    //If a key was pressed
	/*if(e.type == SDL_KEYDOWN)
    {
        //defines the functions for keys
        switch(e.key.keysym.sym)
        {
            case SDLK_UP: tiles[0].moveUp(); break;
            case SDLK_DOWN: tiles[0].moveDown(); break;
            case SDLK_LEFT: tiles[0].moveLeft(); break;
            case SDLK_RIGHT: tiles[0].moveRight(); break;
        }*/


    if(e.type == SDL_MOUSEBUTTONDOWN){

        //get the position of mouse.
        int x, y;
        SDL_GetMouseState(&x, &y);
        for(int i=0; i<6; i++){
            if(x > tiles[i].posX && x<tiles[i].posX+tiles[i].width && y > tiles[i].posY && y < tiles[i].posY + tiles[i].height){

                ++score;
                std::cout<<"\n"<<score;
                if(!(tiles[i].rgbColor.red == 0x00&&
                tiles[i].rgbColor.green == 0xBB &&
                tiles[i].rgbColor.blue == 0xAC &&
                tiles[i].rgbColor.alpha == 0x08 ))
                {
                  int music= rand()%7;
                  switch (music){
                            case 0:
							Mix_PlayChannel( -1, a1, 0 );
							break;
                            case 1:
							Mix_PlayChannel( -1, b1, 0 );
							break;

							//Play medium sound effect
							case 2:
							Mix_PlayChannel( -1, c1, 0 );
							break;

							//Play low sound effect
							case 3:
							Mix_PlayChannel( -1, d1, 0 );
							break;

							//Play scratch sound effect
							case 4:
							Mix_PlayChannel( -1, e1, 0 );
							break;
							case 5:
							Mix_PlayChannel( -1, f1, 0 );
							break;
							case 6:
							Mix_PlayChannel( -1, g1, 0 );
							break;




                  }
                }
                 //Mix_PlayChannel( -1, gLow, 0 );
                tiles[i].rgbColor.red = 0x00;
                tiles[i].rgbColor.green = 0xBB;
                tiles[i].rgbColor.blue = 0xAC;
                tiles[i].rgbColor.alpha = 0x08;
            }
        }
    }

}
