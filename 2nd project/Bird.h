#ifndef BIRD_H
#define BIRD_H
#include "obstacles.h"

class Bird
{
    public:
        Bird();
        ~Bird();
        void set_state(int);       //used to pause/unpause the game

        // takes key presses and adjusts the bird's velocity
        void handle_input(bool);

        // moves the bird
        virtual void moveBird() = 0;

        // checks collision with the obstacles or screen borders
        bool checkCollision(Obstacle& obs);

        // shows the bird on the screen
        void show();

        int get_score();
        void set_score(int);
        //gets the collision coord
        SDL_Rect& getCollisionBox();
        //gets the lives
        int getLives();
        bool setLives(int);

        static int yVel;

    protected:
        // bird velocity

        int nextFrame;      //bird animation frame number
        int score;
        // bird animation frames
        SDL_Surface *bird[NO_OF_DRAGON_FRAMES]= {nullptr};
        SDL_Rect dragonBox; // bird collision box
    private:
};

//init static var
int Bird::yVel = 5;

bool check_collision( const SDL_Rect& A, const SDL_Rect& B );
Bird::Bird()
{
    //ctor
}

Bird::~Bird()
{
    //dtor
}

int Bird:: get_score()
{
    return score;
}

void Bird:: set_score(int addToScore)
{
    score += addToScore;
}

void Bird:: set_state(int vel)
{
    Bird::yVel = vel;
}

void Bird::handle_input(bool game_paused)
{
    // if a key was pressed
    if( event.type == SDL_KEYDOWN ){
        // adjust the velocity
        if (event.key.keysym.sym == myDefKeys::upKey ) { Bird::yVel -= DRAGON_HEIGHT / 3; }
        else if (event.key.keysym.sym == myDefKeys::downKey) { Bird::yVel += DRAGON_HEIGHT / 5; }
        //if the user pressed any other key the score wont be incremented
        else { return;}
        // increment the score only if the game is unpaused
        if (game_paused == false) score+=2;
    }
    // if a key was released
    else if( event.type == SDL_KEYUP ){
        // adjust the velocity
        if (event.key.keysym.sym == myDefKeys::upKey ) { Bird::yVel += DRAGON_HEIGHT / 3; }
            else if (event.key.keysym.sym == myDefKeys::downKey) { Bird::yVel -= DRAGON_HEIGHT / 5; }
            //if the user pressed any other key the score wont be incremented
            else { return; }
            // increment the score only if the game is unpaused
            if (game_paused == false) score+=2;
        }
}

bool Bird::checkCollision(Obstacle& obs){

    // COLLISION LOOP
    for(int i=0; i < maxNoOfObstacles; ++i){

        // If the bird went too far up or down or has collided with the obstacles
        if( ( dragonBox.y < -DRAGON_HEIGHT ) || ( dragonBox.y + DRAGON_HEIGHT > SCREEN_HEIGHT ) || check_collision(dragonBox, obs.coordBox[i])){
            apply_surface( obs.coordBox[i].x, obs.coordBox[i].y, background, screen, &obs.coordBox[i] );
            SDL_UpdateWindowSurface(gameWindow);
            SDL_Delay(500);
            //deletes the obstacle in case the dragon has more lifes
            obs.coordBox[i].x = -100;
            obs.coordBox[i].y = -100;
            return true;
        }
    }
    return false;
}

void Bird::show()
{
    //shows the bird
    //if animation frame > max No of frames, reset animation frame
    if (++nextFrame > (NO_OF_DRAGON_FRAMES-1)) nextFrame = 0;
    apply_surface( dragonBox.x, dragonBox.y, bird[nextFrame], screen );
}

SDL_Rect& Bird::getCollisionBox(){
    return dragonBox;
}

#endif // BIRD_H
