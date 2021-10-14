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


#if !defined EXIT_SUCCESS
    #define EXIT_SUCCESS 0
#endif

#include "cross_lib.h"

#include "images.h"

#if YSize>=17
    #define LINE_SKIP 2
#else
    #define LINE_SKIP 1
#endif

int main(void)
{        
    _XL_INIT_GRAPHICS();
    
    _XL_INIT_SOUND();

    _XL_INIT_INPUT();

    _XL_CLEAR_SCREEN();
    
    _XL_SET_TEXT_COLOR(_XL_WHITE);
    
    _XL_PRINT(0,   0,"TARGET INFORMATION");

    _XL_PRINT(0,   1*LINE_SKIP,"XSIZE ");
    _XL_PRINTD(6,  1*LINE_SKIP,3,XSize);

    _XL_PRINT(0,   2*LINE_SKIP,"YSIZE ");
    _XL_PRINTD(6,  2*LINE_SKIP,3,YSize);     
    
    _XL_PRINT(0,   3*LINE_SKIP,"TILES ");
    _XL_PRINTD(6,  3*LINE_SKIP,3,_XL_NUMBER_OF_TILES);   
    
    _XL_PRINT(0,   4*LINE_SKIP,"GRAPHICS ");
    #if !defined(_XL_NO_UDG)
        _XL_PRINT(11,4*LINE_SKIP,"ON");
    #else
        _XL_PRINT(11,4*LINE_SKIP,"OFF");
    #endif

    _XL_PRINT(0,     5*LINE_SKIP,"COLOR ");
    #if !defined(_XL_NO_COLOR)
        _XL_PRINT(11,5*LINE_SKIP,"ON");
    #else
        _XL_PRINT(11,5*LINE_SKIP,"OFF");
    #endif

    _XL_PRINT(0,     6*LINE_SKIP,"TEXT COLOR ");
    #if !defined(_XL_NO_TEXT_COLOR)
        _XL_PRINT(11,6*LINE_SKIP,"ON");
    #else
        _XL_PRINT(11,6*LINE_SKIP,"OFF");
    #endif

    _XL_PRINT(0,     7*LINE_SKIP,"JOYSTICK ");
    #if !defined(_XL_NO_JOYSTICK)
        _XL_PRINT(11,7*LINE_SKIP,"ON");
    #else
        _XL_PRINT(11,7*LINE_SKIP,"OFF");
    #endif

    _XL_PRINT(0,     8*LINE_SKIP,"SOUND ");
    #if !defined(_XL_NO_SOUND)
        _XL_PRINT(11,8*LINE_SKIP,"ON");
    #else
        _XL_PRINT(11,8*LINE_SKIP,"OFF");
    #endif
    while(1){};
    
    return EXIT_SUCCESS;
}

