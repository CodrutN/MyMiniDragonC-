#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED
#include <string>
namespace constants                         // namespace containing all the constants
{
        const int FRAMES_PER_SECOND = 100;
        const int TICKS_PER_FRAME = 1000 / FRAMES_PER_SECOND;

        const int DRAGON_WIDTH = 144;
        const int DRAGON_HEIGHT = 60;
        const int BAT_WIDTH = 86;
        const int BAT_HEIGHT = 85;

        const int OBS_WIDTH = 96;
        const int OBS_HEIGHT = 76;
        const int SCREEN_WIDTH = 1366;
        const int SCREEN_HEIGHT = 768;

        const std::string IMG_PATH = "images/";
        const int NO_OF_DRAGON_FRAMES = 13;
        const int NO_OF_BAT_FRAMES = 8;
        const int NO_OF_OBSTACLES = 16;
        const int NO_OF_LEVELS = 5;
}
#endif
