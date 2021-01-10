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

#ifndef _TEXT_STRINGS_H
#define _TEXT_STRINGS_H


#if defined(ONLY_SMALL_LETTERS)
    #if defined(TINY_TEXT)
        #define CROSS_SHOOT_STRING "cross" _XL_SPACE "shoot"
        #define CROSS_SHOOT_SHORT_STRING CROSS_SHOOT_STRING
        #define AUTHOR_STRING "fabrizio" _XL_SPACE "caruso"
    #else
        #define CROSS_SHOOT_STRING \
            "c" _XL_SPACE "r" _XL_SPACE "o" _XL_SPACE "s" _XL_SPACE "s" _XL_SPACE _XL_SPACE "s" _XL_SPACE "h" _XL_SPACE "o" _XL_SPACE "o" _XL_SPACE "t"
        #define CROSS_SHOOT_SHORT_STRING "cross" _XL_SPACE "shoot"
        #define AUTHOR_STRING "by" _XL_SPACE "fabrizio" _XL_SPACE "caruso"
    #endif
    #define KILL_THE_SKULLS_STRING "kill" _XL_SPACE "the" _XL_SPACE "skulls"
    #define KILL_THE_BOSS "kill" _XL_SPACE "the" _XL_SPACE "boss"
    #define DESTROY_MISSILES_STRING "destroy" _XL_SPACE "the" _XL_SPACE "missiles"
    #define LURE_THE_ENEMIES_STRING "kill" _XL_SPACE "all" _XL_SPACE "enemies"
    #define INTO_THE_MINES_STRING ""
    #define SCORE_STRING "score" _XL_SPACE
    #define LEVEL_STRING "level"
    #define GAME_COMPLETED_STRING "game" _XL_SPACE "completed"
    #define SECRET_LEVEL_FOUND_STRING "secret" _XL_SPACE "level" _XL_SPACE "found"
    #define SECRET_FOUND_STRING "secret" _XL_SPACE "found"
    #define EMPTY_STRING        _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE _XL_SPACE
    #define START_LEVEL_STRING "level"
    #define USE_THE_GUN_AGAINST_STRING "shoot" _XL_SPACE "at"
    #define THE_SKULL_AND_STRING "the" _XL_SPACE "skulls" _XL_SPACE "and"
    #define MISSILE_BASES_STRING "missile" _XL_SPACE "bases"
    #define FOR_POINTS_AND___STRING "for" _XL_SPACE "points"
    #define EXTRA_POWERUPS__STRING "and" _XL_SPACE "items"
#elif defined(__PC6001__)
    #define CROSS_SHOOT_STRING "C R O S S  S H O O T"        
    #define CROSS_SHOOT_SHORT_STRING "CROSS SHOOT"
    #define AUTHOR_STRING "BY FABRIZIO CARUSO"
    #define KILL_THE_SKULLS_STRING "KILL THE SKULLS"    
    #define KILL_THE_BOSS "KILL THE BOSS"
    #define DESTROY_MISSILES_STRING "DESTROY THE MISSILES"    
    #define LURE_THE_ENEMIES_STRING "KILL ALL ENEMIES"
    #define INTO_THE_MINES_STRING     ""
    #define SCORE_STRING "SCORE "
    #define LEVEL_STRING "LEVEL"
    #define GAME_COMPLETED_STRING "GAME COMPLETED"
    #define SECRET_LEVEL_FOUND_STRING "SECRET LEVEL FOUND"
    #define SECRET_FOUND_STRING "SECRET FOUND"
    #define EMPTY_STRING        "            "
    #define START_LEVEL_STRING "LEVEL %u"
    #define USE_THE_GUN_AGAINST_STRING "SHOOT AT"
    #define THE_SKULL_AND_STRING "THE SKULLS AND"
    #define MISSILE_BASES_STRING "MISSILE BASES"
    #define FOR_POINTS_AND___STRING "FOR POINTS"
    #define EXTRA_POWERUPS__STRING  "AND ITEMS"    
#else
    #if defined(TINY_TEXT)
        #define CROSS_SHOOT_STRING "CROSS SHOOT"
        #define CROSS_SHOOT_SHORT_STRING CROSS_SHOOT_STRING
        #define AUTHOR_STRING "Fabrizio Caruso"
    #else
        #define CROSS_SHOOT_STRING "C R O S S  S H O O T"        
        #define CROSS_SHOOT_SHORT_STRING "CROSS SHOOT"
        #define AUTHOR_STRING "by Fabrizio Caruso"
    #endif
    #define KILL_THE_SKULLS_STRING "Kill the skulls"
    #define KILL_THE_BOSS "Kill the boss"
    #define DESTROY_MISSILES_STRING "Destroy the missiles"    
    #define LURE_THE_ENEMIES_STRING "Kill all enemies"
    #define INTO_THE_MINES_STRING ""
    #define SCORE_STRING "SCORE "
    #define LEVEL_STRING "LEVEL"    
    #define GAME_COMPLETED_STRING "GAME COMPLETED"
    #define SECRET_LEVEL_FOUND_STRING "SECRET LEVEL FOUND"
    #define SECRET_FOUND_STRING "SECRET FOUND"
    #define EMPTY_STRING        "            "
    #define START_LEVEL_STRING "LEVEL"    
    #define USE_THE_GUN_AGAINST_STRING "Shoot at"
    #define THE_SKULL_AND_STRING "the skulls and"
    #define MISSILE_BASES_STRING "missile bases"
    #define FOR_POINTS_AND___STRING "for points"
    #define EXTRA_POWERUPS__STRING "and items"    
#endif

#if defined(JOYSTICK_CONTROL) || defined(__MSX__) || defined(__CPC_JOYSTICK__)
    #define USE_STRING "use" _XL_SPACE "the" _XL_SPACE "joystick"
#elif !defined(TINY_TEXT)        
    #if !defined(__PC6001__)
        #define USE_STRING "use i j k l space"
    #else
        #define USE_STRING "USE I J K L SPACE"
    #endif
#else
    #if !defined(__PC6001__)
        #define USE_STRING "use ijkl"        
    #else
        #define USE_STRING "USE IJKL"
    #endif            
#endif    

#if defined(LESS_TEXT)
    #if defined(ONLY_SMALL_LETTERS)
        #define PRESS_STRING "go"
        #define DISCOVERED_SECRETS_STRING "secrets"
        #define OF_STRING "of " 
        #define GAME_OVER_STRING "game over"
        #define YOU_MADE_IT_STRING "the end"
    #else
        #define PRESS_STRING "GO"    
        #define DISCOVERED_SECRETS_STRING "SECRETS"
        #define OF_STRING "OF " 
        #define GAME_OVER_STRING "GAME OVER"
        #define YOU_MADE_IT_STRING "THE END"
    #endif
#else
    #if defined(ONLY_SMALL_LETTERS)
        #if defined(JOYSTICK_CONTROL) || defined(__MSX__)
            #define PRESS_STRING "press" _XL_SPACE "fire"
        #else
            #define PRESS_STRING "press a key"
        #endif
        #define DISCOVERED_SECRETS_STRING "secrets"
        #define OF_STRING "of" _XL_SPACE 
        #define GAME_OVER_STRING "game" _XL_SPACE "over"
        #define DEFEAT_STRING "you" _XL_SPACE "lost"
        #define VICTORY_STRING "you" _XL_SPACE "won"
        #define EXTRA_LIFE_STRING "extra" _XL_SPACE "life"
        #define YOU_MADE_IT_STRING "you" _XL_SPACE "made" _XL_SPACE "it"
    #else
        #if defined(JOYSTICK_CONTROL) || defined(__MSX__)
            #define PRESS_STRING "PRESS FIRE"
        #else
            #define PRESS_STRING "PRESS A KEY"
        #endif
        #define DISCOVERED_SECRETS_STRING "SECRETS"
        #define OF_STRING "OF " 
        #define GAME_OVER_STRING "GAME OVER"
        #define DEFEAT_STRING "YOU LOST"    
        #define VICTORY_STRING "YOU WON"
        #define EXTRA_LIFE_STRING "EXTRA LIFE"
        #define YOU_MADE_IT_STRING "YOU MADE IT"    
    #endif
#endif

#if defined(ONLY_SMALL_LETTERS)
    #define BONUS_STRING "bonus "
    #define SCORE_STRING "score" _XL_SPACE
    #define HIGH_SCORE_STRING "hiscore" _XL_SPACE
#else
    #define BONUS_STRING "BONUS "
    #define SCORE_STRING "SCORE "
    #define HIGH_SCORE_STRING "HISCORE "
#endif

#define BONUS_DIGITS "%u0"
#define SCORE_DIGITS "%05u0"

#endif // _TEXT_STRINGS_H

