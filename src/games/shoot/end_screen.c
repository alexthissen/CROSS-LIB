
#include "settings.h"

#include "end_screen.h"
#include "game_text.h"
#include "text_strings.h"
#include "move_player.h"

#if defined(END_SCREEN)
	#include "strategy.h"
	#include "level.h"
	#include "character.h"
	#include "ghost.h"
	
	extern Character player;
	extern Character skulls[];
	extern Character ghosts[GHOSTS_NUMBER];
	extern Character bullet;
	extern uint8_t playerFire;
	extern uint8_t level;
	extern uint8_t guns;
	extern uint8_t ind;
    
    extern uint8_t ghostsOnScreen;
#endif



#if defined(END_SCREEN) || defined(DANCE)
	extern uint8_t bulletDirection;

	void dance(Character * characterPtr)
	{
		deleteCharacter(characterPtr);
		if(!(bulletDirection&3))
		{
			++(characterPtr->_x);
		}
		else if((bulletDirection&3)==1)
		{
			++(characterPtr->_y);			
		}
		else if ((bulletDirection&3)==2)
		{
			--(characterPtr->_x);			
		}
		else
		{
			--(characterPtr->_y);			
		}
		displayCharacter(characterPtr);	
	}

#endif

#if YSize < 20
	#define MESSAGE_START 3
	#define MESSAGE_RANGE 7
#else
	#define MESSAGE_START 7
	#define MESSAGE_RANGE 15
#endif

#if defined(END_SCREEN) && !defined(NO_MESSAGE)
	void gameCompleted(void)
	{
		level = 1;
		
		CLEAR_SCREEN();
        ghostCount = 8;
        ghostsOnScreen = 8;
		fillLevelWithCharacters();

		playerFire = 0;
		skulls[0]._x = player._x-4;
		skulls[0]._y = player._y;	
		bullet._status = 0;
		guns = 1;
		while(!playerFire && !wallReached(&player))
		{
			++bulletDirection;
			displayBombs();
			for(ind=0;ind<ghostsOnScreen;++ind)
			{
				dance(&ghosts[ind]);
			}
			
			displayPlayer(&player);
			
			dance(&skulls[0]);
		
			printCenteredMessageOnRow(MESSAGE_START,  YOU_MADE_IT_STRING);		
			#if SLOW_DOWN>0
				for(ind=0;ind<254;++ind){};
			#endif
					
			MOVE_PLAYER();
		}
	}
#endif


