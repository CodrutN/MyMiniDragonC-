#ifndef STRING_INPUT_H_INCLUDED
#define STRING_INPUT_H_INCLUDED

using namespace constants;

//The key press interpreter
class StringInput{

    private:

        //The member storage string
        std::string m_str;

        //The member text surface
        SDL_Surface* m_text;

        //The member color of the font
        SDL_Color m_textColor;
        //The member font
        TTF_Font* m_font;

    public:

        StringInput();
        ~StringInput();

        //Handles input
        void handle_input(std::string);

        //Shows the message on screen
        void show_text( int, int );

        //get string stored
        std::string getString();


};

StringInput::StringInput()
{
    //Initializers
    m_str = "";
    m_text = nullptr;
    m_font = nullptr;
    m_textColor = { 0x0, 0xFF, 0x0 }; // green

    m_font = TTF_OpenFont( "Haunting Attraction.ttf", 30 );
    if (m_font == nullptr){
        printf("\nUnable to load the font file:  %s\n", TTF_GetError());
    }
}

StringInput::~StringInput()
{
    //Free text surface
    TTF_CloseFont( m_font );
    SDL_FreeSurface( m_text );
    m_text = nullptr;
    m_font = nullptr;
}

void StringInput::handle_input(std::string str){

    bool quit = false;

    //Event handler
    SDL_Event e;

    //Used for covering the text while typing
    SDL_Rect clip;
    clip.x = 0;
    clip.y = 533;
    clip.w = SCREEN_WIDTH;
    clip.h = 110;

    //Shows text parsed in the function
    m_text = TTF_RenderText_Solid( m_font, str.c_str(), m_textColor );

        //While processing text input
        while( !quit ){
            //The render text flag
            bool renderText = false;

            //Handle events on queue
            while( SDL_PollEvent( &e ) ){
                //User requests quit
                if( e.type == SDL_QUIT ){
                    quit = true;
                }
                //Special key input
                else if( e.type == SDL_KEYDOWN ){
                    //Handle ESC or Enter
                    if ( e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_RETURN ){
                            quit = true;
                    }
                    //Handle backspace
                    else if( e.key.keysym.sym == SDLK_BACKSPACE && m_str.length() > 0 ){
                        //pop off character
                        m_str.pop_back();
                        renderText = true;
                    }
                }
                // text input event
                else if( e.type == SDL_TEXTINPUT )
                {
                    //Append character if it's not SPACE otherwise will affect the highscore.txt file
                    if (e.text.text[ 0 ] != ' '){
                    m_str += e.text.text;
                    renderText = true;
                    }
                }
            }

            // render text if needed
            if( renderText ){
                //Text is not empty
                if( m_str != "" ){

                    m_text = TTF_RenderText_Solid( m_font, m_str.c_str(), m_textColor );
                }
                //Text is empty, shows default text
                else{
                    m_text = TTF_RenderText_Solid( m_font, str.c_str(), m_textColor );
                }
            }
            //hide the previous input text
            apply_surface(clip.x,clip.y,highscoreImg,screen,&clip);
            //show the new text
            show_text(( SCREEN_WIDTH - m_text->w ) / 2, 595);
            //update window
            SDL_UpdateWindowSurface(gameWindow);
        }

        // if string is empty, save default
        if (m_str==""){
            m_str="Unknown";
        }
}

void StringInput::show_text( int x, int y )
{
    //If the surface isn't blank
    if( m_text != NULL ){
        //Shows the name
        apply_surface( x, y, m_text, screen );
    }
}

std::string StringInput :: getString()
{
     return m_str;
}


#endif
