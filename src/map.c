#include <ncurses.h>
#include <stdlib.h>

#include "cboy.h"
#include "map.h"

static void
init_building(bool if_random, int count,
	      const char building[][MAX_X+1], int len, int height) {
	int x_0, y_0;
	int tries;

	if (if_random)
		count += rand() % 2;
	for (int num = 0; num < count; num++) {
		if (height >= MAX_Y)
			do {
				x_0 = rand() % MAX_X;
				y_0 = 0;
				tries++;
				if (tries > 10000)
					return;
			} while (x_0 < 17 || x_0+len > MAX_X);
		else
			do {
				x_0 = rand() % MAX_X;
				y_0 = rand() % MAX_Y;
				tries++;
				if (tries > 10000)
					return;
			} while (!is_floor_range(x_0-2, y_0-2, len+2, height+2));
		for (int i = 0; i < len; i++)
			for (int j = 0; j < height; j++)
				if (building[j][i] != ' ')
					set_map(i+x_0, j+y_0, building[j][i]);
	}
}

static void init_barrels(int count, char face) {
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
		set_map(x_0, y_0, face);

		barrelqty = rand()%8;
		for (int j = 0; j < barrelqty; j++) {
			barrelpos = rand()%8;
			switch (barrelpos) {
			case 0: set_map(x_0+1, y_0, face); break;
			case 1: set_map(x_0, y_0+1, face); break;
			case 2: set_map(x_0+1, y_0+1, face); break;
			case 3: set_map(x_0-1, y_0, face); break;
			case 4: set_map(x_0, y_0-1, face); break;
			case 5: set_map(x_0-1, y_0-1, face); break;
			case 6: set_map(x_0+1, y_0-1, face); break;
			case 7: set_map(x_0-1, y_0+1, face); break;
			}
		}
	}
}

/* init_map: assign values to maprand to determine if character displayed there
 * should be a different char */
void init_map(void) {
	int num;
	int rivernum = rand() % 2;
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++)
			worldMap[j][i] = mapstart[j][i];
	switch (rivernum) {
		case 0: init_building(false, 1, river0,  24, 25); break;
		case 1: init_building(false, 1, river1,  24, 25); break;
	}
	init_building(false, 1, saloon, 10, 8);
	init_building(false, 1, jail,   12, 7);
	init_building(false, 1, bank,   14, 5);
	init_building(true,  2, house,   9, 6);
	init_building(true,  0, grave,  14, 6);
	init_building(true,  0, lake0,  10, 6);
	init_building(true,  1, well,   3,  3);
	init_barrels(6, '0');
	for (int i = 0; i < MAX_X; i++)
		for (int j = 0; j < MAX_Y; j++) {
			if ((num = rand() % 50) == 0)
				maprand[j][i] = 1;
			else
				maprand[j][i] = 0;
		}
	mapnum++;
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
		case 's': return false;
		case 'b': return false;
		case 'y': return false;
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
				mvaddch(j, i, '#' + COLOR_PAIR(14));
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
			else if (worldMap[j][i] == 's')
				mvaddch(j, i, '0' + GREY);
			else if (worldMap[j][i] == 'b')
				mvaddch(j, i, '=' + GREY);
			else if (worldMap[j][i] == 'y')
				mvaddch(j, i, '+' + GREY);
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
				attron(COLOR_PAIR(14));
				mvaddch(j, i,
					(maprand[j][i] == 0)
					? ACS_BULLET : ':');
				attroff(COLOR_PAIR(14));
			} else if (worldMap[j][i] == '~')
				mvaddch(j, i, '~' + WATER);
			else if (worldMap[j][i] == 'h')
				mvaddch(j, i, 'h' + BROWN);
			else if (worldMap[j][i] == '-')
				mvaddch(j, i, '-' + BROWN);
}

