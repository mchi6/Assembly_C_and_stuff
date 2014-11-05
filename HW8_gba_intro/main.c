// macros
#define REG_DISPCTL *(u16*) 0x04000000
#define RGB(r,g,b) ((r)|((g)<<5)|((b)<<10))
#define MODE3 3
#define BG2_ENABLE (1<<10)

// typedef
typedef unsigned short u16;

// function prototypes
void setPixel(int r, int c, u16 color);
void drawRect(int r, int c, int width, int height, u16 color);
void drawHollowRect(int r, int c, int width, int height, u16 color);
void plotLine(int x0, int y0, int x1, int y1, u16 color);

// main function
int main(void) {
	
	REG_DISPCTL = MODE3 | BG2_ENABLE; // REG_DISPCTL = 1027/0x0403
	
	drawRect(0, 0, 240, 160, RGB(31, 31, 31)); //color1: white; drawRect

	while (1) {
		// draw UGLY GOOGLE

		// draw "G"
		drawRect(50, 40, 5, 5, RGB(0, 0, 31)); // color2: blue
		drawRect(45, 35, 5, 5, RGB(0, 0, 31));
		drawRect(40, 20, 15, 5, RGB(0, 0, 31));
		drawRect(45, 15, 5, 5, RGB(0, 0, 31));
		drawRect(50, 10, 5, 5, RGB(0, 0, 31));
		drawRect(55, 5, 5, 30, RGB(0, 0, 31));
		drawRect(85, 10, 5, 5, RGB(0, 0, 31));
		drawRect(90, 15, 5, 5, RGB(0, 0, 31));
		drawRect(95, 20, 15, 5, RGB(0, 0, 31));
		drawRect(90, 35, 5, 5, RGB(0, 0, 31));
		drawRect(80, 40, 5, 15, RGB(0, 0, 31));
		drawRect(75, 30, 20, 5, RGB(0, 0, 31));

		// draw "OO"
		drawHollowRect(65, 55, 30, 35, RGB(31, 0, 0)); // color3: red; drawHollowRect
		drawHollowRect(65, 90, 30, 35, RGB(31, 21, 0)); // color4: orange

		// draw 'g'
		drawHollowRect(65, 125, 20, 20, RGB(0, 0, 31));
		setPixel(64, 145, RGB(0, 0, 31)); // setPixel
		setPixel(64, 146, RGB(0, 0, 31));
		setPixel(64, 147, RGB(0, 0, 31));
		setPixel(63, 148, RGB(0, 0, 31));
		plotLine(145, 85, 150, 100, RGB(0, 0, 31)); // plotLine
		drawHollowRect(90, 125, 26, 15, RGB(0, 0, 31));

		// draw 'l'
		drawRect(40, 160, 5, 60, RGB(0, 31, 0)); // color5: green

		// draw 'e'
		drawRect(80, 180, 25, 5, RGB(31, 0, 0));
		drawRect(75, 200, 5, 5, RGB(31, 0, 0));
		drawRect(70, 195, 5, 5, RGB(31, 0, 0));
		drawRect(65, 190, 5, 5, RGB(31, 0, 0));
		drawRect(70, 185, 5, 5, RGB(31, 0, 0));
		drawRect(75, 180, 5, 5, RGB(31, 0, 0));
		drawRect(85, 180, 5, 15, RGB(31, 0, 0));
		drawRect(95, 185, 20, 5, RGB(31, 0, 0));
	}
}


