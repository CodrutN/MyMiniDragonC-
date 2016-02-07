#ifndef PLAY_H_INCLUDED
#define PLAY_H_INCLUDED
#include "Bat.h"

#include "Bonus.h"


void play(){
    // init srand to generate random numbers used for obstacles
    srand (time(NULL));

    // flags
    bool quit = false;
    bool game_paused = false;

    int level = 0;

    //The background offsets
    int bgX = 0, bgY = 0;

    //Load the files
    if( !load_files() ) return;

    Dragon myDragon;        //CREATING DRAGON CLASS OBJECT


    Bat bats[3];
    //std::vector <Bat> bats;
    for (int i = 0; i<3; ++i){
        bats[i] =  Bat();
        //bats.push_back(Bat());
    }

    Timer fps;               //CREATING TIMER CLASS OBJECT

    Obstacle obs;            //CREATING OBSTACLE CLASS OBJECT
    obs.setObstacles();

    Bonus bonus;
    bonus.setBonus();
    //The frame rate regulator
    int start_ticks;
    int calculate_ticks;

    //Start the frame timer
    fps.start();

    //While the user hasn't quit
    while( !quit ){

        start_ticks = fps.get_ticks();
        // dragon's wings flapping sound playing
        if (Mix_PlayingMusic() == 0){
           Mix_PlayMusic( music, 0 );
           //return 1;
        }

        // while there's events to handle
        while( SDL_PollEvent( &event ) ){

            // Handle events for dragon
            myDragon.handle_input(game_paused);

            if(event.type==SDL_KEYDOWN){

                // if escape was pressed: quit
                if( event.key.keysym.sym==SDLK_ESCAPE){
                        Mix_HaltMusic();
                        Mix_FreeMusic( music );
                        quit=true;
                }
                // check if PAUSE was pressed
                else if( event.key.keysym.sym == myDefKeys::pauseKey ){
                    //if it's already paused, will resume
                    if (fps.is_paused()) {
                        fps.unpause();          //unpause the time played
                        game_paused = false;
                        myDragon.set_state(5); //unpause the dragon
                        Mix_ResumeMusic();
                    } else{
                                    //Pause the program
                    fps.pause();
                    game_paused = true;     //sets the paused flag
                    Mix_PauseMusic(); //pause the dragon's wings sound
                    }
                }

            } // if the user has closed the window
            else if( event.type == SDL_QUIT ){
                    //Quit the program
                    quit = true;
                    //saves the score
                    currentScore = myDragon.get_score();
                    Mix_HaltMusic();
                    Mix_FreeMusic( music );
                }
        }
        // check if the game is paused
        if (game_paused == true){
            myDragon.set_state(0);  //pause the dragon
        }
        // sets the velocity the background rolls according to the time passed
        else if(fps.get_ticks() < 10000){
            bgX -=7;
            obs.moveObstacles(7);
            bonus.moveBonus(7);
        }else if(fps.get_ticks()<40000){
            bgX-=10;
            obs.moveObstacles(10);
            bonus.moveBonus(10);
        }else if(fps.get_ticks()<90000){
            bgX-=15;
            obs.moveObstacles(15);
            bonus.moveBonus(15);
        }else if(fps.get_ticks()<120000){
            bgX-=20;
            obs.moveObstacles(20);
            bonus.moveBonus(20);
        }else{
            bgX-=30;
            obs.moveObstacles(30);
            bonus.moveBonus(30);
        }

        // IF THE LEVEL ENDED
        if( bgX <= -background->w ){
            // resets the background offset
            bgX = 0;
            // increment level
            level++;
            // add bonus level score
            myDragon.set_score(50*level);
            // check win condition
            if (level < NO_OF_LEVELS){
                std::ostringstream ss;          //stores the level filename
                ss.clear();
                ss.str("");
                ss << IMG_PATH << "bg_lvl" << level << ".png";
                    //Load the background image
                background = load_image( ss.str());
                //If there was a problem loading the background
                if( background == nullptr ){
                    printf("\nUnable to load the background image:  %s\n", IMG_GetError());
                    return;
                }
            //sets bonus life
            bonus.setBonus();
            //shows level no and sets a small delay
            ss.clear();
            ss.str("");
            ss << "LEVEL " << level+1;
            apply_surface( bgX, bgY, background, screen );
            showTextAtPosition( "theHardwayRMX.ttf", 36, { 0xFF, 0x0, 0xFF }, SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2-100, ss.str() );
            //sets new obstacles with new coordinates
            obs.setObstacles();
            //show dragon
            myDragon.show();
            SDL_UpdateWindowSurface(gameWindow);
            //delay to prepare the user for next level
            SDL_Delay(1500);
            } else {
                    //win situation - end of levels
                    quit = true;
                    //save the score
                    currentScore = myDragon.get_score();
                    //shows Victory
                    showTextAtPosition( "theHardwayRMX.ttf", 48, { 0x0, 0xFF, 0xFF }, SCREEN_WIDTH/2 - 300, SCREEN_HEIGHT/2, "VICTORY !" );
                    SDL_Delay(3000);
            }
        }

        // rolls the background
        apply_surface( bgX, bgY, background, screen );
        // concatenates the background to create the effect of moving when the width is less then screen size
        apply_surface( bgX + background->w, bgY, background, screen );
        // shows the obstacles
        obs.show();
        //shows bonus
        bonus.show();
        //there is 1/1000 chances for the bat to show up
        int randomGen = rand() % 1000;
        //if there is at least 1 bat on the screen then show it
        if (randomGen == 1 || bats[0].isOnScreen){
            if (!bats[0].isOnScreen) noOfBats = rand() % 3;
                for (int j =0; j<= noOfBats; j++){
                    //move the bat(s) on the screen
                    bats[j].moveBird();
                    bats[j].show();
                    //check collision with the bats
                    if (check_collision(bats[j].getCollisionBox(), myDragon.getCollisionBox())){
                        if (myDragon.setLives(-1)) quit = true;
                        //save the score
                        currentScore = myDragon.get_score();
                }
            }
        }
        //bonus life?
        if (check_collision(bonus.getCollisionBox(0), myDragon.getCollisionBox())){
                        myDragon.setLives(1);                        
                        SDL_Delay(500);
                        //apply_surface(bonus.x,clip.y,highscoreImg,screen,&clip);
                        bonus.remove(0);
                }
        // moves & shows the dragon on the screen
        myDragon.moveBird();
        myDragon.show();
        // displays time & score
        update_screen(fps, myDragon);
        // updates the screen
        SDL_UpdateWindowSurface(gameWindow);

        // checks collision
        if ( myDragon.checkCollision(obs) ) {
            if (myDragon.setLives(-1)) quit = true;
            //save the score
            currentScore = myDragon.get_score();
        }
        // if it didn't collide:

        //cap the frame rate
        calculate_ticks = (fps.get_ticks() - start_ticks);
        if( calculate_ticks < TICKS_PER_FRAME ){
            //Wait remaining time
            SDL_Delay(TICKS_PER_FRAME - calculate_ticks);
        }
    }
            //plays the crash sound
            boom=Mix_LoadWAV("sound/Dragon_Roaring.wav");
            Mix_PlayChannel(-1,boom,0);
                   // SHOWS GAME OVER !
            showTextAtPosition( "theHardwayRMX.ttf", 36, { 0xFF, 0x0, 0x0 }, SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2-100, " GAME OVER !" );
            SDL_Delay(2000);
            //reset Dragon::yVel
            Dragon::yVel = 5;
        if( background != nullptr ) SDL_FreeSurface( background );
        if( font != nullptr )   TTF_CloseFont( font );
        if( music != nullptr ) {Mix_HaltMusic(); Mix_FreeMusic( music );}
}


#endif
