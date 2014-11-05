// typedef
typedef unsigned short u16;

// macros
#define OFFSET(row,col) ((row)*240+(col))
extern u16* videoBuffer;

// global variables
u16* videobuffer = (u16*) 0x6000000;

// function prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);

// functions
void setPixel(int r, int c, u16 color) {

	videobuffer[OFFSET(r, c)] = color;
}

void drawRect(int r, int c, int width, int height, u16 color) {
	// loop through every pixel
	for (int x = c; x < c + width; x++) {
		for (int y = r; y < r + height; y++) {
			videobuffer[OFFSET(y, x)] = color;
		}	
	}
}

void drawHollowRect(int r, int c, int width, int height, u16 color) {
	for (int x = c; x < c + width; x++) {
		videobuffer[OFFSET(r, x)] = color;
	}
	for (int x = c; x < c + width; x++) {
		videobuffer[OFFSET(r + height - 1, x)] = color;
	}
	for (int y = r; y < r + height; y++) {
		videobuffer[OFFSET(y, c)] = color;
	}
	for (int y = r; y < r + height; y++) {
		videobuffer[OFFSET(y, c + width - 1)] = color;
	}
}

void plotLine(int x0, int y0, int x1, int y1, u16 color) {
	int dx = x1 - x0;
	int dy = y1 - y0;

	int D = (dy << 1) - dx;
	setPixel(y0, x0, color);
	int y = y0;

	for (int x = x0 + 1; x <= x1; x++) {
		if (D > 0) {
			y = y + 1;
			setPixel(y, x, color);
			D = D + ((dy << 1) - (dx << 1));
		} else {
			setPixel(y, x, color);
			D = D + (dy << 1);
		}
	}
}
