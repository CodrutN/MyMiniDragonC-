#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
#include "dragon.h"
#include "Highscore.h"

//defined menu buttons position
enum Buttons { PLAY = 200, OPTIONS = 270, HIGHSCORE = 340, INSTRUCTIONS = 410, CREDITS = 480, QUIT = 550 };

//back button function
void processBackButton(){

        // mouse coord
        int ax,ay;
        //flag
        bool bye = false;

        // Back button rectangle coord
        int bk_buttonX = SCREEN_WIDTH-250;
        int bk_buttonY = SCREEN_HEIGHT-150;
        int bk_buttonW = 150;
        int bk_buttonH = 48;
        // shows the back button
        showTextAtPosition( "pureevil2.ttf", 48, { 232, 116, 0 }, bk_buttonX, bk_buttonY, "Back" );
        //waiting events from mouse
        while(!bye){
            while(SDL_PollEvent(&mouse_event))
            {
                if(mouse_event.type==SDL_MOUSEMOTION){
                        ax = mouse_event.motion.x;
                        ay = mouse_event.motion.y;

                        // if mouse over back button highlight it
                        if((ax>bk_buttonX)&&(ax<(bk_buttonX + bk_buttonW))&&(ay>bk_buttonY)&&(ay<(bk_buttonY+bk_buttonH)))
                        {
                            showTextAtPosition( "pureevil2.ttf", 48, { 255, 0, 0 }, bk_buttonX, bk_buttonY, "Back" );
                        } else {
                            showTextAtPosition( "pureevil2.ttf", 48, { 232, 116, 0 }, bk_buttonX, bk_buttonY, "Back" );
                          }
                    }
                        // if mouse click on the back button: quit
                if(mouse_event.type == SDL_MOUSEBUTTONDOWN){
                         ax = mouse_event.motion.x;
                         ay = mouse_event.motion.y;
                             if((ax>bk_buttonX)&&(ax<(bk_buttonX + bk_buttonW))&&(ay>bk_buttonY)&&(ay<(bk_buttonY+bk_buttonH))){
                                    bye = true;
                             }
                }

          }
    }

}

//CREDITS
void creditsMenu(){

    SDL_Surface* creditsSurf = nullptr;
    creditsSurf = load_image("images/submenubg.png");

    apply_surface(0,0,creditsSurf,screen);
    SDL_UpdateWindowSurface(gameWindow);

    showTextAtPosition( "theHardwayRMX.ttf", 48, { 232, 116, 0 }, SCREEN_WIDTH/2 - 300, 50, "CREDITS" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, SCREEN_WIDTH/2 - 250, 300, "MY MINI DRAGON" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, SCREEN_WIDTH/2 - 250, 350, "a project for GAMELOFT" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, SCREEN_WIDTH/2 - 250, 400, "by Codrut Niculescu" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, SCREEN_WIDTH/2 - 250, 450, "@ 2015 ALL RIGHTS RESERVED" );

    processBackButton();

    SDL_FreeSurface(creditsSurf);
}

void instructionsMenu(){

    SDL_Surface* instructions = nullptr;
    instructions = load_image("images/submenubg1.png");

    apply_surface(0,0,instructions,screen);
    SDL_UpdateWindowSurface(gameWindow);

    showTextAtPosition( "theHardwayRMX.ttf", 48, { 232, 116, 0 }, SCREEN_WIDTH/2 - 300, 50, "Instructions" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, 200, 300, "Avoid colliding your dragon with the obstacles" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, 200, 350, "Press the UP arrow key to gain height" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, 200, 400, "Press the DOWN arrow key to loose height" );
    showTextAtPosition( "Haunting Attraction.ttf", 36, { 0x0, 0xFF, 0x0 }, 200, 450, "Releasing the UP arrow key makes the dragon to loose height" );

    processBackButton();

    SDL_FreeSurface(instructions);
}

void optionsMenu(){
   // LOAD THE OPTIONS SCREEN
        SDL_Surface* optionsSurf = load_image("images/submenubg.png");
        highscoreImg = load_image("images/submenubg.png");
        apply_surface(0,0,optionsSurf,screen);
        showTextAtPosition( "theHardwayRMX.ttf", 48, { 232, 116, 0 }, SCREEN_WIDTH/2 - 300, 50, "DEFINE KEYS" );

        //define keys
        StringInput upKeyInput;

        // get key for UP
        upKeyInput.handle_input("Press key for gaining height and then hit Enter:");
        std::string modifKey = upKeyInput.getString();
        myDefKeys::upKey = SDL_GetKeyFromName(modifKey.c_str());

        StringInput downKeyInput;
        //CLEAR SCREEN
        apply_surface(0,0,optionsSurf,screen);
        showTextAtPosition( "theHardwayRMX.ttf", 48, { 232, 116, 0 }, SCREEN_WIDTH/2 - 300, 50, "DEFINE KEYS" );
         // get key for DOWN
        downKeyInput.handle_input("Press key for loosing height and then hit Enter:");
        modifKey = downKeyInput.getString();
        myDefKeys::downKey = SDL_GetKeyFromName(modifKey.c_str());
        // wait for back button press
        //processBackButton();

        SDL_FreeSurface(optionsSurf);

}

class MainMenu{

    private:
        SDL_Surface* menu = nullptr;
        SDL_Surface* play_button = nullptr;
        SDL_Surface* option_button = nullptr;
        SDL_Surface* score_button = nullptr;
        SDL_Surface* instruc_button = nullptr;
        SDL_Surface* credits_button = nullptr;
        SDL_Surface* quit_button = nullptr;
        SDL_Color m_textColor;
        TTF_Font* m_font = nullptr;
        int correction = 37; // used to coorect the y coordinate of fonts

    public:
        MainMenu();
        ~MainMenu();
        void loadMainMenu();
        void highlightButton(int, int, std::string);
        void showMainMenu();
};

MainMenu::MainMenu(){

    m_font = TTF_OpenFont( "theHardwayRMX.ttf", 36 );
    loadMainMenu();
}

MainMenu::~MainMenu(){
    // free surfaces
    SDL_FreeSurface(menu);
    SDL_FreeSurface(play_button);
    SDL_FreeSurface(option_button);
    SDL_FreeSurface(score_button);
    SDL_FreeSurface(instruc_button);
    SDL_FreeSurface(credits_button);
    SDL_FreeSurface(quit_button);
    TTF_CloseFont(m_font);

}

void MainMenu::loadMainMenu(){

    m_textColor = { 232, 116, 0};
    menu = load_image("images/menubg.png");
    play_button = TTF_RenderText_Solid( m_font, "PLAY", m_textColor );
    option_button = TTF_RenderText_Solid( m_font, "OPTIONS", m_textColor );
    score_button = TTF_RenderText_Solid( m_font, "HIGHSCORES", m_textColor );
    instruc_button = TTF_RenderText_Solid( m_font, "INSTRUCTIONS", m_textColor );
    credits_button = TTF_RenderText_Solid( m_font, "CREDITS", m_textColor );
    quit_button = TTF_RenderText_Solid( m_font, "QUIT", m_textColor );

}

void MainMenu::showMainMenu(){

        // shows main image
        apply_surface(0, 0, menu, screen);
        // shows the buttons
        // apply a correction to buttons y coord because of font characteristics
        apply_surface(960, PLAY-correction, play_button, screen);
        apply_surface(960, OPTIONS-correction, option_button, screen);
        apply_surface(960, HIGHSCORE-correction, score_button, screen);
        apply_surface(960, INSTRUCTIONS-correction, instruc_button, screen);
        apply_surface(960, CREDITS-correction, credits_button, screen);
        apply_surface(960, QUIT-correction, quit_button, screen);
        // shows the title
        showTextAtPosition( "Haunting Attraction.ttf", 70, { 232, 116, 0 }, 150, 150, "MY MINI DRAGON" );
}

void MainMenu::highlightButton(int x, int y, std::string str){

        //highlight a specified button at x, y position
        SDL_Color color = { 255, 0, 0};
        SDL_Surface* buttonSurface = TTF_RenderText_Solid( m_font, str.c_str(), color );
        apply_surface(x, y-correction, buttonSurface, screen);
        SDL_UpdateWindowSurface(gameWindow);
        SDL_FreeSurface (buttonSurface);

}

int game_menu()
{
    int choice = 1;
    int x,y;
    bool session=true;

    back_music=Mix_LoadWAV("sound/Wind.wav");
    //PLAYS THE BACKGROUND MUSIC
    Mix_PlayChannel(-1,back_music,0);
    selection=Mix_LoadWAV("sound/boom.wav");
    int music_sol=0;

    // menu buttons coordinates and size
    int buttonsX = 960;
    int buttonsY = PLAY;
    int buttonsW = 250;
    int buttonsH = OPTIONS-PLAY;

    //create menu class object
    MainMenu menu;

    //Menu Loop:
    while(session){
    while(SDL_PollEvent(&mouse_event)){
            if(mouse_event.type==SDL_MOUSEMOTION)       //WHEN MOUSE IS IN MOTION
            {
                    x = mouse_event.motion.x;           //SET THE COORDINATES
                    y = mouse_event.motion.y;
                      // HIGHLIGHT PLAY
                    if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>PLAY)&&(y<buttonsH+PLAY))
                    {
                        // shows main menu
                        menu.showMainMenu();
                        //highlight PLAY
                        menu.highlightButton(buttonsX, PLAY, "PLAY");
                        if(music_sol==0){
                            Mix_PlayChannel(-1,selection,0);        // plays the selection sound
                            music_sol=1;
                        }
                    } // HIGHLIGHT OPTIONS
                    else if ((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>OPTIONS)&&(y<buttonsH+OPTIONS))
                    {
                        // shows main menu
                        menu.showMainMenu();
                        //highlight OPTIONS
                        menu.highlightButton(buttonsX, OPTIONS, "OPTIONS");
                        if(music_sol==0)
                            {
                                Mix_PlayChannel(-1,selection,0);
                                music_sol=1;
                            }
                    } // HIGHLIGHT HIGHSCORE
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>HIGHSCORE)&&(y<buttonsH+HIGHSCORE))
                    {
                        // shows main menu
                        menu.showMainMenu();
                        //highlight HIGHSCORES
                        menu.highlightButton(buttonsX, HIGHSCORE, "HIGHSCORES");
                        if(music_sol==0)
                          {
                            Mix_PlayChannel(-1,selection,0);
                            music_sol=1;
                          }

                    } // HIGHLIGHT INSTRUCTIONS
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>INSTRUCTIONS)&&(y<buttonsH+INSTRUCTIONS))
                    {
                        // shows main menu
                        menu.showMainMenu();
                        //highlight INSTRUCTIONS
                        menu.highlightButton(buttonsX, INSTRUCTIONS, "INSTRUCTIONS");
                        if(music_sol==0)
                        {
                            Mix_PlayChannel(-1,selection,0);
                            music_sol=1;
                        }
                    } // HIGHLIGHT CREDITS
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>CREDITS)&&(y<buttonsH+CREDITS))
                    {
                        // shows main menu
                        menu.showMainMenu();
                        //highlight CREDITS
                        menu.highlightButton(buttonsX, CREDITS, "CREDITS");
                        if(music_sol==0)
                        {
                            Mix_PlayChannel(-1,selection,0);
                            music_sol=1;
                        }
                    } // HIGHLIGHT QUIT
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>QUIT)&&(y<buttonsH+QUIT))
                    {
                        // shows main menu
                        menu.showMainMenu();
                        //highlight QUIT
                        menu.highlightButton(buttonsX, QUIT, "QUIT");
                        if(music_sol==0)
                        {
                            Mix_PlayChannel(-1,selection,0);
                            music_sol=1;
                        }
                    }
                    else
                    {
                        // mouse is not over any button
                        menu.showMainMenu();
                        //std::cout << y << std::endl;
                        music_sol=0;
                    }
            }
            // IF MOUSE BUTTON IS PRESSED
            if(mouse_event.type == SDL_MOUSEBUTTONDOWN){
                    x = mouse_event.motion.x;      //SETS THE COORDINATES
                    y = mouse_event.motion.y;
                    // PLAY
                    if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>PLAY)&&(y<buttonsH+PLAY)){
                        choice = 1;  //RETURNS PLAY
                        session = false;
                    }
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>OPTIONS)&&(y<buttonsH+OPTIONS)){
                          // OPTIONS LOOP
                        optionsMenu();
                        // shows main menu
                        menu.showMainMenu();
                    }
                    //HIGHSCORE
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>HIGHSCORE)&&(y<buttonsH+HIGHSCORE)){

                        highScore();
                        // shows main menu
                        menu.showMainMenu();
                    }
                    // Instructions
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>INSTRUCTIONS)&&(y<buttonsH+INSTRUCTIONS)){

                                instructionsMenu();
                                 // shows main menu
                                menu.showMainMenu();
                            }
                    // CREDITS
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>CREDITS)&&(y<buttonsH+CREDITS)){

                        creditsMenu();
                         // shows main menu
                        menu.showMainMenu();
                    }
                    // QUIT
                    else if((x>buttonsX)&&(x<buttonsX+buttonsW)&&(y>QUIT)&&(y<buttonsH+QUIT)){
                                    choice = 6;
                                    session = false;
                    }
            }

            switch( mouse_event.type ){
                    case SDL_KEYDOWN:
                    if( mouse_event.key.keysym.sym == SDLK_ESCAPE )
                    {
                        choice = 6;             //if the user pressed escape
                        session = false;
                    }
                    break;

                    case SDL_QUIT:              //if the user closed the window
                        choice = 6;
                        session = false;
                    break;
            }
        }
   }
    //clean_up
    Mix_FreeChunk(selection);
    Mix_FreeChunk(back_music);
    return choice;
}

void update_screen(Timer& TimE,int score)       //displays score and time
{
    std::stringstream ss;
    int a=TimE.get_ticks();
    if(a<60000)
        {
           ss<< "SCORE: "<<score
           <<"  TIME: " << a/60000<<" : "<<a / 1000;
        }
        else
        {
            int sec=a/1000;
            int min=0;
            min=sec/60;
            sec-=min*60;
            ss<< "SCORE:  "<<score
            << "    TIME: " << min<<" : "<<sec;

        }
    SDL_Color textColor = { 0xFF, 0xFF, 0xFF };
    message = TTF_RenderText_Solid( font , ss.str().c_str() , textColor ) ;
    apply_surface((SCREEN_WIDTH-message->w)/2,0,message,screen);
    SDL_FreeSurface(message);

}


#endif
