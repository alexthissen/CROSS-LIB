#

# COCO_COLOR_GFX_GAME_OPTS ?= 

# CREATIVISION_GAME_OPTS ?= -DMAX_NUMBER_OF_MISSILES=2 -DMAX_ROCKETS_ON_SCREEN=7 -DNO_BOTTOM_WALL_REDRAW

# GAMATE_GAME_OPTS ?= -DMAX_NUMBER_OF_MISSILES=3 -DMAX_ROCKETS_ON_SCREEN=4 

C128_Z80_80COL_GAME_OPTS ?= -DNO_CACTUS_TRANSITION -DSLOWER_FEET -DFEWER_DISPLAYS
    
# ZX81_NO_GFX_GAME_OPTS ?= -DMAX_ROCKETS_ON_SCREEN=7 -DMAX_NUMBER_OF_MISSILES=4 -DMISSILE_DROP_LOOP_MASK=1 -DSMALL_WALL 

ZX81_GFX_GAME_OPTS ?= -DNO_CACTUS_TRANSITION -DSLOWER_FEET -DFEWER_DISPLAYS

# APPLE2_GAME_OPTS ?= -DMAX_ROCKETS_ON_SCREEN=6 -DMAX_NUMBER_OF_MISSILES=4

COMX_GAME_OPTS ?= 	-DNO_CACTUS_TRANSITION

PECOM_GAME_OPTS ?= 	-DNO_CACTUS_TRANSITION

# TMC600_GAME_OPTS ?= 	-DMAX_ROCKETS_ON_SCREEN=6 -DMAX_NUMBER_OF_MISSILES=4 -DSMALL_WALL -DNO_BOTTOM_WALL_REDRAW -DNORMAL_ZOMBIE_SPEED=1 -DSLOW_ZOMBIE_SPEED=7

# CPC_GAME_OPTS ?= -DMAX_ROCKETS_ON_SCREEN=6 -DMAX_NUMBER_OF_MISSILES=4

# CAMPUTERS_LYNX_GAME_OPTS ?= -DMAX_ROCKETS_ON_SCREEN=5 -DMAX_NUMBER_OF_MISSILES=3

# NCURSES_GAME_OPTS ?= -DNO_EXTRA_TITLE

VIC20_UNEXPANDED_NO_GFX_GAME_OPTS ?= -DTINY_GAME -DNO_CACTUS_TRANSITION -DFEWER_DISPLAYS

VIC20_UNEXPANDED_GAME_OPTS ?= -DTINY_GAME 	-DNO_CACTUS_TRANSITION  -DFEWER_DISPLAYS