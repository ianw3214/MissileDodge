# Missile Dodge Game

Game created in C++ with SDL

***

#PROJECT DISCONTINUED
I started making this game to help me learn SDL, and after four months with 
it I feel like I have learned more than enough. Yes, the game is still unfinished in some
parts, but it is redundant to finish those because I have already learned the concepts from
other parts in the game. Because of this, I am no longer going to be working on this game
and will start making new and better games based on the knowledge that I have gained 
through this first experience!

***

##DOWNLOAD/INSTALLATION:
To play the game, download the repository and delete everything except for the build folder.
Simply run the exe in the build folder and the game should start!

If any errors occur, please open an issue on the repository.

***

##Code Cleanup TODOs:
  * ~~Organize collision function to match function name~~
  * ~~Improve game logic behind boons and boon duration~~
  * Break down update function in game class to smaller parts
  * ~~Change player sprite when boon is activated~~
  * ~~Adjust main.cpp to better match the new game state system~~
  * ~~Improve logic behind difficulty scaling~~
  * ~~Change missile spawning rates to coordinate to time instead of frames~~
  * Have music/sound options carry over from game states to other game states

***

##BUGS:
  * ~~Pause menu having multiple countdowns after selecting the resume option~~ 
  * ~~Words from menu still show up on screen faintly after game has started~~
  * ~~key presses during transitions are registered~~
  * ~~Boons would immediately expire when aquired during another boon~~

***

##GAME CREATION TASK FLOW:

### SDL ENGINE
1. Core engine
  * ~~Sprite loading~~
  * ~~Key inputs~~
  * ~~Hero movement~~
  * ~~Sprite Class~~
  * ~~Hero Class~~
  * ~~Missile Class~~
  * ~~Missile Movement~~
  * ~~Missile Spawning~~
  * ~~Collision~~
  * ~~Missile Removal~~
  * ~~Points~~
  * ~~Show Points~~
  * ~~Health~~
  * ~~Health Sprite Update~~
  * ~~Jump~~
  * ~~End Game/Hero Death~~
  * Garbage Handling System
  * ~~Delta Time based update functions~~
2. Game improvements
  * ~~Game Class~~
  * ~~Battle Intro/Countdown~~
  * ~~Randomize fall speeds~~
  * ~~Difficulty increase~~
    * ~~Missile speed~~
    * ~~Missile spawn rate~~
  * ~~Power-ups~~
    * ~~Health~~
    * ~~Speed~~
    * ~~Invincibility~~
  * Missile types
    * ~~Normal Missile~~
    * ~~Gas Missile~~
    * Fire Missile
3. Misc
  * GUI
  * Sprite Animation
    * Hero Animation (In Progress)
    * Missile Animation
      * ~~Normal Missiles~~
      * Gas Missiles
    * Boon Animation
    * Background Animation
  * High Score
  * ~~Game Over~~
  * ~~Menu~~
  * ~~Game State System~~
  * ~~Pause Menu~~
  * ~~Death Menu~~
  * Options
    * ~~Music/Sound Volume~~
    * Fullscreen
    * Key Bindings
  * Intro Screen
  * Loading Screen
  * Hero temporary invincibility after taking damage
  * Slow Motion movement for a little bit after death

### ASSETS
1. Art
  * Sprite
    * ~~Hero~~
    * ~~Missiles~~
    * Health Bar (In Progress)
    * Background
  * ~~Splash Art~~
  * Menu
    * title (In Progress)
    * ~~background~~
    * ~~controls~~
    * settings
  * Logo
  * Icon
  * Text (In Progress)
  * Animations
    * ~~Hero~~
    * Missiles
    * Explosions
    * Tweens
  * Effects
    * ~~Boon Effects~~
    * Condition Effects
    * Ambient Effects
2. Audio
  * ~~Menu music~~
  * ~~Background music~~
  * Death Screen music
  * Sound effects (In Progress)

### EXPORT
  * Installer with NSIS

### PORT TO PLATFORMS
  * Android
  * IOS

***

## POSSIBLE ADD-ONS
* Levels
* ~~Lasers~~
* Boss fights
* Intro music
* Loading Screen
* Game State Tweens
* Customizable Key Bindings
* Game modes
* Classes

***

## IMPOSSIBLE MAYBE POSSIBLE VERY FUTURE ADD-ONS
* Multiplayer
* Level Creator

***

Creator: Ian Wang
Created: May 16th 2016
