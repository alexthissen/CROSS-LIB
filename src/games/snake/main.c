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

#include "init_images.h"

#include "snake.h"
#include "move_snake.h"

#include "control_player.h"

// TODO: REMOVE THIS
#define MAX_INIT_Y_POS ((YSize)+(Y_OFFSET)-19)

#if ((YSize)+(Y_OFFSET)-1)>19
    #define MAX_TILES 19
#else
    #define MAX_TILES ((YSize)+(Y_OFFSET)-1)
#endif


extern Image VERTICAL_HEAD_IMAGE;  
extern Image HORIZONTAL_HEAD_IMAGE; 
extern Image RIGHT_HEAD_IMAGE; 
extern Image LEFT_HEAD_IMAGE; 	


extern Image BODY_IMAGE; 
extern Image BOTTOM_TAIL_IMAGE; 

extern Image HORIZONTAL_JOINT_IMAGE; 

extern Image EXTRA_POINTS_IMAGE; 

extern Image LEFT_TAIL_IMAGE; 

extern Image RIGHT_TAIL_IMAGE; 

extern Image VERTICAL_JOINT_IMAGE; 

extern Image TOP_HEAD_IMAGE; 
extern Image TOP_HEAD_JOINT_IMAGE; 
extern Image BOTTOM_HEAD_JOINT_IMAGE; 
extern Image LEFT_HEAD_JOINT_IMAGE; 
extern Image RIGHT_HEAD_JOINT_IMAGE; 
extern Image TOP_TAIL_IMAGE; 


extern SnakeBody snake[MAX_SNAKE_LENGTH];

extern uint8_t snake_length;

extern uint8_t snake_head;

extern Image *head_image_ptr;

extern uint8_t map[XSize][YSize];

extern Image VERTICAL_BRICK_IMAGE;
extern Image HORIZONTAL_BRICK_IMAGE;

static uint8_t snake_head_x;
static uint8_t snake_head_y;

static uint16_t points;

static uint8_t snake_growth_counter;

#define COL_OFFSET ((XSize-16)/2-1)
#define ROW_OFFSET 3

#define GROWTH_THRESHOLD 20

#define hits_wall(x,y) \
    ((x)<1 || ((x)>=XSize-1) || (y)<1 || ((y)>=YSize-1))

#define hits_snake(x,y) \
    (map[x][y]==SNAKE)

#define hits_bonus(x,y) \
    (map[x][y]==BONUS)

#define BONUS_POINTS 10

void PRESS_KEY(void)
{
    SET_TEXT_COLOR(COLOR_WHITE);
    PRINT(COL_OFFSET,YSize-5, _XL_P _XL_R _XL_E _XL_S _XL_S _XL_SPACE _XL_F _XL_I _XL_R _XL_E);
    WAIT_PRESS();
}

void spawn_bonus(void)
{
    uint8_t x;
    uint8_t y;
    
    while(1)
    {
        x = RAND()%XSize;
        y = RAND()%YSize;
        
        if(!(map[x][y]) && !hits_wall(x,y))
        {
            break;
        }
    }
    map[x][y]=BONUS;
    
    _XLIB_DRAW(x,y,&EXTRA_POINTS_IMAGE);
}


int main(void)
{        

    uint8_t j;

    INIT_GRAPHICS();

    INIT_INPUT();
    
    INIT_IMAGES();
    
    points = 0;

    for(j=0;j<3;++j)
    {
        CLEAR_SCREEN();
        
        PRESS_KEY();
        CLEAR_SCREEN();
        DRAW_BORDERS();

        init_map();
        
        snake_growth_counter = 0;
        
        init_snake();
        
        WAIT_PRESS();
        while(1)
        {
            MOVE_PLAYER();
            DO_SLOW_DOWN(SLOW_DOWN);
            if(snake_growth_counter==GROWTH_THRESHOLD && snake_length<MAX_SNAKE_LENGTH)
            {
                snake_grows(); 
                snake_growth_counter = 0;
                spawn_bonus();
                TICK_SOUND();
                ++points;
            }
            
            snake_head_x = snake[snake_head].x;
            snake_head_y = snake[snake_head].y;
            
            ++snake_growth_counter;

            SET_TEXT_COLOR(COLOR_WHITE);
            PRINTD(0,0,5,points);
            
            if(hits_bonus(snake_head_x,snake_head_y))
            {
                points+=BONUS_POINTS;
                ZAP_SOUND();
            }
            
            if(hits_snake(snake_head_x,snake_head_y) || hits_wall(snake_head_x,snake_head_y))
            {
                break;
            }
        }
        EXPLOSION_SOUND();
        PRESS_KEY();
    }

    PRINT(COL_OFFSET,YSize-5, _XL_E _XL_N _XL_D _XL_SPACE _XL_O _XL_F _XL_SPACE _XL_D _XL_E _XL_M _XL_O);

    while(1){};
    
    return EXIT_SUCCESS;
}
