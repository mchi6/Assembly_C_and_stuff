/*
 * Exported with brandontools v1.0
 * Invocation command was brandontools -mode4 -resize=240,160 -start=0 -weights=25,25,25,25 -dither=1 -dither_level=80 startScreen /home/rosestring/Documents/CS2110/HW11/startScreen.jpg 
 * Time-stamp: Monday 11/10/2014, 23:51:00
 * 
 * Image Information
 * -----------------
 * /home/rosestring/Documents/CS2110/HW11/startScreen.jpg 240@160
 * 
 * Quote/Fortune of the Day!
 * -------------------------
 * To err is human... to really foul up requires the root password.
 * 
 * Love truth, but pardon error.
 * 
 * All bug reports / feature requests are to be sent to Brandon (brandon.whitehead@gatech.edu)
 */

#ifndef STARTSCREEN_BITMAP_H
#define STARTSCREEN_BITMAP_H

extern const unsigned short startScreen_palette[256];
#define STARTSCREEN_PALETTE_SIZE 256

extern const unsigned short startScreen[19200];
#define STARTSCREEN_SIZE 19200
#define STARTSCREEN_WIDTH 240
#define STARTSCREEN_HEIGHT 160

#endif

