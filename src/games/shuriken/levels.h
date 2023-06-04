#include "cross_lib.h"
#include "screen_types.h"

// ------------------------------------------------------------
// Helper macros to compute sizes and offsets
#define LV_OBJECTS_SIZE(no_of_rect) (1+(no_of_rect*6))

#define LV_SHURIKENS_SIZE(horiz,vert,mini) (1+(horiz)*2+ 1+(vert)*2+ 1+(mini))

#define LC_WALLS_SIZE(walls) (1+(walls*7))
//

#include "level_horiz.h"
#include "level_vert_bars.h"
#include "level_cage.h"
#include "level_h_barriers.h"

// LEVEL 0 - Lots of horizontal shurikens
#define LV_0_OBJECTS LV_HORIZ_OBJECTS
#define LV_0_OBJECTS_SIZE LV_HORIZ_OBJECTS_SIZE
#define LV_0_SHURIKENS LV_HORIZ_SHURIKENS
#define LV_0_SHURIKENS_SIZE LV_HORIZ_SHURIKENS_SIZE
#define LV_0_WALLS LV_HORIZ_WALLS 
#define LV_0_WALLS_SIZE LV_HORIZ_WALLS_SIZE

// LEVEL 1 - Vertical walls
#define LV_1_OBJECTS LV_VERT_BARS_OBJECTS
#define LV_1_OBJECTS_SIZE LV_VERT_BARS_OBJECTS_SIZE
#define LV_1_SHURIKENS LV_VERT_BARS_SHURIKENS
#define LV_1_SHURIKENS_SIZE LV_VERT_BARS_SHURIKENS_SIZE
#define LV_1_WALLS LV_VERT_BARS_WALLS 
#define LV_1_WALLS_SIZE LV_VERT_BARS_WALLS_SIZE

// LEVEL 2 - Shuriken cage
#define LV_2_OBJECTS LV_CAGE_OBJECTS
#define LV_2_OBJECTS_SIZE LV_CAGE_OBJECTS_SIZE
#define LV_2_SHURIKENS LV_CAGE_SHURIKENS
#define LV_2_SHURIKENS_SIZE LV_CAGE_SHURIKENS_SIZE
#define LV_2_WALLS LV_CAGE_WALLS 
#define LV_2_WALLS_SIZE LV_CAGE_WALLS_SIZE

// LEVEL 3 - 4 horizontal barriers
#define LV_3_OBJECTS LV_H_BARRIERS_OBJECTS
#define LV_3_OBJECTS_SIZE LV_H_BARRIERS_OBJECTS_SIZE
#define LV_3_SHURIKENS LV_H_BARRIERS_SHURIKENS
#define LV_3_SHURIKENS_SIZE LV_H_BARRIERS_SHURIKENS_SIZE
#define LV_3_WALLS LV_H_BARRIERS_WALLS 
#define LV_3_WALLS_SIZE LV_H_BARRIERS_WALLS_SIZE


// ----------------------------------------------------------
// Objects: static walls and collectable items
const uint8_t objects_map[] =
{

	LV_0_OBJECTS,
	
	LV_1_OBJECTS,
    
	LV_2_OBJECTS,
	
	LV_3_OBJECTS

};


const uint16_t objects_index[] = 
{
	0,
	LV_0_OBJECTS_SIZE,
	LV_0_OBJECTS_SIZE+LV_1_OBJECTS_SIZE,
	LV_0_OBJECTS_SIZE+LV_1_OBJECTS_SIZE+LV_2_OBJECTS_SIZE
    // 0,
    // 1+6*12,
    // 1+6*12+1+6*11,
    // 1+6*12+1+6*11+1+6*12

    // TODO: ....
};


// ----------------------------------------------------------
// Shurikens: horizontal, vertical and mini-shurikens
const uint8_t shurikens_map[] =
{

	LV_0_SHURIKENS,
	
	// level=1
   	LV_1_SHURIKENS,

    // level=2
   	LV_2_SHURIKENS,
        
    // level=3
	LV3_SHURIKENS
  
};


const uint8_t shurikens_index[] = 
{
	0,
	LV_0_SHURIKENS_SIZE,
	LV_0_SHURIKENS_SIZE+LV_1_SHURIKENS_SIZE,
	LV_0_SHURIKENS_SIZE+LV_1_SHURIKENS_SIZE+LV_2_SHURIKENS_SIZE
    // 0,
    // 1+2*12+1+1,
    // 1+2*12+1+1+ 1+2*2+1+1+4*1,
    // 1+2*12+1+1+ 1+2*2+1+1+4*1+ 1+2*2+ 1+4*2+ 1,    
    // TODO: ....
};



// ----------------------------------------------------------
// Walls: dynamic walls
const uint8_t walls_map[] =
{
	LV_0_WALLS,
	LV_1_WALLS,
	LV_2_WALLS,
	LV_3_WALLS,
};

const uint8_t walls_index[] =
{
	0,
	LV_0_WALLS_SIZE,
	LV_0_WALLS_SIZE+LV_1_WALLS_SIZE,
	LV_0_WALLS_SIZE+LV_1_WALLS_SIZE+LV_2_WALLS_SIZE,
	
    // 0,
    // 0,
    // 1,
    // 1+1+2*8,
};
