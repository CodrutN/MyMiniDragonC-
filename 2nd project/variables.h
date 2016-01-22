#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

SDL_Window* gameWindow = nullptr;
//SDL SURFACE POINTERS
SDL_Surface *background = nullptr;
SDL_Surface* highscoreImg=nullptr;
SDL_Surface *screen = nullptr;
SDL_Surface *message=nullptr;

TTF_Font    *font = nullptr;

//MUSIC VARIABLES
Mix_Music   *music = nullptr;
Mix_Chunk   *back_music=nullptr;
Mix_Chunk   *selection = nullptr;
Mix_Chunk   *boom=nullptr;

//SDL global events
SDL_Event event;
SDL_Event mouse_event;
//used to save the last score
int currentScore = 0;
//last score from Top5
int lowestScore = 0;
//max no of obstracles based on level width
int maxNoOfObstacles = 0;
//max no of bats showed in the same time
int noOfBats = 0;

//DEFINED KEYS
namespace myDefKeys {
SDL_Keycode upKey = SDLK_UP;
SDL_Keycode downKey = SDLK_DOWN;
SDL_Keycode pauseKey = SDLK_SPACE;
}
#endif
