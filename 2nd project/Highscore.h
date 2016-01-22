#ifndef HIGHSCORE_H_INCLUDED
#define HIGHSCORE_H_INCLUDED

#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include "String_Input.h"

//FUNCTION PROTOTYPE
void processBackButton();
void showTextAtPosition(std::string fontName, int fontSize, SDL_Color textColor, int x, int y, std::string str);

class HighScore{
  private:
          int m_highscore[5];
          std::string m_playerName[5];
          std::string m_playerAndScore[5];
          TTF_Font* m_font = nullptr;
          SDL_Color m_textColor;
  public:
          HighScore();
          ~HighScore();
          //check if it's able to write the file
          void check_file(std::string);
          //read the file
          std::string* read_file(std::string);
          //write the file
          void write_file(std::string);
          //sort Top 5 players
          void bubble_sort();
          //check if the score is in Top 5
          bool isHighScore(int);
          //insert name and score in Top 5
          void insertScoreAndName(int, std::string);
          //show the Top 5
          void showHiscores();
};

HighScore::HighScore()
{
    //set member font
    m_font = TTF_OpenFont( "Haunting Attraction.ttf", 30 );
    if (m_font == nullptr){
        printf("\nUnable to load the font file:  %s\n", TTF_GetError());
    }
    m_textColor = { 0, 160, 160 };   // green
}
HighScore :: ~HighScore()
{
    TTF_CloseFont( m_font );
    m_font = nullptr;
}

void HighScore::check_file( std::string filename )
{
     // ifstream constructor opens the file
     std::ifstream scoreFile( filename.c_str() , std::ios::in );

     // exit program if ifstream could not open file
     if ( !scoreFile ){
        write_file( filename );
     }
}

std::string* HighScore::read_file( std::string filename )
{
    // ifstream constructor opens the file
     std::ifstream scoreFile( filename.c_str(), std::ios::in );

     // exit program if ifstream could not open file
     if ( !scoreFile ){
        std::cout << "File could not be opened" << std::endl;
        return nullptr;
     }
        std::ostringstream ss;          //concatenates player name and score into a string

     // read each record in file
     for( int i = 0; i < 5; i++ ){
            scoreFile >> m_highscore[i] >> m_playerName[i] ;
            ss.clear();
            ss.str("");
            ss << i+1 << "  " << m_playerName[i] << "  " << m_highscore[i];
            m_playerAndScore[i] = ss.str();
     }
     //insert the lowest score from Top 5 into the dedicated variable
     lowestScore = m_highscore[4];
    return m_playerAndScore;
}


void HighScore::write_file( std::string filename )
{
    // ofstream constructor opens file
     std::ofstream scoreFile( filename.c_str(), std::ios::out );

     // exit program if unable to create file
     if ( !scoreFile ){
        std::cout << "File could not be opened" << std::endl;
        return;
     }
    // writes to the file
     for( int i = 0; i < 5; i++ ) {
        scoreFile << m_highscore[i] << ' ' << m_playerName[i] << std::endl;
     }

}

void HighScore::bubble_sort()
{
     for( int i = 0; i < 5; i++ ){
          for( int j = i+1; j < 5; j++ ){
               if( m_highscore[i] < m_highscore[j] ){
                    int tempInt = m_highscore[i];
                    std::string tempString = m_playerName[i];
                    m_highscore[i] = m_highscore[j];
                    m_playerName[i] = m_playerName[j];
                    m_highscore[j] = tempInt;
                    m_playerName[j] = tempString;
               }
          }
     }
}

bool HighScore::isHighScore( int score ){
    read_file( "highscore.txt" );
    bubble_sort();
    return (score > m_highscore[4]) ? true : false;
}

void HighScore::insertScoreAndName( int score, std::string highscorer )
{
     m_highscore[4] = score;
     m_playerName[4] = highscorer;
     bubble_sort();
}

void HighScore::showHiscores()
{
        std::string *name;

        check_file("highscore.txt");
        name = read_file("highscore.txt");

        apply_surface(0,0,highscoreImg,screen);
        //shows HIGHSCORE
        showTextAtPosition( "theHardwayRMX.ttf", 42, { 232, 116, 0 }, SCREEN_WIDTH/2 - 200, 50, "HIGHSCORES" );
        SDL_Surface* highscores;

        // shows Top 5 names and scores
        for( int i = 0; i < 5; i++ ){
            highscores = TTF_RenderText_Solid( m_font, name[i].c_str(), m_textColor );
            apply_surface( (SCREEN_WIDTH/3), ( SCREEN_HEIGHT/3 + i* 50), highscores, screen );
            SDL_FreeSurface (highscores);
        }
}

// GLOBAL FUNCTION
void highScore(){

        //loads Highscore image background
        highscoreImg=load_image("images/submenubg.png");

        HighScore hs;
        hs.showHiscores();

        // Is the score in Top 5?
        if (hs.isHighScore(currentScore)){
            StringInput myString;

            // input name
            myString.handle_input("Input your name:");

            //insert and sort new scores and names
            hs.insertScoreAndName(currentScore, myString.getString());

            //write new scores and names into a file
            hs.write_file("highscore.txt");

            //update hiscores
            hs.showHiscores();
        }
        // reset the score
        currentScore = 0;
        // wait for back button press
        processBackButton();

    SDL_FreeSurface(highscoreImg);
}


#endif
