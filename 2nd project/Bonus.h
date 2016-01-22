#ifndef BONUS_H
#define BONUS_H

class Bonus : public Obstacle{

        public:
            Bonus();
            void setBonus();
            void moveBonus(int);
            void showBonus();
            void deleteBonus();

        private:
            SDL_Surface *obstacles[1]= {nullptr};
            SDL_Rect box[1];  // the physical box of the Bonus

};

Bonus::Bonus(){
    // ctor
    TTF_Font* font = TTF_OpenFont( "Haunting Attraction.ttf", 36 );
    obstacles[0] = TTF_RenderText_Solid( font, "Life", { 255, 0, 0 } );
    TTF_CloseFont(font);
}

void Bonus::deleteBonus(){

        box[0].x = coordBox[0].x = -100;
        box[0].y = coordBox[0].y = -100;
}
void Bonus::setBonus()
{
            int levelWidth = background->w - OBS_WIDTH;  // max X coord of an obstacle
            int randomX;
            for(int i=0; i < 1; ++i){
                // avoid to generate collision with an obstacle when
                // the level starts and give the user some time to get used with the new level
                randomX = rand() % levelWidth;
                //sets the coordinates for both physical and collision boxes of obstacles
                box[i].w = coordBox[i].w = OBS_WIDTH;
                box[i].h = coordBox[i].h = OBS_HEIGHT;
                box[i].x = coordBox[i].x = randomX;
                box[i].y = coordBox[i].y = rand() % (SCREEN_HEIGHT-OBS_HEIGHT);
            }
}

void Bonus::moveBonus(int x){

    for(int i=0;i<1;++i){
                coordBox[i].x -= x;     // moves the obstacle coordinate along with the background
    }
}

void Bonus::showBonus(){
    //shows the obstacles
    for(int i=0; i<1; ++i)
    apply_surface( box[i].x, box[i].y, obstacles[i], background );
}

#endif // BONUS_H
