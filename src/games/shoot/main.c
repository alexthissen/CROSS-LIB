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

#if defined(__CMOC__) && !defined(__WINCMOC__)
    #include <cmoc.h>
#else
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
#endif

#if !defined EXIT_SUCCESS
    #define EXIT_SUCCESS 0
#endif

// TODO: REMOVE THIS
// #define DEBUG_STRATEGY
// #define DEBUG_ITEMS
// #define DEBUG_END


#include "settings.h"

#include "character.h"
#include "item.h"
#include "strategy.h"
#include "game_text.h"
#include "level.h"
#include "ghost.h"
#include "move_player.h"

#include "text_strings.h"

#include "init_images.h"

#include "display_macros.h"

#include "speed_game_settings.h"

#include "sleep_macros.h"

#include "bullet.h"
#include "skull.h"
    
#include "end_screen.h"

#include "horizontal_missile.h"
#include "rocket.h"

#include "variables.h"

uint8_t skullsCount;

uint8_t bulletStrength;

uint8_t bombCount;

uint8_t reachedByGhost;
    
Character bullets[BULLETS_NUMBER];

Character skulls[SKULLS_NUMBER];


uint8_t innerHorizontalWallY; 
uint8_t innerHorizontalWallX; 
uint8_t innerHorizontalWallLength;

uint8_t ghostsOnScreen;

uint8_t firePowerItemSecret;
uint8_t firePowerLevelSecret;

uint8_t fireChargeSecret;
uint8_t calmDownSecret;
uint8_t extraPointsSecret;
uint8_t freezeSecret;

uint8_t discoveredSecrets[SECRETS_NUMBER];

#define handle_secret_item_at_start_up(secretFlag, item, secretIndex) \
    if(secretFlag) \
    { \
        item._coolDown = 2; \
        setSecret(secretIndex); \
        secretFlag = 0; \
    }\


void resetSecrets(void)
{
    uint8_t i;
    
    for(i=0;i<SECRETS_NUMBER;++i)
    {
        discoveredSecrets[i]=0;
    }
}


void resetItems()
{

    calmDown._coolDown = CALM_DOWN_COOL_DOWN;
    firePower._coolDown = FIRE_POWER_COOL_DOWN;
    fireCharge._coolDown = FIRE_CHARGE_COOL_DOWN;
    freeze._coolDown = FREEZE_COOL_DOWN;
    bombCharge._coolDown = BOMB_CHARGE_COOL_DOWN;
    
    extraPoints._coolDown = EXTRA_POINTS_COOL_DOWN;
    invincibility._coolDown = INVINCIBILITY_COOL_DOWN;

    handle_secret_item_at_start_up(calmDownSecret, calmDown, CALM_DOWN_AT_START_SECRET_INDEX);
    handle_secret_item_at_start_up(extraPointsSecret, extraPoints, EXTRA_POINTS_AT_START_SECRET_INDEX);
    handle_secret_item_at_start_up(freezeSecret, freeze, FREEZE_AT_START_SECRET_INDEX);

    handle_secret_item_at_start_up(firePowerItemSecret, firePower, FIRE_POWER_AT_START_SECRET_INDEX);

    super._coolDown = SUPER_COOL_DOWN;
    extraLife._coolDown = EXTRA_LIFE_COOL_DOWN;
    
    confuse._coolDown = CONFUSE_COOL_DOWN;
    suicide._coolDown = SUICIDE_COOL_DOWN;                
    destroyer._coolDown = DESTROYER_COOL_DOWN;
}


// Constructor for all items
void constructItems()
{
    calmDown._effect = &calmDownEffect;
    fireCharge._effect = &fireChargeEffect;
    bombCharge._effect = &bombChargeEffect;
    firePower._effect = &firePowerEffect;
    extraPoints._effect = &extraPointsEffect;
    freeze._effect = &freezeEffect;
    extraLife._effect = &extraLifeEffect;
    invincibility._effect = &invincibilityEffect;
    super._effect = &superEffect;
    confuse._effect = &confuseEffect;
    suicide._effect = &suicideEffect;
    destroyer._effect = &destroyerEffect;
}    


#if !defined(NO_INITIAL_SCREEN)            
void initialScreen(void)
{    
    CLEAR_SCREEN();                    
    printStartMessage();
    WAIT_PRESS();
    
    #if !defined(NO_HINTS)
        CLEAR_SCREEN();
        printHints();    
    #endif
}
#endif


void handle_special_triggers(void)
{
    // confuse_present_on_level_condition is defined as destroyed_bases_in_completed_levels
    suicide_present_on_level = destroyed_bases_in_completed_levels>=2;
    super_present_on_level = all_skulls_killed_in_completed_levels>=2;
    extraLife_present_on_level = super_present_on_level && suicide_present_on_level;
}


int main(void)
{        
    INIT_GRAPHICS();

    INIT_INPUT();

    highScore = 0;
    
    while(1)
    {

        INIT_IMAGES();
        
        #if !defined(NO_SET_SCREEN_COLORS)
            // Set Screen Colors
            setScreenColors();                
        #endif
        
        #if !defined(NO_INITIAL_SCREEN)
            initialScreen();
            
            WAIT_PRESS();
            CLEAR_SCREEN();    
        #else
            CLEAR_SCREEN();    
            
            printPressKeyToStart();                
        #endif

        
        extraLifeThroughPointsCounter = 1;
        points = 0;
        level = INITIAL_LEVEL;     
        lives = LIVES_NUMBER;
        
        ghostCount = GHOSTS_NUMBER; 
         
        
        destroyed_bases_in_completed_levels = 0;
        all_skulls_killed_in_completed_levels = 0;
        
        firePowerItemSecret = 0;
        calmDownSecret = 0;
        extraPointsSecret = 0;
        freezeSecret = 0;
        fireChargeSecret = 0;
        
        resetSecrets();
        
        do // Level (Re-)Start
        {
            isBossLevel = bossLevel();
            isRocketLevel = rocketLevel();
            isOneMissileLevel = oneMissileLevel();
            isMissileLevel = missileLevel();
            isInnerHorizontalWallLevel = innerHorizontalWallLevel();
            isInnerVerticalWallLevel = innerVerticalWallLevel();
            
            #if defined(DEBUG_STRATEGY)
            ghostsOnScreen = 1;
            #else
            if(isBossLevel)
            {
                ghostsOnScreen = BOSS_LEVEL_GHOSTS_NUMBER;
            }
            else if(isMissileLevel && isRocketLevel)
            {
                ghostsOnScreen = GHOSTS_NUMBER-3;
            }
            else if(isMissileLevel || isRocketLevel)
            {
                ghostsOnScreen = GHOSTS_NUMBER-2;
            }
            else
            {
                ghostsOnScreen = GHOSTS_NUMBER;
            }
            #endif
            
            skullsCount = SKULLS_NUMBER;
            
            bombCount = BOMBS_NUMBER;
            
            loop = 0;
            
            ghostLevel = 0;
        
            
            destroyed_bases = 0;
            exploded_bombs = 0;
            
            invincibilityActive = 1;                
            invincibility_count_down = INITIAL_INVINCIBILITY_COUNT_DOWN;
            
            destroyerActive = 0;
            missileDestroyerActivated = 0;
            bombDestroyerActivated = 0;
            
            #if !defined(INITIAL_GHOST_FREEZE)
                freezeActive = 0;
            #endif
            confuseActive = 0;
            suicideActive = 0; 

            #if defined(DEBUG_ITEMS)
                destroyed_bases_in_completed_levels = 2;
                all_skulls_killed_in_completed_levels = 2;
            #endif

            handle_special_triggers();

            #if !defined(SIMPLE_STRATEGY)
                computeStrategy();            
            #endif
                            
            
            skullActive = 0;
            
            if(fireChargeSecret)
            {
                guns = SECRET_GUNS;
                setSecret(FIRE_CHARGE_AT_START_SECRET_INDEX);
                fireChargeSecret = 0;
            }
            else
            {
                guns = 0;
            }
            
            #if defined(INITIAL_GHOST_FREEZE)
                freezeActive = 1;
                freeze_count_down = INITIAL_FROZEN_COUNT_DOWN;
            #endif
            
            computeSkullParameters();                
            
            levelSlowDown = INITIAL_GHOST_SLOWDOWN;
            ghostSlowDown = computeGhostSlowDown();
            
            CLEAR_SCREEN();
            #if !defined(LESS_TEXT)
                // Clear the screen, put cursor in upper left corner

                printLevel();
                SLEEP(1);
                CLEAR_SCREEN();
            #endif
                
            
                        
            arrowRange = computeArrowRange();
            
            if(firePowerLevelSecret)
            {
                bulletStrength = firePowerLevelSecret;
                setSecret(FIRE_POWER_LEVEL_SECRET_INDEX);
                firePowerLevelSecret = 0;
            }
            else
            {
                bulletStrength = 2;
            }
        
            if(isBossLevel)
            {
                printKillTheSkull();
                SLEEP(2);
                ghostCount = 0;
            }
            CLEAR_SCREEN();
            
            updateInnerVerticalWall();    
            
            updateInnerHorizontalWall();                
            
            printPressKeyToStart();
            WAIT_PRESS();
            CLEAR_SCREEN();
            
            
            #if !defined(NO_BORDERS)
                DRAW_BORDERS();
            #endif
            
            fillLevelWithCharacters();            
            
            constructItems();    
            
            displayStatsTitles();

            
            displayStats();
            
            resetItems();
            while(player._status && (( ((ghostCount>0)&&(skullsCount)) && !isBossLevel) || (skullsCount && isBossLevel))) // while alive && there are still ghosts
            {                
                #if defined(DEBUG_END)
                    gameCompleted();
                #endif
                    
                #if !defined(TURN_BASED)
                    MOVE_PLAYER();                
                    _DRAW_PLAYER();    
                #endif
                        
                handle_rockets();
                handle_horizontal_missiles();
                
                ++loop;
                
                if(points>(extraLifeThroughPointsCounter*EXTRA_LIFE_THROUGH_POINTS))
                {
                    ++extraLifeThroughPointsCounter;
                    PING_SOUND();
                    ++lives;
                    printLivesStats();
                }
                

                handle_bullets();
                handle_bomb();
                

                if(!freezeActive)
                {
                    if(ghostCount)
                    {
                        chaseCharacter();
                    }
                    ++ghostLevel;            
                    
                }
                #if !defined(DEBUG_STRATEGY)
                handle_skulls();
                #endif
            
                // This detects collisions of ghosts that have just moved
                checkBullets();

                
                // Check collisions bombs vs ghosts
                checkBombsVsGhosts();
                if(skullActive)
                {
                    checkBombsVsSkulls();
                }
                
                #if SLOW_DOWN>0
                if(freezeActive)
                {
                        DO_SLOW_DOWN(SLOW_DOWN);
                }
                #endif
                
                #if SLOW_DOWN>0
                if(invincibilityActive)
                {
                        DO_SLOW_DOWN(SLOW_DOWN);
                }
                #endif
                
                #if SLOW_DOWN>0
                if(!skullActive)
                {
                        DO_SLOW_DOWN(SLOW_DOWN);
                }
                #endif
                
                #if SLOW_DOWN>0
                if(ghostCount < GHOST_SLOW_DOWN_THRESHOLD) 
                {
                        DO_SLOW_DOWN(SLOW_DOWN);
                }
                #endif
                
                handle_calmDown_item();
                handle_extraPoints_item();
                handle_firePower_item();
                handle_fireCharge_item();
                handle_bombCharge_item();    
                
                handle_freeze_count_down();                    
                
                handle_freeze_item();    
                handle_invincibility_item();
                handle_invincibility_count_down();                    

                handle_destroyer_triggers();
                handle_destroyer_item();
                handle_destroyer_count_down();
                    
                if(super_present_on_level)
                {
                    handle_super_item();
                    if(extraLife_present_on_level)
                    {
                        handle_extraLife_item();
                    }
                }
                
                                    
                if(confuse_present_on_level_condition)
                {
                    handle_confuse_item();
                    handle_confuse_count_down();
                    if(suicide_present_on_level)
                    {
                        handle_suicide_item();
                        handle_suicide_count_down();    
                        if(suicideActive && !(loop&15))
                        {
                            points+=SUICIDE_BONUS;
                            displayScoreStats();
                            reduceItemCoolDowns();
                        }
                    }
                }
                
                reachedByGhost = sameLocationAsAnyGhostLocation(player._x, player._y, ghosts, ghostsOnScreen);
                
                if(destroyerActive && reachedByGhost < ghostsOnScreen)
                {
                    ghostDiesAndSpawns(&ghosts[reachedByGhost]);
                    points += GHOST_VS_BOMBS_BONUS;
                }
                
                
                if(wallReached(&player) || 
                   (!invincibilityActive && ((reachedByGhost<ghostsOnScreen) || innerVerticalWallReached(&player) || innerHorizontalWallReached(&player)))
                  )
                {
                    playerDies();
                }
                
                // Display ghosts
                SKIP_GHOST_DRAW
                    displayGhosts();
                    
                #if defined(TURN_BASED) 
                    if((loop<TURN_BASED_MAX_LOOP) || loop&1)
                    {
                        MOVE_PLAYER();
                    }                    
                    _DRAW_PLAYER();    
                #endif
                
                    
                SKIP_WALL_DRAW
                {
                    ghostSlowDown = computeGhostSlowDown();
                    
                    if(isInnerVerticalWallLevel)
                    {
                        DRAW_VERTICAL_LINE(XSize/2, YSize/2-(innerVerticalWallLength/2), innerVerticalWallLength);
                    }
                    else if(isInnerHorizontalWallLevel)
                    {
                        DRAW_HORIZONTAL_LINE(XSize/2-(innerHorizontalWallLength/2), YSize/2, innerHorizontalWallLength);                                
                    }
                    displayBombs();                                                        
                }
                    
            }; // end inner while [while (player._alive && ghostCount>0), i.e., exit on death or end of level]

            _DRAW_PLAYER();
            if(player._status) // if level finished
            {
                #if defined(BETWEEN_LEVEL)
                    chasedEnemyPtr = &player;
                    SHOW_DOWN();
                #endif
                
                #if !defined(LESS_TEXT)
                    SLEEP(1);
                    printVictoryMessage();
                    SLEEP(2);

                    CLEAR_SCREEN();
                #endif

                points+= LEVEL_BONUS*level+ghostCount*GHOSTS_VS_SUICIDE_BONUS;
                printLevelBonus(LEVEL_BONUS*level+ghostCount*GHOSTS_VS_SUICIDE_BONUS);

                if(ghostCount>=CALM_DOWN_SECRET_THRESHOLD)
                {
                    calmDownSecret = 1;
                    if(ghostCount>=EXTRA_POINTS_SECRET_THRESHOLD)
                    {
                        extraPointsSecret = 1;
                        if(ghostCount>=FREEZE_SECRET_THRESHOLD)
                        {
                            freezeSecret = 1;
                        }
                    }
                }

                SLEEP(2);
                CLEAR_SCREEN();                        

                
                if(isBossLevel)
                {    
                    CLEAR_SCREEN();
                    SLEEP(1);
                    PING_SOUND();
                    #if !defined(LESS_TEXT)
                        printExtraLife();
                    #endif
                    SLEEP(2);
                    ++lives;
                    all_skulls_killed_in_completed_levels = 1;
                    destroyed_bases_in_completed_levels/=2;
                }
                else
                {
                    if(!skullsCount)
                    {
                        ++all_skulls_killed_in_completed_levels;
                    }
                    destroyed_bases_in_completed_levels+=destroyed_bases;
                }
                ++level;
                ghostCount = GHOSTS_NUMBER + 2*level;

            }
            else // if dead
            {        
                #if defined(BETWEEN_LEVEL)
                    chasedEnemyPtr = &skulls[0];    
                #endif
                
                CLEAR_SCREEN();
                --lives;
                if(lives>0)
                {
                    player._status = 1;
                }
                firePowerItemSecret = 0;
                calmDownSecret = 0;
                extraPointsSecret = 0;
                freezeSecret = 0;
                fireChargeSecret = 0;
            }
            #if defined(BETWEEN_LEVEL)
                spiral(chasedEnemyPtr, 2*MIN_SIZE-18);
                SLEEP(1);
            #endif
            
        } while (player._status && (level<(FINAL_LEVEL+1))); // lives left and not completed game game 
            
        if(level==FINAL_LEVEL+1) // if completed game
        {
            gameCompleted();
            #if !defined(NO_SLEEP)
                SLEEP(1);
            #else
                WAIT_PRESS();
            #endif
        }

        // GAME OVER    
        CLEAR_SCREEN();
        printAchievements();
        SLEEP(1);
        WAIT_PRESS();
        CLEAR_SCREEN();
        printGameOver();
        
        #if !defined(NO_SLEEP)
            SLEEP(1);
        #else
            WAIT_PRESS();
        #endif
        
        if(points>highScore)
        {
            highScore = points;
        }
        
    } // while(1) -> restart from the beginning

    return EXIT_SUCCESS;
}
