#ifndef BAT_H
#define BAT_H


class Bat : public Bird
{
    public:
        Bat();
        bool isOnScreen;
        void batSetY ();

        virtual void moveBird();

    protected:
    private:
        int xVel;
};

Bat::Bat()
{
    isOnScreen = false;
    //Load the bat images
    std::ostringstream ss;          //stores the filenames for the bat frames
    //ss = std::to_string(i);       //bug in MINGW so I'll use ostringstream
    for (int i=0; i < NO_OF_BAT_FRAMES; ++i){
    ss.clear();
    ss.str("");
    ss << "images/bat/Bat" << i << ".png";
    bird[i] = load_image( ss.str(),0);
           //If there was a problem loading the bat's img
        if( bird[i] == nullptr ){
           fprintf(stderr, "\nUnable to load bat image:  %s\n", IMG_GetError());
           printf("\nUnable to load bat image:  %s\n", IMG_GetError());
           exit (136);
        }
    }
    //Set initial bat position
    dragonBox.x =1050;
    SDL_Delay(rand() % SCREEN_HEIGHT);
    dragonBox.y =rand() % SCREEN_HEIGHT-DRAGON_HEIGHT;
    //Set the dragon's dimentions
    dragonBox.w = BAT_WIDTH;
    dragonBox.h = BAT_HEIGHT;
    //Init the velocity
    xVel = 3;

    //Init the starting bat animation frame
    nextFrame = 0;
}

void Bat::moveBird(){
    // Moves Bat inverse than the Dragon
    dragonBox.y -= Dragon::yVel;
    isOnScreen = true;
    //move Bat on X axis
    dragonBox.x -= xVel;
    if ((dragonBox.y >= SCREEN_HEIGHT-DRAGON_HEIGHT) || (dragonBox.y <= 0) ) dragonBox.y += Dragon::yVel;

    if ( (dragonBox.x <= 0) ) {
            dragonBox.x = SCREEN_WIDTH-DRAGON_HEIGHT;
            isOnScreen = false;
            dragonBox.y =rand() % SCREEN_HEIGHT-DRAGON_HEIGHT;
    }

}


void Bat::batSetY(){

    dragonBox.y =rand() % SCREEN_HEIGHT-DRAGON_HEIGHT;
}

#endif // BAT_H
