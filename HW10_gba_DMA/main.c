#include "gba.h"
#include "notebook.h"
#include "titleScreen.h"

volatile u32* KEYS = (volatile u32*)0x04000130;
extern int gameStatus; //0: initialize 1: play 2: end 3: temp

//function prototypes
void startGame();
void gameOver();
void play();
void init();

int main() {
	// this game is in mode 3
	setMode(MODE_3 | BG2_ENABLE);
	gameStatus = 0;
	startGame();
	

	while (1) {
		if (KEY_DOWN_NOW(KEY_START) && gameStatus == 0) {
			gameStatus = 1;
			init();
		}
		if (gameStatus == 1) {			
			play();
		}
		if (gameStatus == 2 || gameStatus == 3) {
			gameOver();
			if (KEY_DOWN_NOW(KEY_START)) {
				delay(10);
				main();
			}
		}
	}
	
}
