#ifndef DRAGON_H_INCLUDED
#define DRAGON_H_INCLUDED


#include "Bird.h"


// DRAGON CLASS
class Dragon : public Bird{
    private:
        int life;
        int xVel;
    public:
        Dragon();
        ~Dragon();
        int getLives();
        bool setLives(int);
        virtual void moveBird();
};



Dragon::Dragon()
{
    life = 1;
    //Load the dragon images
    std::ostringstream ss;          //stores the filenames for the dragon frames
    //ss = std::to_string(i);       //bug in MINGW so I'll use ostringstream
    for (int i=0; i < NO_OF_DRAGON_FRAMES; ++i){
    ss.clear();
    ss.str("");
    ss << "images/dragon/dragon" << i << ".png";
    bird[i] = load_image( ss.str(), 0 );
            //    std::cout << "incarca dragon nr. " << i << '\n';
           //If there was a problem loading the dragon's img
        if( bird[i] == nullptr ){
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

    //Init the starting dragon animation frame
    nextFrame = 0;
    //Init the score
    score = 0;
}

Dragon::~Dragon(){

    //frees the surfaces
    for (int i = 0; i < NO_OF_DRAGON_FRAMES; ++i ){
        if (bird[i] != nullptr) SDL_FreeSurface( bird[i] );
    }
}


void Dragon::moveBird(){
    // Moves the dragon up or down
    dragonBox.y += Dragon::yVel;
}

int Dragon::getLives(){
    return life;
}

bool Dragon::setLives(int x){
    life += x;
    return (life <= 0) ? true : false;
}

#endif
