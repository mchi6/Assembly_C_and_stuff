#include "gba.h"

// structs of the player and enermies
typedef struct {
	int x;
	int y;
	int v;
	int size;
	u16 color; 
} avatar;

avatar player = {0, 74, 2, 10, RED};
avatar enemy1 = {39, 19, 5, 5, BLACK};
avatar enemy2 = {69, 129, -10, 5, BLACK};
avatar enemy3 = {99, 19, 5, 5, BLACK};
avatar enemy4 = {129, 129, -10, 5, BLACK};
avatar enemy5 = {159, 19, 5, 5, BLACK};
avatar enemy6 = {189, 129, -10, 5, BLACK};

int upper_bound = 54;
int lower_bound = 104;
int left_bound = 0;
int right_bound = 239;
int danger_upper_bound = 19;
int danger_lower_bound = 139;
int danger_left_bound = 29;
int danger_right_bound = 209;

int game_over = 0;
int start_game = 0;
int prev_x;
int prev_y;

// function prototypes
void showFirstPage();
void gameInit();
void play();
static void movePlayer();
static void moveEnemies();
static int collision();
static void defineBoundaries();


void showFirstPage(){
	drawString(45, 50, "The WORLD'S HARDEST GAME" , WHITE);
	drawString(70, 130, "<ENTER> TO START" , WHITE);
	if (KEY_DOWN_NOW(KEY_START)) {
		start_game = 1;
	}
}

void gameInit() {
	// the background is in blue
	drawRect(0, 0, 240, 160, BLUE);
	// the entry and exit are in yellow 
	drawRect(left_bound, upper_bound, danger_left_bound + 1, 160 - 2 * (upper_bound + 1), YELLOW);
	drawRect(danger_right_bound, upper_bound, danger_left_bound + 1, 160 - 2 * (upper_bound + 1), YELLOW);
	// the dangerous zoon is in MAG
	drawRect(danger_left_bound, danger_upper_bound, 240 - 2 * (danger_left_bound + 1), 160 - 2 * (danger_upper_bound + 1), YELLOW);
	// set up the player and enemies
	player.x = 0;
	player.y = 74;
	player.v = 5;
	enemy1.x = 39;
	enemy1.y = 19;
	enemy1.v = -3;
	enemy2.x = 69;
	enemy2.y = 129;
	enemy2.v = 5;
	enemy3.x = 99;
	enemy3.y = 19;
	enemy3.v = -3;
	enemy4.x = 129;
	enemy4.y = 129;
	enemy4.v = 5;
	enemy5.x = 159; 
	enemy5.y = 19;
	enemy5.v = -3;
	enemy6.x = 189;
	enemy6.y = 129;
	enemy6.v = 5;
	drawRect(player.x, player.y, player.size, player.size, player.color);
	drawRect(enemy1.x, enemy1.y, enemy1.size, enemy1.size, enemy1.color);
	drawRect(enemy2.x, enemy2.y, enemy2.size, enemy2.size, enemy2.color);
	drawRect(enemy3.x, enemy3.y, enemy3.size, enemy3.size, enemy3.color);
	drawRect(enemy4.x, enemy4.y, enemy4.size, enemy4.size, enemy4.color);
	drawRect(enemy5.x, enemy5.y, enemy5.size, enemy5.size, enemy5.color);
	drawRect(enemy6.x, enemy6.y, enemy6.size, enemy6.size, enemy6.color);
	game_over = 0;
	waitSync();
}


void play() {

	drawRect(player.x, player.y, player.size, player.size, YELLOW);
	drawRect(enemy1.x, enemy1.y, enemy1.size, enemy1.size, YELLOW);
	drawRect(enemy2.x, enemy2.y, enemy2.size, enemy2.size, YELLOW);
	drawRect(enemy3.x, enemy3.y, enemy3.size, enemy3.size, YELLOW);
	drawRect(enemy4.x, enemy4.y, enemy4.size, enemy4.size, YELLOW);
	drawRect(enemy5.x, enemy5.y, enemy5.size, enemy5.size, YELLOW);
	drawRect(enemy6.x, enemy6.y, enemy6.size, enemy6.size, YELLOW);

	prev_x = player.x;
	prev_y = player.y;
	// move player
	movePlayer();

	// draw objects within boundaries
	defineBoundaries();
	drawRect(player.x, player.y, player.size, player.size, player.color);

	// move enemies	
	moveEnemies();

	//collesion detection
	if (collision() == 1) {
		game_over = 1;
	}

	// check if the game is over or not
	if (game_over == 0) {
		drawString(20, 150, "IN PROGRESS. . ." , WHITE);
	} else {
		drawString(20, 150, "IN PROGRESS. . ." , BLUE);
		drawString(20, 150, "GAME OVER!    <ENTER> TO RESTART" , WHITE);
		if (KEY_DOWN_NOW(KEY_START)) {
			gameInit();
		} else {
			player.v = 0;
			enemy1.v = 0;
			enemy2.v = 0;
			enemy3.v = 0;
			enemy4.v = 0;
			enemy5.v = 0;
			enemy6.v = 0;
		}
	}

	// check if the player wins
	if (player.x >= danger_right_bound) {
		drawString(20, 150, "IN PROGRESS. . ." , BLUE);
		drawString(20, 150, "YOU WIN!      <ENTER> TO RESTART" , WHITE);
		if (KEY_DOWN_NOW(KEY_START)) {
			gameInit();
		} else {
			player.v = 0;
			enemy1.v = 0;
			enemy2.v = 0;
			enemy3.v = 0;
			enemy4.v = 0;
			enemy5.v = 0;
			enemy6.v = 0;
		}
	}
	waitSync();
	delay(1);
}


static int collision() {

	if ((player.x <= enemy1.x && player.x + player.size >= enemy1.x && 
		 	player.y <= enemy1.y && player.y + player.size >= enemy1.y) ||
		(player.x <= enemy1.x && player.x + player.size >= enemy1.x && 
			player.y <= enemy1.y + enemy1.size && player.y + player.size >= enemy1.y + enemy1.size) ||
		(player.x <= enemy1.x + enemy1.size && player.x + player.size >= enemy1.x + enemy1.size && 
			player.y <= enemy1.y && player.y + player.size >= enemy1.y) ||
		(player.x <= enemy1.x + enemy1.size && player.x + player.size >= enemy1.x + enemy1.size && 
			player.y <= enemy1.y + enemy1.size && player.y + player.size >= enemy1.y + enemy1.size) ||

		(player.x <= enemy2.x && player.x + player.size >= enemy2.x && 
		 	player.y <= enemy2.y && player.y + player.size >= enemy2.y) ||
		(player.x <= enemy2.x && player.x + player.size >= enemy2.x && 
			player.y <= enemy2.y + enemy2.size && player.y + player.size >= enemy2.y + enemy2.size) ||
		(player.x <= enemy2.x + enemy2.size && player.x + player.size >= enemy2.x + enemy2.size && 
			player.y <= enemy2.y && player.y + player.size >= enemy2.y) ||
		(player.x <= enemy2.x + enemy2.size && player.x + player.size >= enemy2.x + enemy2.size && 
			player.y <= enemy2.y + enemy2.size && player.y + player.size >= enemy2.y + enemy2.size) ||

		(player.x <= enemy3.x && player.x + player.size >= enemy3.x && 
		 	player.y <= enemy3.y && player.y + player.size >= enemy3.y) ||
		(player.x <= enemy3.x && player.x + player.size >= enemy3.x && 
			player.y <= enemy3.y + enemy3.size && player.y + player.size >= enemy3.y + enemy3.size) ||
		(player.x <= enemy3.x + enemy3.size && player.x + player.size >= enemy3.x + enemy3.size && 
			player.y <= enemy3.y && player.y + player.size >= enemy3.y) ||
		(player.x <= enemy3.x + enemy3.size && player.x + player.size >= enemy3.x + enemy3.size && 
			player.y <= enemy3.y + enemy3.size && player.y + player.size >= enemy3.y + enemy3.size) ||

		(player.x <= enemy4.x && player.x + player.size >= enemy4.x && 
		 	player.y <= enemy4.y && player.y + player.size >= enemy4.y) ||
		(player.x <= enemy4.x && player.x + player.size >= enemy4.x && 
			player.y <= enemy4.y + enemy4.size && player.y + player.size >= enemy4.y + enemy4.size) ||
		(player.x <= enemy4.x + enemy4.size && player.x + player.size >= enemy4.x + enemy4.size && 
			player.y <= enemy4.y && player.y + player.size >= enemy4.y) ||
		(player.x <= enemy4.x + enemy4.size && player.x + player.size >= enemy4.x + enemy4.size && 
			player.y <= enemy4.y + enemy4.size && player.y + player.size >= enemy4.y + enemy4.size) ||

		(player.x <= enemy5.x && player.x + player.size >= enemy5.x && 
		 	player.y <= enemy5.y && player.y + player.size >= enemy5.y) ||
		(player.x <= enemy5.x && player.x + player.size >= enemy5.x && 
			player.y <= enemy5.y + enemy5.size && player.y + player.size >= enemy5.y + enemy5.size) ||
		(player.x <= enemy5.x + enemy5.size && player.x + player.size >= enemy5.x + enemy5.size && 
			player.y <= enemy5.y && player.y + player.size >= enemy5.y) ||
		(player.x <= enemy5.x + enemy5.size && player.x + player.size >= enemy5.x + enemy5.size && 
			player.y <= enemy5.y + enemy5.size && player.y + player.size >= enemy5.y + enemy5.size) ||

		(player.x <= enemy6.x && player.x + player.size >= enemy6.x && 
		 	player.y <= enemy6.y && player.y + player.size >= enemy6.y) ||
		(player.x <= enemy6.x && player.x + player.size >= enemy6.x && 
			player.y <= enemy6.y + enemy6.size && player.y + player.size >= enemy6.y + enemy6.size) ||
		(player.x <= enemy6.x + enemy6.size && player.x + player.size >= enemy6.x + enemy6.size && 
			player.y <= enemy6.y && player.y + player.size >= enemy6.y) ||
		(player.x <= enemy6.x + enemy6.size && player.x + player.size >= enemy6.x + enemy6.size && 
			player.y <= enemy6.y + enemy6.size && player.y + player.size >= enemy6.y + enemy6.size)) {
			
			return 1; 
		} else {
			return 0;
		}
}

static void movePlayer() {

	if(KEY_DOWN_NOW(KEY_UP)) {
		player.y -= player.v;
	}
	if(KEY_DOWN_NOW(KEY_DOWN)) {
		player.y += player.v;
	}
	if(KEY_DOWN_NOW(KEY_LEFT)) {
		player.x -= player.v;
	}
	if(KEY_DOWN_NOW(KEY_RIGHT)) {
		player.x += player.v;
	}

}

static void moveEnemies() {

	if (enemy1.y + enemy1.size + 1 >= danger_lower_bound || enemy1.y <= danger_upper_bound) {
		enemy1.v = -enemy1.v;
	}
	enemy1.y += enemy1.v;
	drawRect(enemy1.x, enemy1.y, enemy1.size, enemy1.size, enemy1.color);

	if (enemy2.y + enemy2.size + 1 >= danger_lower_bound || enemy2.y <= danger_upper_bound) {
		enemy2.v = -enemy2.v;
	}
	enemy2.y += enemy2.v;
	drawRect(enemy2.x, enemy2.y, enemy2.size, enemy2.size, enemy2.color);

	if (enemy3.y + enemy3.size + 1 >= danger_lower_bound || enemy3.y <= danger_upper_bound) {
		enemy3.v = -enemy3.v;
	}
	enemy3.y += enemy3.v;
	drawRect(enemy3.x, enemy3.y, enemy3.size, enemy3.size, enemy3.color);

	if (enemy4.y + enemy4.size + 1 >= danger_lower_bound || enemy4.y <= danger_upper_bound) {
		enemy4.v = -enemy4.v;
	}
	enemy4.y += enemy4.v;
	drawRect(enemy4.x, enemy4.y, enemy4.size, enemy4.size, enemy4.color);

	if (enemy5.y + enemy5.size + 1 >= danger_lower_bound || enemy5.y <= danger_upper_bound) {
		enemy5.v = -enemy5.v;
	}
	enemy5.y += enemy5.v;
	drawRect(enemy5.x, enemy5.y, enemy5.size, enemy5.size, enemy5.color);

	if (enemy6.y + enemy6.size + 1 >= danger_lower_bound || enemy6.y <= danger_upper_bound) {
		enemy6.v = -enemy6.v;
	}
	enemy6.y += enemy6.v;
	drawRect(enemy6.x, enemy6.y, enemy6.size, enemy6.size, enemy6.color);
}

static void defineBoundaries() {
	if(player.x < left_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}
	if(player.x < danger_left_bound && player.y < upper_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}
	if(player.x < danger_left_bound && player.y + player.size > lower_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}

	if(player.x + player.size > right_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}
	if(player.x + player.size > danger_right_bound && player.y > lower_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}

	if(player.x + player.size > danger_right_bound && player.y < upper_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}


	if(player.x + player.size > danger_right_bound && player.y + player.size > lower_bound) {
		player.x = prev_x;
		player.y = prev_y;
	}
	if(player.x > danger_left_bound && player.x + player.size < danger_right_bound) {
		if(player.y < danger_upper_bound) {
			player.x = prev_x;
			player.y = prev_y;
		}
		if(player.y + player.size > danger_lower_bound) {
			player.x = prev_x;
			player.y = prev_y;
		}
	}
	if((player.x < danger_left_bound && player.y < upper_bound) ||
	   (player.x < danger_left_bound && player.y + player.size > lower_bound)) {
		player.x = prev_x;
		player.y = prev_y;
	}
	if((player.x + player.size > danger_right_bound && player.y < upper_bound) ||
	   (player.x + player.size > danger_right_bound && player.y + player.size > lower_bound)) {
		player.x = prev_x;
		player.y = prev_y;
	}
}
