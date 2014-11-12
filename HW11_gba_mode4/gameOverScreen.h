/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=240,160 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 gameOverScreen /home/rosestring/Documents/CS2110/HW11/gameOver.jpg 
 * Time-stamp: Sunday 11/09/2014, 21:08:00
 * 
 * Image Information
 * -----------------
 * /home/rosestring/Documents/CS2110/HW11/gameOver.jpg 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * Why do we want intelligent terminals when there are so many stupid users?
 * 
 * There is not greater pleasure than seeing your loved ones prosper.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef GAMEOVERSCREEN_BITMAP_H
#define GAMEOVERSCREEN_BITMAP_H

extern const unsigned short gameOverScreen_palette[256];
#define GAMEOVERSCREEN_PALETTE_SIZE 256

extern const unsigned short gameOverScreen[19200];
#define GAMEOVER_SIZE 19200
#define GAMEOVER_WIDTH 240
#define GAMEOVER_HEIGHT 160

#endif

