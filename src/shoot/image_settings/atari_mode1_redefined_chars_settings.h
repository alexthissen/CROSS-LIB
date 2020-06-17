
#ifndef _ATARI_MODE1_ANIMATE_PLAYER_SETTINGS
#define _ATARI_MODE1_ANIMATE_PLAYER_SETTINGS

#define _ATARI_MODE1_RED 0
#define _ATARI_MODE1_WHITE	64
#define _ATARI_MODE1_BLUE 128
#define _ATARI_MODE1_YELLOW 192

#define _PLAYER_DOWN_OFFSET 60
#define _PLAYER_UP_OFFSET 61
#define _PLAYER_RIGHT_OFFSET 62
#define _PLAYER_LEFT_OFFSET 63

#define _EXTRA_LIFE_OFFSET 60
#define _GHOST_OFFSET 59
#define _DEAD_GHOST_OFFSET 59
#define _SKULL_OFFSET 30 

#define _BOMB_OFFSET 29
#define _POWERUP_OFFSET 28
#define _FREEZE_OFFSET 28
#define _SUPER_OFFSET 28
#define _CONFUSE_OFFSET 30
#define _GUN_OFFSET 11
#define _BULLET_OFFSET 10 
#define _INVINCIBILITY_OFFSET 12 
#define _LEFT_HORIZONTAL_MISSILE_OFFSET 9
#define _RIGHT_HORIZONTAL_MISSILE_OFFSET 8	
#define _ROCKET_OFFSET 7
#define _VERTICAL_BRICK_OFFSET 5
#define _HORIZONTAL_BRICK_OFFSET 6

#define _PLAYER_DOWN (_PLAYER_DOWN_OFFSET + _ATARI_MODE1_BLUE)
#define _PLAYER_UP (_PLAYER_UP_OFFSET + _ATARI_MODE1_BLUE)
#define _PLAYER_RIGHT (_PLAYER_RIGHT_OFFSET + _ATARI_MODE1_BLUE)
#define _PLAYER_LEFT (_PLAYER_LEFT_OFFSET + _ATARI_MODE1_BLUE)


#define _EXTRA_LIFE (_EXTRA_LIFE_OFFSET + _ATARI_MODE1_YELLOW)
#define _GHOST (_GHOST_OFFSET + _ATARI_MODE1_WHITE)
#define _DEAD_GHOST (_DEAD_GHOST_OFFSET + _ATARI_MODE1_RED)
#define _SKULL (_SKULL_OFFSET + _ATARI_MODE1_YELLOW)
#define _BOMB (_BOMB_OFFSET + _ATARI_MODE1_RED)
#define _POWERUP (_POWERUP_OFFSET + _ATARI_MODE1_YELLOW)
#define _FREEZE (_FREEZE_OFFSET + _ATARI_MODE1_BLUE)
#define _SUPER (_SUPER_OFFSET + _ATARI_MODE1_RED)
#define _CONFUSE (_CONFUSE_OFFSET + _ATARI_MODE1_RED)
#define _GUN (_GUN_OFFSET + _ATARI_MODE1_YELLOW)
#define _BULLET (_BULLET_OFFSET + _ATARI_MODE1_RED)
#define _INVINCIBILITY (_INVINCIBILITY_OFFSET + _ATARI_MODE1_YELLOW)

#define _LEFT_HORIZONTAL_MISSILE (_LEFT_HORIZONTAL_MISSILE_OFFSET + _ATARI_MODE1_WHITE)
#define _RIGHT_HORIZONTAL_MISSILE (_RIGHT_HORIZONTAL_MISSILE_OFFSET + _ATARI_MODE1_WHITE)	
#define _ROCKET (_ROCKET_OFFSET + _ATARI_MODE1_WHITE)

#define _EXTRA_POINTS (4 + _ATARI_MODE1_YELLOW)
#define _VERTICAL_BRICK (5 + _ATARI_MODE1_YELLOW)
#define _HORIZONTAL_BRICK (6 + _ATARI_MODE1_YELLOW)

#define _BROKEN_BRICK _BOMB

#endif // _ATARI_MODE1_ANIMATE_PLAYER_SETTINGS
