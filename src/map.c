#include <ncurses.h>
#include <stdlib.h>

#include "cboy.h"

static char worldMap[MAX_Y][MAX_X+1] = {
"ggggggggggggggggggggggggggggggggwwwwwwwwgggggggggggggggggggggggggggggggggggggggg",
"ggggggggggggggggggggggggggggggggwwwwwwwwgggggggggggggggggggggXXXXXXXXXXXXXXggggg",
"ggggXXXXXXXXXXXXgggggg00gggggggggwwwwwwwwggggggXXXXXXXXXXggggX............Xggggg",
"ggggX..........Xgggggg0ggggggggggwwwwwwwwggggggX........XggggX............Xggggg",
"ggggX..........XgggggggggggggggggwwwwwwwwggggggXXXXXXXX+XggggX............Xggggg",
"ggggX..........XgggggggggggggggggwwwwwwwwggggggX..h.h.h.XggggXXXX+XXXXXXXXXggggg",
"ggggXXXXXXXXX+XXggggggggggggggggwwwwwwwwwggggggXh.......Xgggg..............ggggg",
"gggggggggggggggggggg0ggggggggggwwwwwwwwwgggggggXo.......XggggX............Xggggg",
"ggggggggggggggggggg00ggggggggggwwwwwwwwggggggggXh.....hoXggggggggggggggggggggggg",
"ggggggggggggggggggggggggggggggwwwwwwwwwggggggggXXX+XXXXXXggggggggggggggggggggggg",
"ggggggggggggggggggggggggggggggwwwwwwwwwggggggggggggggggggggggggggggggggggggggggg",
"ggggggg0ggg0ggggggggggggggggXXXXXXXXXXXggggggggggggggggggggggggggggggggggggggggg",
"gggggggggggggggggggggggggggXX.........XXgggggggggggggggggggggggggggggggggggggggg",
"gggg0ggggggggg0gggggggggggg.............gggggggggggggggggggggggggggggggg#ggggggg",
"ggggggggggggggggggggggggggg.XXXXXXXXXXX.ggggggggggggggggggggggggggggggg#w#gggggg",
"ggggggg0ggg0gggggggggggggggXXwwwwwwwggXXgggggggggggggggggggggggggggggggg#ggggggg",
"gggggggggggggggggggggggggggggwwwwwwwgggggggggggggggg0ggggggggggggggggggggggggggg",
"gggggggggggggg0ggggggggggggggwwwwwwwggggggggwwggggggggggg0gggggggg00gggggggggggg",
"#ggggggggggggg00gggggggggggggwwwwwwwwggggggwwwwwgggggggg000ggggggggggggggggggggg",
"###ggggggggggggggggg0ggggggggwwwwwwwwwwggggwwwwwwwgggggg00gggg0ggggggggggggggggg",
"######ggggggggggggg00gggggggggwwwwwwwwwwwwwwwwwwwwgggggggggggg0gggg00ggggggggggg",
"###########gggggggggggggggggggwwwwwwwwggwwwwwwwwwwwggg0gggggggggggggggggg0gggggg",
"###############gggggggggggggggwwwwwwwwwggggggwwwwwggggggggggggggggggggggg0gggggg",
"################ggggggggggggggwwwwwwwwwggggggggggggggggggggggggggggggggggggggggg",
};

static int maprand[MAX_Y][MAX_X+1];

/* init_map: asign values to maprand to determine if character displayed there
 * should be a different char */
void init_map(void) {
	int num;
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
		case 'w': return false;
		case '+': return false;
		case 'o': return false;
		case '0': return false;
		default: return true;
	}
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
				attron(GRASS);
				mvaddch(j, i,
					(maprand[j][i] == 0)
					? ACS_BULLET : '*');
				attroff(GRASS);
			} else if (worldMap[j][i] == 'w')
				mvaddch(j, i, '~' + WATER);
			else if (worldMap[j][i] == 'h')
				mvaddch(j, i, 'h' + BROWN);
			else if (worldMap[j][i] == '-')
				mvaddch(j, i, '-' + BROWN);
}

