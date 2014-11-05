#include "gba.h"

volatile u32* KEYS = (volatile u32*)0x04000130;
extern int start_game; //0: stop 1: initialize 2: play


void gameInit();
void play();
void showFirstPage();

int main() {
	// this game is in mode 3
	setMode(MODE_3 | BG2_ENABLE);

	while (1) {
		if (start_game == 0) {
			showFirstPage(); // show the front page of the game
			
		}
		if (start_game == 1) {	
			gameInit(); // initialize the game
			start_game = 2;
		}
		if (start_game == 2) {
			play();
		}
	}
	while (1);

	return 0;
}
