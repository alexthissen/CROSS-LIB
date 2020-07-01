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

#include "character.h"
#include "item.h"
#include "ghost.h"
#include "game_text.h"
#include "level.h"
#include "game_text.h"

extern uint16_t points;

extern uint8_t guns;
extern uint8_t lives;

extern uint8_t level;

extern uint8_t freezeActive;
extern uint16_t freeze_count_down;

extern uint8_t bombCount;

extern uint8_t bulletStrength;

#if defined(FULL_GAME)
    extern uint8_t invincibilityActive;
    extern uint8_t confuseActive;
    extern uint8_t zombieActive;
    
    extern uint16_t invincibility_count_down;
    extern uint16_t confuse_count_down;
    extern uint16_t zombie_count_down;
    
    extern uint8_t missileBasesDestroyed;
    extern uint8_t skullsKilled;    
    
    extern uint8_t extraLife_present_on_level;
    extern uint8_t zombie_present_on_level;
#endif

extern Image DEAD_GHOST_IMAGE;

extern Character ghosts[GHOSTS_NUMBER];
extern Character bombs[BOMBS_NUMBER];
extern Character skull;

extern Character player;

extern Item powerUp;
extern Item bombCharge;
extern Item firePower;
extern Item extraPoints;

extern uint8_t ghostsOnScreen;


#if defined(FULL_GAME)
    extern Character *chasedEnemyPtr;

    extern Item freeze;

    extern Item invincibility;

    extern Item super;
    extern Item extraLife;

    extern Item confuse;
    extern Item zombie;
#endif
    
#if !defined(TINY_GAME)

    void itemReached(Character * itemPtr)
    {
        ZAP_SOUND();
        deletePowerUp(itemPtr);
        displayPlayer(&player);
        itemPtr->_status = 0;
        displayStats();
    }

    void relocateItem(Character * itemPtr)
    {
            itemPtr->_status = 1;
            
            #if defined(FULL_GAME)
            do
            {
                relocateCharacter(itemPtr);
            } while(nearInnerWall(itemPtr)||nearInnerHorizontalWall(itemPtr));        
            #else
                relocateCharacter(itemPtr);
            #endif    
    }    
    
    void _commonPowerUpEffect(void)
    {
        points+=POWER_UP_BONUS;
        decreaseGhostLevel();
        freezeActive = 1;    
        freeze_count_down += FROZEN_COUNT_DOWN;    
    }

    void _increaseBullets(uint8_t bullets)
    {
        uint8_t missing = MAX_GUNS - guns;
        
        if(missing>=bullets)
        {
            guns+=bullets;
        }
        else
        {
            guns=MAX_GUNS;
        }
        printGunsStats();
    }
    
    
    void powerUpEffect(void)
    {
        _increaseBullets(BULLET_GUNS);

        powerUp._coolDown = POWER_UP_COOL_DOWN;        
    }

    void bombChargeEffect(void)
    {
        uint8_t i;
        
        for(i=0;i<BOMBS_NUMBER;++i)
        {
            deleteBomb(&bombs[i]);
        }

        placeBombs();
        bombCount = 0;
        // TODO: delete Bombs
        bombCharge._coolDown = BOMB_CHARGE_COOL_DOWN;    
    }

    void _firePowerEffect(void)
    {
        ++bulletStrength;
        points+=FIRE_POWER_BONUS;        
    }

    void firePowerEffect(void)
    {
        _firePowerEffect();
        firePower._coolDown = FIRE_POWER_COOL_DOWN*2;    
    }

    void extraPointsEffect(void)
    {
        points+=EXTRA_POINTS+level*EXTRA_POINTS_LEVEL_INCREASE;
        extraPoints._coolDown = SECOND_EXTRA_POINTS_COOL_DOWN;//(EXTRA_POINTS_COOL_DOWN<<4); // second time is harder        
    }

    void handle_item(register Item *itemPtr)
    {
        // Manage item
        if(itemPtr->_character._status == 1)
        {    
            if(areCharctersAtSamePosition(&player, (Character *) itemPtr))
            {
                itemPtr->_effect();
                itemReached((Character *) itemPtr);            
            }
            else
            {
                _blink_draw(itemPtr->_character._x, itemPtr->_character._y, itemPtr->_character._imagePtr, &(itemPtr->_blink));
            }        
        }
        else if (itemPtr->_coolDown <= 0)
        {
            relocateItem((Character *) itemPtr);

            _blink_draw(itemPtr->_character._x, itemPtr->_character._y, itemPtr->_character._imagePtr, &(itemPtr->_blink));
        }
        else
        {
            --itemPtr->_coolDown;
        }
    }

    void handle_count_down(uint8_t * flagPtr, uint16_t * countDownPtr)
    {
        if(*flagPtr)
        {
            if(*countDownPtr<=0)
            {
                *flagPtr=0;
            }
            else
            {
                --(*countDownPtr);
            }
        }
    }    
    
#endif // !defined(TINY_GAME)

    
#if defined(FULL_GAME)
    void reducePowerUpsCoolDowns(void)
    {
        extraPoints._coolDown-=extraPoints._coolDown/8;
        invincibility._coolDown-=invincibility._coolDown/16;
        TICK_SOUND();        
    }
#elif !defined(TINY_GAME)
    void reducePowerUpsCoolDowns(void)
    {
        extraPoints._coolDown/=2;
        TICK_SOUND();        
    }
#else    
#endif    


    
#if defined(FULL_GAME)

    void _freezeEffect(void)
    {
        _commonPowerUpEffect();
    }

    void freezeEffect(void)
    {
        _freezeEffect();
        freeze._coolDown = ((uint16_t) (FREEZE_COOL_DOWN));    
    }
    
    
    void extraLifeEffect(void)
    {
        ++lives;
        skullsKilled=1;
        // missileBasesDestroyed = 0;
        extraLife_present_on_level = 0;
        // extraLife._coolDown = EXTRA_LIFE_COOL_DOWN*10; // second time must be impossible
        printLivesStats();        
    }

    void _invincibilityEffect(void)
    {
        invincibilityActive = 1;
        invincibility_count_down = INVINCIBILITY_COUNT_DOWN;            
    }
    
    void invincibilityEffect(void)
    {
        _invincibilityEffect();
        invincibility._coolDown = ((uint16_t) (INVINCIBILITY_COOL_DOWN)*4);
    }
    
    void superEffect(void)
    {
        _freezeEffect();
        _firePowerEffect();
        _invincibilityEffect();
        super._coolDown = ((uint16_t) (SUPER_COOL_DOWN)*8);
    }

    void confuseEffect(void)
    {
        confuseActive = 1;
        confuse._coolDown = SECOND_CONFUSE_COOL_DOWN; //20000UL;//(CONFUSE_COOL_DOWN<<4);
        confuse_count_down = CONFUSE_COUNT_DOWN;
    }
    
    void zombieEffect(void)
    {
        uint8_t i;
        
        zombieActive = 1;
        missileBasesDestroyed = 1;
        zombie._coolDown = SECOND_ZOMBIE_COOL_DOWN; 
        zombie_count_down = ZOMBIE_COUNT_DOWN;
        for(i=0;i<ghostsOnScreen;++i)
        {
            if(ghosts[i]._status)
            {
                deleteGhost(&ghosts[i]);
                ghostDies(&ghosts[i]);
                points+=GHOSTS_VS_ZOMBIE_BONUS;
            }
        }
    }

#endif
