#ifndef BONUS_H
#define BONUS_H

class Bonus : public Obstacle{

        public:
            Bonus();
            void setBonus();
            void moveBonus(int);
			void show() override;            		

        private:
            SDL_Surface *obstacles[1]= {nullptr};          
};

Bonus::Bonus(){
    // ctor
    TTF_Font* font = TTF_OpenFont( "Haunting Attraction.ttf", 36 );
    obstacles[0] = TTF_RenderText_Solid( font, "Life", { 255, 0, 0 } );
    TTF_CloseFont(font);
}


void Bonus::setBonus()
{
            int levelWidth = background->w - OBS_WIDTH;  // max X coord of an obstacle                         
                // avoid to generate collision with an obstacle when
                // the level starts and give the user some time to get used with the new level
				int randomX = rand() % levelWidth;
                //sets the coordinates for both physical and collision boxes of obstacles
                coordBox[0].w = OBS_WIDTH;
                coordBox[0].h = OBS_HEIGHT;
                coordBox[0].x = randomX;
                coordBox[0].y = rand() % (SCREEN_HEIGHT-OBS_HEIGHT);            
}

void Bonus::moveBonus(int x){

    
                coordBox[0].x -= x;     // moves the obstacle coordinate along with the background
				   
}

void Bonus::show(){
    //shows the obstacles
    	
	apply_surface(coordBox[0].x, coordBox[0].y, obstacles[0], screen );
}

#endif // BONUS_H
