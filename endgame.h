#include <iostream>
#include <SDL2/SDL.h>
#include<SDL2/SDL_image.h>
//#include<SDL2/SDL_ttf.h>
#include <stdio.h>
#include"endgame.h"

// global variable for delay
//int delay = 40;

class Endgame{

private:

    const int screenWidth=480;
    const int screenHeight=640;

    //The window we'll be rendering to
    SDL_Window* window = NULL;

    //The window renderer
    SDL_Renderer* renderer = NULL;


public:

    //Starts up SDL and creates window
   bool init();

    //Loads media
  bool  loadMedia();

    // initialize position and color of tiles.

  void close();



};

