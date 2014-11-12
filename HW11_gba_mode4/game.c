#include "gba.h"
#include "startScreen.h"
#include "gameOverScreen.h"
#include "GPalette.h"

// macros
#define numOfSnakes 3
#define numOfCars 4
#define numOfWoods 3
#define numOfCrocodiles 2


// avatar structs
typedef struct {
	int x;
	int y;
	int dx;
	int dy;
	const u16* imgU1;
	const u16* imgU2;
	const u16* imgU3;
	const u16* imgD1;
	const u16* imgD2;
	const u16* imgD3;
	const u16* imgL1;
	const u16* imgL2;
	const u16* imgL3;
	const u16* imgR1;
	const u16* imgR2;
	const u16* imgR3;
} FROG;

typedef struct {
	int x;
	int y;
	int dx;
	const u16* img1;
	const u16* img2;
	const u16* img3;
	const u16* img4;
	const u16* img5;
} SNAKE;

typedef struct {
	int x;
	int y;
	int dx;
	const u16* img;
} CAR;

typedef struct {
	int x;
	int y;
	int dx;
	const u16* img;
} WOOD;

typedef struct {
	int x;
	int y;
	int dx;
	const u16* img;
} CROCODILE;

// variables
// game status
int gameStatus = 0;
int numOfLives = 3;
// animation frames
int frogFrame = 0;
int snakeFrame = 0;
// declare avatars
FROG frog;
SNAKE snakes[numOfSnakes];
CAR cars[numOfCars];
WOOD woods[numOfWoods];
CROCODILE crocodiles[numOfCrocodiles];
// other shared variables
const u16* prevImg = frogU1;
int homeFlags[5];

// function prototypes
void startGame();
void lose();
void win();
void play();
void init();
static void avatarInit();
static void drawBG();
static void drawFrog();
static void drawSnakes();
static void drawCars();
static void drawWoods();
static void drawCrocodiles();
static void collisionDetection();
static void loseLife();
static void resetDetection();
static int getHomeDetection(int safeFlag);

// functions
void startGame() {
	fillPalette(startScreen_palette, 0, STARTSCREEN_PALETTE_SIZE);
	drawImage4(0, 0, 240, 160, startScreen);
	drawString4(30, 140, "PRESS <START> TO START", PALETTE[1]);
}

void lose() {
	fillPalette(gameOverScreen_palette, 0, GAMEOVERSCREEN_PALETTE_SIZE);
	drawImage4(0, 0, 240, 160, gameOverScreen);
	drawString4(90, 130, "YOU LOSE!", PALETTE[1]);
	drawString4(60, 145, "<START> TO RESTART", PALETTE[1]);
	gameStatus = 2;
}

void win() {
	fillPalette(gameOverScreen_palette, 0, GAMEOVERSCREEN_PALETTE_SIZE);
	drawImage4(0, 0, 240, 160, gameOverScreen);
	drawString4(90, 130, "YOU WIN!", PALETTE[1]);
	drawString4(60, 145, "<START> TO RESTART", PALETTE[1]);
	gameStatus = 2;
}

void init() {
	numOfLives = 3;
	// initialize all avatars
	avatarInit();
	// fill palette with the global palette
	fillPalette(GPalette, 0, GPALETTE_SIZE);
	// fill palette with 5 basic colors
	PALETTE[200] = BLACK;
	PALETTE[201] = WHITE;
	PALETTE[202] = RED;
	PALETTE[203] = GREEN;
	PALETTE[204] = BLUE;
	// initialize all homeflags
	for (int i = 0; i < 5; i++) {
		homeFlags[i] = 0;
	}
}

void play() {
	// draw the background
	drawBG();
	// use strings to represent game status
	char liveStr[7];
	if (numOfLives >= 0) {
		sprintf(liveStr, "%d", numOfLives);
		drawString4(10, 147, "LIVES LEFT:  ", PALETTE[1]);
		drawString4(80, 147, liveStr, PALETTE[1]);
	}
	// draw the snakes
	drawSnakes();
	// draw the cars
	drawCars();
	// draw the woods
	drawWoods();
	// draw the crocodiles
	drawCrocodiles();
	// draw the frog with animation
	drawFrog();
	// collision detections
	collisionDetection();
	// game reset detection
	resetDetection();

	delay(3);
	waitSync();
	flipPage();

}

static void drawBG() {
	fillScreen4(200);
	drawImage4(10, 10, 220, 140, frogBG);
}

static void drawFrog() {
	drawImage4(frog.x, frog.y, 14, 14, prevImg);
	if (KEY_DOWN_NOW(KEY_LEFT)) {
		frog.x -= frog.dx;
		drawImage4(frog.x, frog.y, 14, 14, frog.imgL1);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgL2);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgL3);
		prevImg = frog.imgL1;
	} else if (KEY_DOWN_NOW(KEY_RIGHT)) {
		frog.x += frog.dx;
		drawImage4(frog.x, frog.y, 14, 14, frog.imgR1);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgR2);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgR3);
		prevImg = frog.imgR1;
	} else if (KEY_DOWN_NOW(KEY_UP)) {
		frog.y -= frog.dy;
		drawImage4(frog.x, frog.y, 14, 14, frog.imgU1);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgU2);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgU3);
		prevImg = frog.imgU1;
	} else if (KEY_DOWN_NOW(KEY_DOWN)) {
		frog.y += frog.dy;
		drawImage4(frog.x, frog.y, 14, 14, frog.imgD1);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgD2);
		drawImage4(frog.x, frog.y, 14, 14, frog.imgD3);
		prevImg = frog.imgD1;
	}	
}

static void drawSnakes() {
	snakeFrame++;
	for (int i = 0; i < numOfSnakes; i++) {
		if (snakes[i].x + 30 <= 10) {
			snakes[i].x = 220;
		}
		snakes[i].x -= snakes[i].dx;
		switch (snakeFrame) {
			case 1:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img1);
				break;
			case 2:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img2);
				break;
			case 3:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img3);
				break;
			case 4:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img4);
				break;
			case 5:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img5);
				break;
			case 6:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img4);
				break;
			case 7:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img3);
				break;
			case 8:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img2);
				break;
			default:
				drawImage4(snakes[i].x, snakes[i].y, 30, 14, snakes[i].img1);
				snakeFrame = 0;
		}
	}
}

static void drawCars() {
	for (int i = 0; i < numOfCars; i++) {
		if (cars[i].x + 30 <= 10) {
			cars[i].x = 220;
		}
		cars[i].x -= cars[i].dx;
		drawImage4(cars[i].x, cars[i].y, 16, 10, cars[i].img);
	}
}

static void drawWoods() {
	for (int i = 0; i < numOfWoods; i++) {
		if (woods[i].x + 30 <= 10) {
			woods[i].x = 220;
		}
		woods[i].x -= woods[i].dx;
		drawImage4(woods[i].x, woods[i].y, 42, 12, woods[i].img);
	}
}

static void drawCrocodiles() {
	for (int i = 0; i < numOfCrocodiles; i++) {
		if (crocodiles[i].x >= 230) {
			crocodiles[i].x = 0;
		}
		crocodiles[i].x += crocodiles[i].dx;
		drawImage4(crocodiles[i].x, crocodiles[i].y, 46, 16, crocodiles[i].img);
	}
}

static void collisionDetection() {
	int safeFlag = 0;
	safeFlag = getHomeDetection(safeFlag);

	int forgive = 5;
	if (frog.x <= 10 || frog.x >= 230 || frog.y <= 10 || frog.y >= 150) {
		numOfLives--;
		loseLife();
	}
	
	// with crocodiles
	for (int i = 0; i < numOfCrocodiles; i++) {
		if (frog.x + 14 >= crocodiles[i].x &&
			frog.x <= crocodiles[i].x + 20 &&
			frog.y + 14 >= crocodiles[i].y &&
			frog.y <= crocodiles[i].y + 16 - forgive) {
			frog.x += crocodiles[i].dx;
			safeFlag = 1;
		}
	}
	// with woods
	for (int i = 0; i < numOfWoods; i++) {
		if (frog.x + 14 >= woods[i].x &&
			frog.x <= woods[i].x + 42 - forgive &&
			frog.y + 14 >= woods[i].y &&
			frog.y <= woods[i].y + 12 - forgive) {
			frog.x -= woods[i].dx;
			safeFlag = 1;
		}
	}
	// with cars
	for (int i = 0; i < numOfCars; i++) {
		if (frog.x + 14 >= cars[i].x &&
			frog.x <= cars[i].x + 16 - forgive &&
			frog.y + 14 >= cars[i].y &&
			frog.y <= cars[i].y + 10 - forgive) {
			loseLife();
		}
	}
	// with snakes
	for (int i = 0; i < numOfSnakes; i++) {
		if (frog.x + 14 >= snakes[i].x &&
			frog.x <= snakes[i].x + 30 - forgive &&
			frog.y + 14 >= snakes[i].y &&
			frog.y <= snakes[i].y + 14 - forgive) {
			loseLife();
		}
	}
	// with river
	if (safeFlag == 0 && frog.y <= 60 && frog.y >= 10) {
		loseLife();
	}
}

static void loseLife() {
	numOfLives--;
	
	if (numOfLives >= 0) {
		drawString4(100, 75, "LIVES   -1", PALETTE[1]);
		flipPage();
		delay(20);
		avatarInit();
	} else {
		lose();
	}
}
static int getHomeDetection(int safeFlag) {
	if (homeFlags[0] == 0 && frog.y >= 10 && frog.y <= 30 && frog.x >= 10 && frog.x <= 25) {
		drawString4(100, 75, "GOOD JOB!", PALETTE[1]);
		flipPage();
		homeFlags[0] = 1;
		avatarInit();
		safeFlag = 1;
		delay(20);
	}
	if (homeFlags[0]) {
		drawImage4(18, 15, 14, 14, frog.imgU1);
	}
	if (homeFlags[1] == 0 && frog.y >= 10 && frog.y <= 30 && frog.x >= 60 && frog.x <= 70) {
		drawString4(100, 75, "GOOD JOB!", PALETTE[1]);
		flipPage();
		homeFlags[1] = 1;
		avatarInit();
		safeFlag = 1;
		delay(20);
	}
	if (homeFlags[1]) {
		drawImage4(66, 15, 14, 14, frog.imgU1);
	}
	if (homeFlags[2] == 0 && frog.y >= 10 && frog.y <= 30 && frog.x >= 108 && frog.x <= 118) {
		drawString4(100, 75, "GOOD JOB!", PALETTE[1]);
		flipPage();
		homeFlags[2] = 1;
		avatarInit();
		safeFlag = 1;
		delay(20);
	}
	if (homeFlags[2]) {
		drawImage4(114, 15, 14, 14, frog.imgU1);
	}
	if (homeFlags[3] == 0 && frog.y >= 10 && frog.y <= 30 && frog.x >= 155 && frog.x <= 165) {
		drawString4(100, 75, "GOOD JOB!", PALETTE[1]);
		flipPage();
		homeFlags[3] = 1;
		avatarInit();
		safeFlag = 1;
		delay(20);
	}
	if (homeFlags[3]) {
		drawImage4(160, 15, 14, 14, frog.imgU1);
	}
	if (homeFlags[4] == 0 && frog.y >= 10 && frog.y <= 30 && frog.x >= 195 && frog.x <= 210) {
		drawString4(100, 75, "GOOD JOB!", PALETTE[1]);
		flipPage();
		homeFlags[4] = 1;
		avatarInit();
		safeFlag = 1;
		delay(20);
	}
	if (homeFlags[4]) {
		drawImage4(208, 15, 14, 14, frog.imgU1);
	}
	if (homeFlags[0] && homeFlags[1] && homeFlags[2] && homeFlags[3] && homeFlags[4]) {
		win();
	}
	return safeFlag;
}

static void resetDetection() {
	if (KEY_DOWN_NOW(KEY_SELECT)) {
		startGame();
		gameStatus = 0;
	}
}

static void avatarInit() {
	frogFrame = 0;
	snakeFrame = 0;
	prevImg = frogU1;
	// frog initialization
	frog.x = 110;frog.y = 145;frog.dx = 3;frog.dy = 6;
	frog.imgU1 = frogU1;frog.imgU2 = frogU2;frog.imgU3 = frogU3;
	frog.imgD1 = frogD1;frog.imgD2 = frogD2;frog.imgD3 = frogD3;
	frog.imgL1 = frogL1;frog.imgL2 = frogL2;frog.imgL3 = frogL3;
	frog.imgR1 = frogR1;frog.imgR2 = frogR2;frog.imgR3 = frogR3;
	// snakes initialization
	int xOffset = 0;
	for (int i = 0; i < numOfSnakes; i++) {
		snakes[i].x = 200 - xOffset; snakes[i].y = 115; snakes[i].dx = 1;
		snakes[i].img1 = snake1;snakes[i].img2 = snake2;snakes[i].img3 = snake3;
		snakes[i].img4 = snake4;snakes[i].img5 = snake5;
		xOffset += 80; // space between two snakes
	}
	// cars initialization
	xOffset = 0;
	for (int i = 0; i < numOfCars; i++) {
		cars[i].x = 200 - xOffset; cars[i].y = 95; cars[i].dx = 4;
		cars[i].img = car;
		xOffset += 60; // space between two cars
	}
	// crocodiles initialization
	xOffset = 0;
	for (int i = 0; i < numOfCrocodiles; i++) {
		crocodiles[i].x = 200 - xOffset; crocodiles[i].y = 55; crocodiles[i].dx = 1;
		crocodiles[i].img = crocodile;
		xOffset += 120; // space between two cars
	}
	// woods initialization
	xOffset = 0;
	for (int i = 0; i < numOfWoods; i++) {
		woods[i].x = 10 + xOffset; woods[i].y = 35; woods[i].dx = 3;
		woods[i].img = wood;
		xOffset += 80; // space between two cars
	}
}
