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

#include "SDL.h"
#include "SDL_image.h"
#include <SDL_mixer.h>
#include <string>
#include <stdlib.h>
#include "dragon.h"
#include "loader.h"
#include "timer.h"
#include "window.h"
#include "obstacles.h"
#include "game_functions.h"
#include "play.h"
#include "String_Input.h"



int wmain(int argc, wchar_t *argv[]) {

    bool cont=true;
    // init SDL
    init();
    // welcome screen
    wel_come();
    // init lowest score


    while(cont){
        // creates Menu window
        Window menuWindow;
        int choice = game_menu();

        //GAME MENU LOOP
        switch(choice){
            case 1:
                //PLAY
                play();
                // if the player didn't score more than the 5th player
                if ( currentScore <= lowestScore) break;
                // the player is in Top 5 and proceed to input the name

            case 2:
            // OPTIONS

            case 3:
            // HIGHSCORES
                highScore();
                break;
            case 4:
            // INSTRUCTIONS
                break;
            case 5:
            // CREDITS
                break;
            case 6:
            // QUIT FROM PROGRAM
                cont=false;
                break;
            default:
                break;
        }
        clean_up();
        // init and start over
        init();
    }

    clean_up();
    return 0;
}
