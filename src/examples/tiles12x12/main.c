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

#include "cross_lib.h"

#define MAX_NUMBER_OF_HORIZONTAL_MINES 6

#define EMPTY 0
#define DEADLY 1
#define SUPER_RING 2
#define RING 3
#define EXTRA 4
#define APPLE 5
#define EXTRA_LIFE 6
#define WALL  7
#define HORIZONTAL_WALL 8
#define VERTICAL_WALL 9
#define TRANSPARENT 10


#define MINE_RIGHT 0
#define MINE_LEFT 1
#define MINE_UP 2
#define MINE_DOWN 3


uint8_t x;
uint8_t y;

uint8_t horizontal_mine_x[MAX_NUMBER_OF_HORIZONTAL_MINES];
uint8_t horizontal_mine_y[MAX_NUMBER_OF_HORIZONTAL_MINES];
uint8_t horizontal_mine_direction[MAX_NUMBER_OF_HORIZONTAL_MINES];
uint8_t horizontal_mine_transition[MAX_NUMBER_OF_HORIZONTAL_MINES];

uint8_t map[XSize][YSize];


// Left low player in the 2x2 multi-tile
#define LEFT_LOW_TILE0  _TILE_2
#define LEFT_LOW_TILE1  _TILE_6
#define LEFT_LOW_TILE2  _TILE_10
#define LEFT_LOW_TILE3  _TILE_14

#define RIGHT_LOW_TILE0 _TILE_3
#define RIGHT_LOW_TILE1 _TILE_7
#define RIGHT_LOW_TILE2 _TILE_11
#define RIGHT_LOW_TILE3 _TILE_15

#define LEFT_UP_TILE0   _TILE_0
#define LEFT_UP_TILE1   _TILE_4
#define LEFT_UP_TILE2   _TILE_8
#define LEFT_UP_TILE3   _TILE_12

#define RIGHT_UP_TILE0  _TILE_1
#define RIGHT_UP_TILE1  _TILE_5
#define RIGHT_UP_TILE2  _TILE_9
#define RIGHT_UP_TILE3  _TILE_13

#define MINE_TILE       _TILE_16
#define MINE_TILE_DOWN  _TILE_17
#define MINE_TILE_UP    _TILE_18
#define MINE_TILE_LEFT  _TILE_19
#define MINE_TILE_RIGHT _TILE_20


#define move_left() \
{ \
    bow_shape_tile = 2*((--bow_x)&1); \
    if(bow_shape_tile) \
    { \
        _XL_DELETE((bow_x>>1)+2,BOW_Y); \
    } \
    display_bow(); \
}


#define move_right() \
{ \
    bow_shape_tile = 2*((++bow_x)&1); \
    if(!bow_shape_tile) \
    { \
        _XL_DELETE((bow_x>>1)-1,BOW_Y); \
    } \
    display_bow(); \
}


/*

static const uint8_t bow_tile[8] =
{
    EMPTY_BOW_LEFT_TILE_0,
    EMPTY_BOW_RIGHT_TILE_0,
    EMPTY_BOW_LEFT_TILE_1,
    EMPTY_BOW_RIGHT_TILE_1,
    LOADED_BOW_LEFT_TILE_0,
    LOADED_BOW_RIGHT_TILE_0,
    LOADED_BOW_LEFT_TILE_1,
    LOADED_BOW_RIGHT_TILE_1,
};

*/


// void display_bow(void)
// {
    // _XL_DRAW((bow_x>>1),BOW_Y,bow_tile[4*loaded_bow+0+bow_shape_tile],bow_color);
    // _XL_DRAW((bow_x>>1)+1,BOW_Y,bow_tile[1+4*loaded_bow+bow_shape_tile],bow_color);  
// }



static const uint8_t player_tile[4][4] =
{
	{ // left lower 12x12 multi-tile 
		LEFT_UP_TILE0,
		RIGHT_UP_TILE0,
		LEFT_LOW_TILE0,
		RIGHT_LOW_TILE0,
	},
	{ // right lower 12x12 multi-tile
		LEFT_UP_TILE1,
		RIGHT_UP_TILE1,
		LEFT_LOW_TILE1,
		RIGHT_LOW_TILE1,
	},
	{ // left upper 12x12 multi-tile 
		LEFT_UP_TILE2,
		RIGHT_UP_TILE2,
		LEFT_LOW_TILE2,
		RIGHT_LOW_TILE2,
	},
	{ // right upper 12x12 multi-tile 
		LEFT_UP_TILE3,
		RIGHT_UP_TILE3,
		LEFT_LOW_TILE3,
		RIGHT_LOW_TILE3,
	},
};


void display_player(void)
{
	uint8_t tile_group = (x&1)+2*(y&1);
	
    _XL_DRAW((x>>1),((y+1)>>1),player_tile[tile_group][2],_XL_WHITE);
    _XL_DRAW((x>>1)+1,((y+1)>>1),player_tile[tile_group][3],_XL_WHITE);  
    _XL_DRAW((x>>1),((y+1)>>1)+1,player_tile[tile_group][0],_XL_WHITE);
    _XL_DRAW((x>>1)+1,((y+1)>>1)+1,player_tile[tile_group][1],_XL_WHITE);  


}

void display_mine(uint8_t x, uint8_t y)
{
	if(!(x&1) && !(y&1))
	{
		_XL_DRAW(x>>1,y>>1,MINE_TILE,_XL_CYAN);
	}
	else if(!(x&1))
	{
		_XL_DRAW(x>>1,(y>>1),MINE_TILE_UP,_XL_CYAN);
		_XL_DRAW(x>>1,(y>>1)+1,MINE_TILE_DOWN,_XL_CYAN);
	}
	else
	{
		_XL_DRAW(x>>1,y>>1,MINE_TILE_LEFT,_XL_CYAN);
		_XL_DRAW((x>>1)+1,y>>1,MINE_TILE_RIGHT,_XL_CYAN);
	}
}

#define MIN_Y 3
#define MAX_Y (2*YSize-6)
#define MIN_X 3
#define MAX_X (2*XSize-3)


void init_map(void)
{
    uint8_t i;
    uint8_t j;
    
    for(i=0;i<XSize;++i)
    {
        map[i][0]=WALL;
        map[i][YSize-1]=WALL;
    }
    for(i=0;i<YSize-1;++i)
    {
        map[0][i]=WALL;
        map[XSize-1][i]=WALL;
    }
    for(i=1;i<XSize-1;++i)
    {
        for(j=1;j<YSize-1;++j)
        {
            map[i][j]=EMPTY;
        }
    }
    for(i=0;i<MAX_NUMBER_OF_HORIZONTAL_MINES;++i)
    {
        horizontal_mine_y[i]=2;
        horizontal_mine_transition[i]=0;
        horizontal_mine_x[i]=2;
        horizontal_mine_direction[i]=MINE_RIGHT;
        
    }
}

void update_player_display(void)
{
	_XL_CLEAR_SCREEN();
	display_player();
}


void display_horizontal_transition_mine(uint8_t x, uint8_t y)
{
    _XL_DRAW(x-1,y,MINE_TILE_LEFT, _XL_CYAN);
    _XL_DRAW(x,y,MINE_TILE_RIGHT, _XL_CYAN);
}


void handle_horizontal_mine(register uint8_t index)
{
    register uint8_t x = horizontal_mine_x[index];
    register uint8_t y = horizontal_mine_y[index];
    
    if(horizontal_mine_direction[index]==MINE_LEFT)
    {
        
        if(!horizontal_mine_transition[index]) // transition not performed, yet
        {
            if(!map[x-1][y])
            {
                // Do left transition
                display_horizontal_transition_mine(x,y);
                map[x-1][y]=DEADLY;
                ++horizontal_mine_transition[index];
            }
            else
            {
                horizontal_mine_direction[index]=MINE_RIGHT;
            }
        }
        else // transition already performed
        {
            horizontal_mine_transition[index]=0;
            map[x][y]=EMPTY;
            _XL_DELETE(x,y);
            --horizontal_mine_x[index];
            _XL_DRAW(horizontal_mine_x[index],y,MINE_TILE,_XL_CYAN);
        }
    }
    else // direction is RIGHT
    {
        if(!horizontal_mine_transition[index]) // transition not performed, yet
        {
            if(!map[x+1][y])
            {
                // Do right transition
                display_horizontal_transition_mine(x+1,y);
                map[x+1][y]=DEADLY;
                ++horizontal_mine_transition[index];
            }
            else
            {
                horizontal_mine_direction[index]=MINE_LEFT;
            }
        }
        else // transition already performed
        {
            horizontal_mine_transition[index]=0;
            map[x][y]=EMPTY;
            _XL_DELETE(x,y);
            ++horizontal_mine_x[index];
            _XL_DRAW(horizontal_mine_x[index],y,MINE_TILE,_XL_CYAN);
        }
    }
}


int main(void)
{        

	uint8_t input;

	// uint8_t i;
	
    _XL_INIT_GRAPHICS();

    _XL_INIT_INPUT();
    
    _XL_INIT_SOUND();

    _XL_CLEAR_SCREEN();

    init_map();

	x = XSize;
	y = YSize;
	
	// _XL_DRAW(XSize/2,YSize/2,MINE_TILE,_XL_CYAN);
	// _XL_DRAW(XSize/2+2,YSize/2,MINE_TILE_LEFT,_XL_CYAN);
	// _XL_DRAW(XSize/2+3,YSize/2,MINE_TILE_RIGHT,_XL_CYAN);
	// _XL_DRAW(XSize/2+5,YSize/2,MINE_TILE_UP,_XL_CYAN);
	// _XL_DRAW(XSize/2+5,YSize/2+1,MINE_TILE_DOWN,_XL_CYAN);
	
	// display_mine(XSize,YSize);
	
	// display_mine(XSize+3,YSize);
	
	// display_mine(XSize+6,YSize-3);
	
	// for(i=MIN_X;i<MAX_X;++i)
	// {

		// display_mine(i,((YSize>>1)<<1));
		// _XL_SLOW_DOWN(_XL_SLOW_DOWN_FACTOR);
		// _XL_CLEAR_SCREEN();
	// }
	
	update_player_display();
	
	while(1)
	{
		input = _XL_INPUT();
		
		if(_XL_UP(input))
		{
			if(y>MIN_Y)
			{
				--y;
				update_player_display();
			}
		}
		else if(_XL_DOWN(input))
		{	
			if(y<MAX_Y)
			{
				++y;
				update_player_display();
			}
		}
		else if(_XL_LEFT(input))
		{
			if(x>MIN_X)
			{
				--x;
				update_player_display();
			}
		}
		else if(_XL_RIGHT(input))
		{	
			if(x<MAX_X)
			{
				++x;
				update_player_display();
			}
		}
        
        handle_horizontal_mine(0);
        
		_XL_SLOW_DOWN(_XL_SLOW_DOWN_FACTOR);
	};
    
    return EXIT_SUCCESS;
}

