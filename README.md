# Missile Dodge Game

Game created in C++ with SDL

***

##DOWNLOAD/INSTALLATION:
To play the game, download the repository and delete everything except for the build folder.
Simply run the exe in the build folder and the game should start!

If any errors occur, please open an issue on the repository.

***

##Code Cleanup TODOs:
  * ~~Organize collision function to match function name~~
  * Improve game logic behind boons and boon duration
  * Break down update function in game class to smaller parts
  * Change player sprite when boon is activated
  * Adjust main.cpp to better match the new game state system
  * Improve logic behind difficulty scaling

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
  * Power-ups
    * ~~Health~~
    * Speed
    * ~~Invincibility~~
  * Missile types
  * Implement Custom Fonts
  * Sprite sheet loading
3. Misc
  * GUI
  * Sprite Animation
  * High Score
  * ~~Game Over~~
  * ~~Menu~~
  * ~~Game State System~~
  * ~~Pause Menu~~
  * Options
    * Music/Sound Volume
    * Key Bindings
  * Intro Screen
  * Loading Screen

### ASSETS
1. Art
  * Sprite
    * Hero
    * Missiles
    * Hearts (In Progress)
    * Background
  * Splash Art
  * Logo
  * Icon
  * Font
    * ~~Numbers~~
    * Text
  * Animations
    * Hero
    * Missiles
    * Explosions
    * Tweens
2. Music/Sound
  * Background music
  * Sound effects

### EXPORT
  * Installer with NSIS

### PORT TO PLATFORMS
  * Android
  * IOS

***

## POSSIBLE ADD-ONS
* Levels
* Lasers
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
