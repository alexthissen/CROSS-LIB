

# CROSS LIB
![LOGO](snapshots/CrossLibLogoByHamletShorter.jpg)

*Cross-Lib* and games that use it (e.g., Chase, Shoot, Bomber, Snake, Horde, Verbix, Shuriken, Stinger, Trex)

by Fabrizio Caruso (fabrizio_caruso@hotmail.com)

*Cross-Lib* is a *retro-hardware abstraction layer* for coding "universal" games with **the very same code** for hundreds of mostly 8-bit systems (consoles, computers, scientific calculators, hand-held consoles, arcade boards, hacked toy computers, etc.).

*Cross-Lib* is a *WORA* (Write Once Run Anywhere) framework for vintage systems, i.e., you code a game **once** in an abstract hardware-agnostic way and *Cross-Lib* produces the very same game for about 200 vintage systems.

Read the <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/DISCLAIMER.md"><b>Disclaimer.</b></a>

<br />

<p float="left">
  <img src="snapshots/XSnake_MSX2.png" width="100" />
  <img src="snapshots/XStinger_Vic20.png" width="100" /> 
  <img src="snapshots/XVerbix_Vic20_gameplay.jpg" width="100" />
  <img src="snapshots/XSnake_GB.png" width="100" />
  <img src="snapshots/XShoot_Level1_Skulls_VIC20.jpg" width="100" />
  <img src="snapshots/XShuriken_Vic20_gameplay.jpg" width="100" />
</p>

-------------------------------------------

## ARTICLE ABOUT CROSS-LIB
Article in English (updated and modified version of an article published in C.A.L.L. Apple Volume 3 Number 1 (January 2023):
https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/EnglishArticle.md

Article in French (first published in the French magazine "Programmez! Hors série #6") that describes Cross-Lib in details.
https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/articles/CROSS_LIB_PUBLIC.pdf

-------------------------------------------


## THE GAMES

These games are the proof of the flexibility of *Cross-Lib*.

Play the games online:

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md

1. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#trex"><b>Trex</b></a> is a mini-game and an obvious clone of off-line Chrome T-Rex game.
2. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#stinger"><b>Stinger</b></a> is a tank-shooter with several enemies, levels, power-ups and items to pick.
3. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#shuriken"><b>Shuriken</b></a> is somehow inspired by Pac-man and Pengo.
4. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#verbix"><b>Verbix</b></a> is a Scrabble-like game that looks like Tetrix with letters.
5. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#horde"><b>Horde</b></a> is a zombie shooter with several different enemies, levels, power-ups and special items to pick.
6. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#snake"><b>Snake</b></a> is my personal re-interpretation of Nibbler (arcade game) to which I have added more game elements
7. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#bomber"><b>Bomber</b></a> is a mini-game and clone of Air Attack (aka Blitz).
8. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#shoot"><b>Shoot</b></a> is a shooter somehow similar to Robotron. It has many items and secrets to discover.
9. <a href="https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/GAMES.md#chase"><b>Chase</b></a> is somehow similar to *Gnome Robots* but in real-time game and with several items and power-ups.

-------------------------------------------


## CURRENTLY SUPPORTED SYSTEMS AND ARCHITECTURES

Cross-Lib can be used to build games for about 200 different vintage systems (computers, consoles, hand-helds, arcade boards, scientific pocket calculators, etc.). 
A partial list of the supported systems with their status is in: 

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/STATUS.md

The most significant supported vintage CPU architectures are:

- COSMAC RCA 1802 
- Intel 8080 
- MOS 6502 
- Motorola 6803 
- Motorola 6809
- TMS 9900
- Zilog 80 

Cross-Lib has also some experimental support for vintage 16-bit and 32-bit systems and for the native PC console.

For a more complete list of architectures you can look at:

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/ARCHITECTURES.md

-------------------------------------------

## THE TOOL-CHAIN

Cross-Lib provides a full tool-chain to build universal vintage 8-bit games. 

### Cross-Lib components

Cross-Lib provides:
- a C library with hardware-agnostic APIs for game development;
- the "user-friendly" script `xl`.



### The build process

When a game is built for a specific target, the Cross-Lib tool-chain will automatically:
1. if needed, convert the abstract graphics assets in graphics assets for the given target on the fly;
2. compile the game code (and the target-specific game assets) by using the appropriate compiler;
3. if needed, whenever possible, create a disk/cassette/cartridge image.

The user has to
- code the game in C with Cross-Lib APIs;
- draw the graphics assets in the *tiles* directory;
- run the `xl` script (see below).

![User](snapshots/User2.bmp)

More details on the build process are here:

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/BUILD_PROCESS.md


### The compilers

Code written in C with Cross-Lib can be compiled by several different cross-compilers and natively on the PC.

The tool-chain currently supports: `CC65`, `Z88DK` (`SCCZ80` and `ZSDCC`), `CMOC`, `LCC1802`, `ACK`, `XTC68`, `GCC`, `GCC-Z8K`, `GCC-ATARI-ST`, `GCC-AMIGA`, `GCC-TI`, `VBCC`, `CC6303`.
For more details on the supported compilers we refer to:

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/COMPILERS.md


-------------------------------------------

## INSTALLATION

An installation is not strictly necessary because Cross-Lib can be used through GitHub Codespaces on any browser.
For an actual installation you can use
- the pre-build docker image, 
- the dockerfile to build an image or 
- a clone of this repository, which requires some dependencies (compilers and a few tools).

For the details go here:

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/INSTALL.md

-------------------------------------------

## THE `xl` SCRIPT

Inside the project main directory, you find the `src` and the `build` directories:
- `src` contains the source code and all other files that are necessary to build the games and tests
- `build` is supposed to be empty at first and it is the target directory for the build process.

First of all you need to be in the `src` directory.
From `src` you can use the `xl` script  to do different operations on projects.


`xl` is used as follows:
```
xl <command> <[optional] parameters>
```

You can get help with:
```
xl help <[optional] command>
```

You can build games and examples with :

`xl <game_or_example_name> <[optional] system_name>`

For example `xl snake vic20` builds the *snake* for the *Commodore Vic 20 +16K* and `xl stinger` builds *stinger* for the *native terminal*.

For more details read here:

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/XL.md

-------------------------------------------

## HOW TO CODE WITH CROSS-LIB

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/HARDWARE_AGNOSTIC_CODE.md

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/CROSS_LIB_APIS.md


-------------------------------------------

## LOADING THE GAMES

https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/HOW_TO_LOAD.md

-------------------------------------------

## ACKNOWLEDGEMENTS

Cross-Lib would not exist without the cross-compilers and the support of their developers and the support of some people who have helped me handle the input/output of some targets.

A partial list of the people who have helped in found in: https://github.com/Fabrizio-Caruso/CROSS-LIB/blob/master/docs/CREDITS.txt

-------------------------------------------

## LICENCE

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Permission is granted to anyone to use this software for non-commercial applications, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software in
a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not
be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.

For example I do not authorize selling hardware, software, firmware or any other product that contains any part of Cross-Lib and/or its games (e.g., pre-loaded disks, tapes, cartridges, etc.).
On the other hand I authorize people to load the games in the most convenient way for their personal use.

