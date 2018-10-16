#include "../display_macros.h"

#include "../graphics_mode/memory_mapped_graphics.h"

#if defined(ALT_DISPLAY_STATS) || defined(ALT_HISCORE)

	#if !defined(CC65)
		#define POKE(addr,val)     (*(unsigned char*) (addr) = (val))
		#define POKEW(addr,val)    (*(unsigned*) (addr) = (val))
		#define PEEK(addr)         (*(unsigned char*) (addr))
		#define PEEKW(addr) (*(unsigned*) (addr))
	#else
		#include <peekpoke.h>	
	#endif

	#if  defined(__VIC20__) && defined(VIC20_UNEXPANDED) && defined(REDEFINED_CHARS)
		char screenCode(char ch)
		{
			if(ch==32)
			{
				return (32+128);
			}
			else
			{
				return 64+ch;
			}	
		}
	#endif
	
	void _displayShort(unsigned short value)
	{ 
		unsigned char i; 

		for(i=1;i<6;++i) 
		{ 
			value -= POKE(BASE_ADDR+6-i,(unsigned char) ((value)%10)); 
			value/=10; 
			POKE(BASE_ADDR+6-i,PEEK(BASE_ADDR+6-i)+48); 
		} 
		POKE(BASE_ADDR+6,48); 	
	}

	void PRINT(unsigned char x, unsigned char y, char * str)
	{
		unsigned char i = 0;
		while(str[i]!='\0')
		{
			#if defined(CBM_SCREEN_CODES) || (defined(__CMOC__) && !defined(__WINCMOC__))
			POKE(loc(x+i,y), screenCode(str[i])); 		
			#elif defined(__VIC20__) && defined(VIC20_UNEXPANDED) && defined(REDEFINED_CHARS)
			POKE(loc(x+i,y), screenCode(str[i])); 
			#else
			POKE(loc(x+i,y), str[i]); 
			#endif
			++i;
		}
	}	
#endif
