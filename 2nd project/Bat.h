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

#ifndef BAT_H
#define BAT_H

#include "dragon.h"


class Bat : public Dragon
{
    public:
        Bat();
        bool isOnScreen;

        virtual void moveDragon();
    protected:
    private:
};

Bat::Bat()
{
    isOnScreen = false;
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
    dragonBox.x =1050;
    dragonBox.y =350;
    //Set the dragon's dimentions
    dragonBox.w = DRAGON_WIDTH;
    dragonBox.h = DRAGON_HEIGHT;
    //Init the velocity
    xVel = 3;
    yVel = 5;
    //Init the starting dragon animation frame
    nextFrame = 0;
}

void Bat::moveDragon(){
    // Moves Bat inverse than the Dragon
    dragonBox.y -= yVel;
    isOnScreen = true;
    //move Bat on X axis
    dragonBox.x -= xVel;
    if ((dragonBox.y >= SCREEN_HEIGHT-DRAGON_HEIGHT) || (dragonBox.y <= 0) ) dragonBox.y += yVel;

    if ( (dragonBox.x <= 0) ) {
            dragonBox.x = SCREEN_WIDTH-DRAGON_HEIGHT;
            isOnScreen = false;
    }

}

#endif // BAT_H
