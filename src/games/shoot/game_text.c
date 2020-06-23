/* --------------------------------------------------------------------------------------- */ 
// 
// CROSS SHOOT by Fabrizio Caruso
//
// Fabrizio_Caruso@hotmail.com
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from
// the use of this software.

// Permission is granted to anyone to use this software for non-commercial applications, 
// subject to the following restrictions:

// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software. If you use this software in
// a product, an acknowledgment in the product documentation would be
// appreciated but is not required.

// 2. Altered source versions must be plainly marked as such, and must not
// be misrepresented as being the original software.

// 3. This notice may not be removed or altered from any source distribution.
/* --------------------------------------------------------------------------------------- */ 

#include "settings.h"
#include "../cross_lib/cross_lib.h"

#include "game_text.h"
#include "character.h"
#include "settings.h"
#include "text_strings.h"


extern Image GHOST_IMAGE;
extern Image BULLET_IMAGE;
extern Image PLAYER_IMAGE;

extern uint8_t guns; 

#if !defined(NO_TEXT_COLOR)
    #define SET_COLOR(c) SET_TEXT_COLOR(c)
#else
    #define SET_COLOR(c)
#endif

#if defined(WIDE) && !defined(TINY_GAME)
    #define BULLET_IMAGE_X 18
    #define BULLET_IMAGE_Y 0
    #define GHOST_IMAGE_X 14
    #define GHOST_IMAGE_Y 0
    #define PLAYER_IMAGE_X 17
    #define PLAYER_IMAGE_Y 1
    #define LEVEL_X 6
#else
    #define BULLET_IMAGE_X 11
    #define BULLET_IMAGE_Y 0
    #define GHOST_IMAGE_X 8
    #define GHOST_IMAGE_Y 0
    #define PLAYER_IMAGE_X 14
    #define PLAYER_IMAGE_Y 0
    #define LEVEL_X 18
#endif

#if defined(ALT_DISPLAY_STATS)
    #define printCenteredMessageOnRow(row, text) PRINT(6,row,text)
#endif

#if defined(NO_TEXT_COLOR)

    #define printCenteredMessageOnRowWithCol(row,col,text) printCenteredMessageOnRow(row,text)
#endif    

extern uint8_t level;
extern uint8_t lives;

extern uint16_t points;
extern uint8_t ghostCount;
extern uint16_t ghostLevel;
extern uint16_t highScore;

extern Image BULLET_IMAGE;

#if defined(FULL_GAME) && !defined(NO_MESSAGE)
    void printKillTheSkull(void)
    {
        printCenteredMessage(KILL_THE_SKULL_STRING);    
        printCenteredMessageOnRow(((uint8_t)YSize)/2+2,DESTROY_MISSILES_STRING);
    }
    
#endif

#if defined(NO_TITLE_LINE)
    #define TITLE_Y 0
    #define TITLE_LINE()
#else
    #define TITLE_Y 1
    #define TITLE_LINE() PRINT(XSize-11,+0,  "-----------")
#endif


#define PRINT_WIDE_TITLE() \
    SET_COLOR(COLOR_CYAN); \
    PRINT(0, +0,   SCORE_STRING); \
    PRINT(0, +0+1, LEVEL_STRING); \
    \
    SET_COLOR(COLOR_RED); \
    TITLE_LINE(); \
    PRINT(XSize-11,TITLE_Y,"cross shoot");    


// TODO: This is SLOW
#if !defined(TINY_GAME)
    void displayStatsTitles(void)
    {                
        #if defined(WIDE)
                PRINT_WIDE_TITLE();
        #endif
        
        SET_COLOR(TEXT_COLOR);
        
        #if (X_OFFSET==0) && (Y_OFFSET==0)
            #define _draw_stat _draw
        #endif
    
        _draw_stat(BULLET_IMAGE_X, BULLET_IMAGE_Y, &BULLET_IMAGE);
        _draw_stat(GHOST_IMAGE_X, GHOST_IMAGE_Y, &GHOST_IMAGE);
        _draw_stat(PLAYER_IMAGE_X, PLAYER_IMAGE_Y, &PLAYER_IMAGE);                    
    }

    
    void printGunsStats(void)
    {
        SET_COLOR(TEXT_COLOR);    
        
        #if defined(WIDE)
            PRINTD(BULLET_IMAGE_X+1,0+0,2,guns);
        #else
            PRINTD(BULLET_IMAGE_X+0,0+0,2,guns);
        #endif
    }
#endif

#if !defined(NO_STATS)
    void printLevelStats(void)
    {    
        SET_COLOR(TEXT_COLOR);
    
        #if defined(WIDE) && !defined(TINY_GAME)
            PRINTD(LEVEL_X,1+0,2,level);
        #else
            PRINTD(LEVEL_X,+0,2,level);    
        #endif    
    }


    void printGhostCountStats(void)
    {
        SET_COLOR(TEXT_COLOR);        
        
        #if defined(WIDE) && !defined(TINY_GAME)
            PRINTD(GHOST_IMAGE_X+1,+0,2,ghostCount);
        #else
            PRINTD(GHOST_IMAGE_X+0,+0,2,ghostCount);    
        #endif    
    }


    void printLivesStats(void)
    {
        SET_COLOR(TEXT_COLOR);
        
        #if defined(WIDE) && !defined(TINY_GAME)
            PRINTD(PLAYER_IMAGE_X+1,+0+1,2,lives);
        #else
            PRINTD(PLAYER_IMAGE_X+0,+0,2,lives);    
        #endif
    }    
    
#endif

#if !defined(NO_MESSAGE)
    void printPressKeyToStart(void)
    {
        printCenteredMessage(PRESS_STRING);
    }    
#endif


void displayStats(void)
{    
    SET_COLOR(TEXT_COLOR);
    
    #if defined(WIDE) && !defined(TINY_GAME)
        PRINTD(6,+0,5,points);
    #else
        PRINTD(1,0,5,points);    
    #endif    
}

#if !defined(LESS_TEXT)    
    void printLevel(void)
    {
        PRINTD(((XSize -7)>>1), (YSize>>1), 2, level);
    }
#endif


#if !defined(TINY_GAME) && !defined(NO_MESSAGE)
    void _printScoreOnRow(uint8_t row, uint16_t score)
    {
        PRINTD((uint8_t) ((XSize)>>1)-2, row, 5, score);
    }    
    
    void _printScore(uint16_t score)
    {
        _printScoreOnRow((YSize>>1), score);
    }
#endif

#if !defined(END_SCREEN) && !defined(NO_MESSAGE)
    void gameCompleted(void)    
    {
        CLEAR_SCREEN();
        printCenteredMessage(YOU_MADE_IT_STRING); 
    }
#endif


#if !defined(LESS_TEXT)
    void printExtraLife(void)
    {
        printCenteredMessageWithCol(COLOR_RED, EXTRA_LIFE_STRING); 
    }

    void printVictoryMessage(void)
    {
        printCenteredMessageWithCol(COLOR_RED, VICTORY_STRING);
    }    
#endif


#if !defined(LESS_TEXT)    
    void printDefeatMessage(void)
    {            
        printCenteredMessageWithCol(COLOR_RED, DEFEAT_STRING);
    }    
#endif
    
    
#if !defined(NO_MESSAGE)
    void printGameOver(void)
    {
        printCenteredMessageWithCol(COLOR_RED, GAME_OVER_STRING);
    }    
#endif



#if (defined(FULL_GAME) && !defined(NO_HINTS)) || !defined(NO_INITIAL_SCREEN)
    #if defined(FULL_GAME) && !defined(NO_HINTS)
    void _printCrossShoot(void)
    {
        printCenteredMessageOnRowWithCol(3, COLOR_RED,  CROSS_SHOOT_STRING);        
        SET_COLOR(TEXT_COLOR);
        
    }
    #else
        #define _printCrossShoot() \
            printCenteredMessageOnRowWithCol(3, COLOR_RED,  CROSS_SHOOT_STRING);    \
            SET_COLOR(TEXT_COLOR);    
    #endif
#endif


#if defined(FULL_GAME) && !defined(NO_HINTS)
    void printHints(void)
    {
        _printCrossShoot();
        
        printCenteredMessageOnRow(6,  USE_THE_GUN_AGAINST_STRING);

        printCenteredMessageOnRow(8,  THE_SKULL_AND_STRING);

        printCenteredMessageOnRow(10, MISSILE_BASES_STRING);    
        
        printCenteredMessageOnRow(12, FOR_POINTS_AND___STRING);

        printCenteredMessageOnRow(14, EXTRA_POWERUPS__STRING);
    }
#endif

#if !defined(NO_INITIAL_SCREEN)
    void printStartMessage(void)
    {
        _printCrossShoot();
        
        printCenteredMessageOnRow(5, AUTHOR_STRING);    

        #if !defined(TINY_GAME) && !defined(NO_TITLE_INFO)
            _printTopScore();
            
            SET_COLOR(COLOR_CYAN);
            
            printCenteredMessageOnRow((YSize>>1)-1, LURE_THE_ENEMIES_STRING);
            printCenteredMessageOnRow((YSize>>1)+1, INTO_THE_MINES_STRING);
            
            SET_COLOR(TEXT_COLOR);    
            
        #endif

        #if !defined(NO_CONTROL_INSTRUCTIONS)
            printCenteredMessageOnRow(YSize-3, USE_STRING);
        #endif
    }
#endif



