#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED
#include "dragon.h"
#include "loader.h"

class Window
{
    private:
    //if the window is windowed or not
    bool windowed;

    public:
     Window();
    ~Window();

    //Handle window events
    void handle_events();

    //Check if anything's wrong with the window
    bool error();
};

Window::Window()
{
    // Set up the screen
    gameWindow = SDL_CreateWindow( "My Mini Dragon a Project for Gameloft by Codrut Niculescu", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN  );

    //If there's an error
    if( gameWindow == NULL ){
        fprintf(stderr, "\nUnable to initialize Window:  %s\n", SDL_GetError());
        printf("\nUnable to initialize Window:  %s\n", SDL_GetError());
        exit(75);
    }
    screen = SDL_GetWindowSurface(gameWindow);

    //Set window flag
    windowed = true;
}
Window::~Window(){

    SDL_DestroyWindow (gameWindow);
    gameWindow = nullptr;
    screen = nullptr;
}

void Window::handle_events()
{
    //If the window resized
    switch (event.type){
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            //Resize the screen
            SDL_SetWindowSize (gameWindow, event.window.data1, event.window.data2);
            //If there's an error
            if( gameWindow == NULL ){
                fprintf(stderr, "\nUnable to resize Window:  %s\n", SDL_GetError());
                printf("\nUnable to resize Window:  %s\n", SDL_GetError());
                exit(76);
            }
            screen = SDL_GetWindowSurface(gameWindow);
            SDL_UpdateWindowSurface(gameWindow);

        case SDL_WINDOWEVENT_CLOSE :
             switch( mouse_event.type ){
                case SDL_KEYDOWN:
                if( mouse_event.key.keysym.sym == SDLK_ESCAPE )
                {
                                // is escape is pressed
                    SDL_DestroyWindow (gameWindow);
                    clean_up();         //close the SDL
                    exit (0);
                }
                break;

                case SDL_QUIT:
                    SDL_DestroyWindow (gameWindow);
                    clean_up();         //close the SDL
                    exit (0);

                break;
            }

        case SDL_WINDOWEVENT_EXPOSED :
            //Update the screen
            if( SDL_UpdateWindowSurface(gameWindow) == -1 ){
                //If there's an error
            fprintf(stderr, "\nError on Window:  %s\n", SDL_GetError());
            printf("\nError on Window:  %s\n", SDL_GetError());
            exit(77);
            }
    }

}

bool Window::error()
{
    return false;
}

#endif
