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

#ifndef OBSTACLES_H_INCLUDED
#define OBSTACLES_H_INCLUDED
#include "constants.h"
#include "variables.h"

using namespace constants;

bool check_collision( const SDL_Rect& A, const SDL_Rect& B )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    //Calculate the sides of rect B
    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB ){
        return false;
    }

    if( topA >= bottomB ){
        return false;
    }

    if( rightA <= leftB ){
        return false;
    }

    if( leftA >= rightB ){
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;

    //Get offsets
    offset.x = x;
    offset.y = y;

    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );

}

class Obstacle
{
    private:
        SDL_Surface *obstacles[NO_OF_OBSTACLES]= {nullptr};    // obstacle's images holder
        SDL_Rect box[NO_OF_OBSTACLES];  // the physical box of the Obstacle
        SDL_Surface* loadImage( std::string ); //function to load the obstacles images

    public:

        SDL_Rect coordBox[NO_OF_OBSTACLES];  // used to check the collision with obstacles

        Obstacle();
        ~Obstacle();

        void setObstacles();
        void moveObstacles(int);
        void show();

};

Obstacle::Obstacle(){
    // ctor

    //Load the dragon images
    std::ostringstream ss;          //stores the filenames for the obstacles images
    for (int i=0; i < NO_OF_OBSTACLES; ++i){
    ss.clear();
    ss.str("");
    ss << "images/obs/bubbles" << i << ".png";
    // should check if NO_OF_OBSTACLES > max number of obstacle image files (16)
    obstacles[i] = loadImage( ss.str() );
           //If there was a problem loading the obstacles' img
        if( obstacles[i] == nullptr ){
           std::cout << "\nUnable to load obstacles image:  " << IMG_GetError();
           exit (139);
        }
    }
}

Obstacle::~Obstacle(){
    //destructor
    //frees the surfaces
    for (int i=0; i < NO_OF_OBSTACLES; ++i){
        SDL_FreeSurface (obstacles[i]);
    }
}

void Obstacle::setObstacles()
{
            int levelWidth = background->w - OBS_WIDTH;  // max X coord of an obstacle
            int randomX;
            //sets max no of obstacles based on level width
            if ((maxNoOfObstacles = levelWidth/500) > NO_OF_OBSTACLES){
                    maxNoOfObstacles = NO_OF_OBSTACLES;
            }
            std::cout << maxNoOfObstacles << " ";

            for(int i=0; i < maxNoOfObstacles; ++i){
                // avoid to generate collision with an obstacle when
                // the level starts and give the user some time to get used with the new level
                while ((randomX = rand() % levelWidth) < SCREEN_WIDTH){}
                //sets the coordinates for both physical and collision boxes of obstacles
                box[i].w = coordBox[i].w = OBS_WIDTH;
                box[i].h = coordBox[i].h = OBS_HEIGHT;
                box[i].x = coordBox[i].x = randomX;
                box[i].y = coordBox[i].y = rand() % (SCREEN_HEIGHT-OBS_HEIGHT);
            }
}

void Obstacle::moveObstacles(int x){

    for(int i=0;i<NO_OF_OBSTACLES;++i){
                coordBox[i].x -= x;     // moves the obstacle coordinate along with the background
    }
}

void Obstacle::show(){
    //shows the obstacles
    for(int i=0; i<NO_OF_OBSTACLES; ++i)
    apply_surface( box[i].x, box[i].y, obstacles[i], background );
}

// LOADING OBSTACLE IMAGE & SETTING TRANSPARENCY
SDL_Surface* Obstacle::loadImage( std::string filename ){

    //The image that's loaded
    SDL_Surface* loadedImage = nullptr;

    //The optimized surface that will be used
    SDL_Surface* optimizedImage = nullptr;

    //Load the image
    loadedImage = IMG_Load( filename.c_str() );

    //If the image loaded
    if( loadedImage != nullptr ){
        // Create an optimized surface
        optimizedImage = SDL_ConvertSurfaceFormat(loadedImage, SDL_PIXELFORMAT_RGB24, 0);

        // Free the old surface
        SDL_FreeSurface( loadedImage );

        // If the surface was optimized check for masking flag and apply
        if( optimizedImage != nullptr ){
                //Set the black color key for masking
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0, 0 );
            SDL_SetColorKey( optimizedImage, SDL_TRUE, colorkey );

        }
    }

    //Return the optimized surface
    return optimizedImage;
}

#endif
