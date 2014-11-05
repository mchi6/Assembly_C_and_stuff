#include "gba.h"
#include "font.h"

u16* videoBuffer = (u16*)VRAM;

void setPixel(int x, int y, u16 color) {
	videoBuffer[OFFSET(x, y, 240)] = color;
}

void drawRect(int x, int y, int width, int height, u16 color) {
	for (int c = x; c <= x + width; c++) {
		for (int r = y; r <= y + height; r++) {
			videoBuffer[OFFSET(c, r, 240)] = color;
		}
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
    	setPixel(x0,y0, color);
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

void drawChar(int x, int y, char ch, u16 color) {
	int c, r;
	for(c = 0; c < 6; c++) {
		for(r = 0; r < 8; r++) {
			if(fontdata_6x8[OFFSET(c, r, 6) + ch * 48]) {
				setPixel(x + c, y + r, color);
			}
		}
	}
}

void drawString(int x, int y, char *str, u16 color) {
	while(*str) {
		drawChar(x, y, *str++, color);
		x += 6;
	}
}

void drawText(u8 *str, int x, int y, u16 color) {
	
}

void delay(int n) {
	volatile int x = 0;
	for (int i = 0; i < n*10000; i++) {
		x++;
	} 	
}

void waitSync() {
	while (VCount > 160);
	while (VCount < 160);
}
