#include <stdio.h>
#include <stdlib.h>
#include "gba.h"
#include "titleScreen.h"
#include "gameOverScreen.h"
#include "notebook.h"


#define numOfStairs 6

typedef struct {
	int x;
	int y;
	int dx;
	int dy;
	int a; //acceleration
	int size;
	int color;
} AVATAR;

typedef struct {
	int x;
	int y;
	int dy;
	int width;
	int height;
	u16 color;
} STAIR;

// function prototypes
void startGame();
void gameOver();
void init();
void play();
static void drawPlayer();
static void hidePlayerTraces();
static void drawStairs();
static void collisionDetection();
static void gameOverDetection();
static void moveAllStairs(int y1, int y2);

//initialization
int gameStatus = 0;
int prev_x;
int prev_y;
int prev_touch_index = numOfStairs-1;
int score = 0;

AVATAR player;
STAIR stairs[numOfStairs];


void startGame() {
	drawImage3(0, 0, 240, 160, titleScreen);
	drawString(95, 140, "<ENTER> TO START", RED);
}

void gameOver() {
	if (gameStatus == 2) {
		drawImage3(0, 0, 240, 160, gameOverScreen);
		gameStatus = 3;
	}	
	drawString(90, 40, "GAME OVER", RED);
	char scoreStr[15];
	sprintf(scoreStr, "%d", score);
	drawString(80, 110, "YOUR SCORE", BLUE);
	drawString(105, 125, scoreStr, BLUE);
}

void init() {
	drawImage3(0, 0, 240, 160, titleScreen);
	drawImage3(10, 10, 220, 140, notebook);
	player.x = 100;
	player.y = 110;
	player.dx = 5;
	player.dy = 0;
	player.a = 1;
	player.size = 10;
	player.color = RED;
	for (int n = 0; n < numOfStairs; n++) {
		stairs[n].x = 15 + rand() % 155;
		stairs[n].y = (n + 1) * 24;
		stairs[n].dy = 30;
		stairs[n].width = 30;
		stairs[n].height = 5;
		stairs[n].color = BLUE;
	}
	stairs[numOfStairs-1].x = 80;
	score = 0;
}

void play() {

	char scoreStr[15];
	sprintf(scoreStr, "%d", score);
	drawString(0, 2, "SCORE:", BLACK);

	prev_x = player.x;
	prev_y = player.y;

	// boarder protection
	if (player.y <= 10) {
		player.y = 10;
		player.dy = -player.dy;
	}
	if (player.x <= 10) {
		player.x = 220;
	}

	// hide moving traces (very important)
	hidePlayerTraces();
	drawString(50, 2, scoreStr, BLACK);
	
	// move and draw the player
	drawPlayer();
	// detect colliction between the player and the stairs
	drawStairs();
	//moveAllStairs();
	collisionDetection();
	
	// wait for vblank	
	waitSync();
	delay(1);
	// update score
	drawString(50, 2, scoreStr, WHITE);
	// game over detection
	gameOverDetection();
	
}

static void drawPlayer() {
	if (KEY_DOWN_NOW(KEY_LEFT)) {
		player.x -= player.dx;
	} else if (KEY_DOWN_NOW(KEY_RIGHT)) {
		player.x += player.dx;
	}
	if (player.dy <= 5) {
		player.dy = player.dy + player.a;
		player.y = player.y + player.dy;
	} else {
		player.y = player.y + player.dy;
	}
	drawRect(player.x, player.y, player.size, player.size, player.color);
}

static void hidePlayerTraces() {
	
	for (int c = prev_x; c <= prev_x + player.size; c++) {
		for (int r = prev_y; r <= prev_y + player.size; r++) {
			videoBuffer[OFFSET(c, r, 240)] = notebook[OFFSET(c-10, r-10, 220)];
		}
	}
}

static void collisionDetection() {

	for (int n = 0; n < numOfStairs; n++) {
		if (player.x + player.size >= stairs[n].x && player.x <= stairs[n].x + stairs[n].width && 
			abs(player.y + player.size - stairs[n].y) >= 0 && 
			abs(player.y + player.size - stairs[n].y) <= 3) {
			player.dy = -10;
			if (n != prev_touch_index && stairs[n].y < stairs[prev_touch_index].y) {
				moveAllStairs(stairs[n].y, stairs[prev_touch_index].y);
				prev_touch_index = n;
				score += 64;
			}
			break;
		}
	}
}

static void gameOverDetection() {
	if (player.y  + player.size >= 150) {
		gameStatus = 2;
	}
}

static void drawStairs() {
	for (int n = 0; n < numOfStairs; n++) {
		drawRect(stairs[n].x, stairs[n].y, stairs[n].width, stairs[n].height, stairs[n].color);
	}
}

static void moveAllStairs(int y1, int y2) {
	int arr[numOfStairs];
	int numOfElements = 0;
	int min = 150;

	for (int n = 0; n < numOfStairs; n++) {
		for (int c = stairs[n].x; c <= stairs[n].x + stairs[n].width; c++) {
			for (int r = stairs[n].y; r <= stairs[n].y + stairs[n].height; r++) {
				videoBuffer[OFFSET(c, r, 240)] = notebook[OFFSET(c-10, r-10, 220)];
			}
		}
		stairs[n].y += y2-y1;
		if (stairs[n].y < min) {
			min = stairs[n].y;
		}
		if (stairs[n].y + stairs[n].height >= 150) {
			arr[numOfElements] = n;
			numOfElements++;
		}
	}
	int level = min;

	if (numOfElements >= 1) {
		for (int i = 0; i < numOfElements; i++) {
			stairs[arr[i]].x = 15 + rand() % 155;
			stairs[arr[i]].y = level - 24;
			level -= 24;
		}
	}
}
