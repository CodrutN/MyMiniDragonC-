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

#ifndef DRAGON_H_INCLUDED
#define DRAGON_H_INCLUDED

#include "loader.h"
#include "obstacles.h"
#include "timer.h"

//FUNCTION PROTOTYPE
void showTextAtPosition(std::string fontName, int fontSize, SDL_Color textColor, int x, int y, std::string str);

class Dragon        // DRAGON CLASS
{
    protected:
        // dragon velocity
        int xVel, yVel;
        int nextFrame;      //dragon animation frame number
        int score;
        // dragon animation frames
        SDL_Surface *dragon[NO_OF_DRAGON_FRAMES]= {nullptr};
        SDL_Rect dragonBox; // dragon collision box

    public:
        Dragon();
        ~Dragon();
        void set_state(int);       //used to pause/unpause the game

        // takes key presses and adjusts the dragon's velocity
        virtual void handle_input(bool);

        // moves the dragon
        virtual void moveDragon();

        // checks collision with the obstacles or screen borders
        bool checkCollision(Obstacle& obs);

        // shows the dragon on the screen
        void show();

        int get_score();
        void set_score(int);
        SDL_Rect& getCollisionBox();
};

Dragon::Dragon()
{
    //Load the dragon images
    std::ostringstream ss;          //stores the filenames for the dragon frames
    //ss = std::to_string(i);       //bug in MINGW so I'll use ostringstream
    for (int i=0; i < NO_OF_DRAGON_FRAMES; ++i){
    ss.clear();
    ss.str("");
    ss << "images/dragon/dragon" << i << ".png";
    dragon[i] = load_image( ss.str(), 0 );
            //    std::cout << "incarca dragon nr. " << i << '\n';
           //If there was a problem loading the dragon's img
        if( dragon[i] == nullptr ){
           fprintf(stderr, "\nUnable to load dragon image:  %s\n", IMG_GetError());
           printf("\nUnable to load dragon image:  %s\n", IMG_GetError());
           exit (136);
        }
    }
    //Set initial dragon position
    dragonBox.x =350;
    dragonBox.y =350;
    //Set the dragon's dimentions
    dragonBox.w = DRAGON_WIDTH;
    dragonBox.h = DRAGON_HEIGHT;
    //Init the velocity
    xVel = 0;
    yVel = 5;
    //Init the starting dragon animation frame
    nextFrame = 0;
    //Init the score
    score = 0;
}

Dragon::~Dragon(){

    //frees the surfaces
    for (int i = 0; i < NO_OF_DRAGON_FRAMES; ++i ){
        if (dragon[i] != nullptr) SDL_FreeSurface( dragon[i] );
    }
}

int Dragon:: get_score()
{
    return score;
}

void Dragon:: set_score(int addToScore)
{
    score += addToScore;
}

void Dragon:: set_state(int vel)
{
    yVel = vel;
}

void Dragon::handle_input(bool game_paused)
{
    // if a key was pressed
    if( event.type == SDL_KEYDOWN ){
        // adjust the velocity
        if (event.key.keysym.sym == myDefKeys::upKey ) { yVel -= DRAGON_HEIGHT / 3; }
        else if (event.key.keysym.sym == myDefKeys::downKey) { yVel += DRAGON_HEIGHT / 5; }
        //if the user pressed any other key the score wont be incremented
        else { return;}
        // increment the score only if the game is unpaused
        if (game_paused == false) score+=2;
    }
    // if a key was released
    else if( event.type == SDL_KEYUP ){
        // adjust the velocity
        if (event.key.keysym.sym == myDefKeys::upKey ) { yVel += DRAGON_HEIGHT / 3; }
            else if (event.key.keysym.sym == myDefKeys::downKey) { yVel -= DRAGON_HEIGHT / 5; }
            //if the user pressed any other key the score wont be incremented
            else { return; }
            // increment the score only if the game is unpaused
            if (game_paused == false) score+=2;
        }
}

void Dragon::moveDragon(){
    // Moves the dragon up or down
    dragonBox.y += yVel;
}

bool Dragon::checkCollision(Obstacle& obs){

    // COLLISION LOOP
    for(int i=0; i < maxNoOfObstacles; ++i){

        // If the dragon went too far up or down or has collided with the obstacles
        if( ( dragonBox.y < -DRAGON_HEIGHT ) || ( dragonBox.y + DRAGON_HEIGHT > SCREEN_HEIGHT ) || check_collision(dragonBox, obs.coordBox[i])){

            return true;
        }
    }
    return false;
}

void Dragon::show()
{
    //shows the dragon
    //if animation frame > max No of frames, reset animation frame
    if (++nextFrame > (NO_OF_DRAGON_FRAMES-1)) nextFrame = 0;
    apply_surface( dragonBox.x, dragonBox.y, dragon[nextFrame], screen );
}

SDL_Rect& Dragon::getCollisionBox(){
    return dragonBox;
}
#endif
