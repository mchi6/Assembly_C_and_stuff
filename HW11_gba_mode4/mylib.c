#include "gba.h"
#include "font.h"

u16* videoBuffer = (u16*)VRAM;

void setPixel3(int x, int y, u16 color) {
	videoBuffer[OFFSET(x, y, 240)] = color;
}

void setPixel4(int x, int y, u8 index) {
	int whichPixel = OFFSET(x, y, 240);
	int whichShort = whichPixel/2;
	if (x & 1) {
		// odd column
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0x00FF) | (index << 8);
	} else {
		// even column
		videoBuffer[whichShort] = (videoBuffer[whichShort] & 0xFF00) | (index);
	}
}

void drawRect3(int x, int y, int width, int height, u16 color) {
	for(int r = 0; r < height; r++) {
		DMA[3].src = &color;
		DMA[3].dst = &videoBuffer[OFFSET(x, y + r, 240)];
		DMA[3].cnt = width | DMA_ON | DMA_SOURCE_FIXED;
	}
}

/* Draw Rectangle for mode4 using DMA.*/
void drawRect4(int x, int y, int height, int width, u8 color) {
  	volatile u16 clr = color<<8 | color;
  	for(int r=0; r<height; r++) {
   		DMA[3].src = &clr;
    	DMA[3].dst = videoBuffer + OFFSET(x, y+r, 240)/2;
    	DMA[3].cnt = (width/2) | DMA_ON | DMA_SOURCE_FIXED;
  	}
}

 /* drawimage3
  * A function that will draw an arbitrary sized image
  * onto the screen (with DMA).
  * @param x column to draw the image
  * @param y row to draw the image
  * @param height height of the image
  * @param width width of the image
  * @param image Pointer to the first element of the image.
  */
void drawImage3(int x, int y, int width, int height, const u16* image) {
	for(int r = 0; r < height; r++) {
		DMA[3].src = &image[OFFSET(0, r, width)];
		DMA[3].dst = &videoBuffer[OFFSET(x, y + r, 240)];
		DMA[3].cnt = width | DMA_ON;
	}
}

void drawImage4(int x, int y, int width, int height, const u16* image) {
	for(int r = 0; r < height; r++) {
		DMA[3].src = &image[OFFSET(0, r, width/2)];
		DMA[3].dst = &videoBuffer[OFFSET(x, y + r, 240)/2];
		DMA[3].cnt = width/2 | DMA_ON;
	}
}

void flipPage() {
  	if(REG_DISPCNT & BUFFER1FLAG) {
   		REG_DISPCNT &= ~BUFFER1FLAG;
    	videoBuffer = BUFFER1;
  	} else {
    	REG_DISPCNT |= BUFFER1FLAG;
    	videoBuffer = BUFFER0;
  	}
}

void fillScreen3(volatile u16 color) {
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 38400 | DMA_ON | DMA_SOURCE_FIXED; 
}

void fillScreen4(u8 index) {
	volatile u16 color = index | (index << 8);
	DMA[3].src = &color;
	DMA[3].dst = videoBuffer;
	DMA[3].cnt = 19200 | DMA_ON | DMA_SOURCE_FIXED;
}

void fillPalette(const u16 *palette, int start, int pal_size) {
	for (int i = start; i < pal_size; i++) {
		PALETTE[i] = palette[i];
	}
}

void drawHollowRect(int x, int y, int width, int height, u16 color) {
	for (int c = x; c <= x + width; c += width) {
		for (int r = y; r <= y + height; r += height) {
			videoBuffer[OFFSET(c, r, 240)] = color;
		}
	}

	for (int r = y; r <= y + height; r += height) {
		for (int c = x; c <= x + width; c += width) {
			videoBuffer[OFFSET(c, r, 240)] = color;
		}
	}
}

void drawLine(int x0, int y0, int x1, int y1, u16 color) {
 
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
  	int err = (dx>dy ? dx : -dy)/2, e2;
 
  	for(;;){
    	setPixel3(x0,y0, color);
    	if(x0==x1 && y0==y1) {
    		break;
    	}	
    	e2 = err;
    	if(e2 >-dx) { 
    		err -= dy; 
    		x0 += sx; 
    	}
    	if(e2 < dy) {
     		err += dx; 
     		y0 += sy; 
 		}
  	}
}

void drawChar3(int x, int y, char ch, u16 color) {
	int c, r;
	for(c = 0; c < 6; c++) {
		for(r = 0; r < 8; r++) {
			if(fontdata_6x8[OFFSET(c, r, 6) + ch * 48]) {
				setPixel3(x + c, y + r, color);
			}
		}
	}
}

void drawString3(int x, int y, char *str, u16 color) {
	while(*str) {
		drawChar3(x, y, *str++, color);
		x += 6;
	}
}

void drawChar4(int x, int y, char ch, u8 index) {
	int c, r;
	for(c = 0; c < 6; c++) {
		for(r = 0; r < 8; r++) {
			if(fontdata_6x8[OFFSET(c, r, 6) + ch * 48]) {
				setPixel4(x + c, y + r, index);
			}
		}
	}
}

void drawString4(int x, int y, char *str, u8 index) {
	while(*str) {
		drawChar4(x, y, *str++, index);
		x += 6;
	}
}

void delay(int n) {
	volatile int x = 0;
	for (int i = 0; i < n*10000; i++) {
		x++;
	} 	
}

void waitSync() {
	while (VCount >= 160);
	while (VCount < 160);
}
