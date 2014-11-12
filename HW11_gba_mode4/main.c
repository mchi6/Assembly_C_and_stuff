#include "gba.h"
#include "startScreen.h"
#include "gameOverScreen.h"

volatile u32* KEYS = (volatile u32*)0x04000130;
extern int gameStatus; // 0--welcome; 1--play; 2--game over (win or lose)

// function prototypes
void startGame();
void gameOver();
void play();
void init();

int main() {
	setMode(MODE_4 | BG2_ENABLE);
	startGame();

	while(1) {
		if (KEY_DOWN_NOW(KEY_START) && gameStatus == 0) {			
			gameStatus = 1;
			init();
		}
		if (gameStatus == 1) {
			play();
		}
		if (gameStatus == 2) {
			while (1) {
				if (KEY_DOWN_NOW(KEY_START)) {
					gameStatus = 0;
					break;
				}
			}
		}
	}
	return 0;
}