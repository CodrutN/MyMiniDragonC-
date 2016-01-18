/* Copyright(c) 2014 - 2015 Codrut Niculescu

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution. */

#ifndef LOADER_H_INCLUDED
#define LOADER_H_INCLUDED

#include"SDL.h"
#include "SDL_image.h"
#include <string>
#include <iostream>
#include <sstream> // ostringstream
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "constants.h"
#include "obstacles.h"
#include "variables.h"
#include <stdio.h> // fprintf()
#include <stdlib.h>     // srand, rand
#include <time.h>       // time


SDL_Surface *load_image( std::string filename,int n = 3 )         //Loads an image and applies a mask
{
    //The image that's loaded
    SDL_Surface* loadedImage = nullptr;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = nullptr;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != nullptr ){
        //Create an optimized surface
        optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGB24, 0);

        //Free the old surface
        SDL_FreeSurface( loadedImage );

        //If the surface was optimized check for masking flag and apply
        if( optimizedImage != nullptr ){

            if(n==0){

                //Set green color key for masking
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 73, 203, 58 );
            SDL_SetColorKey( optimizedImage, SDL_TRUE, colorkey );
            }else if(n==1){
                //Set yellow color key for masking
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 255, 255, 128 );
            SDL_SetColorKey( optimizedImage, SDL_TRUE, colorkey );
            }else if(n==2){
                //Set black color key for masking
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0 );
            SDL_SetColorKey( optimizedImage, SDL_TRUE, colorkey );
            }
        }
    }

    //Return the optimized surface
    return optimizedImage;
}
bool load_files()
{
    //Load the background image
    background = load_image( IMG_PATH + "bg_lvl0.png", 3 );

    //If there was a problem loading the background
    if( background == nullptr ){
        printf("\nUnable to load the background image:  %s\n", IMG_GetError());
        return false;
    }

    //Open the font
    font = TTF_OpenFont( "Haunting Attraction.ttf", 30 );
    if (font == nullptr){
        printf("\nUnable to load the font file:  %s\n", TTF_GetError());
        return false;
    }

    //Load the game music
    music = Mix_LoadMUS( "sound/Flapping_Wings.wav" );

    //If there was a problem loading the game music
    if( music == nullptr ){
        printf("\nUnable to initialize SDL_mixer:  %s\n", Mix_GetError());
        return false;
    }

    //If everything loaded fine
    return true;
}

void init(){

    //Initialize all SDL subsystems
    if( SDL_Init(SDL_INIT_EVERYTHING) == -1 ){

        fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
        printf("\nUnable to initialize SDL:  %s\n", SDL_GetError());
        exit(125);
    }

    //Initialize SDL_ttf
    if( TTF_Init() == -1 ){
        fprintf(stderr, "\nUnable to initialize SDL_ttf:  %s\n", TTF_GetError());
        printf("\nUnable to initialize SDL_ttf:  %s\n", TTF_GetError());
        exit(127);
    }

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ){
        fprintf(stderr, "\nUnable to initialize SDL_mixer:  %s\n", Mix_GetError());
        printf("\nUnable to initialize SDL_mixer:  %s\n", Mix_GetError());
        exit(129);
    }

    //everything initialized fine

}

void clean_up()
{
    // Quit SDL_ttf
    TTF_Quit();
    // Quit SDL_mixer
    Mix_CloseAudio();
    // Quit SDL_img
    IMG_Quit();
    // Quit SDL
    SDL_Quit();
}
#endif

