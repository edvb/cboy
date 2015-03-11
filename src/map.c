#include <ncurses.h>
#include <stdlib.h>

#include "cboy.h"

static char worldMap[MAX_Y][MAX_X+1] = {
"gggggggggggggggggggggggggggggggg~~~~~~~~gggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggggg~~~~~~~~gggggggggggggggggggggXXXXXXXXXXXXXXggggg",
"ggggXXXXXXXXXXXXggggggggggggggggg~~~~~~~~ggggggXXXXXXXXXXggggX............Xggggg",
"ggggX..........Xggggggggggggggggg~~~~~~~~ggggggX........XggggX............Xggggg",
"ggggX..........Xggggggggggggggggg~~~~~~~~ggggggX=======+XggggX............Xggggg",
"ggggX..........Xggggggggggggggggg~~~~~~~~ggggggX..h.h.h.XggggXXXX+XXXXXXXXXggggg",
"ggggXXXXXXXXX+XXgggggggggggggggg~~~~~~~~~ggggggXh.......Xgggg..............ggggg",
"ggggggggggggggggggggggggggggggg~~~~~~~~~gggggggXo.......XggggX............Xggggg",
"ggggggggggggggggggggggggggggggg~~~~~~~~ggggggggXh.....hoXggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggg~~~~~~~~~ggggggggXXX+XXXXXXggggggggggggggggggggggg",
"gggggggggggggggggggggggggggggg~~~~~~~~~ggggggggggggggggggggggggggggggggggggggggg",
"ggggggggggggggggggggggggggggXXXXXXXXXXXggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggXX.........XXgggggggggggggggggggggggggggggggggggggggg",
"ggggggggggggggggggggggggggg.............gggggggggggggggggggggggggggggggggggggggg",
"ggggggggggggggggggggggggggg.XXXXXXXXXXX.gggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggXX~~~~~~~ggXXgggggggggggggggggggggggggggggggggggggggg",
"ggggggggggggggggggggggggggggg~~~~~~~gggggggggggggggggggggggggggggggggggggggggggg",
"ggggggggggggggggggggggggggggg~~~~~~~gggggggg~~gggggggggggggggggggggggggggggggggg",
"#gggggggggggggggggggggggggggg~~~~~~~~gggggg~~~~~gggggggggggggggggggggggggggggggg",
"###gggggggggggggggggggggggggg~~~~~~~~~~gggg~~~~~~~gggggggggggggggggggggggggggggg",
"######gggggggggggggggggggggggg~~~~~~~~~~~~~~~~~~~~gggggggggggggggggggggggggggggg",
"###########ggggggggggggggggggg~~~~~~~~gg~~~~~~~~~~~ggggggggggggggggggggggggggggg",
"###############ggggggggggggggg~~~~~~~~~gggggg~~~~~gggggggggggggggggggggggggggggg",
"################gggggggggggggg~~~~~~~~~ggggggggggggggggggggggggggggggggggggggggg",
};

static int maprand[MAX_Y][MAX_X+1];

static void init_wells(int count) {
	int x_0, y_0;

	if (rand() % 2 == 0)
		count += rand() % 2;
	for (int i = 0; i <= count; i++) {
		do {
			x_0 = rand() % MAX_X;
			y_0 = rand() % MAX_Y;
		} while (!is_floor_range(x_0, y_0, 8, 8));
		/* TODO: Make this a for loop and 2D array */
		set_map(x_0+1, y_0+1, '~');
		set_map(x_0+1, y_0, '#');
		set_map(x_0, y_0+1, '#');
		set_map(x_0+2, y_0+1, '#');
		set_map(x_0+1, y_0+2, '#');
	}
}

static void init_barrels(int count) {
	int x_0, y_0;
	int barrelqty;
	int barrelpos;

	if (rand() % 2 == 0)
		count += rand() % 5;
	else
		count -= rand() % 2;
	for (int i = 0; i <= count; i++) {
		do {
			x_0 = rand() % MAX_X;
			y_0 = rand() % MAX_Y;
		} while (!is_floor_range(x_0-1, y_0-1, 3, 3));
		set_map(x_0, y_0, '0');

		barrelqty = rand()%8;
		for (int j = 0; j < barrelqty; j++) {
			barrelpos = rand()%8;
			switch (barrelpos) {
			case 0: set_map(x_0+1, y_0, '0'); break;
			case 1: set_map(x_0, y_0+1, '0'); break;
			case 2: set_map(x_0+1, y_0+1, '0'); break;
			case 3: set_map(x_0-1, y_0, '0'); break;
			case 4: set_map(x_0, y_0-1, '0'); break;
			case 5: set_map(x_0-1, y_0-1, '0'); break;
			case 6: set_map(x_0+1, y_0-1, '0'); break;
			case 7: set_map(x_0-1, y_0+1, '0'); break;
			}
		}
	}
}

/* init_map: assign values to maprand to determine if character displayed there
 * should be a different char */
void init_map(void) {
	int num;
	init_wells(0);
	init_barrels(4);
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++) {
			if ((num = rand() % 50) == 0)
				maprand[j][i] = 1;
			else
				maprand[j][i] = 0;
		}
}

/* get_map: get character of map at x and y position */
char get_map(int x, int y) {
	return worldMap[y][x];
}

/* set_map: set character of map at x and y position to newch */
void set_map(int x, int y, char newch) {
	worldMap[y][x] = newch;
}

bool is_floor(int x, int y) {
	switch (get_map(x, y)) {
		case '#': return false;
		case 'X': return false;
		case '=': return false;
		case '~': return false;
		case '+': return false;
		case 'o': return false;
		case '0': return false;
		default: return true;
	}
}

bool is_floor_range(int x, int y, int dx, int dy) {
	for (int i = x; i <= dx+x; i++)
		for (int j = y; j <= dy+y; j++)
			if (get_map(i, j) != 'g')
				return false;
	return true;
}

int floor_count(char ch) {
	int count;
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			/* TODO: Incorporate smart is_floor intergration */
			if (get_map(i, j) == ch)
				count++;
	return count;
}

/* TODO: Incorporate entity direction */
/* toggle_door: open or close door next to entity */
void toggle_door(int x, int y) {
	if (get_map(x-1, y) == '+') set_map(x-1, y, '-');
	else if (get_map(x+1, y) == '+') set_map(x+1, y, '-');
	else if (get_map(x, y-1) == '+') set_map(x, y-1, '-');
	else if (get_map(x, y+1) == '+') set_map(x, y+1, '-');
	else if (get_map(x-1, y) == '-') set_map(x-1, y, '+');
	else if (get_map(x+1, y) == '-') set_map(x+1, y, '+');
	else if (get_map(x, y-1) == '-') set_map(x, y-1, '+');
	else if (get_map(x, y+1) == '-') set_map(x, y+1, '+');
	for (int i = 0; i <= playerqty; i++)
		draw_map_floor(player[i], 10);
}

/* TODO: Use get_map function */
/* draw_map: draw the map foreground (stuff that is on top of entities) */
void draw_map(Ent e, int r) {
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			if (worldMap[j][i] == '#')
				mvaddch(j, i, '#' + COLOR_PAIR(12));
			else if (worldMap[j][i] == 'X')
				mvaddch(j, i, 'X' + COLOR_PAIR(13));
			else if (worldMap[j][i] == '=')
				mvaddch(j, i, '=' + COLOR_PAIR(13));
			else if (worldMap[j][i] == '+')
				mvaddch(j, i, '+' + COLOR_PAIR(13));
			else if (worldMap[j][i] == 'o')
				mvaddch(j, i, 'o' + BROWN);
			else if (worldMap[j][i] == '0')
				mvaddch(j, i, '0' + BROWN);
}

/* draw_map: draw the map background (stuff that is below entities) */
void draw_map_floor(Ent e, int r) {
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			if (worldMap[j][i] == ' ')
				mvaddch(j, i, worldMap[j][i]);
			else if (worldMap[j][i] == '.') {
				attron(COLOR_PAIR(5));
				mvaddch(j, i,
					(maprand[j][i] == 0)
					? ACS_BULLET : ':');
				attroff(COLOR_PAIR(5));
			} else if (worldMap[j][i] == 'g') {
				attron(YELLOW);
				mvaddch(j, i,
					(maprand[j][i] == 0)
					? ACS_BULLET : ':');
				attroff(YELLOW);
			} else if (worldMap[j][i] == '~')
				mvaddch(j, i, '~' + WATER);
			else if (worldMap[j][i] == 'h')
				mvaddch(j, i, 'h' + BROWN);
			else if (worldMap[j][i] == '-')
				mvaddch(j, i, '-' + BROWN);
}

