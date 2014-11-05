#include <stdio.h>
#include <stdlib.h>

// typedef
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned long vu32;

// display definitions
#define REG_DISPCNT *(u16*)0x04000000		
#define VRAM 0x06000000
#define M5_VRAM 0x0600A000 
#define BACKBUFFER  0x010
#define PALETTE 0x5000000
#define MODE_3 0x03	
#define MODE_4 0x04
#define MODE_5 0x05
#define BG2_ENABLE 0x0400
#define setMode(Mode) REG_DISPCNT=(Mode)

#define RED RGB(31, 0, 0)
#define GREEN RGB(0, 31, 0)
#define BLUE RGB(0, 0, 31)
#define BLACK RGB(0, 0, 0)
#define WHITE RGB(31, 31, 31)
#define CYAN RGB(0, 31, 31)
#define MAG	RGB(31, 0, 31)
#define YELLOW	RGB(31, 31, 0)

#define OFFSET(x, y, width) ((x)+(width)*(y))
#define RGB(R, G, B) ((R) | (G)<<5 | (B)<<10)
#define VCount *(volatile u16*) 0x4000006

extern u16* videoBuffer;
extern u16* pallete_mem;


// keys definitions
extern volatile u32* KEYS;
#define KEY_A 1 << 0
#define KEY_B 1 << 1
#define KEY_SELECT 1 << 2
#define KEY_START 1 << 3
#define KEY_RIGHT 1 << 4
#define KEY_LEFT 1 << 5
#define KEY_UP 1 << 6
#define KEY_DOWN 1 << 7
#define KEY_R 1 << 8
#define KEY_L 1 << 9
#define KEY_DOWN_NOW(key) (!((*KEYS)&key))

// text
extern const u8 fontdata_6x8[12288];

// function prototypes
void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawLine(int x0, int y0, int x1, int y1, u16 color);
void drawChar(int x, int y, char ch, u16 color);
void drawString(int x, int y, char *str, u16 color);
void delay(int n);
void waitSync();
