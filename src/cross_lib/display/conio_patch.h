
#if defined(FORCE_NO_CONIO_LIB) && defined(C16_UNEXPANDED)
	#include<peekpoke.h>
	#define textcolor(c) POKE(0x053B,c)
	#define bgcolor(c)
	#define bordercolor(c)
#endif

#if defined(Z88DK)
	#define cprintf printf
#endif

#if defined(Z88DK) && !defined(__SMS__) && !defined(Z88DK_PUTC4X6) && !defined(__ZX80__) && !defined(__ZX81__) && !defined(__LAMBDA__)
	#define cputc(c) fputc_cons(c)	
#endif


#if defined(__SMS__)
	#include <stdio.h>
	#include <stropts.h>
	#include <arch/sms.h>
	#include <rect.h>
	#include <input.h>
	#include <arch/sms/SMSlib.h>
	#include <arch/sms/PSGlib.h>

	#define gotoxy(x,y) \
		SMS_setNextTileatXY(x,y)
		
	#define cputc(c) \
		SMS_setTile(c)

#endif

// TODO: BOGUS! Implement this
#if defined(__MZ2500__)
	#define gotoxy(x,y)
		
	#define clrscr() printf("--------------------\n");
#endif

#  if defined(CONIO_ADM3A)
	#define gotoxy(x,y) printf("\033=%c%c",y+32,x+32);
	#define clrscr() printf("\032")

#elif defined(CONIO_ADM3A_WITH_UNDEF)
	// TODO: Remove undef's below
	#undef gotoxy
	#undef clrscr 
	#define gotoxy(x,y) printf("\033=%c%c",y+32,x+32);
	#define clrscr() printf("\032")	
#elif defined(CONIO_VT52)
	#undef gotoxy
	#define gotoxy(x,y) printf("\033Y%c%c",y+32,x+32)

	#undef clrscr
	#define clrscr() printf("\033E")

#elif defined(CONIO_VT100)
	#include <stdio.h>

	#define gotoxy(x,y) printf("\033[%d;%dH", y+1, x+1)
	#define clrscr() printf("\033[H\033[2J")
	
#elif defined(Z88DK_PUTC4X6)
	#include <stdio.h>
	#include <graphics.h>
	#include <games.h>

	extern int _LIB_putc4x6(char c);
	extern unsigned char x_4x6;
	extern unsigned char y_4x6;

	#undef gotoxy
	#define gotoxy(x,y) do \
		{ \
			x_4x6 = (x)*4; \
			y_4x6 = (y)*6; \
		\
		} while(0)
		
	#undef clrscr
	#define clrscr() clg();

	#define cprintf printf
			
	#define cputc(c) putc4x6(c)
	
#elif defined(__ATARI_LYNX__)
	#include <tgi.h>
	#include <stdio.h>
	#include <lynx.h>
	
	#define gotoxy(a,b) tgi_gotoxy(a*8,b*8)
	#define clrscr() tgi_clear()
	#define cprintf(str) tgi_outtext(str)
	#define cputc(c) 
	#define textcolor tgi_setcolor

#elif defined(__SUPERVISION__)
	#include <stdio.h>
	
	#define gotoxy(a,b) 
	#define clrscr() 
	#define cprintf 
	#define cputc(c) 	
	#define textcolor
	
#elif defined(__ZX81__) || defined(__ZX80__) || defined(__LAMBDA__)
	#undef gotoxy
	
	#if defined(__ZX80__) && defined(ZX80_GEN_TV_FIELD)
		#define gotoxy(x,y) do {gen_tv_field(); zx_setcursorpos(y,x); gen_tv_field();} while(0)
		#define cputc(c) do { gen_tv_field(); fputc_cons(c); gen_tv_field(); } while(0)
	#else
		#define gotoxy(x,y) zx_setcursorpos(y,x)
		#define cputc(c) fputc_cons(c)
	#endif
	

 
#elif defined(__MSX__) || (defined(__SVI__) && defined(MSX_MODE0))
	#define gotoxy(a,b)     printf("\033Y%c%c",b+31+1,a+31)
	#define clrscr() printf("\033E") 


#elif defined(__KC__)
	#include <stdio.h>
	
	#define gotoxy(x,y) do \
		{ \
		printf("\1B%c%c",y+0x80, x+0x80); \
		\
		} while(0)
		
	#define clrscr() printf("\0C");

	#define cprintf printf

#elif defined(__CMOC__) && !defined(__WINCMOC__) && !defined(__MO5__) && !defined(__TO7__)

	#define cprintf printf
	#define gotoxy(x,y) locate(y,x)
	#define cputc(c) printf("%c",c)

#elif defined(__MO5__) || defined(__TO7__)
	void SWITCH_COLOR_BANK_OFF(void);
	void SWITCH_COLOR_BANK_ON(void);
	
	void PUTCH(unsigned char ch);
	
	#define POKE(addr,val)     (*(unsigned char*) (addr) = (val))
	
	#define cputc(c) \
		PUTCH(c)	

	void gotoxy(unsigned char x, unsigned char y);
			
		
#elif defined(__NCURSES__)
	#include <ncurses.h>
	
	#define gotoxy(x,y) do { move(y,x); refresh(); } while(0)
	#define cputc(c) do { addch(c); refresh(); } while(0)

#else
	//
#endif

#if !defined(NO_COLOR)
	#ifndef COLOR_BLACK
		#if defined(Z88DK)
			#define COLOR_BLUE BLUE
			#define COLOR_BLACK BLACK
			#if defined(__PC6001__)
				#define COLOR_WHITE 7
			#else
				#define COLOR_WHITE WHITE
			#endif
		#endif
	#endif
	
	#ifndef COLOR_RED
		#define COLOR_GREEN GREEN
		#define COLOR_CYAN CYAN
		#define COLOR_MAGENTA MAGENTA
		#define COLOR_RED RED
		#define COLOR_YELLOW YELLOW		
	#endif	
#else
	#if !defined(CONIO_LIB)
		#define textcolor 
	#endif
#endif


